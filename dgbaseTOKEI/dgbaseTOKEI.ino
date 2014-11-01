#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>      /** tmp, hu */
#include <MPL115A2.h> /** press */

#include <WS2812.h>  /** LED */
#include <dgbaseTOKEI.h>
#include <dgbaseTime.h>
#include <dgbaseTime2.h>
#include <dgbaseTemp.h>  /** 温度/湿度 */
#include <dgbasePress.h> /** 気圧 */

#define DHTTYPE DHT11
#define DHTPIN 4 //DHT-11 Data Pin
#define RTCDIV 64//64分周

/** LED */
#define TIME_PIN 13     //LED pin
#define TIME_LEDCNT 60   //LED数

/** color     G   R   B */
cRGB chh = {  0,  0, 60 };  //時
cRGB cmm = {  0, 60,  0 };  //分
cRGB css = { 40, 40, 40 };  //秒

WS2812 LED(TIME_LEDCNT);
dgbaseTime2* dgtime;


DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;

float humi, temp_d, hpa, temp_m;
DateTime now;
volatile uint8_t cnt1 = 0, cnt2 = 0;
uint8_t cnt2old = 128;
const int sec = 4096 / RTCDIV;

volatile boolean lock = false;
volatile boolean lock2 = false;

volatile int y = 0;
volatile int8_t mo, d, h, mi, s;
boolean isRtcAdjust = true;
volatile int8_t tmpcnt = 2;


void rtcAdjust() {
    now = rtc.now();
    y = now.year();
    mo = now.month();
    d = now.day();
    h = now.hour();
    mi = now.minute();
    s = now.second();
    
    isRtcAdjust = false;
}


void setup() {
  //LED  
  dgtime = new dgbaseTime2(TIME_PIN, TIME_LEDCNT, &LED, chh, cmm, css);
  
  //Serial.begin(9600);
 
  rtc.begin();
  MPL115A2.begin();
  MPL115A2.shutdown();
  dht.begin();
 
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //割り込み立ち上がり時
  attachInterrupt(0, rtcTimer, RISING);
  //SQWピン4kHz出力
  rtc.writeSqwPinMode(SquareWave4kHz);
  //
  rtcAdjust();
}

void rtcTimer(void){
  //INT割り込み。この中ではI2C通信が出来ないのでrtc.nowが使用不可
  //1秒間に4096回呼ばれる、64分周で64回
  if(cnt1%RTCDIV == 0){
    //1秒に64回
    if (cnt2%sec == 0) {
      //1秒に1回
      if ((++s) >= TIME_LEDCNT) {
        s = 0;
        if ((++mi) >= TIME_LEDCNT) {
          mi = 0;
          if ((++h) >= 24) {
            h = 0;
          }
          isRtcAdjust = true;
          rtcAdjust();
        }
      }
    }
    cnt2++;
    lock = false;
  }
  cnt1++;
  lock2 = false;
}

void loop() {
  //メインループは1ms遅延の為1ms+αで回っている
  //cnt2は1秒間に64回カウント、64分周で1sec
  if(cnt2%sec == 0 && !lock){
    lock = true;

    //debug用に表示
    /*
    Serial.print(y, DEC);
    Serial.print('/');
    Serial.print(mo, DEC);
    Serial.print('/');
    Serial.print(d, DEC);
    Serial.print(' ');
    Serial.print(h, DEC);
    Serial.print(':');
    Serial.print(mi, DEC);
    Serial.print(':');
    Serial.print(s, DEC);
     */
    
//    Serial.println();

    //センサはxx秒毎
    //気圧センサはレスポンスが早い（数ms？）
    //温湿度センサはレスポンスが遅い（6～10sec）
    if((--tmpcnt) <= 0) {
      tmpcnt = 20;

      MPL115A2.ReadSensor();
      MPL115A2.shutdown();
      humi = dht.readHumidity();
      temp_d = dht.readTemperature();
      hpa = MPL115A2.GetPressure();
      temp_m = MPL115A2.GetTemperature();

      //debug用に表示
      /*
      Serial.print("AirPressure : ");
      Serial.print(hpa * 10);
      Serial.print("hPa  Temp(MPL) : ");
      Serial.print(temp_m, 1);
      Serial.print("C  Temp(DHT) : ");
      Serial.print(temp_d, 1);
      Serial.print("C  Humidity : ");
      Serial.print(humi, 1);
      Serial.print("%");
       */

      //温度/湿度
      dgbaseTemp tmp(TIME_LEDCNT, &LED, chh, cmm, css);
      tmp.execute(temp_m, temp_d, 50, 200);
      tmp.execute(humi, 50, 150);
      tmp.fader(30);
      //気圧
      dgbasePress prs(TIME_LEDCNT, &LED, chh, cmm, css);
      prs.execute((hpa * 10), 50, 250, true);
      prs.fader(30);
/*
      prs.execute(1043, 50, 250);
      prs.fader(30);

      prs.execute(1024, 50, 250);
      prs.fader(30);

      prs.execute(1014, 50, 250);
      prs.fader(30);
      
      prs.execute(1013, 50, 250);
      prs.fader(30);

      prs.execute(1012.9, 50, 250);
      prs.fader(30);

      prs.execute(999.9, 50, 250);
      prs.fader(30);

      prs.execute(998, 50, 250);
      prs.fader(30);
 */
//      prs.execute(984, 50, 250);
//      prs.fader(30);

      /*
      Serial.print("  hpa=");
      Serial.print(prs.mHpa, 1);

      Serial.println();
       */

//      rtcAdjust();
    }

    //LED
    dgtime->execute(h, mi, s, 1);
//    dgtime->isAlarm(h, mi, s);

    //Serial.println();

  }
  if ((cnt2 != cnt2old)&&(!lock2)) {
    lock2 = true;
    cnt2old = cnt2;
    //テスト:この中は1秒間に64回呼ばれる
    
    //LEDをグラデーション変化
    dgtime->execGradation();
    //LEDの点灯
    dgtime->syncLED();
  }
  //lock=trueが反映される前にif分を通ることがある為、1ms遅延
  delay(1);
}

