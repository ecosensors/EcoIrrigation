/*
 * EcoIrrigation from EcoSensors
 * 
 * Here is a exemple how to read a value of WATERMARK sensor with the EcoIrrigation board
 *
 * Exemple code is currenty being writing
 */


const int wm1_power_pin = 13;       // Pin which will power the sensor
const int wm1_read_pin = 15;        //A1, Anaog pin to read the value return by the EcoIrrigation board
int16_t soil_temperature = 24;      // The temprature of the soil is very important to have a accurate measure. 
                                    // If you dont, 24°C will be considered

#include <EcoIrrigation.h>
EcoIrrigation watermark;


void setup(void)
{
  Serial.begin(9600); 

  delay(8000);

  pinMode(wm1_power_pin, OUTPUT);
  digitalWrite(wm1_power_pin,LOW);
  pinMode(wm1_read_pin, INPUT_PULLUP);
  
  watermark.begin();
  
  Serial.println("     EcoIrrigation    ");
  Serial.println("     by EcoSensors    ");
  Serial.println("------------------");
  Serial.println("");

  /* Reading the temperature of the soil */

  /*
  * Read sensor at A1. Pin 13 will power th sensor while HIGH.
  * (It's better to do it with a MOSFET to power the sensor with VCC)
  */
  int16_t swp = 0;                // Soil Water Content
  
  Serial.println(F("# Reading the WATERMARK SENSOR"));
  watermark.read(wm1_read_pin, wm1_power_pin, 1000000, soil_temperature, swp); // Third parameter is the timeout in ms

  Serial.print(swp);
  Serial.println("kPa");
}

void loop(){
}
