#include <cell/cell_fs.h>
#include <string>
#include <stdint.h>
#include <cellstatus.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/types.h>
#include <math.h>
#include <fastmath.h>
#include <cell/sysmodule.h>
#include <sys/random_number.h>
#include <ppu_intrinsics.h>
#include <spu_printf.h>
#include <ctype.h>
#include <cell/pad.h>
#include <cell/sysmodule.h>
#include <limits.h>
#include <sys/return_code.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_msgdialog.h>

#include <sys/synchronization.h>
#include <sys/tty.h> 

#define	TOC	0x93CFF0
#define HIWORD(x)	((x) >> 16)
#define LOWORD(x)	((x) & 0xFFFF)
#define HIDWORD(x)	((x) >> 32)
#define LODWORD(x)	((x) & 0xFFFFFFFF)
#define Sizeof(x) sizeof(x) / 4

typedef unsigned char byte;
typedef long long __int64;
typedef unsigned int uint;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned char    uchar;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char   undefined;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    word;

extern "C"
{
	int _sys_printf(const char* format, ...);
	int _sys_sprintf(char* s, const char* format, ...);
	int _sys_snprintf(char* s, size_t n, const char* format, ...);
	int _sys_vprintf(const char* format, va_list arg);
	int _sys_vsprintf(char* s, const char* format, va_list arg);
	void* _sys_malloc(size_t n);
	void* _sys_memchr(void* ptr, int value, size_t num);
	void* _sys_memcpy(void* destination, const void* source, size_t num);
	int _sys_memcmp(const void* ptr1, const void* ptr2, size_t num);
	void* _sys_memset(void* ptr, int value, size_t num);
	void* _sys_memmove(void* destination, const void* source, size_t num);
	char* _sys_strcat(char* destination, const char* source);
	char* _sys_strchr(char* str, int character);
	int _sys_strcmp(const char* str1, const char* str2);
	char* _sys_strcpy(char* destination, const char* source);
	size_t _sys_strlen(const char* str);
	char* _sys_strncat(char* destination, const char* source, size_t num);
	int _sys_strncmp(const char* str1, const char* str2, size_t num);
	char* _sys_strstr(const char*, const char*);
	char* _sys_strncpy(char* destination, const char* source, size_t num);
	char* _sys_strrchr(char* str, int character);
	int _sys_tolower(int c);
	int _sys_toupper(int c);
	void* _sys_memalign(size_t boundary, size_t size_arg);
	void _sys_free(void* ptr);
}

void fsel_asm(float* frD, float* frA, float* frC, float* frB)
{
	if (*frA >= 0.0f)
	{
		*frD = *frC;
	}
	else
	{
		*frD = *frB;
	}
}
void sleep(usecond_t time)
{
	sys_timer_usleep(time * 1000);
}

enum ps3hardware
{
	CELL_,
	RSX_
};

void Read_Temp(uint64_t CELL_RSX, uint32_t* temperature)
{
	uint32_t _temp;
	system_call_2(383, CELL_RSX, (uint64_t)&_temp);
	*temperature = _temp >> 24; // return °C
}

void console_write(const char* s)
{
	int len = strlen(s);
	system_call_4(SYS_TTY_WRITE, 0, (uint64_t)s, len, (uint64_t)&len);
}

int32_t __attribute__((noinline)) write_process(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}

int __attribute__((noinline)) read_process(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int);
}

int Com_Sprint_t[2] = { 0xBCF84, TOC };
int(*Com_Sprintf)(char* dest, int size, const char* fmt, ...) = (int(*)(char*, int, const char*, ...))Com_Sprint_t;


template<typename... FMT>
char* va(const char* text, FMT... params)
{
	char vaBuffer[128];
	Com_Sprintf(vaBuffer, 128, text, params...);
	return vaBuffer;
}

void __attribute__((noinline)) chartowide(char* str, wchar_t* wstr)
{
	int end = 0;
	for (int i = 0; str[i]; i++)
	{
		wstr[i] = str[i];
		end = i;
	}
	wstr[++end] = 0;
}

template<typename... FMT>
wchar_t* wide_va(const char* text, FMT... params)
{
	char vaBuffer[128];
	Com_Sprintf(vaBuffer, 128, text, params...);

	wchar_t buffer2[128];
	chartowide(vaBuffer, buffer2);

	return buffer2;
}

