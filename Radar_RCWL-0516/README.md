# Radar Sensor RCWL-0516

Supply Voltage: 5V 

Pinout

Resources:

* [Datasheet](https://github.com/jdesbonnet/RCWL-0516)
* [Radar Sensor Comparison by Andreas Spiess](https://www.youtube.com/watch?v=9WiJJgIi3W0)
* [RCWL-0516 Reverse Engineering](https://electronics.stackexchange.com/questions/278674/help-reverse-engineering-rcwl-0516-microwave-proximity-detector-module)
* [Schematics](https://www.tayloredge.com/reference/Electronics/RF/0242.pdf)
* [Explaining Video](https://www.youtube.com/watch?v=jAeFQEHWLZU)
* [Radar Speed Gun](https://www.youtube.com/watch?v=Kzsh59TM4MY)
* [Lidar Sensors](https://www.youtube.com/watch?v=PldrKkZmJYk)


## Sensor Notes

* CDS is the enable pin (pulled up on the sensor board). Therefore it should be possible to trigger (enable/disable) the radar sensor
* Photo resistor (CDS) is not assembled on the sensor board.
* Sensor is operated in retriggerable mode (MODE pin of RCWL-9196 chip is connected to 3V3 on sensor board). Therefore sensor stays high as long as movement is detected.
* C-TM can be used to change (increase) the trigger pulse width. t = 24576 x R x C where R = 10K, C = C2 || C-TM with C2 = 0.01 uF
* Looks like sensor board can be powered by 3.3V over the 3V3 pin. To be verified

## Other Sensors

* HB100, more advanced radar sensor, 10GHz
* CDM324, 24GHz Radar Sensor
* LIDAR sensors - laser technology

## Arduino Sketch



