#include <Servo.h>
#include <Arduino.h>
#define LINE_A A5 // IZQUIERDO
#define LINE_B A4// DERECHO 
#define RIGHT A3
#define FRONT_A A2 // ENFRENTE DERECHP2
#define FRONT_B A1 // ENFRENTE IZQUIERDO1
#define LEFT A0
#define SERVO 9 //servo izquierda
#define SERVO2 10
int Mder1 = 3;    //motor 1 izqueirda bn1
int Mder2 = 5;   // MOTOR 1 IZQUIERDA bni1
int Mizq1 = 6;
int Mizq2 = 11;
int led = 4;
int led2 = 12;
int led3 = 13;
#define REMOTE 7

Servo FLAG;

Servo FLAG2;

int sensorState;
int lineState;



void setup() {
  FLAG.attach(SERVO);
  FLAG2.attach(SERVO2);
  pinMode(LINE_A, INPUT);
  pinMode(LINE_B, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(FRONT_A, INPUT);
  pinMode(FRONT_B, INPUT);
  pinMode(Mizq1, OUTPUT);
  pinMode(Mizq2, OUTPUT);
  pinMode(Mder1, OUTPUT);
  pinMode(Mder2, OUTPUT);
  pinMode(REMOTE, INPUT);
    pinMode(led,OUTPUT);
    pinMode(led2,OUTPUT);
      pinMode(led3,OUTPUT);
  Serial.begin(9600);


  FLAG.write(85);
  FLAG2.write(105);
}

void loop() {

  Serial.println(digitalRead(REMOTE));

  while (digitalRead(REMOTE) == 1) //mientras esta activo el arrancador poner la bandera a 20 grados y ejecutar battle
  {
    FLAG.write(170); //servo izquierda
    FLAG2.write(10);
    sensorState = sensorValue();
    lineState = lineValue();



    switch (lineState) {
      case 41:
        Serial.print("negro - ");

        switch (sensorState) {

          case 1:  //DETECTA SENSOR ENFRENTE DERECHA.
            Serial.println("caso  1");
            derecha(200, 200); //gira con muy poca potencia a la derecha
            delay(20);
            paro();
            delay(10);
            
            break;

          case 2: //DETECTA SENSOR ENFRENTE IZQUIERDA.
            Serial.println("caso 2 ");
            izquierda(200, 200);
            delay(20);//gira con poca potencia a la izquierda
            paro();
            delay(10);
            
            break;

          case 3: //DETECTA DOBLE SENSOR ENFRENTE.
            Serial.println("caso  3");

                          digitalWrite(led3,HIGH);
            delay(5);
            adelante (255, 255);
            delay(30);
            paro();
            delay(10);
            
                                          digitalWrite(led3,LOW);
            delay(5);

            break;

          case 4: //DETECTA SOLO SENSOR DERECHO.
            Serial.println("caso  4");
            digitalWrite(led,HIGH);
            delay(5);
            derecha(230, 230); //gira casi full a la derecha.
            delay(20);
            paro();
            delay(10);
                        digitalWrite(led,LOW);
            delay(5);
            break;

          case 5: //DETECTA ENFRENTE DERECHA Y DERECHA.
            Serial.println("caso  5");
                                      digitalWrite(led3,HIGH);
            delay(5);
                        digitalWrite(led,HIGH);
            delay(5);

            derecha(200, 200); //gira con poca potencia a la derecha
            delay(20);
            paro();
            delay(10);
                        
                                          digitalWrite(led3,LOW);
            delay(5);
                                    digitalWrite(led,LOW);
            delay(5);
            
            break;

          case 8: //DETECTA SOLO SENSOR IZQUIERDO
            Serial.println("caso  8");

                        digitalWrite(led2,HIGH);
            delay(5);

            izquierda(230, 230); //gira casi full a la izquierda
            delay(20);
            paro();
            delay(10);

                                    digitalWrite(led2,LOW);
            delay(5);
            
            break;

          case 10:  //DETECTA ENFRENTE IZQUIERDA E IZQUIERDA.
            Serial.println("caso  10");
                                                  digitalWrite(led3,HIGH);
            delay(5);
                                    digitalWrite(led2,HIGH);
            delay(5);
            izquierda(200, 200); //gira con poca potencia a la izquierda
            delay(20);
            paro();
            delay(10);

                                                      digitalWrite(led3,LOW);
            delay(5);
                                                digitalWrite(led2,LOW);
            delay(5);
            break;

          case 15:  //DETECTAN TODOS, 1vs10000 kmara qleros, manos les van a faltar para pelarme la verga.
            Serial.println("caso Todos");
            derecha(130, 130); //torbellino mortal a la derecha, impactrueno.
            delay(50);
            
            
            break;

          case 11: // 3 sensores izquierda
            Serial.println("caso 11");
            izquierda(255, 255); //vueltas izquierda contra banderas
            delay(20);
            paro();
            delay(10);
            
            break;

          case 7: //3 sensores derecha
            Serial.println("caso 12");
            derecha(255, 255); // vueltas derecha contra banderas
            delay(20);
            paro();
            delay(10);
            
            break;

          default:
            Serial.println("yyyyy"); //NO DETECTA yyyyyyyy numero izquierda motor izquierda

            adelante (10, 11); // valor derecha es motor izquierdo
            delay(30);
            paro();
            delay(20);
            
            break;
        }
        break;

      case 20:
        Serial.println("Blanco 1");
        atras(255, 255);
        delay(90);
        paro();
        izquierda(255, 255);
        delay(200);
        paro();
        delay(200);
        
        break;

      case 21:
        Serial.println("Blanco 2");
        atras(255, 255);
        delay(90);
        paro();
        derecha(255, 255);
        delay(200);
        paro();
        delay(200);
        
        break;

      case 0:
        Serial.println("Blanco doble");
        atras(250, 250);
        delay(40);
        izquierda(255, 255);
        delay(240);
        paro();
        delay(200);
        
        break;

      default:
        Serial.println("Line default");
        
        break;
    }
  }
  paro ();
  FLAG.write(85);

}

// --------------- Funciones de sensores --------------- .

int sensorValue() {
  int sens1 = digitalRead(FRONT_A) * 1;// enfrente derecho 
  int sens2 = digitalRead(FRONT_B) * 2;
  int sens3 = digitalRead(RIGHT) * 4;
  int sens4 = digitalRead(LEFT) * 8;
  int total = sens1 + sens2 + sens3 + sens4;
  return total;
}

int lineValue() {
  int line1 = digitalRead(LINE_A) * 20;
  int line2 = digitalRead(LINE_B) * 21;
  int total = line1+line2 ;
  return 41;
}


// --------------- Funciones de motores --------------- .

void adelante(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255

  analogWrite(Mder1, potenciaDerecha);
                  digitalWrite(Mder2, LOW);
  analogWrite(Mizq1, potenciaIzquierda);
                    digitalWrite(Mizq2, LOW);
}
void atras(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255
  analogWrite(Mder2, potenciaDerecha);
    
  analogWrite(Mizq2, potenciaIzquierda);

}
void paro() {
  digitalWrite(Mder1, LOW);
  digitalWrite(Mder2, LOW);
  digitalWrite(Mizq1, LOW);
  digitalWrite(Mizq2, LOW);
}

void izquierda(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255

  analogWrite(Mder1, potenciaDerecha);
                             digitalWrite(Mder2, LOW);
                          digitalWrite(Mizq1, LOW);
  analogWrite(Mizq2, potenciaIzquierda);
}

void derecha(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255

                     digitalWrite(Mder1, LOW);
  analogWrite(Mder2, potenciaDerecha);
  analogWrite(Mizq1, potenciaIzquierda);
                       digitalWrite(Mizq2, LOW);
}
