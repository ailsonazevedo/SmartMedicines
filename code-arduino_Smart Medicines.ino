#include <Wire.h>                                                           // biblioteca wire para o i2c
#include <EEPROM.h>                                                         // biblioteca EEPROM.
#include <DS1307.h>                                                         // biblioteca ds1307/3231.
#include <LiquidCrystal_I2C.h>                                              // biblioteca lcd i2c
#include <SoftwareSerial.h>                                                 // biblioteca para o módulo blueetoth

SoftwareSerial mySerial(10, 11);  // (TX 10  RX 11) PROTOBORD
char statusLed ='0';                                                      // variável para guardar a varíavel do vibracall.

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

#define botaoS 6                                                           // botão para ajuste.
#define botaoMais 4                                                        // botão incrementa.
#define botaoMenos 5                                                       // botão descrementa.
#define botaoMenu 3                                                        // botão menu.
#define botaoOff 2                                                         // botão desliga alarme.

#define led 7                                    // variável led.                         
#define led2 8                                   // variável led2.
#define led3 9                                   // variável led3.
#define led4 12                                  // variável led4.
#define led5 A0                                  // variável led5.
#define led6 A1                                  // variável led6.
#define led7 A2                                  // variável led7.
#define led8 A3                                  // variável led8.
#define buzzer 13                                // variavél buzzer.

int ajusterelogio;                              // variavel para ajustar a configuração relogio.
int quantidade = 8;                             // quantidade de menus da configuração relogio.

int ajusteMenu;                                 // variavel para ajustar o menu.
int quantidadeMenu = 8;                         // quantidade de menu.  

int min = 0;                                    // variavel minutos.
int sec = 0;                                    // variavel segundos.
int hour = 0;                                   // variavel horas.
int mon = 1;                                    // variavel mes.
int year = 1;                                   // variavel ano.
int date =1;                                    // variavel dia.
int dow = 1;                                    // variavel dia da semana.

char dateTime[20];                              // variavel rtc.
int RTCValues[7];                               // valores para a leitura do rtc(horas,minutos...etec).
 
boolean alarmeOn =  false;     // variavel alarme1 inicialmente 0.
boolean alarmeOn2 = false;    // variavel alarme2 inicialmente 0.
boolean alarmeOn3 = false;    // variavel alarme3 inicialmente 0.
boolean alarmeOn4=  false;     // variavel alarme4 inicialmente 0.
boolean alarmeOn5 = false;    // variavel alarme5 inicialmente 0.
boolean alarmeOn6 = false;    // variavel alarme6 inicialmente 0.
boolean alarmeOn7 = false;    // variavel alarme7 inicialmente 0.
boolean alarmeOn8 = false;    // variavel alarme8 inicialmente 0.
boolean alarmeOn9 = false;    // variavel alarme8 inicialmente 0.

char alarme[30];              // variavel para escrever o alarme.
 
 int modo = 0;                                     // variavél para fazer piscar alarme1.
int modo2 = 0;                                  // variavél para fazer piscar alarme2.
int modo3 = 0;                                  // variavél para fazer piscar alarme3.
int modo4 = 0;                                    // variavél para fazer piscar alarme4.
int modo5 = 0;                                  // variavél para fazer piscar alarme5.
int modo6 = 0;                                  // variavél para fazer piscar alarme6.
int modo7 = 0;                                  // variavél para fazer piscar alarme6
int modo8 = 0;                                  // variavél para fazer piscar alarme6

const int N=3;                                  // variavél para leitura do piscar alarme1.
const int N2=3;                                 // variavél para leitura do piscar alarme2.
const int N3=3;                                 // variavél para leitura do piscar alarme3.
const int N4=3;                                 // variavél para leitura do piscar alarme4.
const int N5=3;                                 // variavél para leitura do piscar alarme5.
const int N6=3;                                 // variavél para leitura do piscar alarme6.
const int N7=3;                                 // variavél para leitura do piscar alarme7.
const int N8=7;                                 // variavél para leitura do piscar alarme8.

int minutos_alarme1,horas_alarme1 = 0;                     // variavel do alarme1 inicialmente 0.
int minutos_alarme2,horas_alarme2 = 0;                     // variavel do alarme2 inicialmente 0.
int minutos_alarme3,horas_alarme3 = 0;                     // variavel do alarme3 inicialmente 0.
int minutos_alarme4,horas_alarme4 = 0;                     // variavel do alarme4 inicialmente 0.
int minutos_alarme5,horas_alarme5 = 0;                     // variavel do alarme5 inicialmente 0.
int minutos_alarme6,horas_alarme6 = 0;                     // variavel do alarme6 inicialmente 0.
int minutos_alarme7,horas_alarme7 = 0;                     // variavel do alarme7 inicialmente 0.
int minutos_alarme8,horas_alarme8 = 0;                     // variavel do alarme8 inicialmente 0.
int minutos_alarme9,horas_alarme9 = 0;                     // variavel do alarme8 inicialmente 0.

int contador_alarme1 = 59;                                 // variavél para desligar o alarme1 automatico.
int contador_alarme2 = 59;                                 // variavél para desligar o alarme2 automatico.
int contador_alarme3 = 59;                                 // variavél para desligar o alarme3 automatico.
int contador_alarme4 = 59;                                 // variavél para desligar o alarme4 automatico.
int contador_alarme5 = 59;                                 // variavél para desligar o alarme5 automatico.
int contador_alarme6 = 59;                                 // variavél para desligar o alarme6 automatico.
int contador_alarme7 = 59;                                 // variavél para desligar o alarme7 automatico.
int contador_alarme8 = 59;                                 // variavél para desligar o alarme8 automatico.
int contador_alarme9 = 59;    
byte sino[8] = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};                           // sino do alarme.
byte tempo[8] = {0x1f,0x11,0xa,0x4,0xa,0x1f,0x1f};                       // tempo do rtc.
byte gota[8] = {0x4,0x4,0xe,0xe,0x1f,0x1d,0x1b,0xe};                     // gota alarme.


