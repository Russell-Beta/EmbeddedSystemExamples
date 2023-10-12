#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//- 상수 선언 -----------------------------------------------------------------------------
#define MAXTIMINGS 85 //- 온습도 읽은 데이터 사이즈
#define DHTPIN 3
//- 전역변수 선언 ------------------------------------------------------------------------
int data[5] = {0, }; //- 온습도 데이터 저장 변수
//- 함수 선언 -----------------------------------------------------------------------------
void read_dht11_data();
//- 시작 함수 -----------------------------------------------------------------------------
int main(void){
    //- wiringPi 초기화
    if( wiringPiSetup() == -1){
        printf("Setup Fail ~!!");
        return -1;
    }
    while (1){
        read_dht11_data();
        delay(2000) ;
    }
    return 0 ;
}
//- 온습도 값 읽어오기 ------------------------------------------------------------------
void read_dht11_data(){
    uint8_t laststate = HIGH ; //- DHTPIN의 기본 신호
    uint8_t counter = 0 ; //- 데이터 읽기 위한 시간 계산 카운터
    uint8_t j = 0, i ;
    //- 데이터 저장 변수 초기화
    data[0]=data[1]=data[2]=data[3]=data[4]= 0 ;
    //- DHT11 센서 동작 신호 출력 (온습도 값 요구 명령)
    pinMode(DHTPIN, OUTPUT) ;
    digitalWrite(DHTPIN, LOW) ;
    delay(18) ;
    //- DHT11센서로부터 응답신호를 받기 위해서 대기
    digitalWrite(DHTPIN, HIGH) ;
    delayMicroseconds(30) ;
    //- DHT11센서로부터 데이터 받기 위한 입력 모드 설정
    pinMode(DHTPIN, INPUT) ;
    //- 입력되는 데이터 신호 체크
    for (i = 0; i < MAXTIMINGS; i++){
        counter = 0 ;
        while( digitalRead(DHTPIN) == laststate ){
            counter++ ;
            delayMicroseconds(1) ;
            if (counter == 255) break ;
        }
        //- 온습도 값 읽기
        laststate = digitalRead(DHTPIN) ;
        //- 온습도 값 읽기 위한 시간 초과한 경우 처리
        if (counter == 255) break ;
        //- 시간 내 온습도 값을 읽어온 경우 처리
        //- 데이터 비트 0일 경우 => 26~28us 동안 HIGH신호 출력
        //- 데이터 비트 1일 경우 => 70us 동안 HIGH신호 출력
        if ((i >= 4) && (i % 2 == 0)) {
            data[j / 8] <<= 1 ;
            if (counter > 60) data[j / 8] |= 1 ;
            j++ ;
        }
    }
    //- 읽은 데이터의 유효성 검사
    if(j >= 40){
        if(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xff))
        printf("humidity = %d.%d %% Temperature = %d.%d *C \n",data[0], data[1], data[2], data[3]) ;
    }else{
        printf("Data get failed\n");
    }
}