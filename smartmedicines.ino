// Programa : Modulo I2C Display e Modulo DS1307

#include "Wire.h"
#include <LiquidCrystal_I2C.h>
// Modulo RTC no endereco 0x68
#define DS1307_ADDRESS 0x68

// Modulo I2C display no endereco 0x27
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

byte remedio[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B00000
};

int sensor01 = 8;
int buzzer = 10;
byte zero = 0x00;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  lcd.begin (16, 2);

  //A linha abaixo pode ser retirada apos setar a data e hora
 //SelecionaDataeHora();

  {
    lcd.setBacklight(HIGH);

    lcd.begin (16, 2);
    {
      lcd.setCursor(1, 0);
      lcd.print(" Bem Vindo . ");
      delay(500);
      lcd.clear();

      lcd.setCursor(1, 0);
      lcd.print(" Bem Vindo .. ");
      delay(500);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print(" Bem Vindo ... ");
      delay(500);
      lcd.clear();
      //////
      lcd.setCursor(1, 0);
      lcd.print(" Bem Vindo . ");
      delay(500);
      lcd.clear();

      lcd.setCursor(1, 0);
      lcd.print(" Bem Vindo .. ");
      delay(500);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print(" Bem Vindo ... ");
      delay(100);
      lcd.clear();


      //////
      lcd.setCursor(3,0);
      lcd.print(" Smart ");
      lcd.setCursor(2,1);
      lcd.print(" Medicines ");
      delay(2000);
      lcd.clear();
    }
    pinMode (sensor01, INPUT);
//    pinMode (sensor02, INPUT);
    pinMode (buzzer, OUTPUT);
    pinMode (9, OUTPUT);

    lcd.setBacklight(HIGH);
    lcd.begin (16, 2);
    lcd.createChar(1, remedio);
    lcd.setCursor(3, 0);
    
  }
}

void loop()
{
  {

    int estado;
    

    ////////////////////sensor 01/////////////////////////////////
    estado = digitalRead (sensor01);

   
     
    if (estado == 0)
     {
      lcd.setCursor(3, 0);
      lcd.write (1);   // print remedio 1
        delay(1000);
      


    }
    
    else
    {
      lcd.setCursor(3, 0);
      
    }
    
    ////////////////////sensor 02/////////////////////////////////
  
  }


  // Le os valores (data e hora) do modulo DS1307
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int segundos = ConverteparaDecimal(Wire.read());
  int minutos = ConverteparaDecimal(Wire.read());
  int horas = ConverteparaDecimal(Wire.read() & 0b111111);
  int diadasemana = ConverteparaDecimal(Wire.read());
  int diadomes = ConverteparaDecimal(Wire.read());
  int mes = ConverteparaDecimal(Wire.read());
  int ano = ConverteparaDecimal(Wire.read());
     ////////////////////// BLUETOOTH COM ALARME ///////////////////////////////////
if(Serial.available()>0)
   {         
     char hr = Serial.read();    
     if(hr == "1127")   
   {}
   }
//   Serial.print(hr);
   if (minutos%3==0)
   {
   delay(50);
    tone(10,300,300);
    delay(500);
    tone(10,300,300);
    delay(500);
    tone(10,300,300);
    delay(500);
    tone(10,300,300);
    delay(500);
    tone(10,300,300);
    delay(500);
   }
    
    

  // Mostra os dados no display
  lcd.setCursor(0, 0);
  lcd.print("     ");
  // Acrescenta o 0 (zero) se a hora for menor do que 10
  if (horas < 10)
    lcd.print("0");
  lcd.print(horas);
  lcd.print(":");
  // Acrescenta o 0 (zero) se minutos for menor do que 10
  if (minutos < 10)
    lcd.print("0");
  lcd.print(minutos);
  lcd.setCursor(2, 1);
  // Acrescenta o 0 (zero) se segundos for menor do que 10
  if (segundos < 10)
    lcd.print("0");
  lcd.print(segundos);
  lcd.setCursor(2, 1);

  // Mostra o dia da semana
  switch (diadasemana)
  {
    case 0: lcd.print("Dom");
      break;
    case 1: lcd.print("Seg");
      break;
    case 2: lcd.print("Ter");
      break;
    case 3: lcd.print("Quar");
      break;
    case 4: lcd.print("Qui");
      break;
    case 5: lcd.print("Sex");
      break;
    case 6: lcd.print("Sab");
  }
  lcd.setCursor(6, 1);
  // Acrescenta o 0 (zero) se dia do mes for menor do que 10
  if (diadomes < 10)
    lcd.print("0");
  lcd.print(diadomes);
  lcd.print("/");
  // Acrescenta o 0 (zero) se mes for menor do que 10
  if (mes < 10)
    lcd.print("0");
  lcd.print(mes);
  lcd.print("/");
  lcd.print(ano);
  


}

void SelecionaDataeHora()   //Seta a data e a hora do DS1307
{
  byte segundos = 00; //Valores de 0 a 59
  byte minutos = 47; //Valores de 0 a 59
  byte horas = 21; //Valores de 0 a 23
  byte diadasemana = 2; //Valores de 0 a 6 - 0=Domingo, 1 = Segunda, etc.
  byte diadomes = 06; //Valores de 1 a 31
  byte mes = 11; //Valores de 1 a 12
  byte ano = 18; //Valores de 0 a 99

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados

  //As linhas abaixo escrevem no CI os valores de
  //data e hora que foram colocados nas variaveis acima
  Wire.write(ConverteParaBCD(segundos));
  Wire.write(ConverteParaBCD(minutos));
  Wire.write(ConverteParaBCD(horas));
  Wire.write(ConverteParaBCD(diadasemana));
  Wire.write(ConverteParaBCD(diadomes));
  Wire.write(ConverteParaBCD(mes));
  Wire.write(ConverteParaBCD(ano));
  Wire.write(zero);
  Wire.endTransmission();
}

byte ConverteParaBCD(byte val)
{
  //Converte o número de decimal para BCD
  return ( (val / 10 * 16) + (val % 10) );
}

byte ConverteparaDecimal(byte val)
{
  //Converte de BCD para decimal
  return ( (val / 16 * 10) + (val % 16) );
}


