#include "lr3.h"
#include <memory>
#include <vector>

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

// Функция умножения точки на скаляр с умными указателями
point multiply_edv(point Q, const Digit k[CD]) {
    // Умные указатели для всех временных переменных
    auto xr = std::make_unique<Digit[]>(CD);
    auto yr = std::make_unique<Digit[]>(CD);
    auto bx = std::make_unique<Digit[]>(CD);
    auto by = std::make_unique<Digit[]>(CD);
    auto c1 = std::make_unique<Digit[]>(CD);
    auto c2 = std::make_unique<Digit[]>(CD);
    
    point answer;

    // Инициализация как нейтральный элемент
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", xr.get());
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", yr.get());
    
    Assig(Q.x, bx.get());
    Assig(Q.y, by.get());

    for (int i = 0; i < 16 * CD; i++) {
        Digit current = k[i / 16];
        
        // Сначала добавляем, потом удваиваем
        if ((current >> (i % 16)) & 0x0001) {
            if (Equal(xr.get(), g_zero) && Equal(yr.get(), g_zero)) {
                // Первое добавление
                Assig(bx.get(), xr.get());
                Assig(by.get(), yr.get());
            } else {
                // Сложение R + Q
                Add_Vey(xr.get(), yr.get(), bx.get(), by.get(), c1.get(), c2.get());
                Assig(c1.get(), xr.get());
                Assig(c2.get(), yr.get());
            }
        }
        
        // Удваиваем Q для следующей итерации
        if (!(Equal(bx.get(), g_zero) && Equal(by.get(), g_zero))) {
            Add_Vey(bx.get(), by.get(), bx.get(), by.get(), c1.get(), c2.get());
            Assig(c1.get(), bx.get());
            Assig(c2.get(), by.get());
        }
    }
    
    Assig(xr.get(), answer.x);
    Assig(yr.get(), answer.y);
    return answer;
}

int main(){
    Digit x1[CD], y1[CD], x2[CD], y2[CD], x_res[CD], y_res[CD];
    Digit u1[CD], v1[CD], u2[CD], v2[CD], u_res[CD], v_res[CD];
    
    Init();
    StringToNumber("91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28", x1);
    StringToNumber("32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C", y1);
    StringToNumber("E8C6740E58D616CA220DB7DA0D9C3E19B53E86E38BF3E8747774631452EC174C", x2);
    StringToNumber("0B837A5E560A29A2327B575F29B4BE8BAEF4BC947FCC2ED4F3264BC434309381", y2);
    
    std::cout << "Начальные значения в форме Вейерштрасса:" << std::endl;
    std::cout << "P1: " << NumToStringDigit(x1) << std::endl;
    std::cout << "    " << NumToStringDigit(y1) << std::endl;
    std::cout << "P2: " << NumToStringDigit(x2) << std::endl;
    std::cout << "    " << NumToStringDigit(y2) << std::endl;
    
    // Сложение в форме Вейерштрасса
    Add_Vey(x1, y1, x2, y2, x_res, y_res);
    std::cout << "\nСложение в форме Вейерштрасса:" << std::endl;
    std::cout << "P1 + P2: " << NumToStringDigit(x_res) << std::endl;
    std::cout << "        " << NumToStringDigit(y_res) << std::endl;
    
    // Преобразование исходных точек в форму Эдвардса
    VeyToEdv(x1, y1);
    Assig(g_u, u1);  // Сохраняем результат преобразования P1
    Assig(g_v, v1);
    
    VeyToEdv(x2, y2);
    Assig(g_u, u2);  // Сохраняем результат преобразования P2  
    Assig(g_v, v2);
    
    std::cout << "\nТочки в форме Эдвардса:" << std::endl;
    std::cout << "P1: " << NumToStringDigit(u1) << std::endl;
    std::cout << "    " << NumToStringDigit(v1) << std::endl;
    std::cout << "P2: " << NumToStringDigit(u2) << std::endl;
    std::cout << "    " << NumToStringDigit(v2) << std::endl;
    
    // Сложение в форме Эдвардса
    Add_Edwards(u1, v1, u2, v2, u_res, v_res);
    std::cout << "\nСложение в форме Эдвардса:" << std::endl;
    std::cout << "P1 + P2: " << NumToStringDigit(u_res) << std::endl;
    std::cout << "        " << NumToStringDigit(v_res) << std::endl;
    
    // Преобразование результата обратно в Вейерштрасса
    EdvToVey(u_res, v_res);
    std::cout << "\nРезультат сложения в форме Эдвардса, преобразованный в Вейерштрасса:" << std::endl;
    std::cout << "P1 + P2: " << NumToStringDigit(x) << std::endl;
    std::cout << "        " << NumToStringDigit(y) << std::endl;
    
    // Сравнение результатов
    std::cout << "\nСравнение результатов:" << std::endl;
    if (Equal(x_res, x) && Equal(y_res, y)) {
        std::cout << "✓ Результаты СОВПАДАЮТ!" << std::endl;
    } else {
        std::cout << "✗ Результаты НЕ СОВПАДАЮТ!" << std::endl;
        std::cout << "Разница по X: " << NumToStringDigit(x_res) << " vs " << NumToStringDigit(x) << std::endl;
        std::cout << "Разница по Y: " << NumToStringDigit(y_res) << " vs " << NumToStringDigit(y) << std::endl;
    }


    StringToNumber("b216b37b9cc0f195906e3432c2a29c9f9a62ad46656bb509ac21801c1b03af1e", x1);
    StringToNumber("41a41af5f12805c26877356b6744cc1535f9f985021be36de6ae53e6d764a6b4", y1);
    StringToNumber("7b104442f1af36cf5685cfc7684c7c1fa240edfcdf053f71d7224f85aa6e8141", x2);
    StringToNumber("45aabc4fb72b218b8f81044d5e839a64e65046d3514f666e6c3917949b8903d7", y2);

    std::cout << "Вариант 8:\nНачальные значения в форме Вейерштрасса:" << std::endl;
    std::cout << "P1: " << NumToStringDigit(x1) << std::endl;
    std::cout << "    " << NumToStringDigit(y1) << std::endl;
    std::cout << "P2: " << NumToStringDigit(x2) << std::endl;
    std::cout << "    " << NumToStringDigit(y2) << std::endl;

    Add_Vey(x1, y1, x2, y2, x_res, y_res);
    std::cout << "\nСложение в форме Вейерштрасса:" << std::endl;
    std::cout << "P1 + P2: " << NumToStringDigit(x_res) << std::endl;
    std::cout << "        " << NumToStringDigit(y_res) << std::endl;
    // Преобразование исходных точек в форму Эдвардса
    VeyToEdv(x1, y1);
    Assig(g_u, u1);  // Сохраняем результат преобразования P1
    Assig(g_v, v1);
    
    VeyToEdv(x2, y2);
    Assig(g_u, u2);  // Сохраняем результат преобразования P2  
    Assig(g_v, v2);

    Add_Edwards(u1, v1, u2, v2, u_res, v_res);
    std::cout << "\nСложение в форме Эдвардса:" << std::endl;
    std::cout << "P1 + P2: " << NumToStringDigit(u_res) << std::endl;
    std::cout << "        " << NumToStringDigit(v_res) << std::endl;
    
    // Преобразование результата обратно в Вейерштрасса
    EdvToVey(u_res, v_res);
    std::cout << "\nРезультат сложения в форме Эдвардса, преобразованный в Вейерштрасса:" << std::endl;
    std::cout << "P1 + P2: " << NumToStringDigit(x) << std::endl;
    std::cout << "        " << NumToStringDigit(y) << std::endl;
    return 0;
}