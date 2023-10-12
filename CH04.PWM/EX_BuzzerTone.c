//- 라이브러리 추가 ---------------------------------------------------
#include <wiringPi.h>
#include <softTone.h>

//- 센서 연결 핀 번호 선언 ------------------------------------------
#define BUZ_P_PIN		21		 //- WPI

//- 전역 변수 선언 ---------------------------------------------------
unsigned int melody[8] = {262, 294, 330, 349, 392, 440, 494, 523};


//- 1초 간격으로 부저 On/Off ---------------------------------------
int main(void)
{
    int idx = 0;

    if( wiringPiSetup() == -1)  exit(1);		//- wiringPi 초기화	
                  		 
    pinMode(BUZ_P_PIN, SOFT_TONE_OUTPUT);

    softToneCreate(BUZ_P_PIN);             	 //- 주파수 출력 설정
    
    while(1)
    {
		for(idx=0; idx<8; idx++)
		{
			softToneWrite(BUZ_P_PIN, melody[idx]);
			delay(1000);
		}
    }
    softToneStop(BUZ_P_PIN);    //- 주파수 출력 중단
}