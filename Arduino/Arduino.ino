#include <SoftwareSerial.h>
#include <Wire.h> //引用二個函式庫SoftwareSerial及Wire
#include <string.h>
#include "pitch.h"

int buzzer = 8;
int rx = 10;
int tx = 11;
int himym[] = {
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_E4, NOTE_FS4, NOTE_E4,
  NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_B3, NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_A3, NOTE_A3 
};
float himymBeats[] = {
  2, 0.5, 1.5, 1.5, 0.5, 1, 1,
  1.5, 0.5, 1.5, 0.5,
  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 2 
};
bool alarm = 0;

SoftwareSerial I2CBT(rx,tx);//定義PIN10及PIN11分別為RX及TX腳位

void setup() {
   Serial.begin(9600); //Arduino起始鮑率：9600
   I2CBT.begin(115200);  //Baud Rate: 9600
   pinMode(buzzer, OUTPUT);  //設定 pin13 為輸出，LED就接在這
}

void loop() {
  
  if(alarm == 1){
    tone(buzzer,650,100); 
    delay(100); 
    noTone(buzzer); 
    tone(buzzer,1550,100); 
    delay(100); 
    noTone(buzzer);
  } 
  
  byte cmmd[20];
  int insize;	
  
  if ((insize=(I2CBT.available()))>0){  //讀取藍牙訊息
    //Serial.print("input size = ");
    //Serial.println(insize);
    for (int i=0; i<insize; i++){
      Serial.print(cmmd[i]=char(I2CBT.read()));
      Serial.print(",");
    }//此段請參考上一篇解釋
    
    char * tok;
    
    
    switch (cmmd[0]) { //讀取第一個字
      case'A'://97為"a"的ASCII CODE
         //digitalWrite(buzzer,HIGH);  //點亮LED
         //tone(buzzer,1000);
         //playHIMYM();
         alarm = 1;
         break;

      case'S':
         Serial.println("stop!!!!!!!");
         noTone(buzzer);
         //digitalWrite(buzzer,LOW);   //熄滅LED
         alarm = 0;
         break;
    } //Switch
      
  }  

}//loop


void playHIMYM(){
  int len = 19;
  for (int i = 0; i< len; i++){
    int duration = (int)(himymBeats[i] * 200);
    tone(buzzer, himym[i], duration);
    
    int pause = (int)(duration * 1.3);
    delay(pause);
    
    noTone(buzzer);
  }
}
