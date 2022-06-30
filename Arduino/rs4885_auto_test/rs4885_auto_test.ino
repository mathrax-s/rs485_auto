#include <SoftwareSerial.h>

// 自分のID
#define myID 3


SoftwareSerial mySerial(10, 9); // RX, TX

void setup() {
  Serial.begin(57600);
  while (!Serial) {
  }
  Serial.println("Start ");
  pinMode(13, OUTPUT);
  mySerial.begin(57600);
}

void loop() {
  
  // 自分のIDを受け取ったら、LEDを光らせ、自分のIDを折り返し送信する
  // （自分のID以外は、LEDを消す）
  if (mySerial.available()) {
    int data = mySerial.read();
    delay(1);
    if(data == myID+'0'){
      digitalWrite(13,HIGH);
      mySerial.write(data);
    }else{
      digitalWrite(13,LOW);
    }
    Serial.write(data);
  }

  // シリアルモニタから、テスト送信してみる
  // 'a' .. .ID 1
  // 'b' ... ID 2
  // 'c' ... ID 3
  // 自分以外のID番号が、返ってくるはず
  if (Serial.available()) {
    int data = Serial.read();
    int senddata= 0;
    delay(1);
    if(data == 'a'){
      senddata ='1';
    }else if(data == 'b'){
      senddata ='2';
    }else if(data == 'c'){
      senddata ='3';
    }
    mySerial.write(senddata);
  }
}
