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



