#include <errno.h>
#include <string.h>
#include "MFRC522.h"
//- 센서 제어 상수 선언 ------------------------------------------------------------------
#define CHAN_CONFIG_SINGLE 8 //- 싱글 채널 설정 값
#define SPI_SPEED 1000000 //- 1MHz
#define SPI_CE0_CHANNEL 0 //- SPI와 연결된 CE0 채널
//- 함수선언---------------------------------------------------------------------------------
int spiSetup(void);
//- 기능 구현 ------------------------------------------------------------------------------
int main (void){
    unsigned char data1[16] = {0x12, 0x34, 0x56, 0x78, 0xED, 0xCB,
    0xA9, 0x87, 0x12, 0x34, 0x56,
    0x78, 0x01, 0xFE, 0x01, 0xFE};
    unsigned char DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    unsigned char g_ucTempbuf[20];
    int count = 0;
    unsigned char status, i;
    //- wiringPi 초기화
    if( wiringPiSetup() == -1){
        printf("Setup Fail ~!!");
    return -1;
    }
    //- SPI 초기화
    spiSetup();
    //- RFID 초기화
    delay(500);
    PcdReset();
    PcdAntennaOff();
    delay(10);
    PcdAntennaOn();
    printf ("... Touch RFID CARD\n\n") ;
    while(1){
        status = PcdRequest(PICC_REQALL, g_ucTempbuf);
        if (status != MI_OK) continue;
        printf("\ncard type:");
        switch(g_ucTempbuf[0]){
            case 0x02: printf("Mifare_One(S70)\n"); break;
            case 0x04: printf("Mifare_One(S50)\n"); break;
            case 0x08: printf("Mifare_Pro(X)\n"); break;
            case 0x44: {
                if(g_ucTempbuf[1] == 0x00){
                    printf("Mifare_UltraLight\n");
                    break;
                }else if(g_ucTempbuf[1] == 0x03){
                    printf("Mifare_DESFire\n");
                    break;
                }
            }
        }
        status = PcdAnticoll(g_ucTempbuf);
        if (status != MI_OK) continue;
        printf("\ncard SN:");
        for(i=0;i<4;i++){
            if(g_ucTempbuf[i] < 0x10)
                printf("0%X",g_ucTempbuf[i]);
            else
                printf("%X",g_ucTempbuf[i]);
        }
        printf("\n");
        status = PcdSelect(g_ucTempbuf);
        if (status != MI_OK) continue;
            status = PcdAuthState(PICC_AUTHENT1A, 1, DefaultKey, g_ucTempbuf);
        if (status != MI_OK) continue;
            status = PcdWrite(1, data1);
        if (status != MI_OK) continue;
            status = PcdBakValue(1, 2);
            for(i=0;i<4;i++){
                status = PcdRead(i, g_ucTempbuf);
                if (status != MI_OK) continue;
                    printf("\nread block %d:", i);
                int j;
                for(j=0;j<16;j++){
                    if(g_ucTempbuf[j] < 0x10)
                        printf("0%X",g_ucTempbuf[j]);
                    else
                        printf("%X",g_ucTempbuf[j]);
                }
            }
        printf("\n");
        PcdHalt();
        delay(1000);
        if(count++>=3) break;
    }
    return 0;
}
int spiSetup(void){
    if( wiringPiSPISetup (SPI_CE0_CHANNEL, SPI_SPEED) == -1 ){
        fprintf (stderr, "wiringPiSPISetup Failed ! ERROR : %s\n", strerror (errno));
        return 1;
    }
}