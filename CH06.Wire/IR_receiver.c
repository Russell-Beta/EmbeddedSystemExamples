#include "irpigpio.h"
#include <stdio.h>
#include <wiringPi.h>
#define IR_PIN 18
#define LED 27
#define BUTTON_0 951308750
#define BUTTON_1 271208262
int deviceSetup(){
    if (gpioInitialise()<0 || wiringPiSetup()<0){
     return -1 ;
    }
    /* IR pin as input */
    gpioSetMode(IR_PIN, PI_INPUT);
    /* 5ms max gap after last pulse */
    gpioSetWatchdog(IR_PIN, 5);
    /* monitor IR level changes */
    gpioSetAlertFunc(IR_PIN, alert);
}
int main(){
    long value;
    if(deviceSetup()<0)
        return 1;
    pinMode(LED, OUTPUT);
    while(1){
        value = readIR();
        printf("IR value %u\n", value);
    }
    gpioTerminate();
}