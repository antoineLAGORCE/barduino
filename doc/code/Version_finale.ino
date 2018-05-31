// RX 7
// TX 6
//Servo 8, 13
// Moteur CC 9,10,11,12




#include <SoftwareSerial.h>  //Software Serial Port  
#define RxD 6    //Pin 6 pour RX, PB2 sur votre board, a brancher sur le TX du HC-06
#define TxD 7    //Pin 7 pour TX, PB3 sur votre board, a brancher sur le RX du HC-06
SoftwareSerial BTSerie(RxD,TxD);  

#include <Servo.h>
Servo myservo;
Servo myservo2;

int Paso [ 8 ][ 4 ] 
   {  {1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {1, 0, 0, 1}
   };

#define IN1  12
#define IN2  11
#define IN3  10
#define IN4  9



int steps_left=4095/6;
boolean Direction = true;
int Steps = 0; // Define el paso actual de la secuencia
int x = 0;

void setup(){ 
     pinMode(IN1, OUTPUT);
     pinMode(IN2, OUTPUT);
     pinMode(IN3, OUTPUT);
     pinMode(IN4, OUTPUT);
     Serial.begin(9600);
      myservo.attach(8,0,180);  // attaches the servo on pin 8 to the servo object
      myservo.write(110);
      myservo2.attach(13,0,180);
      myservo2.write(0);
  
  pinMode(RxD, INPUT);  
  pinMode(TxD, OUTPUT); 
  BTSerie.begin(9600); 
    Serial.println("En attente de la commandes AT"); 
    delay(100);
  
  BTSerie.print("AT+VERSION");  //Demande le NÂ° de version 
  delay(1000);  

   }

void loop()
      {

  
 String recvChar;  
  //On lit caractere par caractere sur le BTSerie et on affiche sur le Terminal Serie  
  if (BTSerie.available()) {  //Ces fonctions moteurCC sont valables pour le moteur avec la tige vers le haut
    recvChar = BTSerie.readString();  
    
 

    
    if(recvChar == "vodka cranberry") { //Vodka cranberry
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      servoMoteur();
      servoMoteur();
      moteurCC_2();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
      Serial.println("Voila un vodka cranberry");
      
      }

      
    if(recvChar == "Bay breeze") { //Bay Breeze
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC_2();
      delay(1000);
      Serial.println("Voila un bay breeze");
    }

    if(recvChar == "all in one") { //Hole in one
      servoMoteur();
      moteurCC2();
      delay(1000);
      servoMoteur();
      servoMoteur();
      moteurCC3();
      delay(1000);
      servoMoteur();
      moteurCC_5();
      delay(1000);
      Serial.println("Voila un Hole in one");
    }


    if(recvChar == "hula hoop") { //Hoola Hoop
      moteurCC_1();
      delay(1000);
      servoMoteur();
      moteurCC2();
      delay(1000);
      servoMoteur();
      moteurCC2();
      delay(1000);
      servoMoteur();
      moteurCC_3();
      delay(1000);
      Serial.println("Voila un Hoola Hoop");
    }


    if(recvChar == "gimlet") { //Gimlet
      moteurCC3();
      delay(1000);
      servoMoteur();
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC_4();
      delay(1000);
      Serial.println("Voila un gimlet");
    }





    if(recvChar == "screwdriver") { //Screwdriver
      servoMoteur();
      moteurCC_1();
      delay(1000);
      servoMoteur();
      servoMoteur();
      servoMoteur();
      moteurCC1();
      delay(1000);
     Serial.println("Voila un screwdriver");
    }


    if(recvChar == "supreme") { //Supreme
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC_5 ();
      delay(1000);
      Serial.println("Voila un supreme");
    }



    
    Serial.println(recvChar);  //ecriture
  }
  //On lit caractere par caractere sur le terminal et on affiche sur le BT Serie 
  if (Serial.available()) {  
    recvChar = Serial.read(); //lecture
   // BTSerie.write(recvChar);  //ecriture
  }




}

void stepper()            //Avanza un paso
   {  digitalWrite( IN1, Paso[Steps][ 0] );
      digitalWrite( IN2, Paso[Steps][ 1] );
      digitalWrite( IN3, Paso[Steps][ 2] );
      digitalWrite( IN4, Paso[Steps][ 3] );

      SetDirection();
   }

void stepper_()            //Avanza un paso
   {  digitalWrite( IN1, Paso[Steps][ 3] );
      digitalWrite( IN2, Paso[Steps][ 2] );
      digitalWrite( IN3, Paso[Steps][ 1] );
      digitalWrite( IN4, Paso[Steps][ 0] );

      SetDirection();
   }


void SetDirection()
   {  
      if(Direction)
         Steps++;
      else
         Steps--;

      Steps = ( Steps + 8 ) % 8 ;
   }

void servoMoteur(){
   for (int position=110; position<=165; position ++){
  myservo.write(position);
  myservo2.write(position*1.2-110);
  delay(15);
  if (position==165){delay(2000);}
}
for (int position=165; position>=110; position --){
  myservo.write(position);
  myservo2.write(position*1.2-110);
  delay(15);
}
}

void moteurCC1(){
  for(int x=0; x<1;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }

    delay(0);
  }
}


void moteurCC2(){
  for(int x=0; x<2;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }

    delay(0);
  }
}


void moteurCC3(){
  for(int x=0; x<3;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }

    delay(0);
  }
}

void moteurCC4(){
  for(int x=0; x<4;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }

    delay(0);
  }
}


void moteurCC5(){
  for(int x=0; x<5;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }

    delay(0);
  }
}


void moteurCC_2(){
  for(int x=0; x<2;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper_();
      delay(1);
    }

    delay(0);
  }
}

void moteurCC_1(){
  for(int x=0; x<1;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper_();
      delay(1);
    }

    delay(0);
  }
}


void moteurCC_3(){
  for(int x=0; x<3;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper_();
      delay(1);
    }

    delay(0);
  }
}



void moteurCC_4(){
  for(int x=0; x<4;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper_();
      delay(1);
    }

    delay(0);
  }
}


void moteurCC_5(){
  for(int x=0; x<5;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper_();
      delay(1);
    }

    delay(0);
  }
}
