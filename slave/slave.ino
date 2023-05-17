#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <nRF24L01.h> //INCLUSÃO DE BIBLIOTECA
#include <RF24.h> //INCLUSÃO DE BIBLIOTECA
#include <Servo.h>

Servo servo; 

RF24 radio(9, 10); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CE, CSN)
const byte endereco[6] = "00001"; //CRIA UM ENDEREÇO PARA ENVIO DOS
//DADOS (O TRANSMISSOR E O RECEPTOR DEVEM SER CONFIGURADOS COM O MESMO ENDEREÇO)
int gotArray[4];
int pinoLed = 3; //PINO DIGITAL UTILIZADO PELO LED
int estadoBotao = 1; //VARIÁVEL PARA ARMAZENAR O ESTADO DO BOTÃO

void setup() {
  Serial.begin(9600);
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
  radio.begin(); //INICIALIZA A COMUNICAÇÃO SEM FIO
  radio.openReadingPipe(0, endereco);//DEFINE O ENDEREÇO PARA RECEBIMENTO DE DADOS VINDOS DO TRANSMISSOR
  radio.setPALevel(RF24_PA_HIGH); //DEFINE O NÍVEL DO AMPLIFICADOR DE POTÊNCIA
  radio.startListening(); //DEFINE O MÓDULO COMO RECEPTOR (NÃO ENVIA DADOS)

  //servo conexão
  servo.attach(5); 
}

void loop(){
  if (radio.available()){ //SE A COMUNICAÇÃO ESTIVER HABILITADA, FAZ
    radio.read(&gotArray, sizeof(gotArray)); // LÊ OS DADOS RECEBIDOS
  if(gotArray[0] == 0){ //SE O PARÂMETRO RECEBIDO (ESTADO ATUAL DO BOTÃO) FOR IGUAL A 0 (PRESSIONADO), FAZ
    digitalWrite(pinoLed, HIGH); //LIGA O LED
  }else{
          if(gotArray[0] == 1){ //SE O PARÂMETRO RECEBIDO (ESTADO ATUAL DO BOTÃO) FOR IGUAL A 1 (NÃO PRESSIONADO), FAZ
            digitalWrite(pinoLed, LOW); //DESLIGA O LED
        }
    }
  }
  Serial.println(gotArray[1]);
  Serial.println(gotArray[0]);
  delay(5); //INTERVALO DE 5 MILISSEGUNDOS
}
