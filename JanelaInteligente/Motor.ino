
int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;
int delayTime = 10;

void InicializarPinosMotor(){
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void GirarParaDireita(int delayTime){
  EnergizarPinos(HIGH,LOW,LOW, LOW);
  delay(delayTime);
  EnergizarPinos(LOW,HIGH,LOW, LOW);
  delay(delayTime);
  EnergizarPinos(LOW,LOW,HIGH, LOW);
  delay(delayTime);
  EnergizarPinos(LOW,LOW,LOW, HIGH);
  delay(delayTime);
}

void GirarParaEsquera(int delayTime){
  EnergizarPinos(LOW,LOW,LOW, HIGH);
  delay(delayTime);
  EnergizarPinos(LOW,LOW,HIGH,LOW);
  delay(delayTime);
  EnergizarPinos(LOW,HIGH,LOW,LOW);
  delay(delayTime);
  EnergizarPinos(HIGH,LOW,LOW,LOW);
  delay(delayTime); 
}

void PararMotor(){
  EnergizarPinos(LOW,LOW,LOW, LOW);
}

void EnergizarPinos(int statusPino1, int statusPino2, int statusPino3, int statusPino4){
  digitalWrite(motorPin1, statusPino1);
  digitalWrite(motorPin2, statusPino2);
  digitalWrite(motorPin3, statusPino3);
  digitalWrite(motorPin4, statusPino4);
}
