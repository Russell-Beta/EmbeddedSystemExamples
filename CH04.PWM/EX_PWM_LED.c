//- 관련 라이브러리 추가----------------------------------------------------------
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>


//- 전역변수 선언 -----------------------------------------------------------------
#define R_LED_PIN		  27    //- PWM기능 핀

//- Entry Point 기능 구현 함수 --------------------------------------------------
int main(void)
{
      //- wiringPi 초기화
  if( wiringPiSetup() == -1){
    printf("Setup Fail ~!!");
    return -1;
  }
  //- 소프트 PWM으로 센서 초기화
  pinMode(R_LED_PIN, SOFT_PWM_OUTPUT);
  //- PWM 출력 주파서 설정
  softPwmCreate(R_LED_PIN,0, 255);
//- RGB LED 밝기 설정
  while(1){
    for(int idx=0; idx<=255; idx +=5){
      softPwmWrite(R_LED_PIN, idx) ;
      printf("Red LED ON ~%d\n", idx);
      delay(50);
    }
  }
  return 0;
}