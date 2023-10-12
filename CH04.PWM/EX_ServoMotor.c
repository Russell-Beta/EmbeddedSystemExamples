//- 관련 라이브러리 포함 ------------------------------------------------------------------
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
//- DC 모터 연결 핀 선언 -----------------------------------------------------------------
#define SERVO_PIN 26
//- DC모터 동작 기능 ----------------------------------------------------------------------
int main(void){
    //- wiringPi 초기화
    if( wiringPiSetup() == -1){
        printf("Setup Fail ~!!");
        return -1;
    }
    //- ServoMotor 핀 동작모드 설정 및 PWM 범위 설정
    pinMode(SERVO_PIN, SOFT_PWM_OUTPUT);
    softPwmCreate(SERVO_PIN, 0, 200 );
    while(1){
        //- 15도 방향 이동
        softPwmWrite(SERVO_PIN, 15);
        delay(500);
        //- 24도 방향 이동
        softPwmWrite(SERVO_PIN, 24);
        delay(500);
        //- 5도 방향 이동
        softPwmWrite(SERVO_PIN, 5);
        delay(500);
    }
    softPwmStop(SERVO_PIN);
    delay(500);
    return 0;
}