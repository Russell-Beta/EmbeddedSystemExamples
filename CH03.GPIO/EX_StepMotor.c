//- 관련 라이브러리 포함 ------------------------------------------------------------------
#include <wiringPi.h>
#include <stdio.h>
//- Step 모터 연결 핀 선언 ---------------------------------------------------------------
#define BLUE_PIN 22 //WPI
#define PINK_PIN 23 //WPI
#define YELL_PIN 24 //WPI
#define ORAG_PIN 25 //WPI
//- 함수선언---------------------------------------------------------------------------------
void setStep(int _blue, int _pink, int _yell, int _orag);
//- DC모터 동작 기능 ----------------------------------------------------------------------
int main(void)
{
int i;
//- wiringPi 초기화
if( wiringPiSetup() == -1)
{
printf("Setup Fail ~!!");
return -1;
}
//- StepMotor 핀 동작모드 설정
pinMode(BLUE_PIN, OUTPUT);
pinMode(PINK_PIN, OUTPUT);
pinMode(YELL_PIN, OUTPUT);
pinMode(ORAG_PIN, OUTPUT);
while(1)
{
printf(" ---------- CW\n"); //- 시계방 방향
for(i=0;i<=500;i++)
{
setStep(HIGH, HIGH, LOW, LOW); delay(2);
setStep(LOW, HIGH, HIGH, LOW); delay(2);
setStep(LOW, LOW, HIGH, HIGH); delay(2);
setStep(HIGH, LOW, LOW, HIGH); delay(2);
}
printf(" ---------- CCW\n"); //- 반시계 방향
for(i=0;i<=500;i++)
{
setStep(HIGH, LOW, LOW, HIGH); delay(2);
setStep(LOW, LOW, HIGH, HIGH); delay(2);
setStep(LOW, HIGH, HIGH, LOW); delay(2);
setStep(HIGH, HIGH, LOW, LOW); delay(2);
}
printf(" ---------- STOP\n"); //- 정지
setStep(HIGH,HIGH,HIGH,HIGH);
delay(500);
}
setStep(HIGH,HIGH,HIGH,HIGH);
delay(500);
return 0;
}
//- StepMotor 동작제어 함수 -------------------------------------------------------------
void setStep(int _blue, int _pink, int _yell, int _orag)
{
pinMode(BLUE_PIN, OUTPUT);
digitalWrite(BLUE_PIN, _blue);
pinMode(PINK_PIN, OUTPUT);
digitalWrite(PINK_PIN, _pink);
pinMode(YELL_PIN, OUTPUT);
digitalWrite(YELL_PIN, _yell);
pinMode(ORAG_PIN, OUTPUT);
digitalWrite(ORAG_PIN, _orag);
}