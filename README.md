# Analog PC Guages

Original project from Sasa Karanovic - [Here](https://sasakaranovic.com/projects/diy-analog-resource-monitor-for-your-pc/).

---

Here is my code my version of Sasa Karanovic's Analog PC Guages.
Wiring guides for devices can be found online, also the pinouts for whichever board you choose to use.

My Project uses:
-- ESP8266
-- Adafruit MCP4728
-- Analog Voltmeters found on Amazon, Ebay, AliExpress etc.

I collect data on overall CPU, GPU and RAM usages as well as the ambient temperature inside my case with a DHT22 sensor.

The guages need to be modified, as they are rated for 300v. I decided to take out all internal components and send minimal voltage to the guages. Hence the max value the ESP8266 sends to the guages via the MCP4728 is 340 out of a possible 4095 to get full deflection. In the time it has been running it works very well.

![PC_Guages_1](https://kitmakesthings.co.uk/PC_Guages_1.jpg)
![PC_Guages_1](https://kitmakesthings.co.uk/PC_Guages_2.jpg)

### Python Script

-- Pillow and pystray work together to create a tray icon with an Exit option to close the application.
-- Pyserial earches the open COM ports for a project board with a name containing "CP210x" (your boards may be different, you can list boards to find the description name of yours).
-- The command window displays CPU, GPU, and RAM usage percentages, and then sends the over the COM port that the project board is attached to.

### Arduino Code

-- Begins listening to the serial port its connected to.
-- On Startup sweeps the guages to max and back.
-- Listenes to the serial for new data every 0.5 seconds and the updates teh gugaes accordingly.
-- DHT22 Senesor reads temeperature and then sets the temp guage scaled to between 20c and 35c.
