#ifndef _SEW_CLOSE_H
#define _SEW_CLOSE_H


#include "stdint.h"


//Macro de debug
#ifdef DEBUG
#define START_DEBUG(x) Serial.begin (x)
#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
#define DEBUG_PRINTLN(x)
#define START_DEBUG(x)
#endif


//Entradas
#define STOP_INPUT_PIN     6
#define START_INPUT_PIN    7
#define SENSOR_INPUT_PIN   8
#define SENSOR2_INPUT_PIN  9


//Salidas
#define MOTOR1_OUTPUT_PIN 2
#define MOTOR2_OUTPUT_PIN 3
#define MOTOR3_OUTPUT_PIN 4
#define CUTTER_OUTPUT_PIN 5
#define LED_PIN           13

//Manejo de las salidas
#define DRIVEN_STATE 1

//Otros


uint8_t inputPins  [] = {STOP_INPUT_PIN, START_INPUT_PIN,SENSOR_INPUT_PIN, SENSOR2_INPUT_PIN};
uint8_t outputPins [] = {MOTOR1_OUTPUT_PIN, MOTOR2_OUTPUT_PIN,MOTOR3_OUTPUT_PIN, CUTTER_OUTPUT_PIN, LED_PIN  }; 

typedef enum {
  config,
  stop,
  start,
  sew,
  cut  
}states_u;

typedef struct {
  uint8_t SEW_TIME;
} config_u;

typedef enum {
  OK,
  ERROR
} status_u;

typedef enum{
  stop_s,
  start_s,
  sew_s,
  cut_s,
  none
}sensor_u;

//Prototipos 
void estateMachine (states_u *);
void readConfigs(config_u*);
void saveConfigs(config_u*);

void initBoard(void);
sensor_u readSensor(void);

//Prototipos funciones de maquina de estado reciben estado, devuelven estatus (son las que cambian el estado de la maquina
// segun los sensores pero no ejecutan nada, eso lo hacen las actions)
status_u configF(states_u *);
status_u stopF (states_u *);
status_u startF(states_u *);
status_u sewF(states_u *);
status_u cutF(states_u *);

//Actions
void stopAction(void);
void startAction(void);
void sewAction(void);
void cutAction(void);
//Prototipo de funcion de error

void errorHook(void);

#endif
