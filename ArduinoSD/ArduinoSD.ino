#include <SPI.h>
#include <SD.h>
#include <PCM.h>

File myFile;

const unsigned char sample[] PROGMEM = {  
  // Array de PCM
};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("audio.txt");

  if (myFile) {
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    // startPlayback(sample, sizeof(sample));   // Para reproducir en pin 11.
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening txt");
  }
}

void loop() {
}

