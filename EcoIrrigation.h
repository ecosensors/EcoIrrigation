

#ifndef EcoIrrigation_h
#define EcoIrrigation_h


class EcoIrrigation{
 	protected:

 	private:
	
	public:
		EcoIrrigation();
		void begin();
		bool read(int analogPin, int powerPin, unsigned long timeout, int16_t Tsoil, int16_t &swp);
 };
 #endif