#include <QTRSensors.h>
#define MOT_A1_PIN 3
#define MOT_A2_PIN 4
#define MOT_B1_PIN 5 
#define MOT_B2_PIN 6

const uint8_t maxspeeda = 120;
const uint8_t maxspeedb = 120;
const uint8_t basespeeda = 105;
const uint8_t basespeedb = 105;

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

int lastError = 0;

float Kp = 0.1;
float Ki = 0.0;
float Kd = 0.0;
int P;
int I;
int D;


void setup() {
  Serial.begin(9600);
  qtr.setTypeRC();
  //Set up the sensor array pins
  qtr.setSensorPins((const uint8_t[]){14, 15, 16, 17, 18, 19, 12,13}, SensorCount);
  
  qtr.setEmitterPin(2);//LEDON PIN

  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  pinMode(MOT_B1_PIN, OUTPUT);
  pinMode(MOT_B2_PIN, OUTPUT);

  delay(500);
  calibration();
}

void calibration() {
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  digitalWrite(IN1_PIN, HIGH);
  analogWrite(IN2_PIN, pwm);
}

void speedcontrol(int mota, int motb) {
  if (mota >= 0 && motb >= 0) {
    set_motor_pwm(mota, MOT_A1_PIN, MOT_A2_PIN);
    set_motor_pwm(motb, MOT_B1_PIN, MOT_B2_PIN);
  }
  if (mota < 0 && motb >= 0) {
    //dreapta
    mota = 0 - mota;
    set_motor_pwm(mota, MOT_A1_PIN, MOT_A2_PIN);
    set_motor_pwm(motb, MOT_B1_PIN, MOT_B2_PIN);
  }
  if (mota >= 0 && motb < 0) {
    //stanga
    motb = 0 - motb;
    set_motor_pwm(mota, MOT_A1_PIN, MOT_A2_PIN);
    set_motor_pwm(motb, MOT_B1_PIN, MOT_B2_PIN);
  }
}


void loop() {
  int poz = qtr.readLineBlack(sensorValues);
  Serial.println(poz);
  int error = poz - 4000;
  P = error;
  D = error - lastError;
  lastError = error;
  I = I + error;
  
  int motorspeed = Kp * error + Ki * I +  Kd * D;
  
  int motorspeeda = basespeeda + motorspeed;
  int motorspeedb = basespeedb - motorspeed;
  
  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = 0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  } 

  speedcontrol(motorspeeda, motorspeedb);

}
