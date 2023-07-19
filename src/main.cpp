#include <Arduino.h>
#include<SPI.h>

//settign up SPI pins
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_Sclk 18
#define SPI_CS 5
uint8_t comp2s(uint8_t value)
{
  uint8_t val1;
  val1 = (value ^ 0xFF);
  val1 = val1 + 1;
  return val1;
}

//SPIClass vspi;   //Instantiating an object named vspi with SPIClass
void setup() {
  Serial.begin(115200);
  Serial.println("Getting Started....");
  pinMode(SPI_CS, OUTPUT);
  SPI.begin(SPI_Sclk,SPI_MISO, SPI_MOSI, SPI_CS);
  digitalWrite(SPI_CS, HIGH);
  SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
  digitalWrite(SPI_CS, LOW);
  SPI.transfer(0x1B & (~(1<<8)));
  delayMicroseconds(10);
  SPI.transfer(0x00);    //standby mode
  digitalWrite(SPI_CS, HIGH);
  delayMicroseconds(100);
  digitalWrite(SPI_CS, LOW);
  SPI.transfer(0x21 & (~(1<<8)));
  delayMicroseconds(10);
  SPI.transfer(0x06);
  digitalWrite(SPI_CS, HIGH);
  delayMicroseconds(100);
  digitalWrite(SPI_CS, LOW);
  SPI.transfer(0x1B & (~(1<<8)));
  delayMicroseconds(10);
  SPI.transfer(0xC0); //High power mode
  digitalWrite(SPI_CS, HIGH);
}

void loop() {
  int8_t valueL = 0, valueH = 0;
  float value = 0;
  digitalWrite(SPI_CS, LOW);
  SPI.transfer(0x0A | 0x80);
  delayMicroseconds(20);
  valueL  = SPI.transfer(0x00);
  digitalWrite(SPI_CS, HIGH);
  delay(10);
  /*digitalWrite(SPI_CS, LOW);
  SPI.transfer(0x09 | 0x80);
  delayMicroseconds(20);
  valueH = SPI.transfer(0x00);
  digitalWrite(SPI_CS, HIGH);
  int16_t value1 = static_cast<int16_t>((valueH << 8) | valueL); 
  Serial.print("Value: ");
  float value = static_cast<float>(value1); 
  Serial.println(value);*/
  value = static_cast<float>(valueL);
  valueH = comp2s(valueL);
  Serial.println(valueH, HEX);

  delay(100);


  
}
/*void write_reg(int8_t addr, int8_t value)
{
  digitalWrite(SPI_CS, LOW);
  delayMicroseconds(1);
  SPI.beginTransaction(SPISettings(SPI_CS, MSBFIRST,SPI_MODE0));
  SPI.transfer(addr & (~(1<<8)));
  SPI.transfer(value);
  SPI.endTransaction();
  delayMicroseconds(1);
  digitalWrite(SPI_CS, HIGH);
}
int8_t read_reg(int8_t addr)
{
  int8_t data;
  digitalWrite(SPI_CS, LOW);
  delayMicroseconds(1);
  SPI.beginTransaction(SPISettings(SPI_CS, MSBFIRST,SPI_MODE0));
  SPI.transfer(addr | 0x80);
  data = SPI.transfer(0x00);
  SPI.endTransaction();
  delayMicroseconds(1);
  digitalWrite(SPI_CS, HIGH);
  return data;
}
void setup()
{
  Serial.begin(115200);
  Serial.println("Getting Started....");
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);
  SPI.begin(SPI_Sclk,SPI_MISO, SPI_MOSI, SPI_CS);
  write_reg(0x1B, 0x00);
  write_reg(0x21, 0x06);
  write_reg(0x1B, 0xC0);
  delay(50);

}
void loop()
{
  int8_t value1;
  value1 = read_reg(0x08);
  Serial.print("Value1: ");
  Serial.println(value1, HEX);
}
*/
