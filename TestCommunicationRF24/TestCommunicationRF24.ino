#include "rf24_johann_edition.h"
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install from the Libray manager in Sketch 

RF24 myRadio (7, 8); // "myRadio" is the identifier you will use in following methods
/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.

  myRadio.setPALevel(RF24_PA_MAX);  // Uncomment for more power
  //myRadio.setPALevel(RF24_PA_MIN);  // if you Use an Arduino Nano

  myRadio.openWritingPipe( addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  myRadio.openReadingPipe(1, addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  delay(1000);

}

void loop() {
  //shoose which code you want to run just uncomment the right One
  // Receive();
  //Transmit();

}
void Receive()
{

  byte dataReceived[5];
  // in this funktion the incomming bytest where split up and ordert in the right value like char or int
  myRadio.startListening();
  if ( myRadio.available()) // Check for incoming data from transmitter
  {
    while (myRadio.available())  // While there is data ready
    {
      myRadio.read( &dataReceived, sizeOfMsg()); // Get the data payload (You must have defined that already!)
      if (dataReceived > 0)
      {
        readPack adrian = interpretMsg(dataReceived);

        //Serial.print("Type: ");
        //Serial.println(adrian.type);

        switch (adrian.type)
        {
          case INT:
            Serial.print("INT: ");
            Serial.println(adrian.i);
            // here you can use ardian just like a normal int , you can may if funktion : if(adrian.i == 1) just a exaample
            break;
          case FLOAT:
            Serial.print("FLOAT: ");
            Serial.println(adrian.f);
            break;
          case CHAR:
            Serial.print("CHAR: ");
            Serial.println(adrian.c);
            break;
          default:
            break;
        }

      }
    }
  }
}
void Transmit()
{
  int intvalue = 1;
  float floatvalue = 2.00;
  char charvalue = 'a';
  myRadio.stopListening();
  myRadio.write(buildMsg(INT, &intvalue), sizeOfMsg); //  Transmit the data
  delay(1000);
  myRadio.write(buildMsg(FLOAT, &floatvalue), sizeOfMsg); //  Transmit the data
  delay(1000);
  myRadio.write(buildMsg(CHAR, &charvalue), sizeOfMsg); //  Transmit the data
  delay(1000);


}