void setup()
{ Serial.begin(9600);
  mySerial.begin(9600); 
  lcd.begin(16,2);                                         // inicia o lcd.
  DS1307.begin();                                          // inicia o rtc.
  lcd.createChar(0, sino);                                 // cria o sino como caracter 0.
  lcd.createChar(1, tempo);                                // cria o tempo como caracter 1.
  lcd.createChar(2, gota);                                 // cria a gota como caracter 2.
  
  pinMode(botaoS, INPUT);                                                      // botãoSet entrada.
  pinMode(botaoMais,INPUT);                                                    // botãoMais entrada.
  pinMode(botaoMenos, INPUT);                                                  // botãoMenos entrada.
  pinMode(botaoMenu, INPUT);                                                   // botaoMenu entrada.
  pinMode(botaoOff, INPUT);                                                    // botaoMenu entrada.
  pinMode(led, OUTPUT);                                                        // led1 saída. 
  digitalWrite(led, LOW);                                                      //led1 inicialmente desligado.
  pinMode(led2, OUTPUT);                                                       // led2 saída.
  digitalWrite(led2, LOW);                                                     //led2 inicialmente desligado.
  pinMode(led3, OUTPUT);                                                       // led3 saída.
  digitalWrite(led3, LOW);                                                     //led3 inicialmente desligado.
  pinMode(led4, OUTPUT);                                                       // led4 saída.
  digitalWrite(led4, LOW);                                                     //led4 inicialmente desligado.
  pinMode(led5, OUTPUT);                                                       // led5 saída.
  digitalWrite(led5, LOW);                                                     //led5 inicialmente desligado.
  pinMode(led6, OUTPUT);                                                       // led6 saída.
  digitalWrite(led6, LOW);                                                     //led6 inicialmente desligado.
  pinMode(led7, OUTPUT);                                                       // led5 saída.
  digitalWrite(led7, LOW);                                                     //led5 inicialmente desligado.
  pinMode(led8, OUTPUT);                                                       // led6 saída.
  digitalWrite(led8, LOW);                                                     //led6 inicialmente desligado.
  pinMode(buzzer, OUTPUT);                                                     // buzzer saída.
  saudacao(); }                                                                // chama a função saudação.

    void saudacao()                                                         // função saudação.
    {
     lcd.setCursor(4,1);                                                //seta o lcd na coluna 4, linha 1.
     lcd.print(" Aguarde ... ");
     lcd.setCursor(1,1);                                                //seta o lcd na coluna 2, linha 2.
     lcd.print(" Preparando RTC ");
     lcd.print((char)1); 
     delay(3000);                                                       //tempo de 3 segundos.
     lcd.clear();                                                       // limpa lcd.
     lcd.setCursor(0,0);                                                //seta o lcd na coluna 1, linha 2.
     lcd.print("Bem vindo,senhor!");                                   // escreve lcd.
     som();                                                             // chama a função som.
     lcd.clear();}                                                      // limpa lcd.
 
 void mostrarelogio(){                                                 // função mostrarelogio

     horas_alarme1 = EEPROM.read(1);                                   // Lê a hora do alarme 1 salvo na memória EEPROM.
     minutos_alarme1 = EEPROM.read(2);                                 // Lê o minuto do alarme 1 salvo na memória EEPROM.
     alarmeOn = EEPROM.read(3);                                        // Lê a condição(ON/OFF) do alarme 1 salvo na memória EEPROM.
     
     horas_alarme2 = EEPROM.read(5);                                   // Lê a hora do alarme 2 salvo na memória EEPROM.
     minutos_alarme2 = EEPROM.read(6);                                 // Lê o minuto do alarme 2 salvo na memória EEPROM.
     alarmeOn2 = EEPROM.read(7);                                       // Lê a condição(ON/OFF) do alarme 2 salvo na memória EEPROM.

      horas_alarme3 = EEPROM.read(9);                                  // Lê a hora do alarme 3 salvo na memória EEPROM.
      minutos_alarme3 = EEPROM.read(10);                               // Lê o minuto do alarme 3 salvo na memória EEPROM.
      alarmeOn3 = EEPROM.read(11);                                     // Lê a condição(ON/OFF) do alarme 3 salvo na memória EEPROM.

      horas_alarme4 = EEPROM.read(13);                                 // Lê a hora do alarme 4 salvo na memória EEPROM.
      minutos_alarme4 = EEPROM.read(14);                               // Lê o minuto do alarme 4 salvo na memória EEPROM.
      alarmeOn4 = EEPROM.read(15);                                     // Lê a condição(ON/OFF) do alarme 4 salvo na memória EEPROM. 
 
      horas_alarme5 = EEPROM.read(17);                                 // Lê a hora do alarme 5 salvo na memória EEPROM.
      minutos_alarme5 = EEPROM.read(18);                               // Lê o minuto do alarme 5 salvo na memória EEPROM.
      alarmeOn5 = EEPROM.read(19);                                     // Lê a condição(ON/OFF) do alarme 5 salvo na memória EEPROM. 

      horas_alarme6 = EEPROM.read(21);                                 // Lê a hora do alarme 6 salvo na memória EEPROM.
      minutos_alarme6 = EEPROM.read(22);                               // Lê o minuto do alarme 6 salvo na memória EEPROM.
      alarmeOn6 = EEPROM.read(23);                                     // Lê a condição(ON/OFF) do alarme 6 salvo na memória EEPROM.

      horas_alarme7 = EEPROM.read(25);                                 // Lê a hora do alarme 7 salvo na memória EEPROM.
      minutos_alarme7 = EEPROM.read(26);                               // Lê o minuto do alarme 7 salvo na memória EEPROM.
      alarmeOn7 = EEPROM.read(27);                                     // Lê a condição(ON/OFF) do alarme 7 salvo na memória EEPROM. 

      horas_alarme8 = EEPROM.read(29);                                 // Lê a hora do alarme 8 salvo na memória EEPROM.
      minutos_alarme8 = EEPROM.read(30);                               // Lê o minuto do alarme 8 salvo na memória EEPROM.
      alarmeOn8 = EEPROM.read(31);                                     // Lê a condição(ON/OFF) do alarme 8 salvo na memória EEPROM. 
      
      horas_alarme9 = EEPROM.read(33);                                 // Lê a hora do alarme 8 salvo na memória EEPROM.
      minutos_alarme9 = EEPROM.read(34);                               // Lê o minuto do alarme 8 salvo na memória EEPROM.
      alarmeOn9 = EEPROM.read(35);                                     // Lê a condição(ON/OFF) do alarme 8 salvo na memória EEPRO
      
     DS1307.getDate(RTCValues);                                                            // lê os valores salvos no 'RTCValues'.
     lcd.setCursor(5,1);                                                                   // seta cursor na coluna 5 e linha 2.
     sprintf(dateTime, "%02d:%02d:%02d", RTCValues[4], RTCValues[5], RTCValues[6]);        // escreve a hora ([4]= hora, [5] = munutos, [6]= minutos).
     lcd.print(dateTime);                                                                  // escreve a hora no lcd.

     lcd.setCursor(0,1);                                                                   //seta cursor na coluna 0 e linha 3.
     lcd.print("Data: ");                                                                  // escreve no lcd
     sprintf(dateTime,"%02d/%02d/20%02d", RTCValues[2], RTCValues[1], RTCValues[0]);       // escreve a data([2]= dia, [1] = mês, [0]= ano).
     lcd.print(dateTime);                                                                  // escreve a data no lcd.
    
     lcd.setCursor(8,1);                                                                  //seta cursor na coluna 16 e linha 2.     
     lcd.print(fromNumberToWeekDay(RTCValues[3], 2));                                      // escreve o dia da semana no lcd(dom,seg...) //1=EN; 2=PT; 

     lcd.setCursor(1,1);                                                                  //seta cursor na coluna 17 e linha 3. 
     lcd.print(fromNumberToMonth(RTCValues[1], 2));                                        // escreve o mês da semana no lcd(jan,fev...) //1=EN; 2=PT;

     if(alarmeOn == false && alarmeOn2==false && alarmeOn3==false && alarmeOn4==false && alarmeOn5==false && alarmeOn5==false && alarmeOn6 == false )  // se todos alarmes forem falsos.
       
       { lcd.setCursor(1,0);                     // seta cursor na coluna 1 e linha 0.
       lcd.print(" ");}                          // não escreve nada.
        
        else                                     // senão.
       { lcd.setCursor(1,0);                     // seta cursor na coluna 1 e linha 0.
         lcd.print((char)0);}                    // escreve o caracter 0.
       
       if (digitalRead(led) == HIGH) {          // se a leitura do led for verdadeira.
          lcd.clear();                          // limpa lcd.
          lcd.setCursor(1,1);                   // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");        // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,1);                   // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 1");}         // escreve no lcd.
                   
          if (digitalRead(led2) == HIGH) {        // se a leitura do led for verdadeira.
          lcd.clear();                            // limpa lcd.
          lcd.setCursor(1,1);                     // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");          // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,1);                     // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 2");}          // escreve no lcd.
                                   
          
          if (digitalRead(led3) == HIGH) {        // se a leitura do led for verdadeira.
          lcd.clear();                            // limpa lcd.
          lcd.setCursor(1,1);                     // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");          // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,1);                     // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 3");}          // escreve no lcd.
                   
          
          if (digitalRead(led4) == HIGH) {        // se a leitura do led for verdadeira.
          lcd.clear();                            // limpa lcd.
          lcd.setCursor(1,1);                     // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");          // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,1);                   // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 4"); }        // escreve no lcd.
                  
          
          if (digitalRead(led5) == HIGH) {          // se a leitura do led for verdadeira.
          lcd.clear();                          // limpa lcd.
          lcd.setCursor(1,1);                   // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");        // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,1);                   // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 5");}         // escreve no lcd.
                   
          
          if (digitalRead(led6) == HIGH) {      // se a leitura do led for verdadeira.
          lcd.clear();                          // limpa lcd.
          lcd.setCursor(1,1);                   // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");        // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,2);                   // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 6");}        // escreve no lcd.  
                   
          
          if (digitalRead(led7) == HIGH) {          // se a leitura do led for verdadeira.
          lcd.clear();                          // limpa lcd.
          lcd.setCursor(1,1);                   // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");        // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,2);                   // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 7");}         // escreve no lcd.
                  
          
          if (digitalRead(led8) == HIGH) {      // se a leitura do led for verdadeira.
          lcd.clear();                          // limpa lcd.
          lcd.setCursor(1,1);                   // seta cursor na coluna 2 e linha 1.
          lcd.print("Hora do Remedio ");        // escreve no lcd.
          lcd.print((char)2);
          lcd.setCursor(2,1);                   // seta cursor na coluna 2 e linha 2.
          lcd.print("COMPARTIMENTO 8");}}                                       // fim mostrarelogio.

        void som(){                              // função som
        
        tone(buzzer,660,100);                    // faz o buzzer tocar em uma frequencia de 660 hz em 100ms.
        delay(150);                              // tempo de 150ms.
         tone(buzzer,660,100);                   // faz o buzzer tocar em uma frequencia de 660 hz em 100ms.
        delay(300);                              // tempo de 300ms.
         tone(buzzer,660,100);                   // faz o buzzer tocar em uma frequencia de 660 hz em 100ms.
        delay(300);                              // tempo de 300ms.
         tone(buzzer,510,100);                   // faz o buzzer tocar em uma frequencia de 510 hz em 100ms.
        delay(100);                              // tempo de 100ms.
         tone(buzzer,660,100);                   // faz o buzzer tocar em uma frequencia de 660 hz em 100ms.
        delay(300);                              // tempo de 300ms.
         tone(buzzer,770,100);                   // faz o buzzer tocar em uma frequencia de 770 hz em 100ms.
        delay(550);                              // tempo de 550ms.
        }                                        //fim som.
    
  void loop()
{
  if (mySerial.available()){
    Serial.write( mySerial.read());
 }
 
 if (Serial.available()){
    mySerial.write(Serial.read());
 }
  
  statusLed ='0';
         
          while(digitalRead(led) == HIGH){
          mySerial.write('1');
          delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
          lcd.clear();
          digitalWrite(buzzer,LOW);                              // desliga o buzzer.
          digitalWrite(led,LOW);}}

          while(digitalRead(led2) == HIGH){
            mySerial.write('1');
            delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
            lcd.clear();
            digitalWrite(buzzer,LOW);                              // desliga o buzzer.
            digitalWrite(led2,LOW);}}

          while(digitalRead(led3) == HIGH){
            mySerial.write('1');
            delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
            lcd.clear();
            digitalWrite(buzzer,LOW);                              // desliga o buzzer.
            digitalWrite(led3,LOW);}}
  
          while(digitalRead(led4) == HIGH){
            mySerial.write('1');
            delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
            lcd.clear();
              digitalWrite(buzzer,LOW);                              // desliga o buzzer.
              digitalWrite(led4,LOW);}}

          while(digitalRead(led5) == HIGH){
            mySerial.write('1');
            delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
            lcd.clear();
            digitalWrite(buzzer,LOW);                              // desliga o buzzer.
            digitalWrite(led5,LOW);}}

          while(digitalRead(led6) == HIGH){
            mySerial.write('1');
            delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
            lcd.clear();
            digitalWrite(buzzer,LOW);                              // desliga o buzzer.
            digitalWrite(led6,LOW);}}
  
          while(digitalRead(led7) == HIGH){
            mySerial.write('1');
            delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
            lcd.clear();
            digitalWrite(buzzer,LOW);                              // desliga o buzzer.
            digitalWrite(led7,LOW);}}

          while(digitalRead(led8) == HIGH){
            mySerial.write('1');
            delay(3);
          if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
            lcd.clear();                                          // limpa lcd.
            digitalWrite(buzzer,LOW);                             // desliga o buzzer.
            digitalWrite(led8,LOW);}}                             // desliga o led.

         
  if(alarmeOn == true){                                                                              // se o alarme1 for verdadeiro e... 
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme1 && RTCValues[5] == minutos_alarme1){     // se as variaveis forem igual ao relogio.
         digitalWrite(buzzer,HIGH);                              // liga o buzzer.
         digitalWrite(led,HIGH);
         
         }                               // liga o led.
         
         if(contador_alarme1 == RTCValues[6]){                   // se os segundos for igual a 59
          digitalWrite(buzzer,LOW);  }                           // desliga o  buzzer.
       
         if (digitalRead(botaoOff) == HIGH) {                  // se o botaoMenos for pressionado.
          lcd.clear();
          digitalWrite(buzzer,LOW);                              // desliga o buzzer.
          digitalWrite(led,LOW);}                                   // desliga o led.
      }      // fim do alarme 1

