#pragma once
#include "lr2.h"
typedef struct{
    Digit x[CD];
    Digit y[CD];
} point;

void print(point A);
void Add_Edwards(const Digit u1[CD], const Digit v1[CD], 
                const Digit u2[CD], const Digit v2[CD],
                Digit u3[CD], Digit v3[CD]);
void Add_Vey(const Digit x1[CD], const Digit y1[CD], const Digit x2[CD], 
    const Digit y2[CD], Digit x_res[CD], Digit y_res[CD]);