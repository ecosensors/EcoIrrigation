/*
* EcoIrrigation
*
* As the spring season is coming, I gave a priority on SMART BUD project. I will spend more time to finish that library in March 2022, but I hope
* I will have time to do it erlier.
*
* The mibrary does not work yet. Come back later!!!Work in progress
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


float EcoIrrigation::read(int analogPin, int powerPin)
{

}
