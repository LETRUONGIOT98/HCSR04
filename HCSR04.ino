#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

int state = 0;
const int pin = 9;
float gpslat, gpslon;

TinyGPS gps;
//////Cảm biến trước
const int trig1 = 3;     // chân trig của HC-SR04
const int echo1 = 2;     // chân echo của HC-SR04

/////Cảm biến phải
const int trig2 = 4;     // chân trig của HC-SR04
const int echo2 = 5;     // chân echo của HC-SR04

/////Cảm biến sau
const int trig3 = 6;     // chân trig của HC-SR04
const int echo3 = 7;     // chân echo của HC-SR04

/////Cảm biến trái
const int trig4 = 8;     // chân trig của HC-SR04
const int echo4 = 9;     // chân echo của HC-SR04

#define Mode A0
#define cong A1
#define tru  A2
#define led1 10
#define led2 11
#define led3 12
#define led4 13
#define nutnhan 14
int dem=0,maxTruoc = 20, maxPhai = 10, maxSau = 20, maxTrai = 10;
int distance1,distance2,distance3,distance4;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
String tt="";
long time1;
void setup()
{   lcd.init();                      // initialize the lcd 
    lcd.backlight();
    Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
    Serial1.begin(9600);
    Serial2.begin(9600);
    pinMode(trig1,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo1,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(trig2,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo2,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(trig3,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo3,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(trig4,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo4,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(Mode, INPUT_PULLUP);
    pinMode(cong, INPUT_PULLUP);
    pinMode(tru, INPUT_PULLUP);
    pinMode(nutnhan, INPUT_PULLUP);
    maxTruoc = EEPROM.read(0);
    maxSau = EEPROM.read(1);
    delay(100);
}
long times=0;
void gui(){
  while (Serial1.available())
  {
    int c = Serial1.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
    }
  }
    if (distance1 <= maxTruoc && state == 0) {
       if(millis() - times >= 30000){
      Serial2.print("\r");
      delay(1000);
      Serial2.print("AT+CMGF=1\r");
      delay(1000);
      /*Replace XXXXXXXXXX to 10 digit mobile number &
        ZZ to 2 digit country code*/
      Serial2.print("AT+CMGS=\"+ZZXXXXXXXXXX\"\r");
      delay(1000);
      //The text of the message to be sent.
      Serial2.print("CANH BAO VA CHAM: ");
      Serial2.print("Latitude :");
      Serial2.println(gpslat, 6);
      Serial2.print("Longitude:");
      Serial2.println(gpslon, 6);
      delay(1000);
      Serial2.write(0x1A);
      delay(1000);
      state = 1;
    }
    }

    
      delay(100);
  }

void loop()
{  
  if(dem == 0){
  ///Đo khoảng cách trước
    unsigned long duration1; // biến đo thời gian
    int distance1;           // biến lưu khoảng cách
    /* Phát xung từ chân trig */
    digitalWrite(trig1,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig1,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig1,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration1 = pulseIn(echo1,HIGH);  
    // Tính khoảng cách đến vật.
    distance1 = int(duration1/2/29.412);

    ///Đo khoảng cách trước
    unsigned long duration2; // biến đo thời gian
    int distance2;           // biến lưu khoảng cách
    /* Phát xung từ chân trig */
    digitalWrite(trig2,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig2,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig2,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration2 = pulseIn(echo2,HIGH);  
    // Tính khoảng cách đến vật.
    distance2 = int(duration2/2/29.412);

    ///Đo khoảng cách trước
    unsigned long duration3; // biến đo thời gian
    int distance3;           // biến lưu khoảng cách
    /* Phát xung từ chân trig */
    digitalWrite(trig3,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig3,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig3,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration3 = pulseIn(echo3,HIGH);  
    // Tính khoảng cách đến vật.
    distance3 = int(duration3/2/29.412);

    ///Đo khoảng cách trước
    unsigned long duration4; // biến đo thời gian
    int distance4;           // biến lưu khoảng cách
    /* Phát xung từ chân trig */
    digitalWrite(trig4,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig4,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig4,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration4 = pulseIn(echo4,HIGH);  
    // Tính khoảng cách đến vật.
    distance4 = int(duration4/2/29.412);
    lcd.setCursor(0, 0);
    lcd.print("D1:  " +String(distance1) + " D2:  " + String(distance2));
    lcd.setCursor(0, 1);
    lcd.print("D3:  " +String(distance3) + " D4:  " + String(distance4) );
}
else{
  lcd.setCursor(0, 0);
    lcd.print(tt) ;
    lcd.setCursor(0, 1);
    lcd.print("S3:  " +String(maxSau) + " S4:  " + String(maxTrai)) ;
}
    if(digitalRead(Mode) == 0 && millis() - time1+9 <= 500){
      dem = dem+1;
      delay(500);
    }
    else {
      time1 = millis();
    }
    if(dem == 1){
      tt = (" SUA KC TRUOC");
      if(digitalRead(cong) ==0){
        maxTruoc = maxTruoc + 1;
        delay(300);
      }
      if(digitalRead(tru) ==0 && maxTruoc >= 0){
        maxTruoc = maxTruoc - 1;
        delay(300);
      }
    }

    if(dem == 2){
      tt = (" SUA KC SAU  ");
      if(digitalRead(cong) ==0){
        maxSau = maxSau + 1;
        delay(300);
      }
      if(digitalRead(tru) ==0 && maxSau >= 0){
        maxSau = maxSau - 1;
        delay(300);
      }
    }
  if(dem == 3){
    tt = ("  DANG LUU    ");
    EEPROM.write(0, maxTruoc);
    delay(5);
    EEPROM.write(10, maxSau);
    delay(2000);
    dem = 0;
  }
    

    if(distance1 <= maxTruoc){
      digitalWrite(led1, HIGH);
      gui();
      if(digitalRead(nutnhan) == 0){
        state = 1;
    }
    }
    else {digitalWrite(led1, LOW);
    state = 0;
      times = millis();
    }
    if(distance2 <= maxPhai){
      digitalWrite(led2, HIGH);
    }
    else digitalWrite(led2, LOW);

    if(distance3 <= maxSau){
      digitalWrite(led3, HIGH);
    }
    else digitalWrite(led3, LOW);

    if(distance4 <= maxTrai){
      digitalWrite(led4, HIGH);
    }
    else digitalWrite(led4, LOW);
    delay(200);
    lcd.clear();
    
}
