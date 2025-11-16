#include "lr3.h"
extern Digit x[CD], y[CD];
Digit g_2[CD], g_3[CD], g_a[CD];

void check_parameters() {
    std::cout << "Параметры кривой:" << std::endl;
    std::cout << "g_s: " << NumToStringDigit(g_s) << std::endl;
    std::cout << "g_t: " << NumToStringDigit(g_t) << std::endl;
    std::cout << "g_d: " << NumToStringDigit(g_d) << std::endl;
    std::cout << "g_e: " << NumToStringDigit(g_e) << std::endl;
    std::cout << "g_p: " << NumToStringDigit(g_p) << std::endl;
}

void test_conversion_identity() {
    Digit test_x[CD], test_y[CD], test_u[CD], test_v[CD];
    
    // Возьмите известную точку на кривой
    StringToNumber("91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28", test_x);
    StringToNumber("32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C", test_y);
    
    std::cout << "Тест тождественности преобразований:" << std::endl;
    std::cout << "Исходная точка: x=" << NumToStringDigit(test_x) << " y=" << NumToStringDigit(test_y) << std::endl;
    
    // Преобразуем туда-обратно
    VeyToEdv(test_x, test_y);
    Assig(g_u, test_u);
    Assig(g_v, test_v);
    std::cout << "В форме Эдвардса: u=" << NumToStringDigit(test_u) << " v=" << NumToStringDigit(test_v) << std::endl;
    
    EdvToVey(test_u, test_v);
    std::cout << "Обратно в Вейерштрасса: x=" << NumToStringDigit(x) << " y=" << NumToStringDigit(y) << std::endl;
    
    if (Equal(test_x, x) && Equal(test_y, y)) {
        std::cout << "✓ Преобразования тождественны" << std::endl;
    } else {
        std::cout << "✗ Ошибка в преобразованиях!" << std::endl;
    }
}

void print(point A){
    std::cout << NumToStringDigit(A.x) << std::endl;
    std::cout << NumToStringDigit(A.y) << std::endl;
}

void Add_Edwards(const Digit u1[CD], const Digit v1[CD], 
                const Digit u2[CD], const Digit v2[CD],
                Digit u3[CD], Digit v3[CD]) {
    
    auto temp1 = std::make_unique<Digit[]>(CD);
    auto temp2 = std::make_unique<Digit[]>(CD);
    auto temp3 = std::make_unique<Digit[]>(CD);
    auto base = std::make_unique<Digit[]>(CD);
    auto up1 = std::make_unique<Digit[]>(CD);
    auto down1 = std::make_unique<Digit[]>(CD);
    auto down1_rv = std::make_unique<Digit[]>(CD);
    auto up2 = std::make_unique<Digit[]>(CD);
    auto down2 = std::make_unique<Digit[]>(CD);
    auto down2_rv = std::make_unique<Digit[]>(CD);
    

    
    // u3 = (u1*v2 + u2*v1) / (1 + d*u1*u2*v1*v2)
    Mult(u1, v2, temp1.get());
    Mult(u2, v1, temp2.get());
    Add(temp1.get(), temp2.get(), up1.get());
   
    memset(temp1.get(), 0x00, CD * sizeof(Digit));
    memset(temp2.get(), 0x00, CD * sizeof(Digit));

    Mult(g_d, u1, temp1.get());
    Mult(temp1.get(), u2, temp2.get());
    Mult(temp2.get(), v1, temp1.get());
    Mult(temp1.get(), v2, base.get());

    Add(g_1, base.get(), down1.get());

    rev(down1.get(), down1_rv.get());
    Mult(up1.get(), down1_rv.get(), u3);

    // v3 = (v1*v2 - e*u1*u2) / (1 - d*u1*u2*v1*v2)
    memset(temp1.get(), 0x00, CD * sizeof(Digit));
    memset(temp2.get(), 0x00, CD * sizeof(Digit));

    Mult(v1, v2, temp1.get());
    Mult(u1, u2, temp2.get());
    Mult(g_e, temp2.get(), temp3.get());
    Sub(temp1.get(), temp3.get(), up2.get());
    
    Sub(g_1, base.get(), down2.get());
    
    rev(down2.get(), down2_rv.get());
    Mult(up2.get(), down2_rv.get(), v3);
}

void Add_Vey(const Digit x1[CD], const Digit y1[CD], const Digit x2[CD], 
    const Digit y2[CD], Digit x_res[CD], Digit y_res[CD]){
    
    // Умные указатели для всех временных переменных
    auto lamda = std::make_unique<Digit[]>(CD);
    auto mult = std::make_unique<Digit[]>(CD);
    auto mult_rev = std::make_unique<Digit[]>(CD);
    auto add = std::make_unique<Digit[]>(CD);
    auto g_x1_x1 = std::make_unique<Digit[]>(CD);
    auto sub1 = std::make_unique<Digit[]>(CD);
    auto sub2 = std::make_unique<Digit[]>(CD);
    auto sub2_rev = std::make_unique<Digit[]>(CD);
    auto lamda2 = std::make_unique<Digit[]>(CD);
    
    if(Equal(x1, x2)){
        Mult(x1, x1, g_x1_x1.get()); // x_1 ^ 2
        Mult(g_3, g_x1_x1.get(), mult.get()); // (x_1 ^ 2)*3
        Add(mult.get(), g_a, add.get()); // (x_1 ^ 2)*3 + a
        Mult(g_2, y1, mult.get());
        rev(mult.get(), mult_rev.get());
        Mult(add.get(), mult_rev.get(), lamda.get()); // Лямбда подсчитана
    } else {
        Sub(y2, y1, sub1.get());
        Sub(x2, x1, sub2.get());
        rev(sub2.get(), sub2_rev.get());
        Mult(sub1.get(), sub2_rev.get(), lamda.get());
    }
    
    Mult(lamda.get(), lamda.get(), lamda2.get()); // лямбда в квадрате
    Sub(lamda2.get(), x1, sub1.get()); // lambda^2 - x1
    Sub(sub1.get(), x2, x_res); // lambda^2 - x1 - x2
    Sub(x1, x_res, sub2.get());
    Mult(lamda.get(), sub2.get(), mult.get());
    Sub(mult.get(), y1, y_res);
}