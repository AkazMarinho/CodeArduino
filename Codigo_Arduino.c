#include <virtuabotixRTC.h> 

#define rele 5

#define clk 4
#define dat 3
#define rst 2

//Configuração de data
#define segL 55
#define minL 59
#define horL 7
#define d_semL 4
#define d_mesL 25
#define mesL 10
#define anoL 2023

//Declaração de objetos
virtuabotixRTC myRTC(clk, dat, rst);//declara no RTC
void DS1302();
void week(int dayW); //informa o dia sa semana com nime ao inves de numero
void ligaRele();

void setup() {
  Serial.begin(9600);
  myRTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);
  pinMode(rele, OUTPUT);
}

void loop() {
  DS1302();
}

void DS1302(){

  myRTC.updateTime();

  Serial.print(" -> ");
  week(myRTC.dayofweek);
  Serial.print(" | ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  if(myRTC.month < 10){
    Serial.print("0");
  }
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" | ");
  if(myRTC.hours < 10){
    Serial.print("0");
  }
  Serial.print(myRTC.hours);
  Serial.print(":");
  if(myRTC.minutes < 10){
    Serial.print("0");
  }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  if(myRTC.seconds < 10){
    Serial.print("0");
  }
  Serial.print(myRTC.seconds);
  Serial.print("\n");
  ligaRele();
  delay(1000);
}

void week(int dayW){
  
  switch(dayW){
    case 1: 
      Serial.print("Domingo");
      break;
    case 2: 
      Serial.print("Segunda");
      break;
    case 3: 
      Serial.print("Terça");
      break;
    case 4: 
      Serial.print("Quarta");
      break;
    case 5: 
      Serial.print("Quinta");
      break;
    case 6: 
      Serial.print("Sexta");
      break;
    case 7: 
      Serial.print("Sabado");
      break;
  }
}

void ligaRele(){
  myRTC.updateTime();
  if(myRTC.hours == 8 && myRTC.minutes == 0 && myRTC.seconds == 0){
    digitalWrite(rele, HIGH);
    Serial.print("Ativado\n");
    delay(7000);
    digitalWrite(rele, LOW);
    Serial.print("Desativado\n");
  }

  if(myRTC.hours == 8 && myRTC.minutes == 0 && myRTC.seconds == 8){
    digitalWrite(rele, LOW);
    Serial.print("Desativação de segurança\n");
  }

  if(myRTC.hours == 16 && myRTC.minutes == 0 && myRTC.seconds == 0){
    digitalWrite(rele, HIGH);
    Serial.print("Ativado\n");
    delay(7000);
    digitalWrite(rele, LOW);
    Serial.print("Desativado\n");
  }

  if(myRTC.hours == 16 && myRTC.minutes == 0 && myRTC.seconds == 8){
    digitalWrite(rele, LOW);
    Serial.print("Desativação de segurança\n");
  }
}


