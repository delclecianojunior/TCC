int sensorChuvaPinD7 = 7;

void InicializarPinosSensorCuva() {
  pinMode(sensorChuvaPinD7, INPUT);
}

bool VerificarSeEstaChovendo() {
  int valorUmidadeDigital = digitalRead(sensorChuvaPinD7);

  if (valorUmidadeDigital <= 0)
    return true;

  return false;
}
