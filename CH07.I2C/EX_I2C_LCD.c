//- 관련 라이브러리 추가 -----------------------------------------------------------
#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>
#include <stdio.h>
//- PCF8574 &#8212; LCD 연결핀 주소값 선언 -----------------------------------------
#define BASE_ADDR 100
#define RS_PIN BASE_ADDR //- 100
#define RW_PIN BASE_ADDR+1 //- 101
#define EN_PIN BASE_ADDR+2 //- 102
#define BL_PIN BASE_ADDR+3 //- 103
#define D4_PIN BASE_ADDR+4 //- 104
#define D5_PIN BASE_ADDR+5 //- 105
#define D6_PIN BASE_ADDR+6 //- 106
#define D7_PIN BASE_ADDR+7 //- 107
//- 기능 구현 -------------------------------------------------------------------------------
int main (void){
  //- wiringPi 초기화
  if( wiringPiSetup() == -1){
    printf("Setup Fail ~!!");
    return -1;
  }
  //- I2C 통신기반 LCD 슬레이브 설정
  pcf8574Setup(RS_PIN, 0x27); //- P0핀 - LCD의 RS 연결, 주소 지정
  //- P1핀 - LCD의 RW 연결, 동작모드 설정
  pinMode (RW_PIN, OUTPUT);
  digitalWrite (RW_PIN, LOW);
  //- P3핀 - LCD의 Backlight 연결
  pinMode (BL_PIN, OUTPUT);
  digitalWrite (BL_PIN, HIGH); //- Backlight ON
  //- LCD 제어 핸들
  int fd = lcdInit (2, 16, 4, RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN,
  D7_PIN, 0,0,0,0 );
  while(1){
    lcdClear(fd); //- LCD화면 지우기
    delay(500);
    lcdPosition (fd, 2, 0); //- 0번 칸, 0번 줄 커서 위치
    lcdPuts (fd, "Hello, World!"); //- 문자열 출력
    lcdPosition (fd, 2, 1); //- 0번 칸, 1번 줄 커서 위치
    lcdPuts (fd, "* Good Luck *"); //- 문자열 출력
    delay(2000);
  }
  lcdClear(fd); //- LCD화면 지우기
  delay(500);
  return 0;
}