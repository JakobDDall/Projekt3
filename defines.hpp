//------------------- Linetypes ----------------------
#define TYPE_STRAIGHT "Straight"
#define TYPE_RIGHT "Right"
#define TYPE_LEFT "Left"
#define TYPE_TJUNCTION1 "T-junction1"
#define TYPE_TJUNCTION2 "T-junction2"
#define TYPE_TJUNCTION3 "T-junction3"
#define TYPE_UTURN "U-turn"
#define TYPE_4WAY "4-way"
#define TYPE_STOP "Stop"
#define TYPE_UNKNOWN "Unknown"


//------------------- MOVES --------------------------
#define MOV_STRAIGHT "Straight"
#define MOV_LEFT "Left"
#define MOV_RIGHT "Right"
#define MOV_ADJ_LEFT "AdjLeft"
#define MOV_ADJ_RIGHT "AdjRight"
#define MOV_STOP "Stop"
#define MOV_NOTHING "Nothing"

//------------------ Sensors --------------
#define SENSOR_LEFT 0b00100000
#define SENSOR_FRONTLEFT 0b00010000
#define SENSOR_FRONT 0b00001000
#define SENSOR_FRONTRIGHT 0b00000100
#define SENSOR_RIGHT 0b00000010
#define SENSOR_BACK 0b00000001

//---------------- Commands -------------------------
#define CMD_SENSORREQUEST 0x44
#define CMD_DISTREQUEST 0x55
#define CMD_RIGHTTURN 0x11
#define CMD_LEFTTURN 0x12
#define CMD_STRAIGHT 0x13
#define CMD_UTURN 0x14
#define CMD_STOP 0x15
#define CMD_ADJ_RIGHT 0x16
#define CMD_ADJ_LEFT 0x17
