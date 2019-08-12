#include <HCSR04.h> //inclusion des libraries
#include <Servo.h>

  HCSR04 hc1(A0,A1);//déclaration des broches des capteurs a ultrason
  HCSR04 hc2(A2,A3);

  Servo myservo;

  bool BarriereOuverte; //Déclaration des variables
  bool IsOpening;
  int AngleOuvert = 180; //A vérifier
  int AngleFermer = 0;
  int DistanceDeclanchement = 20;
  int pinTrig1 = A1;
  int pinEcho1 = A0;
  long temps;
  float distance;
  int pos = 0;
  int LV = 8;
  int LR = 7;
  

  void OuvrirBarriere (){
    if (BarriereOuverte == false){
      IsOpening = true;
      int AngleBarriere = AngleFermer;
        while (AngleBarriere < AngleOuvert){
          digitalWrite(LV, HIGH);
          delay(10);
          digitalWrite(LV, LOW);
          AngleBarriere ++;
          myservo.write(AngleBarriere);
        }
        BarriereOuverte = true;
        IsOpening = false;
        digitalWrite(LR, HIGH);
        digitalWrite(LV, LOW);
     }
  }


  void FermeBarriere () {
  if (BarriereOuverte = true){
    IsOpening = true;
    int AngleBarriere = AngleOuvert;
      while (AngleBarriere > AngleFermer){
      delay(10);
      AngleBarriere --;
      myservo.write(AngleBarriere);
      }
  BarriereOuverte = false;
  IsOpening = false;
  digitalWrite(LV, HIGH);
  digitalWrite(LR, LOW);
  
  }
  
  
  }


  int MesureEntree (){
    digitalWrite(pinTrig1, HIGH);        
  delayMicroseconds(10);
  digitalWrite(pinTrig1, LOW);

  temps = pulseIn(pinEcho1, HIGH);    

    temps = temps/2;
    distance = (temps*340)/10000.0;                  
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(1000);
  }
/*********************************************************
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
void setup() {
  /*************************************
   * setup pour la mesure de la distance
   */
  pinMode(A1, OUTPUT);
  pinMode(pinEcho1, INPUT);

  digitalWrite(pinTrig1, LOW);
  Serial.begin(9600);
  myservo.attach(9);

  pinMode(LV, OUTPUT);
  pinMode(LR, OUTPUT);

  myservo.write(0);
  digitalWrite(LV, HIGH);
}

void loop() {
MesureEntree() ;
  if(distance < DistanceDeclanchement){
    if(IsOpening == false){
      if(BarriereOuverte == false){
        OuvrirBarriere ();
      }
      
    }
  }
      else{
       if( BarriereOuverte == true){
        FermeBarriere ();
        myservo.write(0);
       }
      }
}
