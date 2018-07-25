// Entradas
const int sens_entr = 8;
const int sens_sai  = 9;

// Saídas
const int semaf_verde   = 5;
const int semaf_vermelho= 4;
const int canc_entr     = 2;
const int canc_sai      = 3;

// Corre aquado do reset( uma unica vez)
int e0,e1,e2,a,b,c;
int carro;
int mem;
void setup() 
{                
  
  Serial.begin(115200);
  
  // Definição de pinos como Entradas/Saidas.
  pinMode(semaf_verde, OUTPUT);     
  pinMode(semaf_vermelho, OUTPUT);     
  pinMode(canc_entr, OUTPUT);     
  pinMode(canc_sai, OUTPUT);     
  pinMode(sens_entr,INPUT_PULLUP); 
  pinMode(sens_sai,INPUT_PULLUP); 
  
  digitalWrite(semaf_verde, HIGH);
  digitalWrite(semaf_vermelho, HIGH);
  digitalWrite(canc_entr, HIGH);
  digitalWrite(canc_sai, HIGH);
  delay(1000);  //Espera 1000ms (1s)
  digitalWrite(semaf_verde, LOW);
  digitalWrite(semaf_vermelho, LOW);
  digitalWrite(canc_entr, LOW);
  digitalWrite(canc_sai, LOW);
  carro=0;
  e0=1;
}

// Sequencia de codigo que corre em ciclo
void loop() 
{
// Alinea A
//
//if(carro==0){
//digitalWrite(semaf_verde, HIGH);}
//if (digitalRead(sens_entr)==LOW && carro==0) {  // entrada ON
//  digitalWrite(canc_entr, HIGH);
//  a=1;
//  
//}
//if(digitalRead(sens_entr)==HIGH && a==1){
//  digitalWrite(canc_entr, LOW);
//  digitalWrite(semaf_verde, LOW);
//  digitalWrite(semaf_vermelho, HIGH);
//  b=1;  
//  carro=1;
// }
// if(digitalRead(sens_sai)==LOW && b==1){
//  digitalWrite(canc_sai, HIGH);
//  c=1;
//  }
//  if(digitalRead(sens_sai)==HIGH && c==1){
//  digitalWrite(canc_sai, LOW);
//  digitalWrite(semaf_vermelho, LOW);
//  digitalWrite(semaf_verde, HIGH);
//  c=0;
//  a=0;
//  b=0;
//  carro=0;
//  }
//  Serial.print  (digitalRead(sens_entr));
//  Serial.println(digitalRead(sens_sai));

//Alinea B
if(e0==1&&digitalRead(sens_entr)==LOW&&carro<5){
  e0=0;
  e1=1;
}
if(e1==1&&digitalRead(sens_entr)==HIGH){
  e1=0;
  e0=1;
}
if(e0==1&&digitalRead(sens_sai)==LOW&&carro>0){
  e0=0;
  e2=1;
}
if(e2==1&&digitalRead(sens_sai)==HIGH){
  e2=0;
  e0=1;
}
if(e0==1){
  digitalWrite(canc_entr,LOW);
  digitalWrite(canc_sai,LOW);
  mem=1;
}
if(e1==1){
  digitalWrite(canc_entr,HIGH);
  digitalWrite(canc_sai,LOW);
  if(mem==1){carro=carro+1;mem=0;}
}
if(e2==1){
  digitalWrite(canc_entr,LOW);
  digitalWrite(canc_sai,HIGH);
  if(mem==1){carro=carro-1;mem=0;}
}
if(carro<5){digitalWrite(semaf_verde,HIGH);digitalWrite(semaf_vermelho,LOW);}else{digitalWrite(semaf_verde,LOW);digitalWrite(semaf_vermelho,HIGH);}

//Alinea C
//if(e0==1&&digitalRead(sens_entr)==LOW&&carro<5){
//  delay(4990);
//  e0=0;
//  e1=1;
//}
//if(e1==1&&digitalRead(sens_entr)==HIGH){
//  e1=0;
//  e0=1;
//}
//if(e0==1&&digitalRead(sens_sai)==LOW&&carro>0){
//  delay(4990);
//  e0=0;
//  e2=1;
//}
//if(e2==1&&digitalRead(sens_sai)==HIGH){
//  e2=0;
//  e0=1;
//}
//if(e0==1){
//  digitalWrite(canc_entr,LOW);
//  digitalWrite(canc_sai,LOW);
//  mem=1;
//}
//if(e1==1){
//  digitalWrite(canc_entr,HIGH);
//  digitalWrite(canc_sai,LOW);
//  if(mem==1){carro=carro+1;mem=0;}
//}
//if(e2==1){
//  digitalWrite(canc_entr,LOW);
//  digitalWrite(canc_sai,HIGH);
//  if(mem==1){carro=carro-1;mem=0;}
//}
//if(carro<5){digitalWrite(semaf_verde,HIGH);digitalWrite(semaf_vermelho,LOW);}else{digitalWrite(semaf_verde,LOW);digitalWrite(semaf_vermelho,HIGH);}
//
Serial.println(carro);

delay(10);                             // 10 ms, manter esta linha
}
