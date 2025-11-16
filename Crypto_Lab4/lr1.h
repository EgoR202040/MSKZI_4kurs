#pragma once
extern Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD], g_q[CD], g_p_1[CD]; //Глобальные переменные
struct EVCL  
{
	Digit a1[CD], a2[CD], a3[CD];
};
//Функция, реализующая расширенный алгоритм Евклида по модулю p
EVCL gcd(EVCL X);
void rev(Digit prym[], Digit obr[]);
void rev_mod(const Digit ch[], Digit res[]);