#ifndef _SEW_CLOSE_H
#define _SEW_CLOSE_H

//Entradas
#define START_INPUT_PIN   6
#define SENSOR_INPUT_PIN  7

//Salidas
#define MOTOR1_OUTPUT_PIN 2
#define MOTOR2_OUTPUT_PIN 3
#define MOTOR3_OUTPUT_PIN 4
#define CUTTER_OUTPUT_PIN 5

//Manejo de las salidas
#define DRIVEN_STATE 1

//Otros



uint8_t outputPins [] = {MOTOR1_OUTPUT_PIN, MOTOR2_OUTPUT_PIN,MOTOR3_OUTPUT_PIN, CUTTER_OUTPUT_PIN }; 

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


//Prototipos 
void estateMachine (states_u *);
void readConfigs(config_u*);
void saveConfigs(config_u*);

//Prototipos funciones de maquina de estado
void configuration(void);

#endif
