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

char cmmd[20] = {'\0'};
int cmmdi = 0;

void loop() {
  
  if(alarm == 1){
    tone(buzzer,650,100); 
    delay(100); 
    noTone(buzzer); 
    tone(buzzer,1550,100); 
    delay(100); 
    noTone(buzzer);
  } 
  

  int insize;	
  
  if ((insize=(I2CBT.available()))>0){  //讀取藍牙訊息
    //Serial.print("input size = ");
    //Serial.println(insize);
    //Serial.print("\n");

    for (int i=0; i<insize; i++){
      Serial.println(cmmd[cmmdi]=char(I2CBT.read()));

      if(cmmd[cmmdi] == '\0'){
        Serial.println(">>function=");
        Serial.println(cmmd);
        if(strcmp(cmmd, "ALARM") == 0){
          alarm = 1;
        }else if(strcmp(cmmd, "STOP") == 0){
          Serial.println("stop!!!!!!!");
          alarm = 0;
          noTone(buzzer);
        }
        
        cmmdi = 0;
      }else{
        cmmdi++;
      }
    }//此段請參考上一篇解釋

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
