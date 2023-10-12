//- 관련 라이브러리 추가----------------------------------------------------------
#include <wiringPi.h>
#include <stdio.h>

//- 핀 번호 선언 -------------------------------------------------------------------
#define ULTRASONIC_TRIG      4
#define ULTRASONIC_ECHO     5

//- 기능 구현 ----------------------------------------------------------------------
int main(void)
{
    int start_time=0, end_time=0;
    float distance=0, duration=0;
    
    wiringPiSetup();
    
    //- 초음파 센서 핀 동작모드 설정
    pinMode(ULTRASONIC_TRIG, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);
    
    printf("ok");
    while(1)
    {
        //- 초음파 센서에 동작 커맨드 신호 보내기
        digitalWrite(ULTRASONIC_TRIG, LOW);
        delay(500);
        digitalWrite(ULTRASONIC_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(ULTRASONIC_TRIG, LOW);
        
        //- 초음파 발사 시작 시간 측정
        while(digitalRead(ULTRASONIC_ECHO) == LOW)
            start_time = micros();

        //- 초음파 반사되어 돌아온 시간 측정
        while(digitalRead(ULTRASONIC_ECHO) == HIGH)
            end_time = micros();
        
        //- 두 시간 차는 왕복으로 나누기 2해서 거리 구하기
        duration = (float)(end_time - start_time);
        duration = duration/1000000/2;
        distance=(340 * duration) * 100;

        printf("Distance : %3.0f cm\n", distance);
    }
    return 0;
}