#define DEBUG
#include "Sew-Close.h"

config_u configuraciones;
states_u estado = config;

void setup(void) {
  START_DEBUG(115200);
  DEBUG_PRINTLN("Iniciando");
  initBoard();
}

void loop(void) {
  estateMachine(&estado);

}

void estateMachine (states_u * estadoP) {

  switch (*estadoP) {
    case config: if (configF(&estado) == OK) {
      }
      else errorHook();
      break;

    case stop: if (stopF(&estado) == OK) {
      }
      else errorHook();
      stopAction();
      break;

    case start: if (startF(&estado) == OK) {
      }
      else errorHook();
      startAction();
      break;

    case sew: if (sewF(&estado) == OK) {
      }
      else errorHook();
      sewAction();
      break;

    case cut: if (cutF(&estado) == OK) {
      }
      else errorHook();
      cutAction();
      break;
  }
}


//Funciones de maquina de estados
status_u configF(states_u * estadoP) {
  DEBUG_PRINTLN("configF");
  * estadoP = stop;
  return OK;
}

status_u stopF(states_u * estadoP) {
  DEBUG_PRINTLN("stopF");
  if (readSensor() == start_s) *estadoP = start;
  return OK;
}

status_u startF(states_u * estadoP) {
  DEBUG_PRINTLN("startF");
  switch (readSensor()) {
    case stop_s: *estadoP = stop;
      break;

    case sew_s: *estadoP = sew;
      break;
  }
  return OK;
}

status_u sewF(states_u * estadoP) {
  DEBUG_PRINTLN("sewF");
  if (readSensor() == cut_s) *estadoP = cut;
  return OK;
}

status_u cutF(states_u * estadoP) {
  DEBUG_PRINTLN("cutF");
  *estadoP = start;
  return OK;
}

//Action functions

void stopAction(void) {
  //Apagamos todo

  for (uint8_t i = 0; i < sizeof(outputPins); i++) {
    digitalWrite(outputPins[i], !DRIVEN_STATE);
  }
}
void startAction(void) {

  digitalWrite(MOTOR1_OUTPUT_PIN, DRIVEN_STATE);

}
void sewAction(void) {

  digitalWrite(MOTOR2_OUTPUT_PIN, DRIVEN_STATE);

}
void cutAction(void) {
  DEBUG_PRINTLN("cut Action");
  digitalWrite(MOTOR2_OUTPUT_PIN, !DRIVEN_STATE);
  delay(150);
  digitalWrite(CUTTER_OUTPUT_PIN, DRIVEN_STATE);
  delay(250);
  digitalWrite(CUTTER_OUTPUT_PIN, !DRIVEN_STATE);

  
}






void initBoard(void) {
  for (uint8_t i = 0; i < sizeof(outputPins); i++) { //Seteamos los pines guardados en outputPins[] como salidas
    pinMode(outputPins[i], OUTPUT);
  }
  for (uint8_t i = 0; i < sizeof(outputPins); i++) { //Setemos los pines guardados en outputPins[] con
    digitalWrite(outputPins[i], !DRIVEN_STATE);  // la negacion del estado de manejo
  }

  for (uint8_t i = 0; i < sizeof(inputPins); i++) { //Seteamos los pines guardados en outputPins[] como salidas
    pinMode(inputPins[i], INPUT_PULLUP);
  }
}


sensor_u readSensor (void) {

  if (!digitalRead(STOP_INPUT_PIN) )  return stop_s;

  if (!digitalRead(START_INPUT_PIN))  return start_s;

  if (!digitalRead(SENSOR_INPUT_PIN)) return sew_s;

  if (!digitalRead(SENSOR2_INPUT_PIN)) return cut_s;
  return none;
}

//Error hook
void errorHook (void) {

  while (true) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
}

