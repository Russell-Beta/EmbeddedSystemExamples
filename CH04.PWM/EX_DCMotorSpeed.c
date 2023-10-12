//- 관련 라이브러리 포함 --------------------------------------------------------
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

//- DC 모터 연결 핀 선언 -------------------------------------------------------
#define DCMotorA     6
#define DCMotorB     31

//- DC모터 동작 기능 ------------------------------------------------------------
int main(void)
{
    wiringPiSetup();
    
    pinMode(DCMotorA, SOFT_PWM_OUTPUT);
    pinMode(DCMotorB, SOFT_PWM_OUTPUT);
    
    //- DC모터 제어 핀에 0~100사이 듀티비의 PMW 출력 생성
    softPwmCreate(DCMotorA, 0, 100);
    softPwmCreate(DCMotorB, 0, 100);

    int duty     = 10;     //- HIGH & LOW 출력 비율
    int updown = 10;      //- 듀티비 증감 값

    while(1)
    {
        if(duty > 90) updown = -10;
        if(duty < 20) updown = 10;
        duty += updown;
        printf("Motor duty = %d\n", duty);
        
        softPwmWrite(DCMotorA, duty);
        softPwmWrite(DCMotorB, 0);
        printf("Motor run CCW\n");
        delay(3000);

        softPwmWrite(DCMotorA, 0);
        softPwmWrite(DCMotorB, 0);
        printf("Motor STOP\n");
        delay(1000);
        
        softPwmWrite(DCMotorA, 0);
        softPwmWrite(DCMotorB, duty);
        printf("Motor run CW\n");
        delay(3000);

        softPwmWrite(DCMotorA, 0);
        softPwmWrite(DCMotorB, 0);
        printf("Motor STOP\n");
        delay(1000);
    }
}