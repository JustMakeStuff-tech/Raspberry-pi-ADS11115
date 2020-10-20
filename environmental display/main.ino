#include <SparkFunBME280.h>
#include <SparkFunCCS811.h>
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
#include <Wire.h>  // Include Wire if you're using I2C

#define PIN_RESET 9  
#define DC_JUMPER 1 
#define CCS811_ADDR 0x5B //Default I2C Address

MicroOLED oled(PIN_RESET, DC_JUMPER);    // I2C declaration
CCS811 myCCS811(CCS811_ADDR);
BME280 myBME280;

void setup() { 
  delay(100);
  Wire.begin();
  oled.begin();   // Initialize the OLED
  
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  oled.clear(PAGE); // Clear the buffer.

  randomSeed(analogRead(A0) + analogRead(A1));
  //Initialize BME280
  //For I2C, enable the following and disable the SPI section
  myBME280.settings.commInterface = I2C_MODE;
  myBME280.settings.I2CAddress = 0x77;
  myBME280.settings.runMode = 3; //Normal mode
  myBME280.settings.tStandby = 0;
  myBME280.settings.filter = 4;
  myBME280.settings.tempOverSample = 5;
  myBME280.settings.pressOverSample = 5;
  myBME280.settings.humidOverSample = 5;
  CCS811Core::CCS811_Status_e returnCode = myCCS811.beginWithStatus ();
  //Calling .begin() causes the settings to be loaded
  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  byte id = myBME280.begin(); //Returns ID of 0x60 if successful
  delay(10000);
}

void print_data() {
  oled.setFontType(0);

  oled.setCursor(0, 0);
  oled.print("TMP");
  oled.setCursor(25, 0);
  oled.print(round(myBME280.readTempF()));

  oled.setCursor(0, 10);
  oled.print("HUM");
  oled.setCursor(25, 10);
  oled.print(round(myBME280.readFloatHumidity()));

  oled.setCursor(0, 20);
  oled.print("VOC");
  oled.setCursor(25, 20);
  oled.print(round(myCCS811.getTVOC()));

  oled.setCursor(0, 30);
  oled.print("BAR");
  oled.setCursor(25, 30);
  oled.print(round(myBME280.readFloatPressure()));
  
  oled.setCursor(0, 40);
  oled.print("CO2");
  oled.setCursor(25, 40);
  oled.print(round(myCCS811.getCO2()));
  
  oled.display();
  }

void loop() {
  delay(2000);
  //Check to see if data is available
  if (myCCS811.dataAvailable())
  {
    //Calling this function updates the global tVOC and eCO2 variables
    myCCS811.readAlgorithmResults();
    //printData fetches the values of tVOC and eCO2

    float BMEtempC = myBME280.readTempC();
    float BMEhumid = myBME280.readFloatHumidity();

    //This sends the temperature data to the CCS811
    myCCS811.setEnvironmentalData(BMEhumid, BMEtempC);
  }
  print_data();
  delay(2000);
}
