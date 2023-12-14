#include "hcsr04.h"

HCSR04::HCSR04(DigitalOut triggerPin, DigitalIn echoPin) : trigger(triggerPin), echo(echoPin) {

}

float HCSR04::distancia() {
    trigger = 1;        // Envía un pulso de 10us para activar el sensor
    wait_us(10);
    trigger = 0;

    while (echo == 0);   // Espera a que el pin de eco se ponga en alto
    Timer temporizadorPulso;
    temporizadorPulso.start();

    while (echo == 1);   // Espera a que el pin de eco se ponga en bajo
    temporizadorPulso.stop();

    // Calcula la distancia utilizando la fórmula: distancia = ancho_del_pulso / 58.0
    return temporizadorPulso.read_us() / 58.0;
}