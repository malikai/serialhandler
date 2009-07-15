#include <SerialHandler.h>

SerialHandler mySerial(available,read,write,Error);

uint8_t available(){
  return Serial.available();
}
int read(){
  return Serial.read();
}
void write(uint8_t Buf){
  Serial.write(Buf);
}
void Error(uint8_t Buffer[]){
  Serial.println("ERROR");
}

void setup()  
{
  Serial.begin(9600);
  mySerial.Abord = 250; //byte that clear the input buffer to be sure the function byte we send is the first one


  //mySerial.Ack = 13; //13 is the byte for Carriage return <cr> so each command must end by a <cr>
  mySerial.Ack = 'd'; //use d as a Ack you will have to send Ex: ad

  mySerial.AttachFunction(Hello,'a'); //attach hello to the byte a... so we need to send a<Ack> Ex: ad
  mySerial.AttachFunction(Repeat,'H');
}

void loop()
{
  mySerial.GetSerial(0);
}

//buffer[] are all the command byte recived for the function + the function byte at pos [0] but does not include the Ack
void Hello(byte Buffer[])//a<Ack> will say hello world !
{
  Serial.println("Hello World !");
}

void Repeat(byte Buffer[])// Send H<Texttoberepeated><ack> be sure to not include in the text that will be repeated the Ack because it will stop there....
{
  for(int a = 1;a < mySerial.BufferLength();a++)
  { 
    Serial.print(Buffer[a]);
  }
}
