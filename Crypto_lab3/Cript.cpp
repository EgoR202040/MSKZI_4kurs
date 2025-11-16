#include "Cript.h"
#define CD 16

Digit hexStringToInt(string hex_pred)
{
	Digit res = 0;
	int deg;
	for (int i = 0; i < hex_pred.size(); i++)
	{
		if (hex_pred[hex_pred.size() - 1 - i] >= '0' && hex_pred[hex_pred.size() - 1 - i] <= '9')
		{
			deg = hex_pred[hex_pred.size() - 1 - i] - '0';
			res += deg * pow(16, i);
		}
		else
			switch ((hex_pred[hex_pred.size() - 1 - i]))
			{
			case ('A'):
				deg = 10;
				res += deg * pow(16, i);
				break;
			case ('B'):
				deg = 11;
				res += deg * pow(16, i);
				break;
			case ('C'):
				deg = 12;
				res += deg * pow(16, i);
				break;
			case ('D'):
				deg = 13;
				res += deg * pow(16, i);
				break;
			case ('E'):
				deg = 14;
				res += deg * pow(16, i);
				break;
			case ('F'):
				deg = 15;
				res += deg * pow(16, i);
				break;
			case ('a'):
				deg = 10;
				res += deg * pow(16, i);
				break;
			case ('b'):
				deg = 11;
				res += deg * pow(16, i);
				break;
			case ('c'):
				deg = 12;
				res += deg * pow(16, i);
				break;
			case ('d'):
				deg = 13;
				res += deg * pow(16, i);
				break;
			case ('e'):
				deg = 14;
				res += deg * pow(16, i);
				break;
			case ('f'):
				deg = 15;
				res += deg * pow(16, i);
				break;
			}
	}
	return res;
}
void StringToNumber(
	string str, /*������������� ������*/
	Digit Res[] /*���������� �����*/
)
{
	for (int i = 0; i < CD; i++)
		Res[CD - 1 - i] = hexStringToInt(str.substr(i * 4, 4));
}
string NumToStringDigit(
	const Digit Numb[]
)
{
	stringstream srt;
	for (int i = 0; i < CD; i++)
		srt << setfill('0') << setw(4) << hex << Numb[CD - 1 - i];
	return srt.str();
}
/*--------------------------------------------------------
������������� ��������
--------------------------------------------------------*/
void Init() {
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", g_1);
	StringToNumber("7e7e82520f9f015faa1d0f18c14ab9fb35188275da3fd94206b74f34a48e0ecd", g_s); //s=(e-d) / 4
	StringToNumber("0100fe73f595ff158e974b44d478d9588744fe5c192ac47ea63075dce7a14aaa", g_t); //t=(e+d) / 6
	StringToNumber("7f7f80c60535007538b45a5d95c39353bc5d80d1f36a9dc0ace7c5118c2f5977", g_h); //t+s
	StringToNumber("7d7d83de1a09024a1b85c3d3ecd1e0a2add38419c11514c36086d957bcecc423", g_k); //s-t
	StringToNumber("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD97", g_p);
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", g_e);
	StringToNumber("0605F6B7C183FA81578BC39CFAD518132B9DF62897009AF7E522C32D6DC7BFFB", g_d);
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000269", g_razn);
	StringToNumber("000000000000000000000000000000000000000000000000000000000000000D", g_u);
	StringToNumber("60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7", g_v);
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", g_zero);
	StringToNumber("400000000000000000000000000000000FD8CDDFC87B6635C115AF556C360C67", g_q);
	StringToNumber("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD96", g_p_1);
	StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", g_1);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000002", g_2);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000003", g_3);
}
/*--------------------------------------------------------
��������� ��������� � ����������
--------------------------------------------------------*/
void Assig(const Digit first[], Digit second[]) {
	for (int i = 0; i < CD; i++) {
		second[i] = first[i];
	}
}
bool Less(const Digit first[], const Digit second[]) {
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return true;
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return false;
	}
	return false;
}
bool More(const Digit first[], const Digit second[]) {
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return true;
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return false;
	}
	return false;
}
bool Equal(const Digit first[], const Digit second[]) {
	for (int i = 0; i < CD; i++)
	{
		if (first[CD - 1 - i] > second[CD - 1 - i])
			return false;
		if (first[CD - 1 - i] < second[CD - 1 - i])
			return false;
	}
	return true;
}
/*--------------------------------------------------------
�������� ������� ����� (*pcf,Res) = first + second
--------------------------------------------------------*/
static void Add(
	Digit Res[], /* ����� (size ����) */
	const Digit first[], /* ������ ��������� (size ����) */
	const Digit second[], /* ������ ��������� (size ����)*/
	Digit *pcf, /* ���� �������� (1 �����), �.�. NULL */
	int size) /* ������ ����� � ������ */
{
	TwoDigit buf; /* ��� �������� �������������� ���������� �������� */
	Digit cf = 0; /* ��� �������� �������������� �������� */
	int i; /* �������� ���������� ����� */
	for (i = 0; i < size; i++) /* ����������� ����� �� i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf;/* �������� i-� ���� � ����������� �������� */
		Res[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� ����� */
		cf = HIDIGIT(buf); /* ������� - ������� ����� ����� */
	}
	if (pcf) *pcf = cf; /* ���� ����� pcf �� 0, ���������� ������� */
}
void Add( /* �������� �� ������ p*/
	const Digit first[], /* ������ ��������� (size ����) */
	const Digit second[], /* ������ ��������� (size ����)*/
	Digit Res[] /* ����� (size ����) */
)
{
	TwoDigit buf; /* ��� �������� �������������� ���������� �������� */
	Digit cf = 0; /* ��� �������� �������������� �������� */
	int i; /* �������� ���������� ����� */
	for (i = 0; i < CD; i++) /* ����������� ����� �� i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf;/* �������� i-� ���� � ����������� �������� */
		Res[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� ����� */
		cf = HIDIGIT(buf); /* ������� - ������� ����� ����� */
	}
	if (cf!=0) {
		cf = 0;
		for (i = 0; i < CD; i++) /* ����������� ����� �� i */
		{
			buf = (TwoDigit)Res[i] + g_razn[i] + cf;/* �������� i-� ���� � ����������� �������� */
			Res[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� ����� */
			cf = HIDIGIT(buf); /* ������� - ������� ����� ����� */
		}
	}/* ���� ����� pcf �� 0, ���������� ������� */
}
void Add_q( /* �������� �� ������ p*/
	const Digit first[], /* ������ ��������� (size ����) */
	const Digit second[], /* ������ ��������� (size ����)*/
	Digit Res[] /* ����� (size ����) */
)
{
	TwoDigit buf; /* ��� �������� �������������� ���������� �������� */
	Digit cf = 0; /* ��� �������� �������������� �������� */
	int i; /* �������� ���������� ����� */
	for (i = 0; i < CD; i++) /* ����������� ����� �� i */
	{
		buf = (TwoDigit)first[i] + second[i] + cf;/* �������� i-� ���� � ����������� �������� */
		Res[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� ����� */
		cf = HIDIGIT(buf); /* ������� - ������� ����� ����� */
	}
	while (More(Res,g_q)) { 
		Digit *z = new Digit[CD];
		Sub(Res, g_q, z);
		Assig(z, Res);
		delete[] z;
	}
}



/*--------------------------------------------------------
��������� ������� ����� (*pcf,Res) = first - second
--------------------------------------------------------*/
static void Sub(
	Digit Res[], /* �������� (size ����) */
	const Digit first[], /* ����������� (size ����) */
	const Digit second[], /* ���������� (size ����) */
	Digit *pcf, /* ���� ����� �������� (1 �����), �.�. NULL */
	int size) /* ������ ����� � ������ */
{
	LongDigit buf; /* �������� ���������� ��� ��������� ����� �������� */
	Digit cf = 0; /* ��� �������� �������������� ����� */
	int i; /* �������� ���������� ����� */
	for (i = 0; i < size; i++) /* ����������� ����� �� i */
	{
		buf = (LongDigit)first[i] - second[i] - cf;/* ��������� i-� ���� � ������ ����������� ����� */
		Res[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� �������� buf */
		cf = HIDIGIT(buf); /* ���� - ������� ����� �������� buf */
		if (cf) cf = 1; /* ���� ���� ���, ����� ����� ����������� 1 */
	}
	if (pcf) *pcf = cf; /* ���� ����� pcf �� 0, ���������� ���� */
}
void Sub(
	const Digit first[], /* ����������� (size ����) */
	const Digit second[], /* ���������� (size ����) */
	Digit Res[] /* �������� (size ����) */
)
{
	Digit Res2[CD];
	LongDigit buf; /* �������� ���������� ��� ��������� ����� �������� */
	Digit cf = 0; /* ��� �������� �������������� ����� */
	int i; /* �������� ���������� ����� */
	if (Less(first, second)) {
		for (i = 0; i < CD; i++) /* ����������� ����� �� i */
		{
			buf = (LongDigit)g_p[i] - second[i] - cf;/* ��������� i-� ���� � ������ ����������� ����� */
			Res2[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� �������� buf */
			cf = HIDIGIT(buf); /* ���� - ������� ����� �������� buf */
			if (cf) cf = 1; /* ���� ���� ���, ����� ����� ����������� 1 */
		}
		Add(first, Res2, Res);
	}
	else {
		for (i = 0; i < CD; i++) /* ����������� ����� �� i */
		{
			buf = (LongDigit)first[i] - second[i] - cf;/* ��������� i-� ���� � ������ ����������� ����� */
			Res[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� �������� buf */
			cf = HIDIGIT(buf); /* ���� - ������� ����� �������� buf */
			if (cf) cf = 1; /* ���� ���� ���, ����� ����� ����������� 1 */
		}
	}
}
void Sub_q(
	const Digit first[], /* ����������� (size ����) */
	const Digit second[], /* ���������� (size ����) */
	Digit Res[] /* �������� (size ����) */
)
{
	Digit Res2[CD];
	LongDigit buf; /* �������� ���������� ��� ��������� ����� �������� */
	Digit cf = 0; /* ��� �������� �������������� ����� */
	int i; /* �������� ���������� ����� */
	if (Less(first, second)) {
		for (i = 0; i < CD; i++) /* ����������� ����� �� i */
		{
			buf = (LongDigit)g_q[i] - second[i] - cf;/* ��������� i-� ���� � ������ ����������� ����� */
			Res2[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� �������� buf */
			cf = HIDIGIT(buf); /* ���� - ������� ����� �������� buf */
			if (cf) cf = 1; /* ���� ���� ���, ����� ����� ����������� 1 */
		}
		Add(first, Res2, Res);
	}
	else {
		for (i = 0; i < CD; i++) /* ����������� ����� �� i */
		{
			buf = (LongDigit)first[i] - second[i] - cf;/* ��������� i-� ���� � ������ ����������� ����� */
			Res[i] = LODIGIT(buf); /* i-� ����� Res - ������� ����� �������� buf */
			cf = HIDIGIT(buf); /* ���� - ������� ����� �������� buf */
			if (cf) cf = 1; /* ���� ���� ���, ����� ����� ����������� 1 */
		}
	}
}

/*--------------------------------------------------------
������� ������� �����
--------------------------------------------------------*/

/*--------------------------------------------------------
	��������� �������� ����� num = 0
--------------------------------------------------------*/
static void Zero(
	Digit num[],                /* ���������� ����� (size ����) */
	int size)                   /* ������ ����� � ������ */
{
	int i;                      /* �������� ���������� ����� */

	for (i = 0; i < size; i++)         /* ����������� ����� �� i */
		num[i] = 0;               /* ��������� i-�� ����� ����� num */
}

static void Assign(
	Digit num1[],               /* ���������� (size ����) */
	const Digit num2[],         /* �������� (size ����) */
	int size)                   /* ������ ����� � ������ */
{
	int i;                      /* �������� ���������� ����� */
	for (i = 0; i < size; i++)         /* ����������� ����� �� i */
		num1[i] = num2[i];        /* ���������� i-�� ����� ����� num1 i-�� ����� ����� num2 */
}

/*--------------------------------------------------------
	��������� �������� ����� �� ����� (*pcf,Res) = num * x
--------------------------------------------------------*/
static void ShortMul(
	Digit Res[],                /* ��������� (size ����) */
	const Digit num[],          /* ������ ����������� (size ����) */
	Digit x,                    /* ������ ����������� (1 �����) */
	Digit *pcf,                 /* ������� �������� ������� (1 �����), �.�. NULL */
	int size)                   /* ������ ����� � ������ */
{
	TwoDigit buf;               /* ���������� ��� �������� �������������� ���������� ��������� ���� ���� */
	Digit cf = 0;                 /* ���������� ��� �������� �������������� ���������� �������� */
	int i;                      /* �������� ���������� ����� */

	for (i = 0; i < size; i++)         /* ����������� ����� �� i */
	{
		buf = (TwoDigit)num[i] * x + cf;/* buf - ����� ��������� ��������� � ����������� �������� */
		Res[i] = LODIGIT(buf);    /* i-� ����� Res - ������� ����� buf */
		cf = HIDIGIT(buf);        /* cf - ������� (������� ����� buf) */
	}
	if (pcf) *pcf = cf;             /* ���� ����� pcf �� 0, ���������� ������� */
}

/*--------------------------------------------------------
	������� �������� ����� �� ����� Res = num/x, *pmod = num % x
--------------------------------------------------------*/
static void ShortDiv(
	Digit Res[],                /* ������� (size ����) */
	const Digit num[],          /* �������  (size ����) */
	Digit x,                    /* �������� (�����) */
	Digit *pmod,                /* ������� (�����), �.�. NULL */
	int size)                   /* ������ ������� ����� � ������ */
{
	TwoDigit buf = 0;             /* ��������������� ���������� */
	int i;                      /* �������� ���������� ����� */

	if (!x) return;              /* ���� x ����� 0 �� ��������� ��������� ������� */
	for (i = size - 1; i >= 0; i--)      /* ����������� ����� �� i */
	{
		buf <<= sizeof(Digit) * 8;  /* ������� ����� buf - ���������� ������� */
		buf |= num[i];            /* ������� ����� buf - i-� ����� ����� num */
		Res[i] = LODIGIT(buf / x);  /* i-� ����� Res - ��������� ������� */
		buf %= x;                 /* ������� ����� buf - ������� */
	}
	if (pmod) *pmod = LODIGIT(buf);/* ���� ����� pmod �� 0, ���������� ������� */
}
/*--------------------------------------------------------
	������� ������� ����� Q = U/V, R = U % V
	���������� ������� �� 0 �� ��������������
--------------------------------------------------------*/
void Div(
	const Digit U[],            /* ������� (sizeU ����) */
	const Digit V[],            /* �������� (sizeV ����) */
	Digit Q[],                  /* ������� (sizeU ����), �.�. NULL */
	Digit R[],					/* ������� (sizeV ����), �.�. NULL */
	int sizeU,
	int sizeV)                  
{
	Digit q, buf1, buf2;                /* ��� �������������� �������� */
	Digit U2[MAX_DIV_OPERAND_SIZE + 1],   /* ��� ���������������� U */
		V2[MAX_DIV_OPERAND_SIZE + 1];   /* ��� ���������������� V */
	TwoDigit inter;                     /* ��� ������������� �������� */
	int i, j, k;                          /* ��������� ���������� */
	Digit d;                            /* ������������� ��������� */

	for (int i = 0; i < 65; i++) {
		U2[i] = 0;
		V2[i] = 0;
	}
/*--- ��������, ����������: */
	if (R) Zero(R, sizeV);                /* ���� ����� ������� R �� 0, �������� ������� */
	if (Q) Zero(Q, sizeU);                /* ���� ����� �������� Q �� 0, �������� ������� */

	for (i = sizeV - 1; (i >= 0)&(!V[i]); i--);  /* ������ ��������, �������� ������� ���������� ���� */
	sizeV = i + 1;                          /* ����� ������ �������� */
	if (!sizeV) return;                  /* ���������� "������� �� ����" (������ ������) */

	for (k = sizeU - 1; (k >= 0)&(!U[k]); k--);  /* ������ ��������, �������� ������� ���������� ���� */
	sizeU = k + 1;                          /* ����� ������ �������� */

	if (sizeV > sizeU)                     /* ���� �������� ������ ��������, �� */
	{
		if (R) Assign(R, U, sizeU);        /* ������� ����� �������� */
		return;                        /* ������ */
	}
	else if (sizeV == 1)                   /* ���� �������� - 1 �����, �� */
	{
		ShortDiv(Q, U, V[0], R, sizeU);     /* ��������� ���������� �������� */
		return;                        /* ������ */
	}

	/*--- ������������: */
	d = (Digit)(((TwoDigit)MAXDIGIT + 1) / ((TwoDigit)V[sizeV - 1] + 1)); /* ������������� ��������� */
	if (d != 1)                        /* ���� d �� 1, */
	{
		ShortMul(V2, V, d, &buf1, sizeV);   /* �������� V �� d */
		V2[sizeV] = buf1;
		ShortMul(U2, U, d, &buf1, sizeU);   /* �������� U �� d */
		U2[sizeU] = buf1;
	}
	else
	{                                   /* ���� d == 1, */
		Assign(V2, V, sizeV);             /* V2 = V */
		V2[sizeV] = 0;
		Assign(U2, U, sizeU);             /* U2 = U */
		U2[sizeU] = 0;
	}
	/*--- �������� ���� */
	for (j = sizeU; j >= sizeV; j--)           /* ����������� �������� ����� �� j (sizeU-sizeV ���) */
	{
		/*--- ��������� ����� �������� */
		inter = MAKE_TWO_DIGIT(U2[j], U2[j - 1]); /* ���������� */
		if (U2[j] == V2[sizeV - 1])          /* ���� ������� ����� �����, */
			q = MAXDIGIT;                 /* ����� �������� q = MAXDIGIT */
		else                            /* ����� */
			q = (Digit)(inter / V2[sizeV - 1]);/* j-� ����� �������� q ������� �������� */
										/* ���� q ���������, */


	/*--- ��������� �������� �������� */
		ShortMul(R, V2, q, &buf1, sizeV);   /* �������� V �� q */
		Sub(U2 + j - sizeV, U2 + j - sizeV, R, &buf2, sizeV);/* �������� ��������� ��������� */
		inter = (LongDigit)U2[j] - buf1 - buf2;
		U2[j] = LODIGIT(inter);

		/*--- ��������� ������� � �������� */
		if (HIDIGIT(inter))              /* ���� ��������� ���� �������������, */
		{                               /* �������������� �������� */
			Add(U2 + j - sizeV, U2 + j - sizeV, V2, &buf2, sizeV);
			U2[j] += buf2;
			q--;                        /* ��������� ����� �������� q �� 1 */
		}
		if (Q)                           /* ���� ����� �������� Q �� 0, */
			Q[j - sizeV] = q;               /* ���������� j-� ����� �������� q */
	}
	/*--- ���������� */
	if (R)                               /* ���� ����� ������� R �� 0, */
	{
		ShortDiv(R, U2, d, NULL, sizeV);    /* �������������� ������� R */
	}
}
void Mod_Div(const Digit U[],            /* ������� (sizeU ����) */
	const Digit V[],				/* �������� (sizeV ����) */
	Digit Q[])						/* ������� */
           
{	Digit *cel = new Digit[CD];
	Div(U, V, cel, Q, CD,CD);
	delete[] cel;
}
void Int_Div(const Digit U[],            /* ������� (sizeU ����) */
	const Digit V[],				/* �������� (sizeV ����) */
	Digit Q[])						/* ����� ����� */
                 
{
	Digit *mod = new Digit[CD];
	Div(U, V, Q, mod,CD,CD);
	delete [] mod;
}


/*--------------------------------------------------------
	��������� �����
--------------------------------------------------------*/

void Mult(const Digit first[], /*������ ���������*/
	const Digit second[], /*������ ���������*/
	Digit Res[] /*������������*/
)
{
	TwoDigit buf; /* ���������� ��� �������� �������������� ���������� ��������� ���� ���� */
	Digit cf = 0; /* ���������� ��� �������� �������������� ���������� �������� */
	int i, j; /* �������� ���������� ����� */
	Digit *Res2 = new Digit[2*CD];
	for (i = 0; i < 2*CD; i++) { Res2[i] = 0; }
	for (i = 0; i < CD; i++)
	{
		cf = 0;
		for (j = 0; j < CD; j++) /* ����������� ����� �� i */
		{
			buf = (TwoDigit)first[i] * second[j] + Res2[i + j] + cf;/* buf - ����� ��������� ��������� � ����������� �������� */
			Res2[i + j] = LODIGIT(buf); /* i-� ����� Res - ������� ����� buf */
			cf = HIDIGIT(buf); /* cf - ������� (������� ����� buf) */
		}
		Res2[i + CD] = cf;
	}
	
	Digit *cel = new Digit[2*CD];
	Div(Res2, g_p, cel, Res, 2*CD, CD);
//	cout << NumToStringDigit(cel) << endl;
//	cout << NumToStringDigit(Res) << endl;
	delete[] cel;
	delete[] Res2;

}
void Mult_q(const Digit first[], /*������ ���������*/
	const Digit second[], /*������ ���������*/
	Digit Res[] /*������������*/
)
{
	TwoDigit buf; /* ���������� ��� �������� �������������� ���������� ��������� ���� ���� */
	Digit cf = 0; /* ���������� ��� �������� �������������� ���������� �������� */
	int i, j; /* �������� ���������� ����� */
	Digit *Res2 = new Digit[2 * CD];
	for (i = 0; i < 2 * CD; i++) { Res2[i] = 0; }
	for (i = 0; i < CD; i++)
	{
		cf = 0;
		for (j = 0; j < CD; j++) /* ����������� ����� �� i */
		{
			buf = (TwoDigit)first[i] * second[j] + Res2[i + j] + cf;/* buf - ����� ��������� ��������� � ����������� �������� */
			Res2[i + j] = LODIGIT(buf); /* i-� ����� Res - ������� ����� buf */
			cf = HIDIGIT(buf); /* cf - ������� (������� ����� buf) */
		}
		Res2[i + CD] = cf;
	}
	Digit *cel = new Digit[2 * CD];

	Div(Res2, g_q, cel, Res, 2 * CD, CD);
	delete[] cel;
	delete[] Res2;
}