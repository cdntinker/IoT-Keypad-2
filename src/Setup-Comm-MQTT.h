////////////////////////////////////////////
//  MQTT Setup
////////////////////////////////////////////

//  this routine is called automatically when something comes in. I’ve used
//  serial.print to let you see it. Also use this to prepare a response.
void callback(char* topic, byte* payload, unsigned int length)
{
  *(payload+length)=0;
  #ifndef SPACESAVING
  Serial.print((char *)topic);
  Serial.print(" : ");
  Serial.println((char *)payload);
  #endif
  //
  //  Why can I only send a single message back?
  //
  //strcpy(msg,"Sorted"); sendit=1;
  strcpy(msg, (char *)payload); sendit=1;
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

char Topic_Out[64] = "Arduino/Keypad/";
