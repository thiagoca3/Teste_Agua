#include <Thermistor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
Thermistor temp(1);

double turb = 0;
double turb0 = 700;
int x = 0;
 
void setup()
{
 pinMode(8, INPUT); // declare pushbutton como input
 Serial.begin(9600);  // inicializar serial
 lcd.begin (16,2); // inicializar LCD
}
 
void loop(){
if (digitalRead(8) == LOW) {  // verifica se deseja medir novo turb0
  turb = 0;
  x = 0;
  do
 {
   delay(20);          // estabilizacao dos sensores
   turb = turb + analogRead(0);  // soma de dez valores para turbidez
   x = x + 1;
 } while (x < 10);
  turb0 = (turb/10);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("NOVO TURB 0 =");
  lcd.setCursor(0,1);
  lcd.print(turb0);
  delay(1000);
  lcd.clear();
  }
 turb = 0;
 x = 0;
 do
 {
   delay(20);          // estabilizacao dos sensores
   turb = turb + analogRead(0);  // soma de dez valores para turbidez
   x = x + 1;
 } while (x < 10);

  turb = turb/10; // media da turbidez 
  turb = (turb - turb0)*100/(1024-turb0); // conversao turbidez

  if (turb < 0) {  // testa se tem água ou não
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("   COLOQUE A");
  lcd.setCursor(0,1);
  lcd.print("    AMOSTRA!");
  delay(2000);
  lcd.clear();
  }
  else {   // se houver água imprime turbidez e temperatura
  int temperature = temp.getTemp();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Turb = ");
  lcd.print(turb);
  lcd.print(" %");
  lcd.setCursor(0,1);
  lcd.print("Temp= ");
  lcd.print(temperature);
  lcd.print(" *C");
  delay(2000);
  lcd.clear();
  }  // imprime mensagem
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("  Prof. Manoela");
  lcd.setCursor(0,1);
  lcd.print("IFRJ - Maracana");
  delay(2000);
  lcd.clear();
}
