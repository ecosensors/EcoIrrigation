

#ifndef EcoIrrigation_h
#define EcoIrrigation_h


class EcoIrrigation{
 	protected:

 	private:
 		void resistanceCalc(float frequencyInput, int32_t &wrm2);
 		void kPaCalc(int32_t ResistanceInput, int16_t CTemperatureInput, int16_t &swp2, bool debug);
 		float kPaCalc_shock(float ResistanceInput, float CTemperatureInput);
	
	public:
		EcoIrrigation();
		void begin();
		bool read(int analogPin, int16_t Tsoil, int16_t &swp, bool debug);
		bool read(int analogPin, int powerPin, bool powerLow, int16_t Tsoil, int16_t &swp);
		bool read(int analogPin, int powerPin, bool powerLow, int16_t Tsoil, int16_t &swp, bool debug);
 };
 #endif