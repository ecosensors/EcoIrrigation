/*
 * EcoIrrigation from EcoSensors
 * 
 * Here is an exemple how to read a value of WATERMARK sensor with the EcoBoard board
 * IMPORTANT: The watermark sensor must be powered only during a measure. Then keep it unpowered.
 * 
 * The EcoBoard has a GPIO Port Expander (PCF8574) and a MOSFET to power the Watermark sensor. The MOSFET-P is trigget by P1 or P2 or P3 (Pin 1,2 or 3 of the PCF8574). 
 */

const int pcf_p1 = 1;               // Pin 1 of PCF8574 (P1)
const int wm1_read_pin = 15;        //A1, Anaog pin to read the value return by the EcoIrrigation board
int16_t soil_temperature = 24;      // The temprature of the soil is very important to have a accurate measure. 
                                    // If you dont, 24°C will be considered. I strongly recommand you to use a [DS18b20 water proof sensor](https://github.com/ecosensors/EcoDs18b20)

#include "PCF8574.h"                // Required for PCF8574
PCF8574 expander;

#include <EcoIrrigation.h>
EcoIrrigation watermark;

void setup(void)
{
  Serial.begin(9600); 

  delay(8000);                    // Give a delay to read the event in the terminal

  Serial.println(F("\r\n# Start PCF8574"));
  expander.begin(0x27);
  expander.pinMode(pcf_p1, OUTPUT);
  expander.digitalWrite(pwd_p1, HIGH);  // Turn OFF, as pwd_p1 id connected to the gate of the MOSFET-P
  
  pinMode(wm1_read_pin, INPUT_PULLUP);  // A1
  
  watermark.begin();
  
  
  int16_t swp = 0;                // Soil Water Content
  
  Serial.println(F("# Powering the WATERMARK SENSOR"));
  expander.digitalWrite(pwd_p1, LOW);  // Power the watermark sensor, The MOSFET is triggered and the sensor is powered by 3.3V
  
  Serial.println(F("# Reading the WATERMARK SENSOR"));
  watermark.read(wm1_read_pin, soil_temperature, swp); 

  Serial.println(F("# Powering off the WATERMARK SENSOR")); // It's important to keep it unpowered
  expander.digitalWrite(pwd_p1, HIGH);

  Serial.print(swp);
  Serial.println("kPa");
}

void loop(){
}