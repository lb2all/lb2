#ifndef LIGHTBRIDGE2_h
#define LIGHTBRIDGE2_h

#include "Arduino.h"
#include "dji_types.h"

class Lightbridge2 {
public:
    Lightbridge2(HardwareSerial & serial);
    void begin();
    const Header* process();
    //template <typename T> bool copyPacketFromHeader( T& packet, const Header* header);
    bool updatePacketFromHeader( StickData& packet, const Header* header);
    bool updatePacketFromHeader( RearButtons& packet, const Header* header);
    uint16_t crc16(byte * data, size_t size);
    template <typename T> inline void updateCRC( T& data){
        byte * bytes = (byte*)&data;
        data.checksum = crc16( bytes, sizeof(data)-2);
    };
private:
    HardwareSerial & _serial;
    const static int BUFFER_SIZE = 256;
    byte m_buffer[BUFFER_SIZE];
    int state = 0;
    int len = 0;
    const Header* evaluatePacket(byte * buffer, byte len);
    template <typename T> inline bool copyIfCorrectType( T& packet, const Header* header, const uint16_t type );
};



#endif

