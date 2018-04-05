// RX 7
// TX 6
//Servo 8
// Moteur CC 9,10,11,12




#include <SoftwareSerial.h>  //Software Serial Port  
#define RxD 6    //Pin 6 pour RX, PB2 sur votre board, a brancher sur le TX du HC-06
#define TxD 7    //Pin 7 pour TX, PB3 sur votre board, a brancher sur le RX du HC-06
SoftwareSerial BTSerie(RxD,TxD);  

#include <Servo.h>
Servo myservo;

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
      myservo.attach(8);  // attaches the servo on pin 8 to the servo object
     
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


  
 char recvChar;  
  //On lit caractere par caractere sur le BTSerie et on affiche sur le Terminal Serie  
  if (BTSerie.available()) {  //Ces fonctions moteurCC sont valables pour le moteur avec la tige vers le haut
    recvChar = BTSerie.read();  
    if(recvChar == '1') { //Vodka cranberry
      servoMoteur();
      moteurCC2();
      delay(1000);
      servoMoteur();
      servoMoteur();
      servoMoteur();
      moteurCC2();
      delay(1000);
      servoMoteur();
      moteurCC2();
      delay(1000);
      
      
    }
    if(recvChar == '2') { //Bay Breeze
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
      servoMoteur();
      moteurCC_2();
      delay(1000);
    }

    if(recvChar == '3') { //Hole in one
      servoMoteur();
      moteurCC2();
      delay(1000);
      servoMoteur();
      servoMoteur();
      moteurCC3();
      delay(1000);
      servoMoteur();
      moteurCC1();
      delay(1000);
    }


    if(recvChar == '4') { //Hoola Hoop
      moteurCC_1();
      delay(1000);
      servoMoteur();
      moteurCC_2();
      delay(1000);
      servoMoteur();
      moteurCC_2();
      delay(1000);
      servoMoteur();
      moteurCC_1();
      delay(1000);
    }


    if(recvChar == '5') { //Gimlet
      moteurCC_2();
      delay(1000);
      servoMoteur();
      moteurCC_1();
      delay(1000);
      servoMoteur();
      servoMoteur();
      moteurCC3();
      delay(1000);
    }





    if(recvChar == '6') { //Screwdriver
      servoMoteur();
      moteurCC_1();
      delay(1000);
      servoMoteur();
      servoMoteur();
      servoMoteur();
      moteurCC1();
      delay(1000);
    }


    if(recvChar == '7') { //Supreme
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
      moteurCC1();
      delay(1000);
    }



    
    Serial.print(recvChar);  //ecriture
  }
  //On lit caractere par caractere sur le terminal et on affiche sur le BT Serie 
  if (Serial.available()) {  
    recvChar = Serial.read(); //lecture
    BTSerie.write(recvChar);  //ecriture
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
   for (int position=90; position<=145; position ++){
  myservo.write(position);
  delay(15);
  if (position==145){delay(2000);}
}
for (int position=145; position>=90; position --){
  myservo.write(position);
  delay(15);
}
}

void moteurCC1(){
  for(int x=0; x<1;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }
    Serial.println(x);
    delay(0);
  }
}


void moteurCC2(){
  for(int x=0; x<2;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }
    Serial.println(x);
    delay(0);
  }
}


void moteurCC3(){
  for(int x=0; x<3;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper();
      delay(1);
    }
    Serial.println(x);
    delay(0);
  }
}


void moteurCC_2(){
  for(int x=0; x<2;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper_();
      delay(1);
    }
    Serial.println(x);
    delay(0);
  }
}

void moteurCC_1(){
  for(int x=0; x<1;x++){
    for (int steps_left = 4095/6;  steps_left>0;  steps_left--){
      stepper_();
      delay(1);
    }
    Serial.println(x);
    delay(0);
  }
}
