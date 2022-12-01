struct opd_s
{
	int sub;
	int toc;
};

float Sqrt(float X)
{
	volatile opd_s Pointer = *(opd_s*)std::f_sqrtf;
	return ((float(*)(float)) (void*) & Pointer)(X);
}

typedef float Vector;
typedef struct Vector2
{
	float x, y;
	Vector2()
	{
		this->x = this->y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Vector2& Vec)
	{
		return (this->x == Vec.x && this->y == Vec.y);
	}
	const Vector2& operator- (Vector2 const& Vector)
	{
		return Vector2(this->x - Vector.x, this->y - Vector.y);
	}
	const Vector2& operator+ (Vector2 const& Vector)
	{
		return Vector2(this->x + Vector.x, this->y + Vector.y);
	}
	float DotProduct(Vector2 const& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y);
	}

	float DistanceTo(Vector2 const& Vector)
	{
		return Sqrt((Vector.x - x) * (Vector.x - x) + (Vector.y - y) * (Vector.y - y));
	}

	inline float Length(void) const
	{
		return Sqrt(x * x + y * y);
	}

	inline Vector2 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector2(0, 1);
		flLen = 1 / flLen;
		return Vector2(x * flLen, y * flLen);
	}

}Vector2, * PVector2;

typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const Vector3& operator-(void) const {
		return Vector3(-x, -y, -z);
	}
	const bool operator==(const Vector3& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	const bool operator!=(const Vector3& v) const {
		return !(*this == v);
	}
	const Vector3& operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	const Vector3& operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	const Vector3& operator*(float fl) const {
		return Vector3(x * fl, y * fl, z * fl);
	}
	const Vector3& operator/(float fl) const {
		return Vector3(x / fl, y / fl, z / fl);
	}
	const float Length(void) const {
		return Sqrt(x * x + y * y + z * z);
	}
	float Vector3::getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	const Vector3 Normalize(void) const
	{
		float flLen = Length();
		if (flLen == 0) return Vector3(0, 0, 1); // ????
		flLen = 1 / flLen;
		return Vector3(x * flLen, y * flLen, z * flLen);
	}

	float Distance(Vector3 const& Vector)
	{
		return sqrt(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const& Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3 const& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector3& RoundHalfUp()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}\
		const Vector3& RoundHalfDown()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
} Vector3, * PVector3;

Vector3 Difference(Vector3 Target, Vector3 Entity)
{
	Vector3 Return = Target - Entity;
	return Return;
}

typedef struct Vector4
{
	float x, y, z, a;
	Vector4()
	{
		x = y = z = a = 0;
	}
	Vector4(float x, float y, float z, float a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}

} Vector4, * PVector4;

typedef float vec_t;
typedef float vec2_t[2];
typedef float vec3_t[3];
typedef float vec4_t[4];

#define RAD2DEG( a ) ( ( (a) * 180.0f ) / M_PI )
#define DEG2RAD( a ) ( ( (a) * M_PI ) / 180.0f )
#define POW(x)     ((x) * (x))
#define M_E      2.718281f

struct Matrix44
{
	vec4_t v[4];
};


#define ELEMTYPE_NORMALSHADER 1
#define ELEMTYPE_TEXT 2
#define ELEMTYPE_UNKOWN 7
#define ELEMTYPE_GRADIENTSHADER 9
#define ELEMTYPE_ANIMATEDSHADER 12

struct MenuInfo
{
	int* vtable;					//0x0
	struct MenuInfo* moreinfo;		//0x4
	int* null;						//0x8
	const char* MenuName;			//0xC
	int hash;						//0x10
	byte flags[8];					//0x14
	int unk1;						//0x1C
	int unk2;						//0x20
	int unk3;						//0x24
	byte pad[8];					//0x28
	int* struct_s;
	int frametime;
};

struct element_params_size
{
	int type1;
	int sizecount1;
	int type2;
	int sizecount2;
	int type3;
	int sizecount3;
	int type4;
	int sizecount4;
	int type5;
	int sizecount5;
};

struct ui_main_t {
	short field_0x0;
	undefined field_0x2;
	undefined field_0x3;
	undefined field_0x4;
	undefined field_0x5;
	undefined field_0x6;
	undefined field_0x7;
	undefined field_0x8;
	char field_0x9;
	undefined field_0xa;
	undefined field_0xb;
	union element_t* elem;
	union element_t* base;
	union element_t* next;
	undefined field_0x18;
	undefined field_0x19;
	undefined field_0x1a;
	undefined field_0x1b;
	uint field_0x1c;
	undefined field_0x20;
	undefined field_0x21;
	undefined field_0x22;
	undefined field_0x23;
	undefined4 field_0x24;
	int field_0x28;
	undefined4 field_0x2c;
	int loopNum;			//0x30
	element_params_size* somestruct;		//0x34
	dword field_0x38;
	uint field_0x3c;
	undefined field_0x40;
	undefined field_0x41;
	undefined field_0x42;
	undefined field_0x43;
	undefined field_0x44;
	undefined field_0x45;
	undefined field_0x46;
	undefined field_0x47;
	undefined field_0x48;
	undefined field_0x49;
	undefined field_0x4a;
	undefined field_0x4b;
	uint field_0x4c;
};

struct Text_Options
{
	float x_angle;		//0x00
	float y_angle;		//0x04
	float DiagonalAxis;	//0x08
	float x_pos;		//0x0C
	float y_pos;		//0x10
	float field0x14;	//0x14
	float RotationY;	//0x18
	float RotationX;	//0x1C
	float angle;		//0x20
	float rotation;		//0x24
	float w;			//0x28
	float h;			//0x2C
	float field0x30;	//0x30
	float field0x34;	//0x34
	float field0x38;	//0x38
	float field0x3C;	//0x3C
	float field0x40;	//0x40
};

struct Shader_Options
{
	float x_angle;		//0x00
	float y_angle;		//0x04
	float field0x8;		//0x08
	float x_pos;		//0x0C
	float y_pos;		//0x10
	float field0x14;	//0x14
	float y_flip;		//0x18
	float x_flip;		//0x1C
	float angle;		//0x20
	float rotation;		//0x24
	float w;			//0x28
	float h;			//0x2C
	float field0x30;	//0x30
	float s0;			//0x34
	float t0;			//0x38
	float s1;			//0x3C
	float t1;			//0x40
	float field0x44;	//0x44
	float field0x48;	//0x48
	float field0x4C;	//0x4C
	float field0x50;	//0x50
};

union OptionsUnion
{
	Text_Options text;
	Shader_Options shader;
};

struct FEColor
{
	int b; int g; int r; int a;
};

struct screenoptions_t
{
	FEColor col;
	OptionsUnion opt;
};

struct txtfileargs
{
	char* startoftext;
	int _0x4;
	char* endoftext;
};

struct stringrandomize_t
{
	stringrandomize_t* field_0x0;
	stringrandomize_t* field_0x4;
	int field_0x8;
	wchar_t randomchars[64];

};

struct stringrandomize_r_t
{
	int* vtable;
	int var;
	stringrandomize_t* pstruct;
};

struct shader_t
{
	void* funcs;		//0x00
	union element_t* next;	//0x04
	union element_t* prev;	//0x08
	int elementNum;		//0x0C
	int hash;			//0x10
	int idk;			//0x14
	int type;			//0x18
	int render_flags;	//0x1C 
	short field_20;		//0x20
	short field_22;		//0x22
	int material_hash;	//0x24
	int field_28;		//0x28
	screenoptions_t* settings;//0x2C
	int color_size;		//0x30
	int* vtable1;		//0x34
	int field_38;		//0x38
	int field_3C;		//0x3C
	int field_40;		//0x40
	int* vtable2;		//0x44
	char pad02[0x10];	//0x48
	struct DrawCmd_t* drawcmd;	//0x58
	int* field_0x5C;	//0x5C
};

struct text_t
{
	void* funcs;			//0x00
	union element_t* next;	//0x04
	union element_t* prev;	//0x08
	int elementNum;		//0x0C
	int hash;			//0x10
	int idk;			//0x14
	int type;			//0x18
	int render_flags;	//0x1C 
	short field_20;		//0x20
	short field_22;		//0x22
	int font_hash;		//0x24
	int field_28;		//0x28
	screenoptions_t* settings;//0x2C
	int color_size;		//0x30
	int* vtable1;		//0x34
	int field_38;		//0x38
	int field_3C;		//0x3C
	int field_40;		//0x40
	int* vtable2;		//0x44
	char pad02[0x10];	//0x48
	struct DrawCmd_t* drawcmd;	//0x58
	int* field_0x5C;	//0x5C
	int texthash;		//0x60
	wchar_t* text;		//0x64
	int alloc_text_len; //0x68
	int field_0x6C;		//0x6C
	int field_0x70;		//0x70
	int field_0x74;		//0x74
};

union element_t
{
	text_t text;
	shader_t shader;
};

struct font_t
{
	int font;
};

struct DrawCmd_t
{
	DrawCmd_t* next;	//0x00
	int pad;			//0x04
	element_t* element;	//0x08
	int or2flag;		//0x0C
	int count;			//0x10
	font_t* font;		//0x14
	int* unk1;			//0x18
	int* unk2;			//0x1C
	int unk3;			//0x20
};

struct huds_list
{
	element_t* data;
	float f1;
};

struct drawparams
{
	int* huds_draw_funcs;
	int idk;
	int inGame;
};

struct button_info
{

};

struct cFeng_t
{
	byte bools[4];			//0x000
	button_info* buttons;	//0x004
	char pad00[0xD8];		//0x008
	MenuInfo* menuinfo1;	//0xE0
	MenuInfo* menuinfo2;	//0xE4
	int* vtable;			//0xE8
	char pad01[0x1c];		//0xEC
	drawparams* draw_params;//0x108
	int hudsnum;			//0x10C
	huds_list hudslist[306];//0x110
};

#define cFEng_mInstance (**(cFeng_t***)0x10180754)

struct asset_t
{
	int hash;	//0x0
	char* name;	//0x4
	int type;	//0x8
	int field_0xC;	//0xC
	int hash_upper;//0x10
	int field_0x14;	//0x14
};

struct ValuesTable_s
{
	short words1[4];		//0x00
	float valuepoints1[9];	//0x08
	short words2[4];		//0x2C
	float valuepoints2[3];	//0x34
};

struct Transmission
{
	short unk0;			//0x00
	short gears;		//0x02
	short unk1;			//0x04
	short unk2;			//0x06
	float reverse;		//0x08
	float unk3;			//0x0C
	float gearratio[7];	//0x10
	int f_0x2c;
	int f_0x30;
	int f_0x34;
	int f_0x38;
	int f_0x3c;
	int f_0x40;
	int f_0x44;
	int f_0x48;
	int f_0x4c;
	int f_0x50;
	int f_0x54;
	int f_0x58;
	int f_0x5c;
};

struct EngineValueTable
{
	int* unk0;
	Transmission* table;
	int* unk8;
	int* unkC;
};

struct EngineLogic_t
{
    int* EngineRacerTable;//0x00
    char pad00[0xC];    //0x04
    int* field_0x10;    //0x10
    int* field_0x14;    //0x14
    int* field_0x18;    //0x18
    int field_0x1c;     //0x1C
    int* vtable2;       //0x20
    char pad01[0xC];    //0x24
    int* field_0x30;    //0x30
    int* field_0x34;    //0x34
    uint64_t field_0x38;//0x38
    int somenum;
    dword field_0x44;
	int* field_0x48;
	int* field_0x4c;
	int* vtable4;
	int* field_0x54;
	int* field_0x58;
	int* field_0x5c;
	int* field_0x60;
	int* field_0x64;
	int* field_0x68;
	int* field_0x6c;
	int* field_0x70;
	int* field_0x74;
	int* field_0x78;
	int* field_0x7c;
	int* field_0x80;
	int* field_0x84;
	int* field_0x88;
	int* field_0x8c;           //0x8C
    int* field_0x90;            //0x90
    int* field_0x94;            //0x94
    int* field_0x98;            //0x98
    int* field_0x9c;            //0x9C
    int* field_0xa0;            //0xA0
    int* field_0xa4;            //0xA4
    float acceleration;         //0xA8
    int gear;                   //0xAC
    float revmatch;             //0xB0
    float throttle;             //0xB4
	float boostPerc;			//0xB8
	float boost;				//0xBC
	float powerIncr;			//0xC0
	float field_0xc4;
	float field_0xc8;
	float field_0xcc;
    float field_0xd0;
	float field_0xd4;
	float field_0xd8;
	float field_0xdc;
	float field_0xe0;
	float field_0xe4;
	float field_0xe8;
	float field_0xec;
	float field_0xf0;
	float field_0xf4;
	float field_0xf8;
	float field_0xfc;
	float field_0x100;
	float field_0x104;
	float field_0x108;
	float field_0x10c;
	float field_0x110;
    float EngineRPS;		//0x114
	float SomeDelta;		//0x118
    float ClutchRPS;		//0x11C
    float nosBar;			//0x120
    float multiplier;		//0x124
	float usingnos;			//0x128
	float field_0x12c;		//0x12C
    char field_0x130;
    char field_0x131;
    char field_0x132;
    char field_0x133;
	float field_0x134;
    int* field_0x138;
	int* field_0x13c;
	int* field_0x140;
	EngineValueTable NitrousMap;	//0x144
	EngineValueTable BoostSettings;	//0x154
	EngineValueTable TorqueMap;		//0x164
	EngineValueTable GearRatios;	//0x174
    int* field_0x184;
    int* field_0x188;
	int field_0x18c;
	int field_0x190;
    float rpm;              //0x194
    int GearChangeResult;	//0x198
    int transmissionLogic;  //0x19C
	float field_0x1a0;
	float field_0x1a4;
	float field_0x1a8;
	float field_0x1ac;
    int field_0x1b0;
	int field_0x1b4;
	float field_0x1b8;
	float field_0x1bc;
};

int getsizeofEngineLogic_t() { return sizeof(EngineLogic_t);}

template<typename T>
class LinkedList
{
public:
	T* mBegin;
	T* mEnd;
	uint32_t mSize;
};

struct Behavior
{
	char pad[0x38]; //0x00
	int hash1;		//0x38
	int hash2;		//0x3C
};

struct BehaviorList
{
	BehaviorList* next;
	int v1;
	Behavior* behavior;
};

struct PVehicle
{
	int* field_0x0;
	dword field_0x4;
	dword field_0x8;
	dword field_0xc;
	int* field_0x10;
	int* field_0x14;
	int* field_0x18;
	dword field_0x1c;
	int* field_0x20;
	dword field_0x24;
	dword field_0x28;
	dword field_0x2c;
	int* field_0x30;
	int* field_0x34;
	dword field_0x38;
	dword field_0x3c;
	int* field_0x40;
	int* field_0x44;
	dword field_0x48;
	dword field_0x4c;
	int* field_0x50;
	int* field_0x54;
	byte field_0x58;
	byte field_0x59;
	byte field_0x5a;
	byte field_0x5b;
	dword field_0x5c;
	dword field_0x60;
	dword field_0x64;
	dword field_0x68;
	dword field_0x6c;
	dword field_0x70;
	dword field_0x74;
	dword field_0x78;
	dword field_0x7c;
	dword field_0x80;
	dword field_0x84;
	dword field_0x88;
	dword field_0x8c;
	dword field_0x90;
	dword field_0x94;
	dword field_0x98;
	dword field_0x9c;
	dword field_0xa0;
	dword field_0xa4;
	dword field_0xa8;
	dword field_0xac;
	dword field_0xb0;
	dword field_0xb4;
	dword field_0xb8;
	LinkedList<BehaviorList> behaviors;//0xBC
	dword field_0xc0;
	dword field_0xc4;
	dword field_0xc8;
	dword field_0xcc;
	dword field_0xd0;
	dword field_0xd4;
	dword field_0xd8;
	dword field_0xdc;
	dword field_0xe0;
	dword field_0xe4;
	dword field_0xe8;
	dword field_0xec;
	dword field_0xf0;
	dword field_0xf4;
	dword field_0xf8;
	dword field_0xfc;
	dword field_0x100;
	dword field_0x104;
	dword field_0x108;
	dword field_0x10c;
	dword field_0x110;
	dword field_0x114;
	dword field_0x118;
	dword field_0x11c;
	dword field_0x120;
	dword field_0x124;
	dword field_0x128;
	dword field_0x12c;
	dword field_0x130;
	dword field_0x134;
	dword field_0x138;
	dword field_0x13c;
	dword field_0x140;
	float field_0x144;
	float field_0x148;
	float field_0x14c;
	float field_0x150;
	float field_0x154;
	float field_0x158;
	dword field_0x15c;
	float field_0x160;
	float field_0x164;
	float field_0x168;
	int DriverClass;
	dword field_0x170;
	dword field_0x174_var1;
	float field_0x178;
	dword field_0x17c_var2;
	byte field_0x180;
	byte field_0x181;
	byte field_0x182;
	byte field_0x183;
	dword field_0x184;
	byte field_0x188;
	byte field_0x189;
	byte field_0x18a;
	byte field_0x18b;
	dword field_0x18c;
	dword field_0x190;
	dword field_0x194;
	dword field_0x198;
	dword field_0x19c;
	dword field_0x1a0;
	dword field_0x1a4;
	dword field_0x1a8;
	dword field_0x1ac;
	byte field_0x1b0;
	byte field_0x1b1;
	byte field_0x1b2;
	byte field_0x1b3;
	dword field_0x1b4;
	byte field_0x1b8;
	byte field_0x1b9;
	byte field_0x1ba;
	byte field_0x1bb;
	dword field_0x1bc;
	dword field_0x1c0;
	byte field_0x1c4;
	byte field_0x1c5;
	byte field_0x1c6;
	byte field_0x1c7;
	dword field_0x1c8;
	dword field_0x1cc;
	dword field_0x1d0;
	dword field_0x1d4;
	dword field_0x1d8;
	dword field_0x1dc;
	byte field_0x1e0;
	byte field_0x1e1;
	byte field_0x1e2;
	byte field_0x1e3;
	dword field_0x1e4;
	dword field_0x1e8;
	dword field_0x1ec;
	dword field_0x1f0;
	dword field_0x1f4;
	dword field_0x1f8;
	dword field_0x1fc;
	dword field_0x200;
	const char* Manager;
	dword field_0x208;
	dword field_0x20c;
};

int getsizeofPVehicle() { return sizeof(PVehicle); }

struct AIVehicleHuman
{
	int* field_0x0;
	int* field_0x4;
	int* field_0x8;
	int* field_0xc;
	int* field_0x10;
	int* field_0x14;
	int* field_0x18;
	int* field_0x1c;
	int* field_0x20;
	int* field_0x24;
	int* field_0x28;
	int* field_0x2c;
	PVehicle* pvehicle;
	char pad00[0x2fc];	//0x34
};

struct View
{
	Matrix44* m1;			//0x00
	char* string;			//0x04
	int idk;				//0x08
	bool render;			//0x0C
	float LodDistance;		//0x10
	float fv0x14;			//0x14
	float fv0x18;			//0x18
	float fv0x1C;			//0x1C
	float fv0x20;			//0x20
	short sh0x24;			//0x24
	int in0x28;				//0x28
	int in0x2C;				//0x2C
	float values[7][4];		//0x30
};