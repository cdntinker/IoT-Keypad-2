////////////////////////////////////////////
//  Network Setup
////////////////////////////////////////////

// Update these with values suitable for your network.

byte mac[]    = {  0xDe, 0xAD, 0xBE, 0xEF, 0x00, 0x02 }; // make this unique
                                                // Mini gets DE:AD:BE:EF:00:00

// internal address of your MQTT broker… or see examples for using address lookup etc.
IPAddress server(192,168, 0, 12);

//. internal IP your want this board to be
// IPAddress ip(192,168, 0, 202);//

// IPAddress mydns(192, 168, 0, 1);       // router
// IPAddress gateway(192, 168, 0, 1);     // router
// IPAddress subnet(255,255,255,0);       // IP address mask – usually this value
