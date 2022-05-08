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


long RESISTORarray[76] = {
  // Watermark Sensor SMX interface to convert Hz to Resistance lookup table per  SMX.pdf page 6.
  // Hz, Ohm 
  48,  10000000,
  76,  262144,
	85,  196608,
	103, 131072,
	122, 98304,
	157, 65536,
	194, 49152,
	264, 32768,
	335, 24567,
	476, 16384,
	612, 12288,
	874, 8192,
	1135,  6144,
	1623,  4096,
	2071,  3072,
	2862,  2048,
	3557,  1536,
	4697,  1024,
	5596,  768,
	6932,  512,
	7878,  384,
	9104,  256,
	9882,  192,
	10802, 128,
	11312, 96,
	11893, 64,
	12200, 48,
	12526, 32,
	12708, 24,
	12871, 16,
	12962, 12,
	13047, 8,
	13092, 6,
	13139, 4,
	13162, 3,
	13186, 2,
	13209, 1,
	13233, 0,
};


long SWPkPAarray[18]{
  // Watermark Sensor SMX interface to vonvert Resistance to SWP kPa lookup table per SMX.pdf page 7. 
  // this table is valid at temperature of 75F, 24C 
  550,  0,
  1000,  9, 
  1100,  10,
  2000,  15,
  6000,  35,
  9200,  55,
  12200, 75,
  15575, 100,
  //28075, 200,
  27950, 200,
};


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
* IMPORTAN: The WATERMRK sensor must not b3 permanetly  powered, but only while reading a measure
*/

bool EcoIrrigation::read(int analogPin, int powerPin, unsigned long timeout, int16_t Tsoil, int16_t &swp)
{
  read(analogPin, powerPin, timeout, Tsoil, swp, false);
}

bool EcoIrrigation::read(int analogPin, int powerPin, unsigned long timeout, int16_t Tsoil, int16_t &swp, bool debug) // , bool debug = false
{

  /*
  * TODO: Add the timeout
  */

	if(debug)
    Serial.println(F("\tPowering the Watermark sensor"));
	digitalWrite(powerPin, HIGH);
	if(debug)
    Serial.println(F("\tNeed a delay for the sensor to be in equilibre with the soil."));
	delay(3000);


	int highInput, lowInput;             		  // Store high and low time of wave in microseconds
  float totalInput;                     		// Temp store of total time of duration for one cycle of high and low pulse
  float frequency;                      		// calculated freqency   1/total time of one cycle.
  int16_t swp_shock;							         // store the swp calculate with Shock
  int percent=0;
  int32_t wrm;								              // Resistance of the sensors calculate from the frenquency returned by EcoIrrigation board output
    //int32_t wrm2;

  highInput = pulseIn(analogPin,HIGH);
  lowInput  = pulseIn(analogPin,LOW);
  totalInput = highInput + lowInput;

  frequency = 1000000 / totalInput;


  if (highInput >0 && lowInput>0)
  {
    if(debug)
      Serial.print(F("\tFrequency: ")); Serial.print((int16_t)frequency); Serial.print(F("Hz\t"));
  }
  else
  {
    if(debug)
      Serial.print(F("\tfrequency: Error "));
    return false;
  }
    
  delay(100);

  if(debug)
    Serial.println(F("\tPowering OFF the Watermark sensor"));
	digitalWrite(powerPin, LOW);
	delay(500);



	/*
	* Calculate the resistance in the soil
	*/
  if(debug)
    Serial.println(F("\tCalculate the resistance of the sensor with measured frenquence (LMC555 Time)"));
	
  resistanceCalc(frequency, wrm);					// Get the resistance of the sensors from the frequemcy
  wrm = constrain(wrm,550,27950);					// Contrain de value from the minimum
  
  if(debug)
  {
    Serial.print(F("\tWRM: "));
    Serial.print(wrm); Serial.print(F(" Ohm"));
  }

  /*
  * Calculation of the Soil Water Potetial
  */
  swp=0;
  // The temperature of te soil is needed. If that value does not exist, the scriot consider a temperazure of 24°C
  if(Tsoil == NULL)
  {
    if(debug)
      Serial.println(F("Tsoil is NULL"));
    Tsoil = 24;
  }

  if(debug)
  {
    Serial.print(F("DEBUG Tsoil: "));
    Serial.println(Tsoil);
  }

  
  /*
  * Converion following a table provided by the manufacturer
  */
  kPaCalc(wrm, Tsoil, swp, debug);
  Serial.print(F("\tSWP: ")); Serial.print(swp); Serial.println(F(" kpa"));

        
  /*
  * Converion with the equation of shock
  * We do not use it any more to calcuate the SWP as we use the table provided by the manufacturer.
  * But I keep it to compare the value or for a future need
  */
  swp_shock = kPaCalc_shock(wrm,Tsoil);											// Conversion with the Shock
  swp_shock = constrain(swp_shock,0,200);
  
  if(debug)
  {
    Serial.print(F("SWPs: ")); 
    Serial.print(swp_shock); 
    Serial.println(F(" kpa (Shock)"));
  }
  return true;


}





