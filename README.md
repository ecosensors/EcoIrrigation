# EcoIrrigation

***The following page is being writting and constently updating***

EcoIrrigation is a small electronic module which applies an AC current to the two electrodes of the Watermark sensor, and returns a frequency as a output.
The library will manage the EcoIrrigation module and convert the output to a humidity value in kPa.


![alt PCB](https://github.com/ecosensors/EcoIrrigation/blob/main/Assets/pcb-ecoirrigation.png)

## WATERMARK sensor
Watermark™ sensors are available from Irrometer Company. These soil moisture sensors are to be buried in intimate contact with soil at root depth, where they will reach equilibrium with the local soil moisture. The measurement correlates well with soil water potential. This is fine for agriculture, because water potential (in units of kilo-Pascal or centibar) best quantifies the work plant roots do to extract moisture from the soil.

The sensor contains a perforated stainless steel cylinder which supports a permeable membrane. Inside, there is a tightly packed sand aggregate, called “granular matrix”, and at one end there is a wafer of gypsum, and concentric electrodes. The electrodes are attached to wires that emerge to the soil surface.

The gypsum wafer serves as a buffer against differences in soil acidity and salinity, so that the electrical resistance between the electrodes depends on moisture and temperature only

### How does EcoIrrigation board work?
The sensoor return an electrical resistance, which decreases with increasing soil moisture. 
DC currents must not be allowed to flow through the wet part of the circuit, or else irreversible reactions will occur and spoil the readings. However, a AC current  avoids these problems, by reversing the polarity of the current many times per second, so that no reaction takes place at either electrode.

EcoIrrigation board provides an AC current at the electrodes. The output signal is a square wave, and its frequency varies (as for the the electrical resistance) from 50 hz when the sensor is bone dry, up to 10000+ hertz when the sensor is soaking wet.

The library that I provides, help you to convert the output to an humidity value in Kpa.

## Pinout

### Header J1
(EcoBoard or any Arduino board)

Pin | Output
--- | ---
1 | GND
2 | VCC
3 | Analog pin (A0, A1, A2, ...)


** Important ** The Watermark sensor must be powered only while reading a measure. The rest of the time, it must not be power, to avoid AC current in the electrodes. 

### Header J2
Watermark sensor wires

Pin | Output
--- | ---
1 | Wire 1
2 | Wire 2




## Library and PCB
The library for Arduino board and the PCB, will be available in the next few months. Wainting for this time, you can follow my activities on [Facebook](https://www.facebook.com/ecosensors) or to read my [project](https://eco-sensors.ch/smart-irrigation/) with LoRaWAN. (Those pages are sadly not translated in english, yet)