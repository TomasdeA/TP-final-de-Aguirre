#include "pdc.h"

// Definir pines para el HC-SR04
DigitalOut triggerPin(D2);
DigitalIn echoPin(D3);

// Definir pin para el buzzer
DigitalOut buzzerPin(D4);

// Objeto HC-SR04
HCSR04 sensorProximidad(triggerPin, echoPin);

// Ticker para controlar el sonido del buzzer
Ticker tickerBuzzer;

// Variables para controlar el sonido del buzzer
int tiempoEncendidoApagado = 0;
bool estadoBuzzer = false;
int temporizadorBuzzer = 0;

// Función para controlar el sonido del buzzer
void controlBuzzer()
{
    // Incrementar el temporizador
    temporizadorBuzzer++;

    // Controlar el sonido del buzzer según el temporizador
    if (estadoBuzzer && temporizadorBuzzer <= tiempoEncendidoApagado) {
        buzzerPin = 1;  // Encender el buzzer
    } else if (!estadoBuzzer && temporizadorBuzzer <= tiempoEncendidoApagado) {
        buzzerPin = 0;  // Apagar el buzzer
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
    // Inicializar el sensor aquí, si es necesario

    // Configurar el temporizador para controlar el buzzer
    tickerBuzzer.attach(&controlBuzzer, 10ms);  // Llamar a controlBuzzer cada 1 ms
}

// Función para actualizar el sensor de proximidad y controlar el sonido del buzzer
void pdcUpdate()
{
    // Obtener la distancia desde el sensor de proximidad
    float distancia = sensorProximidad.distance();

    // Mapear la distancia al rango de tiempo de encendido/apagado del buzzer
    tiempoEncendidoApagado = mapeo(distancia, 10.0, 300.0, 10.0, 1000.0); 

    // Agregar lógica adicional si es necesario
}
