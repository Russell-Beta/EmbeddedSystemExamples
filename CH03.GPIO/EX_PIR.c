//- 관련 라이브러리 --------------------------------------------------------------
#include <wiringPi.h>
#include <stdio.h>

//- 센서 핀 선언 ------------------------------------------------------------------
#define PIR_PIN		  2
#define R_LED_PIN              27

//- PIR 감지 시 LED 제어 -------------------------------------------------------
int main(void)
{
    //- wiringPi 초기화
    wiringPiSetup();
    
    //- PIR, LED 동작 모드 및 초기값 설정
    pinMode(PIR_PIN,    INPUT);
    pinMode(R_LED_PIN,  OUTPUT);

    digitalWrite(PIR_PIN,    HIGH);
    digitalWrite(R_LED_PIN,  LOW);
        
    //- PIR센서 감지에 따른 LED 제어
    while(1)
    {
        if(digitalRead(PIR_PIN) == HIGH)
        {
            digitalWrite(R_LED_PIN, HIGH);
            printf("PIR Sensor ON\n");
        }else{
            digitalWrite(R_LED_PIN, LOW);
            printf("PIR Sensor OFF\n");
        }
        delay(1000);
    }
}