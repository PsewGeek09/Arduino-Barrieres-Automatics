#include <HCSR04.h> //inclusion des libraries
#include <Servo.h>

HCSR04 hc1(A0, A1); //déclaration des broches des capteurs a ultrason
HCSR04 hc2(A2, A3);

Servo myservo;

bool BarriereOuverte; //Déclaration des variables
bool IsOpening;
int AngleOuvert = 180; //A vérifier
int AngleFermer = 0;
int pos = 0;
int DistanceDeclanchement = 20;
int pinEcho1 = A0;
int pinTrig1 = A1;
long temps1;
float distance1;
int pinEcho2 = A2;
int pinTrig2 = A3;
long temps2;
float distance2;
int LV = 8;
int LR = 7;


void OuvrirBarriere () {
  if (BarriereOuverte == false) {
    IsOpening = true;
    int AngleBarriere = AngleFermer;
    while (AngleBarriere < AngleOuvert) {
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
  if (BarriereOuverte = true) {
    IsOpening = true;
    int AngleBarriere = AngleOuvert;
    while (AngleBarriere > AngleFermer) {
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


int MesureEntree () {
  digitalWrite(pinTrig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig1, LOW);

  temps1 = pulseIn(pinEcho1, HIGH);

  temps1 = temps1 / 2;
  distance1 = (temps1 * 340) / 10000.0;
  Serial.print("Distance Entrée: ");
  Serial.print(distance1);
  Serial.println(" cm");
}


int MesureSortie () {
  digitalWrite(pinTrig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig2, LOW);

  temps2 = pulseIn(pinEcho2, HIGH);

  temps2 = temps2 / 2;
  distance2 = (temps2 * 340) / 10000.0;
  Serial.print("Distance Sortie: ");
  Serial.print(distance2);
  Serial.println(" cm");
}



/*********************************************************









*/
void setup() {
  /*************************************
     setup pour la mesure de la distance
  */
  pinMode(A1, OUTPUT);
  pinMode(pinEcho1, INPUT);
  pinMode(pinTrig2, OUTPUT);
  pinMode(pinEcho2, INPUT);  
  
  digitalWrite(pinTrig1, LOW);
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
  MesureSortie() ;
  if (distance1 < DistanceDeclanchement or distance2 < DistanceDeclanchement) {
    if (IsOpening == false) {
      if (BarriereOuverte == false) {
        OuvrirBarriere ();
      }

    }

  }
  else if ( BarriereOuverte == true) {
    FermeBarriere ();
    myservo.write(0);
  }
  delay(500);
    }
//© PsewGeek09
