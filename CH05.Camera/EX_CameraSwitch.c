//- Library -----------------------------------------------------------------------
#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//- Pin Number------------------------------------------------------------------
#define CAPTURE_PUSH_PIN   7		     //- Red Push Switch 

//- Entry Function--------------------------------------------------------------------------
int main(void)
{
     int oldPushedSW = HIGH, pushedSW = LOW;
     int idx = 1;

    wiringPiSetup();
    
    //- Push Switch 동작 모드 설정
    pinMode(CAPTURE_PUSH_PIN, INPUT);

    while(1)
    {
        pushedSW = digitalRead(CAPTURE_PUSH_PIN);
        
        if((oldPushedSW != pushedSW) && (pushedSW == LOW))
        {
			  char cmd[] = "raspistill -w 320 -h 240 -o /home/pi/Pictures/test";
			  char file[3]= { };
			  sprintf(file, "%d", idx++);
			  strcat(cmd, file);
			  strcat(cmd, ".jpg");
			  printf("%s \n", cmd);
			  system(cmd);

			  printf("Take a picture \n");
        }
        oldPushedSW = pushedSW;
    }
	return 0;
}