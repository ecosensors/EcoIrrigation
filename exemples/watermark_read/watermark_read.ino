/*
 * EcoIrrigation from EcoSensors
 * 
 * Here is a exemple how to read a value of WATERMARK sensor with the EcoIrrigation board
 *
 * Exemple code is currenty being writing and not working yet
 */
 
#include <EcoIrrigation.h>
EcoIrrigation watermark;


void setup(void)
{
  Serial.begin(9600); 

  delay(8000);

  watermark.begin();
  
  Serial.println("     EcoIrrigation    ");
  Serial.println("     by EcoSensors    ");
  Serial.println("------------------");
  Serial.println("");

  /*
  * Read sensor at A1. Pin 13 will power th sensor while HIGH.
  * (It's better to do it with a MOSFET to power the sensor with VCC)
  */
  Serial.println(F("Reading the WATERMARK SENSOR:"));
  Serial.println(watermark.read(A1, 13));
}

void loop(){
}
