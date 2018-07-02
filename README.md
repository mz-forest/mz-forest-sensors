# Sensor Evaluation for the MakeZurich City Forest Challenge

[General information about MakeZurich](https://makezurich.ch/)

[General information about the City Forest Challenge](https://makezurich.ch/box/2/)

[People Monitoring Sihlwald](http://www.geo.uzh.ch/dam/jcr:42e776a7-9d10-4172-9661-c4febc30ae7d/2013_masterarbeit_martinbaumgartner_red.pdf)


## Sensors from the MakeZurich Box

Sensor | Product | Properties
--- | --- | ---
Radar Sensor | [RCWL-0516](Radar_RCWL-0516/README.md) | movment detection only <br> no distance information <br> detects human and animals only (due to water)  
Infrared Sensor | [Flying-Fish](IR_Flying-Fish/REAMDE.md) | can be used for distance or proximity measurements <br> does not work in dark environments <br> can measure emission of heat by an object <br> not really suited for outdoor applications...
Laser Sensor | [Waveshare Laser Sensor](Laser_Waveshare/REAMDE.md) | 650nm laser diode + detector <br> range in first tests was below 1m <br> kind of dangerous... <br> essentially a light barrier, no distance measurement

## Alternative Sensors

Sensor | Product | Properties
--- | --- | ---
PIR (passive infrared sensor) | TBD | can detect motion <br> if raw signal is analyzed, even movement direction could be extractable
Ultrasonic Sensors | TBD | distance sensor <br> not too good for human detection (clothes do not reflect sound well)


## Other Stuff
Master's thesis about agent-based modelling of park visitors (there might be some hints for automated visitor counting, the thesis itself does not contain low-level hardware info): http://www.geo.uzh.ch/dam/jcr:42e776a7-9d10-4172-9661-c4febc30ae7d/2013_masterarbeit_martinbaumgartner_red.pdf
