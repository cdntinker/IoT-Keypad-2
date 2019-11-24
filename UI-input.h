
void KeyRead(){
  //  Read the keypad
  char customKey = customKeypad.getKey();
  if (customKey){
  //   int KeyNum = customKey - 48;
  //   if (KeyNum == -6) KeyNum = 10;
  //   if (KeyNum == -13) KeyNum = 11;
  //   strcpy_P(msg, (char*)pgm_read_word(&(GH_Utterances[KeyNum])));
msg[0] = customKey;
msg[1] = '\0';
Serial.print(F("msg: "));
Serial.println(msg);
// strcat(Topic_Out, "/Message");
client.publish(Topic_Out,msg);
sendit=1;

  }

}