if(alarmeOn2 == true){                                                                                 // se o alarme 2 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme2 && RTCValues[5] == minutos_alarme2){       // se as variaveis forem igual a do relogio.      
          digitalWrite(buzzer,HIGH);                             // liga o buzzer.
          digitalWrite(led2,HIGH);}                              // liga o led2.
        
        if(contador_alarme2 == RTCValues[6]){                    // se os segundos for 59.
          digitalWrite(buzzer,LOW);}                             // desliga o buzzer.
       
        if (digitalRead(botaoOff) == HIGH) {                   // se o botão menos for pressionado.
           lcd.clear();
           digitalWrite(buzzer,LOW);                             // desliga o buzzer.
           digitalWrite(led2,LOW);}                              // desliga o led2.
      
          }     // fim alarme 2          

if(alarmeOn3 == true){                                                                               // se o alarme 3 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme3 && RTCValues[5] == minutos_alarme3){      // se as variaveis forem igual a do relogio.
         digitalWrite(buzzer,HIGH);                             // liga o buzzer.
         digitalWrite(led3,HIGH);                               // liga o led3.
         
        }
        
        if(contador_alarme3 == RTCValues[6]){                  // se os segundos forem igual a 59.
          digitalWrite(buzzer,LOW);                            // desliga o buzzer
       
        }
         if (digitalRead(botaoOff) == HIGH) {               // se o botão menos for pressionado.
          lcd.clear();
            digitalWrite(buzzer,LOW);                         // desliga o buzzer
            digitalWrite(led3,LOW);                           // desliga o led3
      }
          }     // fim alarme 3       

 if(alarmeOn4 == true){                                                                              // se o alarme 4 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme4 && RTCValues[5] == minutos_alarme4){     // se as variaveis forem iguais a do relogio.
         digitalWrite(buzzer,HIGH);                             // liga o buzzer.
        digitalWrite(led4,HIGH);                                // liga o led4.
         
        }
        
        if(contador_alarme4 == RTCValues[6]){                   // se os segundos forem iguais a 59.
          digitalWrite(buzzer,LOW);                             // desliga o buzzer.
       
        }
         if (digitalRead(botaoOff) == HIGH) {                 // se o botão menos for pressionado.
             lcd.clear();
            digitalWrite(buzzer,LOW);                          // desliga o buzzer.
            digitalWrite(led4,LOW);                            // desliga o led4.
      }
          }     //fim alarme 4
 
 if(alarmeOn5 == true){                                                                              // se o alarme 5 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme5 && RTCValues[5] == minutos_alarme5){    // se as variáveis forem iguais a do relogio.
         digitalWrite(buzzer,HIGH);                           // liga o buzzer
         digitalWrite(led5,HIGH);                             // liga o led5
         
        }
        
        if(contador_alarme5 == RTCValues[6]){                 // se os segundos forem iguais a 59.
          digitalWrite(buzzer,LOW);                           // desliga o buzzer
       }
         if (digitalRead(botaoOff) == HIGH) {               // se o botão menos for pressionado.
             lcd.clear();
             digitalWrite(buzzer,LOW);                        // desliga o buzzer
             digitalWrite(led5,LOW);                          // desliga o led5
      }
          }     // fim alarme 5

 if(alarmeOn6 == true){                                                                              // se o alarme 6 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme6 && RTCValues[5] == minutos_alarme6){     // se as variáveis forem iguais a do relogio
         digitalWrite(buzzer,HIGH);                            // liga o buzzer.
       digitalWrite(led6,HIGH);                                // liga o led6.
         
        }
        
        if(contador_alarme5 == RTCValues[6]){                  // se os segundos forem iguais a 59.
          digitalWrite(buzzer,LOW);                            // desliga o buzzer.
       
        }
         if (digitalRead(botaoOff) == HIGH) {               // se o botão Menos for pressionado.
          lcd.clear();
       digitalWrite(buzzer,LOW);                              // desliga o buzzer.
       digitalWrite(led6,LOW);                                // desliga o led6.
      }
          }                              

 if(alarmeOn7 == true){                                                                              // se o alarme 6 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme7 && RTCValues[5] == minutos_alarme7){     // se as variáveis forem iguais a do relogio
         digitalWrite(buzzer,HIGH);                            // liga o buzzer.
        digitalWrite(led7,HIGH);                                // liga o led6.
         
        }
        
        if(contador_alarme7 == RTCValues[6]){                  // se os segundos forem iguais a 59.
          digitalWrite(buzzer,LOW);                            // desliga o buzzer.
       
        }
         if (digitalRead(botaoOff) == HIGH) {               // se o botão Menos for pressionado.
          lcd.clear();
       digitalWrite(buzzer,LOW);                              // desliga o buzzer.
       digitalWrite(led7,LOW);                                // desliga o led6.
      }
          } 

 if(alarmeOn8 == true){                                                                              // se o alarme 8 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme8 && RTCValues[5] == minutos_alarme8){     // se as variáveis forem iguais a do relogio
         digitalWrite(buzzer,HIGH);                            // liga o buzzer.
        digitalWrite(led8,HIGH);                                // liga o led6.
         
        }
        
        if(contador_alarme8 == RTCValues[6]){                  // se os segundos forem iguais a 59.
          digitalWrite(buzzer,LOW);                            // desliga o buzzer.
       
        }
         if (digitalRead(botaoOff) == HIGH) {               // se o botão Menos for pressionado.
          lcd.clear();
       digitalWrite(buzzer,LOW);                              // desliga o buzzer.
       digitalWrite(led8,LOW);                                // desliga o led6.
      }
          }

 if(alarmeOn9 == true){                                                                              // se o alarme 9 for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme9 && RTCValues[5] == minutos_alarme9){     // se as variáveis forem iguais a do relogio
         digitalWrite(buzzer,HIGH);                            // liga o buzzer.
        digitalWrite(led8,HIGH);                                // liga o led8.
         
        }
        
        if(contador_alarme8 == RTCValues[6]){                  // se os segundos forem iguais a 59.
          digitalWrite(buzzer,LOW);                            // desliga o buzzer.
       
        }
         if (digitalRead(botaoOff) == HIGH) {               // se o botão Menos for pressionado.
          lcd.clear();
       digitalWrite(buzzer,LOW);                              // desliga o buzzer.
       digitalWrite(led8,LOW);                                // desliga o led6.
      }
          }

