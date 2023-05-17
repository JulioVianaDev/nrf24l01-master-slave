#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA
#include <ResponsiveAnalogRead.h>

int Array[4];

RF24 radio(9, 10); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)     
const byte endereco[6] = "00001"; //CRIA UM ENDEREÇO PARA ENVIO DOS
//DADOS (O TRANSMISSOR E O RECEPTOR DEVEM SER CONFIGURADOS COM O MESMO ENDEREÇO)

int pinoBotao = 2; //PINO DIGITAL UTILIZADO PELO BOTÃO
int estadoBotao = 0; //VARIÁVEL PARA ARMAZENAR O ESTADO DO BOTÃO

const int ANALOG_PIN = A0;

ResponsiveAnalogRead analog(ANALOG_PIN, true);

void setup() {
  pinMode(pinoBotao, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
    //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openWritingPipe(endereco); //DEFINE O ENDEREÇO PARA ENVIO DE DADOS AO RECEPTOR
  radio.setPALevel(RF24_PA_HIGH);  //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.stopListening(); //DEFINE O MÓDULO COMO TRANSMISSOR (NÃO RECEBE DADOS)
  Serial.begin(9600);
}
 
void loop(){
  analog.update();
  int anguloFiltrado = analog.getValue();
  int angleFiltradoConvertido=map(anguloFiltrado, 0, 1023, 0, 180);
  Array[1] = angleFiltradoConvertido;
  //Serial.println(Array[1]);
  Serial.print(analogRead(5));
  Serial.print("\t");
  Serial.println(anguloFiltrado);
  if(digitalRead(pinoBotao) == HIGH){ //SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ
    estadoBotao = 0; //VARIÁVEL RECEBE VALOR 1 
    Array[0] = estadoBotao;
    radio.write(&Array, sizeof(Array)); //ENVIA AO RECEPTOR OS DADOS
  }else{ //SENÃO, FAZ
        if(digitalRead(pinoBotao) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
          estadoBotao = 1; //VARIÁVEL RECEBE VALOR 1 
          Array[0] = estadoBotao;
          radio.write(&Array, sizeof(Array)); //ENVIA AO RECEPTOR OS DADOS
        }
  }
  
}
