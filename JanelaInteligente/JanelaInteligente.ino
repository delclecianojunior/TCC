
void setup() {
  //InicializarPinosMotor();
  InicializarPinosSensorCuva();
  Serial.begin(9600);
}

void loop() {
  if (VerificarSeEstaChovendo()) {
    Serial.println("Esta chovendo...");
    // FecharJanela();
  } else {
    Serial.println("parou de chover...");
    //AbrirJanela();
    // PararMotor();
  }
}

void FecharJanela() {
  GirarParaDireita(2);
}

void AbrirJanela() {
  GirarParaEsquera(2);
}
