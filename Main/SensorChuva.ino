int pinoSensorUmidade = 1;

bool VerificarSeEstaChovendo(){
  int valorUmidade = analogRead(pinoSensorUmidade);

  if(valorUmidade > 270)
    return true;
  return false;  
}
