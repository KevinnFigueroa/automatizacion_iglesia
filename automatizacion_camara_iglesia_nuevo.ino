/*
  1- Al encender ambos motores giran en sentido -1 hasta que encuentran a sus respectivos finales de carrera.

  2- al mover el joystick en el eje x se mueve el motor x en hacia izquierda y derecha respectivamente.

  3- al mover el joystick en el eje y se mueve el motor y en hacia izquierda y derecha respectivamente.

  4- cada microstep que el joystick le indica al motor moverse se debe almacenar en un contador en la memoria como ultima ubicacion.

  5- al presionar el boton a por 5 segundos se debe asignar la ubicacion actual al dicho boton.

  6- al presionar y soltar el boton a se indicara a los motores que regresen a la ubicacion asignada a dicho boton.

  7- lo mismo sucedera con los botones b, c, d y e.

  MOVIMIENTO DE ZOOM

  8- al presionar el boton 1 se movera el servo 45º hacia la izquierda.

  9- al presionar el boton 2 se movera el servo 45º hacia la derecha.

  10- al presionar l boton 1 o 2 se almacenara el tiempo que ah sido pulsado y sera almacenado en la memoria como ubicacion.

  11- al presionar uno de los botones de memoria tambien se movera el servo a izquierda o derecha segun corresponda la cantidad de tiempo almacenada en dicho boton.
*/

#include <Stepper.h> // include stepper motor library

#define stepp 32// define number of steps per revolution

#define IN1  11 // define stepper motor control pins
#define IN2  10
#define IN3   9
#define IN4   8

#define IN11  7 // define stepper motor control pins
#define IN22  6
#define IN33  5
#define IN44  4

#define INButton1 12;
#define INButton2 13;
#define INButton3 14;
#define INButton4 15;

#define INFinalCareerX 16;
#define INFinalCareerY 17;

int demora = 20;       // demora entre pasos, no debe ser menor a 10 ms.

Stepper stepsx(stepp, IN4, IN2, IN3, IN1); // initialize stepper library
Stepper stepsy(stepp, IN44, IN22, IN33, IN11);

int joysx = A0; // joystick  output = A0
int joysy = A1;

void setup() {
  Serial.begin(9600);
  // todos los pines como salida

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(I11, OUTPUT);
  pinMode(IN22, OUTPUT);
  pinMode(IN33, OUTPUT);
  pinMode(IN44, OUTPUT);

  //botones como entradas
  pinMode(INButton1, INPUT);
  pinMode(INButton2, INPUT);
  pinMode(INButton3, INPUT);
  pinMode(INButton4, INPUT);

  //finales de carrera como entradas
  pinMode(INFinalCareer1, INPUT);
  pinMode(INFinalCareer2, INPUT);

  seekEndOfCareer();
}

void seekEndOfCareer() {
  bool finalCareerX = false;
  bool finalCareerY = false;

  for (int i = 0; i < 512 * 4; i++)
  {
    //Si todavia no llegó al final de carrera el motor "x"
    if (!finalCareerX) {
      //Motor 1
      stepsx.step(-1);
    }

    //Si todavia no llegó al final de carrera el motor "y"
    if (!finalCareerY) {
      //Motor 2
      stepsy.step(-1);
    }

    readingFinalOfCareerX = digitalRead(INFinalCareer1);
    readingFinalOfCareerY = digitalRead(INFinalCareer1);

    if (readingFinalOfCareerX == HIGH ) {
      finalCareerX = true;
    }

    if (readingFinalOfCareerY == HIGH ) {
      finalCareerY = true;
    }

    if (finalCareerX && finalCareerY) {
      return;
    }

   delay(demora);
  }
}

int countXSteps = 0;
int countYSteps = 0;

int savePositionXButton1 = 0;
int savePositionYButton1 = 0;

int savePositionXButton2 = 0;
int savePositionYButton2 = 0;

int savePositionXButton3 = 0;
int savePositionYButton3 = 0;

int savePositionXButton4 = 0;
int savePositionYButton4 = 0;

void loop() {
  INButton1Value = digitalRead(INButton1);
  INButton2Value = digitalRead(INButton2);
  INButton3Value = digitalRead(INButton3);
  INButton4Value = digitalRead(INButton4);

  if (INButton1Value == HIGH) {
    delay(5000);

    INButton1Value = digitalRead(INButton1);

    if (INButton1Value == HIGH) {
      //Guardamos la canttidad de pasos dados en x y en y
      savePositionXButton1 = countXSteps;
      savePositionYButton1 = countYSteps;
    } else {
      //Movemos la camara a la posicion guardada
      stepsx.step(savePositionXButton1);
      stepsy.step(savePositionYButton1);
    }

  }

  if (INButton2Value == HIGH) {
    delay(5000);

    INButton2Value = digitalRead(INButton2);

    if (INButton2Value == HIGH) {
      //Guardamos la canttidad de pasos dados en x y en y
      savePositionXButton2 = countXSteps;
      savePositionYButton2 = countYSteps;
    } else {
      //Movemos la camara a la posicion guardada
      stepsx.step(savePositionXButton2);
      stepsy.step(savePositionYButton2);
    }

  }

  if (INButton3Value == HIGH) {
    delay(5000);

    INButton3Value = digitalRead(INButton3);

    if (INButton3Value == HIGH) {
      //Guardamos la canttidad de pasos dados en x y en y
      savePositionXButton3 = countXSteps;
      savePositionYButton3 = countYSteps;
    } else {
      //Movemos la camara a la posicion guardada
      stepsx.step(savePositionXButton3);
      stepsy.step(savePositionYButton3);
    }
  }

  if (INButton4Value == HIGH) {
    delay(5000);

    INButton4Value = digitalRead(INButton4);

    if (INButton4Value == HIGH) {
      //Guardamos la canttidad de pasos dados en x y en y
      savePositionXButton4 = countXSteps;
      savePositionYButton4 = countYSteps;
    } else {
      //Movemos la camara a la posicion guardada
      stepsx.step(savePositionXButton4);
      stepsy.step(savePositionYButton4);
    }

  }

  // lee eje "x"
  int valx = analogRead(joysx); // read analog value from the joystick
  Serial.print(valx);

  // lee eje "y"

  int valy = analogRead(joysy); // read analog value from the joystick
  Serial.print(valy);

  if ( valx > 520 ) {

    /*
      int speed_ = map(valx, 550, 1023, 5, 500);
      stepsx.setSpeed(speed_);
    */

    stepsx.step(1);
    countXSteps += 1;

  } else if ( valx < 480 ) {

    /*
      int speed_ = map(valx, 550, 1023, 5, 500);
      stepsx.setSpeed(speed_);
    */

    stepsx.step(-1);
    countXSteps -= 1;

  }

  if ( valy > 520 ) {

    /*
      int speed_ = map(valy, 550, 1023, 5, 500);
      stepsy.setSpeed(speed_);
    */

    stepsy.step(1);
    countYSteps += 1;

  } else if ( valy < 480 ) {
    /*
      int speed_ = map(valy, 550, 1023, 5, 500);
      stepsy.setSpeed(speed_);
    */

    stepsy.step(-1);
    countYSteps -= 1;

  }
}
