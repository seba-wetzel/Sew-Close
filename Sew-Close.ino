#include "Sew-Close.h"

config_u configuraciones;
states_u estado = config;

void setup(void){
  for(uint8_t i=0; i < sizeof(outputPins); i++){ //Setemos los pines guardados en outputPins[] como salidas
      pinMode(outputPins[i], OUTPUT);
  }
    for(uint8_t i=0; i < sizeof(outputPins); i++){ //Setemos los pines guardados en outputPins[] con
      digitalWrite(outputPins[i], !DRIVEN_STATE);  // la negacion del estado de manejo
  }
}

void loop(void){
 estateMachine(&estado); 
}

void estateMachine (states_u * estadoP) {

  switch (*estadoP) {
    case config: configuration();
      *estadoP = stop;
      break;


  }
}


//Funciones de maquina de estados

void configuration(void){
  
}

