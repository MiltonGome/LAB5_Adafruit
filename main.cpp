#include <Arduino.h>

// or ethernet clients.
#include "config.h"

#define pot 26
#define seg0 0
#define seg1 1
#define seg2 2
#define seg3 3
#define seg4 4
#define seg5 5
#define seg6 6
#define seg7 7

// Definiciones para el display de las decenas y unidades
int displayDecenas[] = {seg0, seg1, seg2, seg3, seg4, seg5, seg6};
int displayUnidades[] = {seg0, seg1, seg2, seg3, seg4, seg5, seg6};

// Mapeo de los números para los segmentos
const int digitos[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};

void setup(){
  pinMode(pot, INPUT_PULLUP);

  // Configuración de pines de salida para los displays
  for(int i = 0; i < 7; i++){
    pinMode(displayDecenas[i], OUTPUT);
    pinMode(displayUnidades[i], OUTPUT);
  }
}

void loop(){
  int valorPot = analogRead(pot);
  int valorMapeado = map(valorPot, 0, 4095, 0, 99);  // Ajustado para ESP32 con un rango de 0 a 4095

  int decenas = valorMapeado / 10;
  int unidades = valorMapeado % 10;

  mostrarDigito(decenas, displayDecenas);
  mostrarDigito(unidades, displayUnidades);

  delay(500);  // Actualizar cada 500ms
}

// Función para mostrar un dígito en el display de 7 segmentos
void mostrarDigito(int digito, int display[]){
  for(int i = 0; i < 7; i++){
    digitalWrite(display[i], digitos[digito][i]);
  }
}