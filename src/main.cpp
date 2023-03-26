/*
by: Junior Guilherme
*/
/*
   Primeiro Byte: tipo de msg: 'i' - Informação
                               'a' - Acknowledgement 
   Segundo Byte:  Endereço
   Terceiro Byte: Payload:     's' - início
*/

#include <Arduino.h>
#include <string.h>
//Constantes
//Endereços
#define ENDERECO 0
#define ENDBOMBA 1
#define ENDCAIXA 2

//Tipos de pacotes
#define ACK    0  //resposta
#define NIVELC 1  //nível da caixa
#define NIVELB 2  //Nível da Bateria
#define COMB   3  //Comando para ligar ou desligar bomba
#define RESPB  4  //Resposta de aviso de ligação ou desligamento da bomba



//StatusMod
#define LIVRE  1
#define OCUPADO  0

//Pinagem
#define AUX 4
#define M0  2
#define M1  3

//Variáveis globais
bool estadoAux = 0;
bool state = 0;
uint8_t cont = 0;
uint16_t cont2 = 0;
char c = ' ';
String info = "";
uint8_t inf[6];
char aux[2];
uint8_t nivelC =7;
uint8_t endO= ENDERECO;
uint8_t endD=0;
uint8_t idMsg = 0;

typedef struct{
  uint8_t destino;
  uint8_t origem;
  uint8_t tipo;
  uint8_t *payload;
  uint8_t verificacao;
}pacote;
pacote msg1;
pacote montaPack(uint8_t *vetor);

// the setup function runs once when you press reset or power the board
void setup() {  
  pinMode(AUX, INPUT);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial3.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
if(Serial.available()){
  int i=0;
  while(Serial.available()){
        c=uint8_t(Serial.read()-uint8_t(32)); 
        inf[i]=c;
        //if(c!='\n') inf[i]=c;
        //else inf[i]= '\0';
        i++;
        delay(10);  
     }
     montaPack(inf);
  msg1 = montaPack(inf);
  Serial.print("Destino: ");
  Serial.print(msg1.destino, HEX);
  Serial.println();
  Serial.print("Origem: ");
  Serial.print(msg1.origem, HEX);
  Serial.println();
  Serial.print("Tipo: ");
  Serial.print(msg1.tipo, HEX);
  Serial.println();
  Serial.print("payload: ");
  Serial.write(msg1.payload[0]+uint8_t(32));
  Serial.println();
  Serial.print("Verificação: ");
  Serial.write(msg1.verificacao+uint8_t(32));
  Serial.println();

   Serial.println();
    Serial.println();
    Serial.println();
  
    
     //Serial.println(byte(msg1.destino));
     /*
      if(msg1.destino==endO){//se sim, significa que o remetente é esta estação
      Serial.println("processar");
      if(msg1.origem == ENDCAIXA){
        nivelC=msg1.payload;        
      }
     */
   
    }
  delay(500);
  digitalWrite(LED_BUILTIN, state);
  state=!state;
}
//mensagem msgVolta;
//msgVolta.destino=msg1.origem;
//msgVolta.origem=endO;
//msgVolta.   msg1.numMsg;

  



pacote montaPack(uint8_t *vetor){
  pacote pack;
  pack.destino = vetor[0];
  pack.origem =  vetor[1];
  pack.tipo   =  vetor[2];

  if((pack.tipo>=0)&(pack.tipo<=4)){//Se for um desses o payload tem 1 Byte
    pack.payload[0] = vetor[3];
    pack.verificacao = vetor[4];
  }
  return(pack);

}


/*

     Serial.println(strncmp(inf, , 1));

     if (!strncmp(inf, "i", 1)){
       uint8_t Origem= uint8_t(inf[1]-'0');
       uint8_t = uint8_t(inf[1]-'0');
     }





if(Serial3.available()){
    while(Serial3.available()){
      c=Serial3.read(); 
      delay(10);      
      info+=c;
    }
    Serial.println(info);
    info = "ACK: " + info;
    Serial3.println(info);
    info = "";
  }






/*
//LEITURA DE COMANDO VIA SERIAL
if(Serial.available()){
  int i=0;
  while(Serial.available()){
        c=Serial.read(); 
        if(c!='\n') inf[i]=c;
        else inf[i]= '\0';
        i++;
        delay(10);  
     }
     
     Serial.println(inf);

     Serial.println(strncmp(inf, "oi", 2));
     if (!strncmp(inf, "oi", 2)){

       digitalWrite(LED_BUILTIN, 1);
       strcpy(inf, "");
       //inf= "";
       inf[0] = 'i';
       inf[1] = '0' + endO;
       inf[2] = '0' + endD;
       inf[3] = '0'+ idMsg;
       inf[4] = 's';
       inf[5] = '\0';
       idMsg++;

       Serial.println(inf);
       //Serial3.println(info);
       delay(2000);
       digitalWrite(LED_BUILTIN, 0);
     }

     if (!strncmp(inf, "send", 4)){

       digitalWrite(LED_BUILTIN, 0);
       strcpy(inf, "");
       //inf= "";
        inf[0] = 'i';
       inf[1] = '0' + endO;
       inf[2] = '0' + endD;
       inf[3] = '0'+ idMsg;
       inf[4] = '0'+ nivelC;
       inf[5] = '\0';
       idMsg++;
       //Serial3.println(info);
       delay(2000);
       digitalWrite(LED_BUILTIN, 1);
     }



}


digitalWrite(LED_BUILTIN, state);
  delay(500);
  state=!state;
}










/*SE O MICROCONTROLADOR RECEBER ALGO DO SERIAL MONITOR:
A informação é lida e enviada para o módulo pela Serial3
*/
/*
  info = "";
  if(Serial.available()){
    if(verEstado()==LIVRE){
        while(Serial.available()){
        c=Serial.read(); 
        info+=c;
        delay(10);  
     }
     Serial3.println(info);
     while(!Serial3.available()){             //  Aguarda enquanto o módulo a outra entidade não responde
       //Serial.println("Aguardando...");
       delay(5); 
     }
    info = ""; 
    while(Serial3.available()){               //  Quando responde ele lê e printa na tela a resposta
      c=Serial3.read(); 
      delay(10);      
      info+=c;
    }
    Serial.println(info);
    info = "";   
    }
  }


/*SE O MICROCONTROLADOR RECEBER ALGO DO MÓDULO PELA SERIAL3:
A informação é lida e enviada para ser exibida via monitor serial
É devolvido um ACK com a informação enviada de volta para confirmaçao de recebimento
*/
/*
  if(Serial3.available()){
    while(Serial3.available()){
      c=Serial3.read(); 
      delay(10);      
      info+=c;
    }
    Serial.println(info);
    info = "ACK: " + info;
    Serial3.println(info);
    info = "";
  }

  //PISCA LED
  digitalWrite(LED_BUILTIN, state);
  delay(500);
  state=!state;
}

uint8_t verEstado(){
  if(digitalRead(AUX)) return(LIVRE);
  else return(OCUPADO);
}


*/



