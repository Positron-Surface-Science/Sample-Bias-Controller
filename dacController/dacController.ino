
#include "Wire.h"
#include "Adafruit_MCP4725.h"
#include <math.h>
#include <string.h>

Adafruit_MCP4725 dac;

void setup(void) {
  Serial.begin(9600);

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x62);
  pinMode(A0, INPUT);

}

float input0 = 0;
uint32_t input2 = 0;
char incomingByte;
int analogToDigitalPin = A0;
float val = 0;
float output = 0;
String inString = ""; 

void loop(void) {
  if (Serial.available() > 0)
  {

 // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();

    if (inChar != '\n') {

      // As long as the incoming byte
      // is not a newline,
      // convert the incoming byte to a char
      // and add it to the string
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value as a float:
    else {
      Serial.print("Input string: ");
      Serial.print(inString);
      Serial.print("\nAfter conversion to float:");
      Serial.println(inString.toFloat());
      input0 = inString.toFloat();
      // clear the string for new input:
      inString = "";
      //continue;
    }
  }
    
    
    Serial.print("Set Voltage: ");
    Serial.println(input0);   // Do something with the value
    input2 = round(pow(input0,2)*0.00086534 + input0*3.0966 - 1.5);
    dac.setVoltage(input2,false);
    //delay(10000);
    
    for (int i=1;i<=20;i++)
    {
      
      val = analogRead(analogToDigitalPin);
      output = val + output;
      //delay(100);
    }

    output = output/20;
    output = -79983.7165 + 10527.07587*log(output + 1259.18753);
    Serial.println("Read Voltage: ");
    Serial.println(output,4);
}
}
