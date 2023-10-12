//- 관련 라이브러리 추가----------------------------------------------
#include <wiringPi.h>
#include <stdlib.h>

//- 핀 번호 선언 ------------------------------------------------------
#define BUZ_A_PIN		30      		//- WPI


//- Buzzer 제어 기능 구현 -------------------------------------------
int main(void)
{
    if( wiringPiSetup() == -1)  exit(1);		//- wiringPi 초기화	

    pinMode(BUZ_A_PIN, OUTPUT);

    while(1)
    {
		digitalWrite(BUZ_A_PIN, HIGH);
		delay(1000);

		digitalWrite(BUZ_A_PIN, LOW);
		delay(1000);
    }
    
    return 0;
}
