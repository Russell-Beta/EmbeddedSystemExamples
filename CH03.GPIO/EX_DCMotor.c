//- 관련 라이브러리 포함 ---------------------------------------------------------
#include <wiringPi.h>
#include <stdio.h>

//- DC 모터 연결 핀 선언 --------------------------------------------------------
#define DCMotorA     6
#define DCMotorB     31

//- DC모터 동작 기능 -------------------------------------------------------------
int main(void)
{
    wiringPiSetup();
    
    pinMode(DCMotorA, OUTPUT);
    pinMode(DCMotorB, OUTPUT);
    
    while(1)
    {
        digitalWrite(DCMotorA, HIGH);
	    digitalWrite(DCMotorB, LOW);
	    printf("Motor run CW\n");
        delay(1000);

        digitalWrite(DCMotorA, LOW);
	    digitalWrite(DCMotorB, HIGH);
	    printf("Motor run CCW\n");
        delay(1000);

        digitalWrite(DCMotorA, LOW);
	    digitalWrite(DCMotorB, LOW);
        printf("Motor run STOP\n");
        delay(1000);
    }
}