template<typename... FMT>
void __attribute__((noinline)) cout(const char* text, FMT... params)
{
	char coutBuffer[256];
	Com_Sprintf(coutBuffer, sizeof(coutBuffer), text, params...);
	console_write(coutBuffer);
}

void PatchInJump(int Address, int HookAddress)
{
	int FuncBytes[4];
	HookAddress = *(int*)HookAddress;
	FuncBytes[0] = 0x3D600000 + ((HookAddress >> 16) & 0xFFFF);
	if (HookAddress & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (HookAddress & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	for (int i = 0; i < 4; i++) *(int*)(Address + (i * 4)) = FuncBytes[i];
}

void HookFunction(int Address, int StubAddress, int HookAddress)
{
	int BranchtoAddress = Address + 16;
	int StubData[8];
	StubData[0] = 0x3D600000 + ((BranchtoAddress >> 16) & 0xFFFF);
	if (BranchtoAddress & 0x8000) StubData[0] += 1;
	StubData[1] = 0x396B0000 + (BranchtoAddress & 0xFFFF);
	StubData[2] = 0x7D6903A6;
	int FunctionBytes[4];
	read_process(Address, FunctionBytes, 16);
	StubData[3] = FunctionBytes[0];
	StubData[4] = FunctionBytes[1];
	StubData[5] = FunctionBytes[2];
	StubData[6] = FunctionBytes[3];
	StubData[7] = 0x4E800420;
	write_process(StubAddress, StubData, 32);
	PatchInJump(Address, HookAddress);
}

void reverse(char s[])
{
	int i, j;
	char c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[])
{
	int i, sign;
	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do  		/* generate digits in reverse order */
	{
		s[i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

bool isdigit(char Num)
{
	return (Num >= 0x30 && Num <= 0x39);
}

//#define KEYBOARD_MAX_LENGTH 256
//namespace keyboard
//{
//	wchar_t Title[KEYBOARD_MAX_LENGTH];
//	wchar_t Preset[KEYBOARD_MAX_LENGTH];
//	void GetWC(const char* c, wchar_t* save) {
//		int len = strlen(c);
//		for (int i = 0; i < len; i++)
//			save[i] = (wchar_t)c[i];
//		save[len + 1] = (wchar_t)'\0';
//	}
//	void(*callbackFunction)(char*) = 0;
//	char str[KEYBOARD_MAX_LENGTH + 1];
//	void keyboardCallback(int LocalClientNum, const wchar_t* wString, int Length) {
//		for (int i = 0; i < Length; i++) {
//			str[i] = wString[i];
//		}
//		str[Length] = '\0';
//		callbackFunction(str);
//	}
//
//	int CallKeyboard_s[2] = { 0x46710C, TOC };
//	void* (*CallKeyboard)(int LocalClientNum, wchar_t* title, wchar_t* PresetMessage, int Length, void(*CompleteFunction), int PanelMode) = (void* (*)(int, wchar_t*, wchar_t*, int, void*, int))CallKeyboard_s;
//
//	void OnScreenKeyboard(int LocalClientNum, wchar_t* Title, wchar_t* PresetMessage, int Length, void(*CompleteFunction)(int LocalClientNum, const wchar_t* wString, int Length), int PanelMode) {
//		*(char*)0xD82144 = 1;
//		CallKeyboard(LocalClientNum, Title, PresetMessage, Length, CompleteFunction, PanelMode);
//	}
//	void openKeyboard(void(*callbackFunc)(char*), int maxLength = KEYBOARD_MAX_LENGTH, const char* title = "Enter Value", const char* presetMessage = "") {
//		callbackFunction = callbackFunc;
//		GetWC(title, Title);
//		GetWC(presetMessage, Preset);
//		OnScreenKeyboard(0, Title, Preset, maxLength, keyboardCallback, 1);
//	}
//}

int __attribute__((noinline)) Atoi(const char* c)
{
	int value = 0;
	int sign = 1;
	if (*c == '+' || *c == '-')
	{
		if (*c == '-') sign = -1;
		c++;
	}
	while (isdigit(*c))
	{
		value *= 10;
		value += (int)(*c - '0');
		c++;
	}
	return value * sign;
}

int getFileSize(char* file) {
	int fd;
	int ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret) {
		CellFsStat sb;
		ret = cellFsFstat(fd, &sb);
		if (!ret) {
			return sb.st_size;
		}
	}
	return -1;
}
void readFile(char* file, char buf[], int size) {
	int fd, ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret)
		{
			cellFsClose(fd);
		}
	}
}