

void setup() {
 InicializarPinosMotor();
}

void loop() { 
  Serial.begin(9600);
  
  if(VerificarSeEstaChovendo()){
    FecharJanela();
  }else{
    AbrirJanela();
  }
}

void FecharJanela(){
   GirarParaDireita(2);
}

void AbrirJanela(){
   GirarParaEsquera(2);
}
