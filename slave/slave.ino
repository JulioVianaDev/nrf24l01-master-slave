#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA

RF24 radio(9, 10); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)
const byte endereco[6] = "00001"; //CRIA UM ENDEREÇO PARA ENVIO DOS
//DADOS (O TRANSMISSOR E O RECEPTOR DEVEM SER CONFIGURADOS COM O MESMO ENDEREÇO)

int pinoLed = 3; //PINO DIGITAL UTILIZADO PELO LED
int estadoBotao = 1; //VARIÁVEL PARA ARMAZENAR O ESTADO DO BOTÃO

void setup() {
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openReadingPipe(0, endereco);//DEFINE O ENDEREÇO PARA RECEBIMENTO DE DADOS VINDOS DO TRANSMISSOR
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.startListening(); //DEFINE O MÓDULO COMO RECEPTOR (NÃO ENVIA DADOS)
}

void loop(){
  if (radio.available()){ //SE A COMUNICAÇÃO ESTIVER HABILITADA, FAZ
    char text[32] = ""; //VARIÁVEL RESPONSÁVEL POR ARMAZENAR OS DADOS RECEBIDOS
    radio.read(&estadoBotao, sizeof(estadoBotao)); // LÊ OS DADOS RECEBIDOS
    
  if(estadoBotao == 0){ //SE O PARÂMETRO RECEBIDO (ESTADO ATUAL DO BOTÃO) FOR IGUAL A 0 (PRESSIONADO), FAZ
    digitalWrite(pinoLed, HIGH); //LIGA O LED
  }else{
        if(estadoBotao == 1){ //SE O PARÂMETRO RECEBIDO (ESTADO ATUAL DO BOTÃO) FOR IGUAL A 1 (NÃO PRESSIONADO), FAZ
        digitalWrite(pinoLed, LOW); //DESLIGA O LED
        }
    }
  }
  delay(5); //INTERVALO DE 5 MILISSEGUNDOS
}
