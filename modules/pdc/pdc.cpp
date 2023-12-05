#include "pdc.h"

#define SENSOR_SAMPLE_FREQUENCY 10ms
#define LED_FREQUENCY 500ms

// Definir pines para el HC-SR04
DigitalOut triggerPin(D2);
DigitalIn echoPin(D3);

// Definir pin para el buzzer
DigitalOut buzzerPin(D4);

// Definir pin para el LED de estado del PDC
DigitalOut pdcStateLed(D1);

// Objeto HC-SR04
HCSR04 sensorProximidad(triggerPin, echoPin);

// Ticker para controlar el sonido del buzzer
Ticker tickerBuzzer;

// Variables para controlar el sonido del buzzer
int tiempoEncendidoApagado = 0;
bool estadoBuzzer = false;
int temporizadorBuzzer = 0;

// Variable de sensor de proximidad
float alpha = 0.5;
float distancia_promedio = 1000;

// Variable para el estado activo/inactivo del PDC
 bool pdcActiveState = false;
 bool pdcLastState = false;

// Variables para el control del LED de estado del PDC
Ticker tickerLED;
bool ledState = false;

// Función para cambiar el estado del LED
void toggleLED()
{
    ledState = !ledState;
    pdcStateLed = ledState;
}

// Función para controlar el sonido del buzzer
void controlBuzzer()
{
    temporizadorBuzzer++;

    if (distancia_promedio < 10.0) {
        // Si la distancia es menor a 10 cm, mantener el buzzer siempre encendido
        buzzerPin = 1;
    } else if (distancia_promedio > 300.0) {
        // Si la distancia es mayor a 300 cm, mantener el buzzer siempre apagado
        buzzerPin = 0;
    } else if (estadoBuzzer && temporizadorBuzzer <= tiempoEncendidoApagado) {
        // Encender el buzzer
        buzzerPin = 1;
    } else if (!estadoBuzzer && temporizadorBuzzer <= tiempoEncendidoApagado) {
        // Apagar el buzzer
        buzzerPin = 0;
    } else {
        // Reiniciar el temporizador y cambiar el estado del buzzer
        temporizadorBuzzer = 0;
        estadoBuzzer = !estadoBuzzer;
    }
        
    
}

// Función de mapeo lineal
float mapeo(float valor, float rangoEntradaMin, float rangoEntradaMax, float rangoSalidaMin, float rangoSalidaMax)
{
    return (valor - rangoEntradaMin) * (rangoSalidaMax - rangoSalidaMin) / (rangoEntradaMax - rangoEntradaMin) + rangoSalidaMin;
}

// Función para inicializar el sensor de proximidad y el buzzer
void pdcInit()
{
    bool pdcActiveState = false;
    bool pdcLastState = false;
}

// Función para actualizar el sensor de proximidad y controlar el sonido del buzzer
void pdcUpdate()
{
    
    if (pdcActiveState) {
        
        // Obtener la distancia desde el sensor de proximidad
        float distancia = sensorProximidad.distancia();
        distancia_promedio = alpha*distancia+(1-alpha)*distancia_promedio; //exponential smoothing

        // Mapear la distancia al rango de tiempo de encendido/apagado del buzzer
        tiempoEncendidoApagado = mapeo(distancia_promedio, 10.0, 300.0, 1.0, 100.0);

        if(!pdcLastState){

            // Configurar el temporizador para controlar el buzzer
            tickerBuzzer.attach(&controlBuzzer, SENSOR_SAMPLE_FREQUENCY);  // Llamar a controlBuzzer cada 10 ms

            tickerLED.attach(&toggleLED, LED_FREQUENCY);  // Iniciar un nuevo ticker con la frecuencia deseada
            
            pdcLastState= true;
        }

    } else if(pdcLastState){
        buzzerPin = 0;
        pdcStateLed = 0;
    
        tickerBuzzer.detach();  // Detener el ticker si el PDC está desactivado
        tickerLED.detach();  // Detener el ticker si el PDC está desactivado
        
        pdcLastState= false;
    }
}
