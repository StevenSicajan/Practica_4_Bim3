/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: ADC y PWM
   Dev: Steven Josué Sicaján Pacheco
   Fecha: 26 de julio.
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           
#define SS_PIN          10          
#define ledVerde        A5           
#define ledRojo         A4          
#define buzz 2

MFRC522 mfrc522(SS_PIN, RST_PIN);   //
MFRC522::MIFARE_Key key;

byte tag1[4] = {0x83, 0x0A, 0xE5, 0x24}; 

byte tagActual[4];


void setup() {
  Serial.begin(9600); 
   while (!Serial);     
   SPI.begin();        
   mfrc522.PCD_Init(); 
   pinMode(ledVerde,OUTPUT);   
   pinMode(ledRojo,OUTPUT);
   pinMode(buzz, OUTPUT);
}

void loop() {
   if ( ! mfrc522.PICC_IsNewCardPresent())   
        return;
 
    if ( ! mfrc522.PICC_ReadCardSerial())       
        return;

 Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);    
       
digitalWrite(ledVerde,LOW);       
digitalWrite(ledRojo,LOW);  
}

void dump_byte_array(byte *buffer, byte bufferSize) {      
    for (byte i = 0; i < bufferSize; i++) {         
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);
      tagActual[i] = buffer[i];
    }
          if(compararArray(tagActual,tag1)){              
          Serial.println(" Acceso Permitido...");
          digitalWrite(ledVerde,HIGH);
          tone(buzz, 200, 2000);
          delay(4000);
          }
          else {
          Serial.println(" Desconocido" );             
          digitalWrite(ledRojo,HIGH);
          tone(buzz, 400, 2000);
          delay(2000);
            }       
}


boolean compararArray(byte array1[], byte array2[]) {
  for (byte i = 0; i < 4; i++) {
    if (array1[i] != array2[i]) return false;
  }
  return true;
}