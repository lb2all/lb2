

#include <Lightbridge2.h>

Lightbridge2 lightbridge2(Serial1);
Lightbridge2 a3(Serial2);

void setup() {
    Serial.begin(115200);
    lightbridge2.begin();
    a3.begin();
}
void printHex2(byte c)
{
    //Serial.print("\\x");
    if( c <= 0xF) {
        Serial.print(0);
    }
    Serial.print(c,HEX);
}
void printHex2(byte * buffer,unsigned int startFrom, unsigned int len )
{
    for( unsigned int i = startFrom; i < len; i++ ){
        //Serial.print(" 0x");
        printHex2(buffer[i]);
    }
    Serial.println();
}

void printRearButtons(const RearButtons * rearButtons)
{
    Serial.print(rearButtons->buttonPlay);
    Serial.print(" ");
    Serial.print(rearButtons->buttonRecord);
    Serial.print(" ");
    Serial.print(rearButtons->buttonEmpty);
    Serial.print(" ");
    Serial.print(rearButtons->buttonScroll);
    Serial.print(" ");
    Serial.print(rearButtons->buttonC1);
    Serial.print(" ");
    Serial.print(rearButtons->buttonC2);
    Serial.print(" ");
    Serial.print(rearButtons->mode);
    Serial.println(" ");
}

void printStickData(const StickData * data )
{

    Serial.print(data->channel1);
    Serial.print(" ");
    Serial.print(data->channel2);
    Serial.print(" ");
    Serial.print(data->channel3);
    Serial.print(" ");
    Serial.print(data->channel4);
    Serial.print(" ");
    Serial.print(data->channel5);
    Serial.print(" ");
    Serial.print(data->channel6);
    Serial.print(" ");
    Serial.print(data->channel7);
    Serial.print(" ");
    Serial.print(data->channel8);
    Serial.print(" ");
    Serial.print(data->channel9);
    Serial.print(" ");
    Serial.print(data->channel10);
    Serial.print(" ");
    Serial.print(data->channel11);
    Serial.print(" ");
    Serial.print(data->channel12);
    Serial.print(" ");
    Serial.print(data->channel13);
    Serial.print(" ");
    Serial.print(data->channel14);
    Serial.print(" ");
    Serial.print(data->channel15);
    Serial.print(" ");
    Serial.print(data->channel16);
    Serial.print(" ");
    Serial.print(data->signal);
    Serial.print(" ");
    Serial.print(data->unknown3);
    Serial.print(" ");
    Serial.print(data->unknown4);
    Serial.print(" ");
    Serial.print(data->landingGear);
    Serial.print(" ");
    Serial.print(data->mode);
    for( size_t i = 0; i < sizeof(StickData::unknownArr); i++) {
        Serial.print(" ");
        printHex2(data->unknownArr[i]);
    }
    Serial.println();
}

void loop() {
    static unsigned long lastTime = 0;

    unsigned long currentTime = millis();
    if( currentTime - lastTime >= 1000 ) {
        lastTime = currentTime;


        static A3Hello a3Hello;
        Serial1.write((byte*)&a3Hello,sizeof(a3Hello));
        static A3Date a3Date;
        Serial1.write((byte*)&a3Date,sizeof(a3Date));

        static A3Battery a3battery;
        static int i = 0;
        i=(i+1)%20;
        a3battery.voltage = 15000+(i*1000);
        lightbridge2.updateCRC(a3battery);
        Serial1.write((byte*)&a3battery,sizeof(a3battery));
    }
    static StickData stickData;
    static RearButtons rearButtons;

    const Header * headerA3 = a3.process();
    const Header * header = lightbridge2.process();
    if( headerA3 ) {
        Serial.print("a3 ");
        Serial.print(headerA3->type,HEX);
        Serial.println(" ");
    }
    if( header ) {
        if( lightbridge2.updatePacketFromHeader(rearButtons,header) )
        {
            printRearButtons(rearButtons);
        }else if( lightbridge2.updatePacketFromHeader(stickData,header) ){
            printStickData(stickData);
        }
    }
}

