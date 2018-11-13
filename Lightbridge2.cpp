
#include "Lightbridge2.h"
#include <FastCRC.h>

static FastCRC16 crc;

//const int SBUS::_millis_until_failsafe = 1000;

Lightbridge2::Lightbridge2(HardwareSerial & serial) :
    _serial (serial)
{
}

void Lightbridge2::begin()
{
    _serial.begin(258000);//, SERIAL_8E2????
}


void printBin(byte c)
{
    for( unsigned char i = 0b10000000; i!=0; i=i>>1 ) {
        if( i & c ) {
            Serial.print("1");
        }else{
            Serial.print("0");
        }
    }
    Serial.print(" ");
}
void printHex(byte c)
{
    Serial.print("\\x");
    if( c <= 0xF) {
        Serial.print(0);
    }
    Serial.print(c,HEX);
}
void printHex(byte * m_buffer,unsigned int startFrom, unsigned int len )
{
    for( unsigned int i = startFrom; i < len; i++ ){
        //Serial.print(" 0x");
        printHex(m_buffer[i]);
    }
    Serial.println();
}

void printHeader( Header * header)
{

    printHex(header->length);
    printHex(header->unknown1a);
    printHex((header->type)>>8);
    printHex(header->type);
    printHex(header->unknown1d);
    Serial.println(" ");
}

const Header* Lightbridge2::process() {


    while(_serial.available()){
        byte c = _serial.read();
        if( state == 0 && c == 0x55 ) {
            m_buffer[state]=c;
            state = 1;
        }else if( state == 1 ) {
            m_buffer[state]=c;
            state = 2;
            len = c-1;
        }else if( len!=0 && state >= len) {
            m_buffer[state]=c;
            state = 0;
            len = 0;
            return evaluatePacket(m_buffer,m_buffer[1]);
        }else if (state >= 2 ) {
            m_buffer[state]=c;
            state++;
        }else{
            state = 0;
        }
    }
    return nullptr;
}
uint16_t Lightbridge2::crc16(byte * data, size_t size)
{
    return crc.generic(0x1021, 0x496c, CRC_FLAG_REFLECT, data, size);
}

bool Lightbridge2::updatePacketFromHeader( StickData& packet, const Header* header)
{
    return copyIfCorrectType(packet,header,STICK_DATA_TYPE);
}
bool Lightbridge2::updatePacketFromHeader( RearButtons& packet, const Header* header)
{
    return copyIfCorrectType(packet,header,REAR_BUTTONS_TYPE);
}
template <typename T> inline bool Lightbridge2::copyIfCorrectType( T& packet, const Header* header, const uint16_t type )
{
    if( header->type == type ) {
        memcpy(&packet,header,sizeof(packet));
        return true;
    }
    return false;
}

void print64(uint64_t number)
{
    char buf[100];
    sprintf(buf, "%0ld", (uint32_t)number);
    Serial.print(buf);
    sprintf(buf, "%0ld", (uint32_t)(number>>32));
    Serial.print(buf);
}


const Header* Lightbridge2::evaluatePacket(byte * m_buffer, byte len)
{
    uint16_t checksum_received = *((uint16_t*)&(m_buffer[len-2]));
    uint16_t cs = crc16(m_buffer, m_buffer[1]-2);//crc.generic(0x1021, 0xa14d, CRC_FLAG_REFLECT, &m_buffer[1], m_buffer[1]-3);
    if( checksum_received == cs) {
        Header * header = ((Header *)m_buffer);
        //Serial.println(header->type,HEX);

        if( header->type == 0x0938 ) { // 0x17//??,only when ground unit connected, gs signal strength?
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0958 ) {//0x2B //contains most channels
            //print2B(m_buffer);
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0E66 ) {//0x0E//??,only when ground unit connected, low freq
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x09A9 ) {//0x15//contains a few channels
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x09C7 ) {//0x12// ????, contains if gs is connected, low freq
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0992 ) {//0x11// ????, contains if gs is connected, lower freq
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0E58 ) {//0x2B// ??? only when ground unit connected
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x035C ) {//0x52// ??? super low freq/infrequent
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x09A2 ) {//0x0F//Scroll and buttons, just on change
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0903 ) {//0x13//rear buttons, sent multiple times on change
            //printHex(m_buffer,startFrom,len);
        }

        /*DJI A3*/
        else if( header->type == 0x031A ) {//I am A3??
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x03A2 ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x036D ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x037F ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0306 ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x03F2 ) {//
            //uint32_t time = (*((uint32_t*)&m_buffer[len-5])) & 0xFFFFFF ;
            /*uint64_t time = (*((uint32_t*)&m_buffer[35]));
      A3Date *a2date = (A3Date*)header;
      print64(time);
      Serial.print(" ");
      print64(a2date->timestamp);
      //Serial.print(a2date->timestamp);
      Serial.print(" ");
      Serial.print(a2date->timestamp2);
      Serial.print(" ");//datetime?*/
        }else if( header->type == 0x0358 ) {// voltage
            //A3Battery *bat = (A3Battery*)header;
            //Serial.print(bat->voltage);
            //Serial.print(" ");
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x03DF ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x03DA ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0349 ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0392 ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0325 ) {//
            //printHex(m_buffer,startFrom,len);
        }else if( header->type == 0x0366 ) {//
            //printHex(m_buffer,0,len);
        }

        //DJI APP from a3
        else if( header->type == 0x0233 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x0320 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x0303 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x03B1 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x03C2 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x0340 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x038A ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x03D1 ) {//
            //printHex(m_buffer,0,len);
        }
        //answer on click 37B
        else if( header->type == 0x037B ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x034E ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x0356 ) {//
            //printHex(m_buffer,0,len);
        }

        //DJI APP to a3
        else if( header->type == 0x0292 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x02A9 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x02Fc ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x02E4 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x0266 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x0253 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x026D ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x020D ) {//
            //printHex(m_buffer,0,len);
        }
        //DJI APP on click
        else if( header->type == 0x0203 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x02A2 ) {//
            //printHex(m_buffer,0,len);
        }else if( header->type == 0x0256 ) {//
            //printHex(m_buffer,0,len);
        }else{
            Serial.print("unknown type received: ");
            Serial.println(header->type,HEX);
            return nullptr;
        }
        return header;
    }else{
        Serial.println("invalid packet");
    }
    return nullptr;
}
