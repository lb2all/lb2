

struct Header
{
    byte startbyte:8;
    byte length:8;
    byte unknown1a:8;//version?????
    uint16_t type:16;//??
    byte unknown1d:8;//
    uint16_t timestamp:16;
}__attribute__((packed));

const uint16_t STICK_DATA_TYPE = 0x0958;
struct StickData
{
    Header header;
    uint32_t unknown2:32;
    uint16_t channel1:11;
    uint16_t channel2:11;
    uint16_t channel3:11;
    uint16_t channel4:11;
    uint16_t channel5:11;
    uint16_t channel6:11;
    uint16_t channel7:11;
    uint16_t channel8:11;
    uint16_t channel9:11;
    uint16_t channel10:11;
    uint16_t channel11:11;
    uint16_t channel12:11;
    uint16_t channel13:11;
    uint16_t channel14:11;
    uint16_t channel15:11;
    uint16_t channel16:11;
    byte signal:8;
    byte unknown3:8;
    byte mode:2;
    byte landingGear:1;
    byte unknown4:5;
    byte unknownArr[4];
    uint16_t checksum:16;// poly: 0x1021  init val: 0xa14d Input reflected, Result reflected
}__attribute__((packed));
static_assert(sizeof(StickData)==43,"fail");

const uint16_t REAR_BUTTONS_TYPE = 0x0903;
struct RearButtons
{
    Header header; //8 bytes
    byte unknownArr[3];
    byte unknown1:1;
    byte buttonEmpty:1;
    byte buttonRecord:1;
    byte buttonPlay:1;
    byte buttonC1:1;
    byte buttonC2:1;
    byte unknown7:2;
    byte unknown8:8;
    byte mode:2;
    byte unknown9:6;
    byte unknown10:8;
    byte buttonScroll:1;
    byte unknownY:7;
    byte unknownZ:8;
    uint16_t checksum:16;// poly: 0x1021  init val: 0xa14d Input reflected, Result reflected
}__attribute__((packed));
static_assert(sizeof(RearButtons)==19,"fail");

const uint16_t A3_DATE_TYPE = 0x03F2;
struct A3Date
{
    A3Date(){
        byte data[]="\x55\x2D\x4\xF2\x3\x2\x13\x1\x0\x3\x6C\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\xF9\x92\xBA\x5B\x74\xC0\xB\x0\x14\xE2";
        memcpy(this,data,sizeof(*this));
        static_assert(sizeof(*this) == (sizeof(data)-1),"data size wrong" );
    }
    Header header; //8 bytes
    byte unknownArr[23];
    uint64_t timestamp;//unix time??
    uint32_t timestamp2;//nanoseconds?
    uint16_t checksum:16;// poly: 0x1021  init val: 0xa14d Input reflected, Result reflected
}__attribute__((packed));
static_assert(sizeof(A3Date)==45,"fail");

const uint16_t A3_BATTERY_TYPE = 0x03F2;
struct A3Battery
{
    A3Battery(){
        byte data[]="\x55\x2B\x04\x58\x03\x02\x91\x89\x00\x03\x51\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x30\x01\x00\x00\x00\x00\x12\x61\x00\x1E\x8A\x00\xC8\xEC";
        memcpy(this,data,sizeof(*this));
        static_assert(sizeof(*this) == (sizeof(data)-1),"data size wrong" );
    }
    Header header; //8 bytes
    byte unknownArr[27];
    uint16_t voltage;//im mV
    uint32_t unknown1;
    uint16_t checksum:16;// poly: 0x1021  init val: 0xa14d Input reflected, Result reflected
}__attribute__((packed));
static_assert(sizeof(A3Battery)==43,"fail");

const uint16_t A3_HELLO_TYPE = 0x031A;
struct A3Hello
{
    A3Hello(){
        byte data[]="\x55\x44\x4\x1A\x3\x9\x16\x1\x0\x3\x43\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x10\x41\x0\x0\x0\x0\x4\x0\x0\x0\x0\x0\x1E\x8A\x1A\xA\x0\x0\x0\x0\x0\x0\x6C\x6F";
        memcpy(this,data,sizeof(*this));
        static_assert(sizeof(*this) == (sizeof(data)-1),"data size wrong" );
    }
    Header header; //8 bytes
    byte unknownArr[58];
    uint16_t checksum:16;// poly: 0x1021  init val: 0xa14d Input reflected, Result reflected
}__attribute__((packed));
static_assert(sizeof(A3Hello)==68,"fail");


//char (*__kaboom)[sizeof( A3Date )] = 1;
