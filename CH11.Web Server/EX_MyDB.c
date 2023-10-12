//- 라이브러리 포함 ------------------------------------------------------
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <time.h>
#include <math.h>
//- raspiDB 데이터베이스 관련 상수 ------------------------------------
#define DB_HOST "000" //- RaspberryPi IP 입력
#define DB_USER "root"
#define DB_PASS "root"
#define DB_NAME "-----"
//- 라이브러리 포함 ------------------------------------------------------
MYSQL *connector;
MYSQL_RES *result;
MYSQL_ROW row;
//- 데이터 저장 구조체 선언 --------------------------------------------
typedef struct _sensor {
    int ultrasonic;
    int illum;
}SENSOR;
//- 전역변수 선언 --------------------------------------------------------
int gUltra=50, gIll = 100;
int main(void){
    printf( "Raspberry Pi - MySQL DB Test \n" );
    if ( wiringPiSetup() == -1 ) exit( 1 );
    //- 연결
    connector = mysql_init(NULL);
    if(!mysql_real_connect(connector, DB_HOST, DB_USER, DB_PASS,DB_NAME, 3306, NULL, 0)){
        fprintf( stderr, "%s \n", mysql_error(connector));
        return 0;
    }else{
        printf("MySQL(raspiDB) opened! \n");
    }
    while(1){
        char query[1024];
        SENSOR gData = {gUltra++,gIll++ };
        sprintf(query, "insert into sensor values (now(), %d, %d)", gData.ultrasonic, gData.illum);
        if(mysql_query(connector, query)){
            fprintf(stderr, "%s \n", mysql_error(connector));
            printf("Write DB error. \n");
        }else{
            printf("Insert OK!! \n");
        }
    delay(1000);
    }
    mysql_close(connector);
    return(0);
}