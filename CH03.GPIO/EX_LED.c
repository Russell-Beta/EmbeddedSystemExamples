#include <stdio.h>
#include <wiringPi.h>
//- 센서 연결 핀 선언 -------------------------------------------------------------
#define R_LED_PIN 27 //WPI
#define G_LED_PIN 28 //WPI
#define B_LED_PIN 29 //WPI
//- 프로그램 실행 함수 ------------------------------------------------------------
int main(void){
    //- wiringPi 초기화
    if( wiringPiSetup() == -1){
        printf("Setup Fail ~!!");
        return -1;
    }
    //- 센서 초기화
    pinMode(R_LED_PIN, OUTPUT);
    pinMode(G_LED_PIN, OUTPUT);
    pinMode(B_LED_PIN, OUTPUT);
    //- 삼색 LED 제어
    while(1){
        digitalWrite(R_LED_PIN, HIGH) ;
        digitalWrite(B_LED_PIN, LOW) ;
        printf("RED LED ON ~\n");
        delay(1000);
        digitalWrite(R_LED_PIN, LOW) ;
        digitalWrite(G_LED_PIN, HIGH) ;
        printf("GREEN LED ON ~\n");
        delay(1000);
        digitalWrite(G_LED_PIN, LOW) ;
        digitalWrite(B_LED_PIN, HIGH) ;
        printf("BLUE LED ON ~\n");
        delay(1000);
        digitalWrite(R_LED_PIN, LOW) ;
        digitalWrite(G_LED_PIN, LOW) ;
        digitalWrite(B_LED_PIN, LOW) ;
        printf("RGB LED OFF ~\n");
        delay(2000);
    }
    return 0;
}