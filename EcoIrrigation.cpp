/*
* EcoIrrigation
*
* As the spring season is coming, I gave a priority on SMART BUD project. I will spend more time to finish that library in March 2022, but I hope
* I will have time to do it erlier.
*
* The library does not work yet. Come back later!!!Work in progress
* FEEL FREE TO IMPROVE IT
*
* Library for the WTAERMARK sensor (not tested for ther DS18x20 sensors)
* It will help you to convert the value of the EcoIrrigation board to a humidity value (kPa)
*
*/

#include "Arduino.h"
#include "EcoIrrigation.h"

EcoIrrigation::EcoIrrigation()
{

}
	

void EcoIrrigation::begin()
{
	Serial.println(F("\r\n**************************"));
	Serial.println(F("*  EcoIrrigation Library   *"));
	Serial.println(F("*   from EcoSensor.ch    *"));
	Serial.println(F("**************************"));

}

/*
* IMPORTAN: The WATERMRK sensot not permanetly be powered, but only while reading a measure
*/


bool EcoIrrigation::read(int analogPin, int powerPin, unsigned long timeout, int16_t Tsoil, int16_t &swp)
{
	Serial.println(F("\tPowering the Watermark sensor"));
	digitalWrite(powerPin, HIGH);
	Serial.println(F("\tNeed a delay for the sensor to be in equilibre with the soil."));
	delay(3000);

	int highInput, lowInput;             		// Store high and low time of wave in microseconds
    float totalInput;                     		// Temp store of total time of duration for one cycle of high and low pulse
    float frequency;                      		// calculated freqency   1/total time of one cycle.
    int16_t freq;								// calculated freqency
    int16_t swp_shock;
    int percent=0;
    int32_t wrm;
    int32_t wrm2;

    highInput = pulseIn(analogPin,HIGH);
    lowInput  = pulseIn(analogPin,LOW);
    totalInput = highInput + lowInput;

    frequency = 1000000 / totalInput;
    freq = (int16_t)frequency;

    if (highInput >0 && lowInput>0)
    {
      Serial.print(F("\tFrequency: ")); Serial.print((int16_t)frequency); Serial.print(F("Hz\t"));
    }
    else
    {
      Serial.print(F("\tfrequency: Error "));
      return false;
    }
    
    delay(100);

    Serial.println(F("\tPowering OFF the Watermark sensor"));
	digitalWrite(powerPin, LOW);
	delay(500);






}
