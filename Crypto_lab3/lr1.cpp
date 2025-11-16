#define _CRT_SECURE_NO_WARNINGS
#include "Cript.h"
#include <iostream>
#include "lr1.h"
#define CD 16

extern Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD], g_q[CD], g_p_1[CD]; //Глобальные переменные

																																		  /*
////////////////////////////////////////////////
Расширенный алгоритм Евклида для нахождения обратного элемента
///////////////////////////////////////////////
*/


// Функция, проверяющая, отлично число от нуля или нет
bool dlina(Digit elem[]) {  
	for (int i = 0; i < CD; i++)
	{
		if (elem[i] != 0) { return false; }
	}
	return true;
}


//Функция, реализующая расширенный алгоритм Евклида по модулю p
EVCL gcd(EVCL X) {  
	EVCL U;
	if (dlina(X.a2)) { //Если НОД = 1
		Assig(X.a1, U.a1);
		StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", U.a2);
		StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", U.a3);
		return U;
	}
	else {
		Digit *res = new Digit[CD];
		Digit *res1 = new Digit[CD];
		Mod_Div(X.a1, X.a2, res); //Вычисление остатка от деления
		Assig(X.a2, U.a1);
		Assig(res, U.a2);
		Assig(X.a3, U.a3); 
		U = gcd(U); //Рекурсивный вызов функции gcd(b, a % b, mod)
		Int_Div(X.a1, X.a2, res);
		Mult(U.a3, res, res1);
		Sub(U.a2, res1, res);
		Assig(U.a1, X.a1);
		Assig(U.a3, X.a2);
		Assig(res, X.a3);
		delete[] res;
		delete[] res1;
		return X;
	}
}
//Функция, реализующая расширенный алгоритм Евклида по модулю q
EVCL gcd_q(EVCL X) {  
	EVCL U;
	if (dlina(X.a2)) { //Если НОД = 1
		Assig(X.a1, U.a1);
		StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", U.a2);
		StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", U.a3);
		return U;
	}
	else {
		Digit *res = new Digit[CD];
		Digit *res1 = new Digit[CD];
		Mod_Div(X.a1, X.a2, res); //Вычисление остатка от деления
		Assig(X.a2, U.a1);
		Assig(res, U.a2);
		Assig(X.a3, U.a3); //Рекурсивный вызов функции
		U = gcd_q(U);
		Int_Div(X.a1, X.a2, res);
		Mult_q(U.a3, res, res1);
		Sub_q(U.a2, res1, res);
		Assig(U.a1, X.a1);
		Assig(U.a3, X.a2);
		Assig(res, X.a3);
		delete[] res;
		delete[] res1;
		return X;
	}
}

// Вспомогательная функция для нахождения обратного элемента по модулю p
void rev(Digit prym[], Digit obr[]) 
{
	EVCL A;
	Assig(prym, A.a1);
	Assig(g_p, A.a2);
	Assig(g_p, A.a3);
	A = gcd(A);
	Assig(A.a2, obr);
}
// Вспомогательная функция для нахождения обратного элемента по модулю q
void rev2(Digit prym[], Digit obr[])
{
	EVCL A;
	Assig(prym, A.a1);
	Assig(g_q, A.a2);
	Assig(g_q, A.a3);
	A = gcd_q(A);
	Assig(A.a2, obr);
}

//Нахождение обратного элемента модулярным возведением в степень
void rev_mod(const Digit ch[], Digit res[]) {
	Digit *bufer = new Digit[CD];
	Digit *step = new Digit[CD];
	Digit *a = new Digit[CD];
	Assig(g_e, res);
	Assig(ch, bufer);
	StringToNumber("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD95", step);
	for (int i = 0; i <= 16 * CD - 1; i++)
	{
		Digit current = step[(int)(i / 16)];
		if ((current >> (i % 16)) & 0x0001) {
			Mult(res, bufer, a);
			Assig(a, res);
		}
		Mult(bufer, bufer, a);
		Assig(a, bufer);
	}
	delete[] bufer;
	delete[] step;
	delete[] a;
}