if (digitalRead(botaoMenu) == HIGH) {                        // se o botão menu for pressionado.
    tone(buzzer,2500,100);
        delay(250);                                          // tempo de 250ms.
      lcd.clear();                                           // limpa lcd
       ajusteMenu=ajusteMenu+1;                              // incrementa menu
   
  } 
  if (ajusteMenu>quantidadeMenu){                            // se o menu for maior que 6.
  ajusteMenu=0;                                              // menu volta a ser 0.
  }
  else (digitalRead(botaoMenu) == LOW);                      // senão o botão menu não é pressionado.

  switch(ajusteMenu){                                        // chave do menu
    
    case 0:                                                  // caso zero.
    
    if(digitalRead(botaoS) == HIGH)                          // se o botão S for pressionado
{ lcd.clear();                                               // limpa lcd
  delay(250);                                                // tempo de 250 ms
  ajusterelogio ++;                                          // incrementa ajusterelogio
  }

  if(ajusterelogio>quantidade)                               // se o ajuste relogio for maior que 8.
  { lcd.clear();                                             // limpa lcd
    ajusterelogio = 0;}                                      // ajuste relogio volta a ser 0.

  else(digitalRead(botaoS) == LOW);                          // senão o botão S não é pressionado.
  
 switch(ajusterelogio)                                       // chave para ajustar o relogio.
  { case 0:                                                  // caso0.
    mostrarelogio();                                         // função mostrarelogio.
      break;                                                 // pausa.
  
     case 1 :                                                // caso1.
   
     lcd.clear();                                            // limpa lcd
     lcd.setCursor(2,0);                                     // seta o cursor na 2º coluna e na linha 0.
     lcd.print(" Defina o dia ");                            // escreve no lcd.
     lcd.setCursor(8,1);                                     // seta o cursor na 8º coluna e na linha 1.
     if(date < 10){                                          // se a data for menos que 10.
        lcd.print("0");                                      // escreve 0 no lcd.
       }
       lcd.print(date);                                      // escreve a variável dia no lcd.
    
      if(digitalRead(botaoMais) == HIGH)                     // se o botão mais for pressionado.
     {date++;                                                // dia incrementa.
      if(date == 32)                                         // se o dia for igual a 32.
        { date = 1;}}                                        // data volta a ser 0.

       if(digitalRead(botaoMenos) == HIGH)                   // se o botão menos for pressionado.
     {date --;                                               // dia descrementa.
      if(date == 0)                                          // se o dia for igual 0.
      {date = 31;}}                                          // dia volta a ser 31.
         break;                                              // pausa.

      case 2:                                                   // caso2.
   
     lcd.clear();                                            // limpa lcd.
     lcd.setCursor(2,0);                                     // seta o cursor.
     lcd.print(" Defina o mes ");                            // escreve no lcd.
     lcd.setCursor(4,1);                                     // seta o cursor.
     if(mon<10)                                              // se o mês for menor que 10.
     { lcd.print("0");}                                      // escreve no lcd.
     lcd.print(mon);                                         // escreve a variavel mês no lcd.
     lcd.print("- ");                                        // escreve lcd.
     
    lcd.setCursor(8,1);                                      // seta o cursor.
    if(mon == 1)                                             // se o mês for igual a 1.
     {lcd.print("Janeiro");}                                 // escreve Janeiro.
     if(mon == 2)                                            // se o mês for igual a 2.
     {lcd.print("Fevereiro");}                               // esvreve Fevereiro.
     if(mon == 3)                                            // se o mês for igual a 3.
     {lcd.print("Marco");}                                   // esvreve Março.
     if(mon == 4)                                            // se o mês for igual a 4.
     {lcd.print("Abril");}                                   // escreve Abril.
     if(mon == 5)                                            // se o mês for igual a 5.
     {lcd.print("Maio");}                                    // escreve Maio.
     if(mon == 6)                                            // se o mês for igual a 6.
     {lcd.print("Junho");}                                   // escreve Junho.
     if(mon == 7)                                            // se o mês for igual a 7.
     {lcd.print("Julho");}                                   // escreve Julho.
     if(mon == 8)                                            // se o mês for igual a 8.
     {lcd.print("Agosto");}                                  // escreve Agosto.
     if(mon == 9)                                            // se o mês for igual a 9.
     {lcd.print("Setembro");}                                // escreve Setembro.
     if(mon == 10)                                           // se o mês for igual a 10.
     {lcd.print("Outubro");}                                 // escreve Outubro.
     if(mon == 11)                                           // se o mês for igual a 11.
     {lcd.print("Novembro");}                                // escreve Novembro.
     if(mon == 12)                                           // se o mês for igual a 12.
     {lcd.print("Dezembro");}                                // escreve Dezembro.
     
   
     if(digitalRead(botaoMais) == HIGH)                     // se o Botão Mais for pressionado.
     {mon++;                                                // mês incrementa.
      if(mon == 13)                                         // se o mês for igual a 13.
      { mon = 1;}}                                          // o mês volta a ser 1.
      
     if(digitalRead(botaoMenos) == HIGH)                    // se o botão Menos for pressionado.
     {mon --;                                               // mês descrementa.
      if(mon == 0)                                          // se o mês for igual a 0.
      {mon = 12;}}                                          // mês volta a ser 12.
       break;                                               // pausa.

      case 3:                                                        // caso3.
     lcd.clear();                                           // limpa o lcd.
     lcd.setCursor(2,0);                                    // seta o cursor.
     lcd.print(" Defina o ano ");                           // escreve no lcd.
     lcd.setCursor(8,1);                                    // seta o cursor.
     if(year<10)                                            // se o ano for menor que 10.
     {lcd.print("0");}                                      // escreve 0 no lcd.
     lcd.print(year);                                       // escreve a variável ano no lcd.
     
     if(digitalRead(botaoMais) == HIGH)                     // se o botão mais for pressionado.
     {year++;                                               // ano incrementa.
      if(year == 99)                                        // se o ano for igual a 99.
      { year = 0;}}                                         // o ano volta a ser 0.
 
     if(digitalRead(botaoMenos) == HIGH)                    // se o botão menos for pressionado.
     {year --;                                              // ano descrementa.
      if(year == 0)                                         // se o ano for igual a 0.
      {year = 99;}}                                         // o ano volta a ser 99.
        break;                                              // pausa.

        case 4:                                             // caso4.
      lcd.clear();                                          // limpa o lcd.
      lcd.setCursor(2,0);                                   // seta o cursor.
      lcd.print("Defina as horas ");                        // escreve no lcd.
      lcd.setCursor(8,1);                                   // seta o cursor.
      if(hour<10)                                           // se a hora for menor que 10.
      {lcd.print("0");}                                     // escreve 0 no lcd.
      lcd.print(hour);                                      // escreve a variável hora.
      
      if(digitalRead(botaoMais) == HIGH)                    // se o botão Mais for pressionado.
      {hour++;                                              // horas incrementa.
       if(hour == 24)                                       // se a hora for igual a 24.
       { hour = 0;}}                                        // ela volta a ser 0.
   
    if(digitalRead(botaoMenos) == HIGH)                     // se o botão Menos for pressionado.
     {hour --;                                              // horas descrementa.
      if(hour == -1)                                        // se a horas for -1. (ou menor que zero)
      {hour = 23;}}                                         // ela volta a ser 23.
       break;                                                         // pausa.
 
      case 5:                                                   // case5.
      
      lcd.clear();                                         // limpa lcd.
      lcd.setCursor(2,0);                                  // seta o cursor.
      lcd.print("Defina os minutos ");                     // escreve no lcd.
      lcd.setCursor(8,1);                                  // seta o cursor.
     if(min<10)                                            // se os minutos forem menor que 10.
     {lcd.print("0");}                                     // escreve 0 no lcd.
      lcd.print(min);                                      // escreve a variável minuto no lcd.
    
     if(digitalRead(botaoMais) == HIGH)                    // se o botão Mais for pressionado.
     {min++;                                               // minutos incrementa.
      if(min == 60)                                        // se o minuto for igual a 60.
      { min = 0;}}                                         // minuto volta a ser 0.

     if(digitalRead(botaoMenos) == HIGH)                   // se o botão menos for pressionado.
     {min --;                                              // minutos descrementa.
      if(min == -1)                                        // se os minutos forem igual a -1 ( ou menor que zero).
      {min = 59;}}                                         // minutos voltam a ser 59.
       break;                                                     // pausa.

       case 6:                                                    // caso6.

        lcd.clear();                                       // limpa o lcd.
        lcd.setCursor(1,0);                                // seta o cursor.
     lcd.print("Defina os segundos");                      // escreve no lcd.
     lcd.setCursor(8,1);                                   // seta o cursor.
     if(sec<10)                                            // se os segundos forem menor que 10.
     {lcd.print("0");}                                     // escreve 0.
     lcd.print(sec);                                       // escreve a variável segundos.
     if(digitalRead(botaoMais) == HIGH)                    // se o botão mais for pressionado.
     {sec++;                                               // segundos incrementa.
      if(sec == 60)                                        // se os segundos forem igual a 60.
      { sec = 0;}}                                         // segundos voltam a ser 0.
      
     if(digitalRead(botaoMenos) == HIGH)                   // se o botão menos for pressionado.
     {sec --;                                              // segundos descrementa.
      if(sec == -1)                                        // se os segundos for -1.
      {sec = 59;}}                                         // segundos voltam a 59.
       break;

      case 7:                                              // caso 7.
     lcd.clear();                                          // limpa lcd.
     lcd.setCursor(3,0);                                   // seta o cursor
     lcd.print(" Defina o Dds ");                          // escreve no lcd.
     lcd.setCursor(5,1);                                   // seta o cursor.
     lcd.print(dow);                                       // escreve a variável dias da semana.
     lcd.print(" -");                                      // escreve no lcd depois do dias da semana.
     lcd.setCursor(5,1); 
     lcd.print(" ");
     
     lcd.setCursor(6,1);                                   // seta o cursor
     if(dow == 1)                                          // se o dia da semana for 1.
     {lcd.print("Domingo");}                               // escreve no lcd.
     if(dow == 2)                                          // se o dia da semana for 2.
     {lcd.print("Segunda");}                               // escreve no lcd.
     if(dow == 3)                                          // se o dia da semana for 3.
     {lcd.print("Terca");}                                 // escreve no lcd.
     if(dow == 4)                                          // se o dia da semana for 4.
     {lcd.print("Quarta");}                                // escreve no lcd.
     if(dow == 5)                                          // se o dia da semana for 5.
     {lcd.print("Quinta");}                                // escreve no lcd.
     if(dow == 6)                                          // se o dia da semana for 6.
     {lcd.print("Sexta");}                                 // escreve no lcd.
     if(dow == 7)                                          // se o dia da semana for 7.
     {lcd.print("Sabado");}                                // escreve no lcd.
    
     if(digitalRead(botaoMais) == HIGH)                    // se o botão mais for pressionado.
     {dow++;                                               // dias da semana incrementa.
     if(dow==8)                                            // se o dia da semana for igual a 8.
     {dow=1;}}                                             // ele volta a ser 1.
      
     if(digitalRead(botaoMenos) == HIGH)                   // se o botão menos for pressionado.
     {dow --;                                              // dias da semana descrementa.
      if(dow == 0)                                         // se o dia da semana for igual a 0.
      {dow = 7;}}                                          // ele volta a ser 7.
      
    break;                                                 // pausa.
    
    case 8:
   
     DS1307.setDate(year,mon,date,dow,hour,min,sec);        // envia os ajustes para o RTC.
     delay(150);                                            // tempo.
     lcd.setCursor(0,0);                                    // seta o cursor.
     lcd.print(" HORARIOS AJUSTADOS");                      // escreve no lcd.
     lcd.setCursor(0,2);                                    // seta o cursor.
     lcd.print(" Pressione o botao ");                      // escreve no lcd.
     lcd.setCursor(4,3);                                    // seta o cursor.
     lcd.print(" para sair ");                              // escreve no lcd.
     lcd.print("-");                                        // escreve no lcd.
     lcd.print(">");                                        // escreve no lcd.
     break; }                                               // pause
     
     delay(150);
     break;                                                 // pause
    
     case 1:                                                             // (caso 1 do menu) alarme 1.

     lcd.setCursor(5,0);                                                 // seta cursor.
     lcd.print("Alarme 1");                                              // escreve lcd.
     lcd.setCursor(5,1);                                                 // seta cursor.
     sprintf(alarme, "%02d:%02d",horas_alarme1, minutos_alarme1);        // escreve a variavel alarme(horas_alarme,minutos_alarme) no lcd.
     lcd.print(alarme);                                                  // chama a variável alarme.
    
      if(alarmeOn == true){                                                                           // se o alarme on for verdadeiro e...
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme1 && RTCValues[5] == minutos_alarme1){      // as variaveis iguais.
          digitalWrite(led,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}

       if(digitalRead(botaoS)==HIGH){                                      // se o botão de setar for pressionado
         delay(250);                                                       // tempo.
         modo++;                                                           // modo incrementa.                
         if(modo>N){modo=0;                                                // se o modo fo maior que N, modo volta a ser 0.
         }}                          
       
   switch(modo) {                                                          // chave modo.
           
           case 0:                                                         // caso 0.
            horas_alarme1 = EEPROM.read(1);                                   // Lê a hora do alarme 1 salvo na memória EEPROM.
            minutos_alarme1 = EEPROM.read(2);                                 // Lê o minuto do alarme 1 salvo na memória EEPROM.
            alarmeOn = EEPROM.read(3);                                        // Lê a condição(ON/OFF) do alarme 1 salvo na memória EEPROM.
           lcd.noBlink();                                                  // sem piscar o lcd.
           lcd.setCursor(15,3);                                            // seta o cursor.
           lcd.print("Prox.");
           break;                                                          // pausa.
          
           case 1:                                                         // caso 1.
           lcd.setCursor(15,3);                                            // seta o cursor.
           lcd.print("     ");                                             // escreve no lcd.
           lcd.setCursor(5,1);                                             // seta o cursor.
           lcd.blink();                                                    // pisca o lcd.
           delay(140);                                                     // tempo.

           if(digitalRead(botaoMais) == HIGH){                             // se o botão mais for pressionado.
           horas_alarme1 ++;                                               // hora do alarme 1 incrementa.
           alarmeOn = false;                                               // sendo que o alarme é falso(desligado).
           
            if(horas_alarme1 > 23){                                        // se a horas do alarme 1 for maior que 23.
              horas_alarme1 = 0;}                                          // volta a ser 0.
              }

              if(digitalRead(botaoMenos) == HIGH){                         // se o botão menos for pressionado.
           horas_alarme1 --;                                               // hora do alarme 1 descrementa.
           alarmeOn = false;                                               // alarme desligado.
            if(horas_alarme1 <0 ){                                         // se o alarme for menor que 0.
              horas_alarme1 = 23;}}                                        // horas do alarme volta a ser 23.
             
           break;                                                          // pausa.
           
           case 2:                                                        // caso 2.
           lcd.setCursor(15,3);                                           // seta o cursor.
           lcd.print("     ");                                            // escreve no lcd.
           lcd.setCursor(8,1);                                            // seta o cursor.
           lcd.blink();                                                   // pisca lcd.
           delay(140);                                                    // tempo.

            if(digitalRead(botaoMais) == HIGH){                           // se o botão mais for pressionado.
            minutos_alarme1 ++;                                           // minutos alarme 1 incrementa.
            alarmeOn = false;
            if(minutos_alarme1 == 60){                                                              // alarme desligado igual a 60
            minutos_alarme1 = 0;}}                                        // minutos voltam a ser 0
              
            if(digitalRead(botaoMenos) == HIGH){                          // se o botão menos for pressionado.
            minutos_alarme1 --;                                           // minutos alarme 1 descrementa.
            alarmeOn = false;                                             // alarme desligado.
              if(minutos_alarme1 == -1){                                  //
              minutos_alarme1 = 59;}}
              break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn = true;
            tone(13,291,291);
            eeprom_write_word(1,horas_alarme1);
            eeprom_write_word(2,minutos_alarme1);
            eeprom_write_word(3,alarmeOn);
            }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn = false;
            eeprom_write_word(3,alarmeOn);
           }
            break;
         }
         break;

  case 2:

  lcd.setCursor(5,0);                                                                 // alarme2
     lcd.print("Alarme 2");
      lcd.setCursor(5,1);
      sprintf(alarme, "%02d:%02d",horas_alarme2, minutos_alarme2);
      lcd.print(alarme);
      

       if(alarmeOn2 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme2 && RTCValues[5] == minutos_alarme2){
          digitalWrite(led2,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}

       if(digitalRead(botaoS)==HIGH){
         delay(250); 
         modo2++;
         if(modo2>N2){modo2=0;
         }}

    switch(modo2) {
           case 0:
           horas_alarme2 = EEPROM.read(5);                                   // Lê a hora do alarme 2 salvo na memória EEPROM.
           minutos_alarme2 = EEPROM.read(6);                                 // Lê o minuto do alarme 2 salvo na memória EEPROM.
           alarmeOn2 = EEPROM.read(7);                                       // Lê a condição(ON/OFF) do alarme 2 salvo na memória EEPROM.
            lcd.noBlink();
            lcd.setCursor(15,3);
            lcd.print("Prox.");
           
           break;
          
           case 1:
           lcd.setCursor(15,3);
           lcd.print("     ");
           
           lcd.setCursor(5,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme2 ++;
           alarmeOn2 = false;
            if(horas_alarme2 > 23){
              horas_alarme2 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme2 --;
           alarmeOn2 = false;
            if(horas_alarme2 < 0 ){
              horas_alarme2 = 23;}
              }
            
           break;
           case 2:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,1);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme2 ++;
            alarmeOn2 = false;
            if(minutos_alarme2 > 59){
              minutos_alarme2 = 0;}
              }

                if(digitalRead(botaoMenos) == HIGH){
           minutos_alarme2 --;
            alarmeOn2 = false;
            if(minutos_alarme2 < 0 ){
              minutos_alarme2 = 59;
             }}
           break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn2 = true;
             tone(13,291,291);
             eeprom_write_word(5,horas_alarme2);
             eeprom_write_word(6,minutos_alarme2);
             eeprom_write_word(7,alarmeOn2);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn2 = false;
            eeprom_write_word(7,alarmeOn2);
           }
            break;
         }
         break;

        case 3:

        lcd.setCursor(5,0);                                                                 // alarme3
        lcd.print("Alarme 3");
        lcd.setCursor(5,1);
        sprintf(alarme, "%02d:%02d",horas_alarme3, minutos_alarme3);
        lcd.print(alarme);
      

       if(alarmeOn3 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme3 && RTCValues[5] == minutos_alarme3){
          digitalWrite(led3,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}

       if(digitalRead(botaoS)==HIGH){
         delay(250); 
         modo3++;
         if(modo3>N3){modo3=0;}}

      switch(modo3) {
           case 0:
            horas_alarme3 = EEPROM.read(9);                                  // Lê a hora do alarme 3 salvo na memória EEPROM.
            minutos_alarme3 = EEPROM.read(10);                               // Lê o minuto do alarme 3 salvo na memória EEPROM.
            alarmeOn3 = EEPROM.read(11);                                     // Lê a condição(ON/OFF) do alarme 3 salvo na memória EEPROM.
            lcd.noBlink();
            lcd.setCursor(15,3);
            lcd.print("Prox.");
           
           
           break;
          
           case 1:
           lcd.setCursor(15,3);
           lcd.print("     ");
           
           lcd.setCursor(5,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme3 ++;
           alarmeOn3 = false;
            if(horas_alarme3 > 23){
              horas_alarme3 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme3 --;
           alarmeOn3 = false;
            if(horas_alarme3 <0 ){
              horas_alarme3 = 23;}
              }
            
           break;
           case 2:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,1);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme3 ++;
            alarmeOn3 = false;
            if(minutos_alarme3 > 59){
              minutos_alarme3 = 0;}
              }

                if(digitalRead(botaoMenos) == HIGH){
           minutos_alarme3 --;
            alarmeOn3 = false;
            if(minutos_alarme3 <0 ){
              minutos_alarme3 = 59;}
              }
           
           break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn3 = true;
             tone(13,291,291);
             eeprom_write_word(9,horas_alarme3);
             eeprom_write_word(10,minutos_alarme3);
             eeprom_write_word(11,alarmeOn3);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn3 = false;
             eeprom_write_word(11,alarmeOn3);
           }
            break;
         }
         break; 

         case 4:

  lcd.setCursor(5,0);                                                                 // alarme4
     lcd.print("Alarme 4");
      lcd.setCursor(5,1);
      sprintf(alarme, "%02d:%02d",horas_alarme4, minutos_alarme4);
      lcd.print(alarme);
      

       if(alarmeOn4 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme4 && RTCValues[5] == minutos_alarme4){
          digitalWrite(led4,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}

       if(digitalRead(botaoS)==HIGH){
         delay(250); 
         modo4++;
         if(modo4>N4){modo4=0;}}

     switch(modo4) {
           case 0:
           horas_alarme4 = EEPROM.read(13);                                 // Lê a hora do alarme 4 salvo na memória EEPROM.
           minutos_alarme4 = EEPROM.read(14);                               // Lê o minuto do alarme 4 salvo na memória EEPROM.
           alarmeOn4 = EEPROM.read(15);                                     // Lê a condição(ON/OFF) do alarme 4 salvo na memória EEPROM. 
          lcd.noBlink();
          lcd.setCursor(15,3);
          lcd.print("Prox.");
           break;
          
           case 1:
           lcd.setCursor(15,3);
           lcd.print("     ");
           
           lcd.setCursor(5,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme4 ++;
           alarmeOn4 = false;
            if(horas_alarme4 >23){
              horas_alarme4 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme4 --;
           alarmeOn4 = false;
            if(horas_alarme4 <0 ){
              horas_alarme4 = 23;}
              }
            
           break;
           case 2:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,1);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme4 ++;
           alarmeOn4 = false;
            if(minutos_alarme4 > 59){
              minutos_alarme4 = 0;}
              }
                 if(digitalRead(botaoMenos) == HIGH){
                  minutos_alarme4 --;
                  alarmeOn4 = false;
            if(minutos_alarme4 <0){
              minutos_alarme4 = 59;}
              }
           break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn4 = true;
             tone(13,291,291);
             eeprom_write_word(13,horas_alarme4);
             eeprom_write_word(14,minutos_alarme4);
              eeprom_write_word(15,alarmeOn4);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn4 = false;
             eeprom_write_word(15,alarmeOn4);
           }
            break;
         }
         break; 

         case 5:
              lcd.setCursor(5,0);                                                                 // alarme5
              lcd.print("Alarme 5");
              lcd.setCursor(5,1);
              sprintf(alarme, "%02d:%02d",horas_alarme5, minutos_alarme5);
              lcd.print(alarme);
     
       if(alarmeOn5 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme5 && RTCValues[5] == minutos_alarme5){
         digitalWrite(led5,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}

       if(digitalRead(botaoS)==HIGH){
         delay(250); 
         modo5++;
         if(modo5>N5){modo5=0;}}

     switch(modo5) {
           case 0:
           horas_alarme5 = EEPROM.read(17);                                 // Lê a hora do alarme 5 salvo na memória EEPROM.
           minutos_alarme5 = EEPROM.read(18);                               // Lê o minuto do alarme 5 salvo na memória EEPROM.
           alarmeOn5 = EEPROM.read(19);                                     // Lê a condição(ON/OFF) do alarme 5 salvo na memória EEPROM. 
          lcd.noBlink();
          lcd.setCursor(15,3);
          lcd.print("Prox.");
           break;
          
           case 1:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(5,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme5 ++;
           alarmeOn5 = false;
            if(horas_alarme5 > 23){
              horas_alarme5 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme5 --;
           alarmeOn5 = false;
            if(horas_alarme5 <0){
              horas_alarme5 = 23;}
              }
            
           break;
           case 2:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,1);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme5 ++;
           alarmeOn5 = false;
            if(minutos_alarme5 > 59){
              minutos_alarme5 = 0;}
              }

                if(digitalRead(botaoMenos) == HIGH){
           minutos_alarme5 --;
           alarmeOn5 = false;
            if(minutos_alarme5 < 0){
              minutos_alarme5 = 59;}
              }
           break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn5 = true;
             tone(13,291,291);
             eeprom_write_word(17,horas_alarme5);
             eeprom_write_word(18,minutos_alarme5);
             eeprom_write_word(19,alarmeOn5);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn5 = false;
            eeprom_write_word(19,alarmeOn5);
           }
            break;
         }
         break; 

         case 6:

      lcd.setCursor(5,0);                                                                 // alarme6
      lcd.print("Alarme 6");
      lcd.setCursor(5,1);
      sprintf(alarme, "%02d:%02d",horas_alarme6, minutos_alarme6);
      lcd.print(alarme);
     

       if(alarmeOn6 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme6 && RTCValues[5] == minutos_alarme6){
          digitalWrite(led6,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}

       if(digitalRead(botaoS)==HIGH){
         delay(250); 
         modo6++;
         if(modo6>N6){modo6=0;}}

     
      switch(modo6) {
           case 0:
            horas_alarme6 = EEPROM.read(21);                                 // Lê a hora do alarme 6 salvo na memória EEPROM.
            minutos_alarme6 = EEPROM.read(22);                               // Lê o minuto do alarme 6 salvo na memória EEPROM.
            alarmeOn6 = EEPROM.read(23);                                     // Lê a condição(ON/OFF) do alarme 6 salvo na memória EEPROM.
           lcd.noBlink();
           lcd.setCursor(15,3);
           lcd.print("Prox.");
           break;
          
           case 1:
           lcd.setCursor(15,3);
           lcd.print("     ");
           
           lcd.setCursor(5,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme6 ++;
           alarmeOn6 = false;
            if(horas_alarme6 > 23){
              horas_alarme6 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme6 --;
           alarmeOn6 = false;
            if(horas_alarme6 < 0){
              horas_alarme6 = 23;}
              }
            
           break;
           case 2:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,1);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme6 ++;
           alarmeOn6 = false;
            if(minutos_alarme6 > 59){
              minutos_alarme6 = 0;}
              }

                if(digitalRead(botaoMenos) == HIGH){
           minutos_alarme6 --;
           alarmeOn6 = false;
            if(minutos_alarme6 < 0){
              minutos_alarme6 = 59;}
              }
           break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn6 = true;
             tone(13,291,291);
             eeprom_write_word(21,horas_alarme6);
             eeprom_write_word(22,minutos_alarme6);
             eeprom_write_word(23,alarmeOn6);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn6 = false;
            eeprom_write_word(23,alarmeOn6);
           }
            break;
         }
         break; 
         
         case 7:

      lcd.setCursor(5,0);                                                                 // alarme7
      lcd.print("Alarme 7");
      lcd.setCursor(5,1);
      sprintf(alarme, "%02d:%02d",horas_alarme7, minutos_alarme7);
      lcd.print(alarme);
     

       if(alarmeOn7 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme7 && RTCValues[5] == minutos_alarme7){
          digitalWrite(led7,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}

       if(digitalRead(botaoS)==HIGH){
         delay(250); 
         modo7++;
         if(modo7>N7){modo7=0;}}

     
      switch(modo7) {
           case 0:
            horas_alarme7 = EEPROM.read(25);                                 // Lê a hora do alarme 7 salvo na memória EEPROM.
            minutos_alarme7 = EEPROM.read(26);                               // Lê o minuto do alarme 7 salvo na memória EEPROM.
            alarmeOn7 = EEPROM.read(27);                                     // Lê a condição(ON/OFF) do alarme 7 salvo na memória EEPROM. 
           lcd.noBlink();
           lcd.setCursor(15,3);
           lcd.print("Prox.");
           break;
          
           case 1:
           lcd.setCursor(15,3);
           lcd.print("     ");
           
           lcd.setCursor(5,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme7 ++;
           alarmeOn7 = false;
            if(horas_alarme7 > 23){
              horas_alarme7 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme7 --;
           alarmeOn7 = false;
            if(horas_alarme7 < 0){
              horas_alarme7 = 23;}
              }
            
           break;
           case 2:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,1);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme7 ++;
           alarmeOn7 = false;
            if(minutos_alarme7 > 59){
              minutos_alarme7 = 0;}
              }

                if(digitalRead(botaoMenos) == HIGH){
           minutos_alarme7 --;
           alarmeOn7 = false;
            if(minutos_alarme7 < 0){
              minutos_alarme7 = 59;}
              }
           break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn7 = true;
             tone(13,291,291);
             eeprom_write_word(25,horas_alarme7);
             eeprom_write_word(26,minutos_alarme7);
             eeprom_write_word(27,alarmeOn7);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn7 = false;
            eeprom_write_word(27,alarmeOn7);
           }
            break;
         }
         break; 
         
         case 8:

      lcd.setCursor(5,0);                                                                 // alarme8
      lcd.print("Alarme 8");
      lcd.setCursor(5,1);
      sprintf(alarme, "%02d:%02d",horas_alarme8, minutos_alarme8);
      lcd.print(alarme);
      
      if(alarmeOn8 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme8 && RTCValues[5] == minutos_alarme8){
          digitalWrite(led8,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}
      
      lcd.setCursor(5,2);
      sprintf(alarme, "%02d:%02d",horas_alarme9, minutos_alarme9);
      lcd.print(alarme);
      
     if(alarmeOn9 == true){
        if(RTCValues[6]==0 && RTCValues[4] == horas_alarme9 && RTCValues[5] == minutos_alarme9){
          digitalWrite(led8,HIGH);
          }

       lcd.print(" ON ");}
      else{
       lcd.print(" OFF");}
       if(digitalRead(botaoS)==HIGH){
         delay(250); 
         modo8++;
         if(modo8>N8){modo8=0;}}

     
      switch(modo8) {
           case 0:
            
            horas_alarme9 = EEPROM.read(33);                                 // Lê a hora do alarme 8 salvo na memória EEPROM.
            minutos_alarme9 = EEPROM.read(34);                               // Lê o minuto do alarme 8 salvo na memória EEPROM.
            alarmeOn9 = EEPROM.read(35);                                     // Lê a condição(ON/OFF) do alarme 8 salvo na memória EEPRO
           
           lcd.noBlink();
           lcd.setCursor(15,3);
           lcd.print("Prox.");
           break;
          
           case 1:
           lcd.setCursor(15,3);
           lcd.print("     ");
           
           lcd.setCursor(5,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme8 ++;
           alarmeOn8 = false;
            if(horas_alarme8 > 23){
              horas_alarme8 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme8 --;
           alarmeOn8 = false;
            if(horas_alarme8 < 0){
              horas_alarme8 = 23;}
              }
            
           break;
           case 2:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,1);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme8 ++;
           alarmeOn8 = false;
            if(minutos_alarme8 > 59){
              minutos_alarme8 = 0;}
              }

                if(digitalRead(botaoMenos) == HIGH){
           minutos_alarme8 --;
           alarmeOn8 = false;
            if(minutos_alarme8 < 0){
              minutos_alarme8 = 59;}
              }
           break;
           
           case 3:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,1);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn8 = true;
             tone(13,291,291);
             eeprom_write_word(29,horas_alarme8);
             eeprom_write_word(30,minutos_alarme8);
             eeprom_write_word(31,alarmeOn8);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn8 = false;
            eeprom_write_word(31,alarmeOn8);
           }
            break;

            case 4:
            horas_alarme8 = EEPROM.read(29);                                 // Lê a hora do alarme 8 salvo na memória EEPROM.
            minutos_alarme8 = EEPROM.read(30);                               // Lê o minuto do alarme 8 salvo na memória EEPROM.
            alarmeOn8 = EEPROM.read(31);                                     // Lê a condição(ON/OFF) do alarme 8 salvo na memória EEPROM. 
            lcd.setCursor(15,3);
            lcd.print("Prox.");
            lcd.noBlink();
            break;
            
            case 5:
           lcd.setCursor(15,3);
           lcd.print("     ");
           
           lcd.setCursor(5,2);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
           horas_alarme9 ++;
           alarmeOn9 = false;
            if(horas_alarme9 > 23){
              horas_alarme9 = 0;}
              }

              if(digitalRead(botaoMenos) == HIGH){
           horas_alarme9 --;
           alarmeOn9 = false;
            if(horas_alarme9 < 0){
              horas_alarme9 = 23;}
              }
            
           break;
           case 6:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(8,2);
           lcd.blink();
           delay(140);

            if(digitalRead(botaoMais) == HIGH){
           minutos_alarme9 ++;
           alarmeOn9 = false;
            if(minutos_alarme9 > 59){
              minutos_alarme9 = 0;}
              }

                if(digitalRead(botaoMenos) == HIGH){
           minutos_alarme9 --;
           alarmeOn9 = false;
            if(minutos_alarme9 < 0){
              minutos_alarme9 = 59;}
              }
           break;
           
           case 7:
           lcd.setCursor(15,3);
           lcd.print("     ");
           lcd.setCursor(11,2);
           lcd.blink();
           delay(140);

           if(digitalRead(botaoMais) == HIGH){
            alarmeOn9 = true;
             tone(13,291,291);
             eeprom_write_word(33,horas_alarme9);
             eeprom_write_word(34,minutos_alarme9);
             eeprom_write_word(35,alarmeOn9);
           }
           if(digitalRead(botaoMenos) == HIGH){
            alarmeOn9 = false;
            eeprom_write_word(35,alarmeOn9);
           }
            break; 
         } break; }}       