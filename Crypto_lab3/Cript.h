#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cmath>
using namespace std;
typedef unsigned long int TwoDigit;
typedef unsigned short int Digit;
typedef long int LongDigit;
#define CD 16
#define RANDOM true
#define NotRANDOM false
#define MAX_DIV_OPERAND_SIZE 64
#define MAXDIGIT 0xFFFF
#define LODIGIT(twodigit) (Digit)(twodigit)
#define HIDIGIT(twodigit) (Digit)((twodigit)>>(sizeof(Digit)*8))
#define MAKE_TWO_DIGIT(digit1,digit2) (((TwoDigit) (digit1) << (sizeof(Digit) * 8)) | (digit2))
extern Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD], g_q[CD], g_p_1[CD], g_1[CD], g_2[CD], g_3[CD];

void Init();
void StringToNumber(string str, Digit Res[]);
string NumToStringDigit(const Digit Numb[]);
void Assig(const Digit first[], Digit second[]);
bool Less(const Digit first[], const Digit second[]);
bool More(const Digit first[], const Digit second[]);
bool Equal(const Digit first[], const Digit second[]);
void Add(const Digit first[], const Digit second[], Digit Res[]);
void Add_q(const Digit first[], const Digit second[], Digit Res[]);
void Sub(const Digit first[], const Digit second[], Digit Res[]);
void Sub_q(const Digit first[], const Digit second[], Digit Res[]);
void Mod_Div(const Digit U[], const Digit V[], Digit Q[]);
void Int_Div(const Digit U[], const Digit V[], Digit Q[]);
void Mult(const Digit first[], const Digit second[], Digit Res[]);
void Mult_q(const Digit first[], const Digit second[], Digit Res[]);