#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

//- 전역변수 선언 --------------------------------------------------------------------------------------
int  g_hSerial;                                                         //-  제어 핸들


//- PC와 시리얼 통신 --------------------------------------------------------------------------------------
int main()
{
    unsigned int  nSendTime;

    wiringPiSetup();                                                //- 라이브러리 초기화
    g_hSerial = serialOpen("/dev/ttyAMA0", 9600);      //- 시리얼 통신 초기화
    printf("Serial init - %d\n" , g_hSerial);
        
    while(1)
    {
	if(millis()-nSendTime >=1000)
       {
	    serialPrintf(g_hSerial, "Data from RasperryPi\r\n");
	    nSendTime = millis();
        }
    }
    printf ("\n") ;
    return 0 ;
}