void EcoIrrigation::kPaCalc(int32_t ResistanceInput, int16_t CTemperatureInput, int16_t &swp2, bool debug){
  // Convert from Resistance to SWP kPa measurement
  // From SMX.pdf datasheet, page 7
  //   550 Ohms =  0 SWP kPa
  //  6000 Ohms = 35 SWP kPa
  // 28075 Ohms =200 SWP kPa
  // using lookup table held in the array  SWPkPAarray   
  // table valid for temperature of 75F, 24C
  // for increase of 1°F increase resistance by 1%.
  // ** this function accepts temperature in Fahrenheit units **
  //float newVal;


  // Adjust compensate resistance for temperature and convert celculs to Fahrenheit
  // per page 8 of SMX.pdf 
  swp2=0;
  float ResistanceCompensated =  ResistanceInput *(1 + 0.001*((CTemperatureInput * 1.8 + 32)-75));
  if(debug)
  {
    Serial.print(F("\tWRMc: ")); 
    Serial.print((int16_t)ResistanceCompensated); 
    Serial.print(F(" Ohm"));
  }
  
  if (ResistanceCompensated <= SWPkPAarray[0]) {     // Minimum value
    swp2 = SWPkPAarray[0+1];
  //Serial.print(F("swp2a:")); Serial.println(swp2);
  }
  if (ResistanceCompensated >= SWPkPAarray[16]) {     // Maximum value
    swp2 = SWPkPAarray[16+1];
    //Serial.print(F("swp2b:")); Serial.println(swp2);
  } 
  //for (int i=0; i<SWPkPAarray.length-2; i=i+2) {
  for (int i=0; i<16; i=i+2) {
    if ((ResistanceCompensated >= SWPkPAarray[i]) && (ResistanceCompensated <= SWPkPAarray[i+2])) {
      //swp2 = SWPkPAarray[i+1] - ((SWPkPAarray[i+1]-SWPkPAarray[i+3]) * ((ResistanceInput-SWPkPAarray[i]) / (SWPkPAarray[i+2]-SWPkPAarray[i])));
      swp2 = SWPkPAarray[i+1] - ((SWPkPAarray[i+1]-SWPkPAarray[i+3]) * ((ResistanceCompensated -SWPkPAarray[i]) / (SWPkPAarray[i+2]-SWPkPAarray[i])));
      break;
    }
  } 
}
 


void EcoIrrigation::resistanceCalc(float frequencyInput, int32_t &wrm2){
  wrm2=0;
  // Convert from freqency to Resistance measurement
  // Minimum and maximum frequency of the sensor
  // 48 Hz    = 10,000,000 Ohms
  // 13233 Hz =          0 ohms 
  // using lookup table held in the array  RESISTORarray   

  frequencyInput = constrain(frequencyInput,48, 13233);
  
  if (frequencyInput <= RESISTORarray[0]) {     // Minimum value
    wrm2 = RESISTORarray[0+1];
  }
  if (frequencyInput >= RESISTORarray[74]) {     // Maximum value
    wrm2 = RESISTORarray[74+1];
  }  
  for (int i=0; i<74; i=i+2) {
    if ((frequencyInput >= RESISTORarray[i]) && (frequencyInput <= RESISTORarray[i+2]))
    {
      wrm2 = RESISTORarray[i+1] - ((RESISTORarray[i+1]-RESISTORarray[i+3]) * ((frequencyInput-RESISTORarray[i]) / (RESISTORarray[i+2]-RESISTORarray[i])));
      break;
    }
  }
  //Si.sprint(F("WRM2: "),2); Si.sprintln(wrm2,2);
}


 /*
* Above function are not used any more. I keep it for record
*/

float EcoIrrigation::kPaCalc_shock(float ResistanceInput, float CTemperatureInput){
  // Second Method of conversion
  // Convert from Resistance to SWP kPa measurement
  // From SMX.pdf datasheet, page 9
  // kPa = (3.213 * kohms + 4.093) / {1 - 0.009733 * kohms - 0.01205 * Celsius)
  // ** this function accepts temperature in Celsius units **
  
  ResistanceInput = ResistanceInput/1000;     // ohms to Kohms
  float newVal = (3.213 * ResistanceInput + 4.093) / (1 - 0.009733 * ResistanceInput - 0.01205 * CTemperatureInput);
 
  return newVal;
}