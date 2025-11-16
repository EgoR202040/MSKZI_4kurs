#include "lr4.h"
extern Digit x[CD], y[CD];
point multiply_vey(point Q, const Digit k[CD]) {
    Digit xr[CD], yr[CD], bx[CD], by[CD], c1[CD], c2[CD];
    point answer;
    
    bool is_infinity = true;
    
    Assig(Q.x, bx);
    Assig(Q.y, by);

    for (int i = 16 * CD - 1; i >= 0; i--) {
        Digit current = k[i / 16];
        
        if (!is_infinity) {
            Add_Vey(xr, yr, xr, yr, c1, c2);
            Assig(c1, xr);
            Assig(c2, yr);
        }

        if ((current >> (i % 16)) & 0x0001) {
            if (is_infinity) {
                Assig(bx, xr);
                Assig(by, yr);
                is_infinity = false;
            } else {
                Add_Vey(xr, yr, bx, by, c1, c2);
                Assig(c1, xr);
                Assig(c2, yr);
            }
        }
    }
    
    Assig(xr, answer.x);
    Assig(yr, answer.y);
    return answer;
}

point multiply_edv(point Q, const Digit k[CD]){
     Digit xr[CD], yr[CD], bx[CD], by[CD], c1[CD], c2[CD];
    point answer;
    
    Assig(Q.x, bx);
    Assig(Q.y, by);
    
    // Инициализация нейтрального элемента для Эдвардса: (0, 1)
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", xr);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", yr);
    
    for (int i = 16 * CD - 1; i >= 0; i--) {
        Digit current = k[i / 16];
        
        // Удвоение точки 
        if (!(Equal(xr, g_zero) && Equal(yr, g_1))) {
            Add_Edwards(xr, yr, xr, yr, c1, c2);
            Assig(c1, xr);
            Assig(c2, yr);
        }
        
        
        if ((current >> (i % 16)) & 0x0001) {
            if (Equal(xr, g_zero) && Equal(yr, g_1)) {
                Assig(bx, xr);
                Assig(by, yr);
            } else {
                Add_Edwards(xr, yr, bx, by, c1, c2);
                Assig(c1, xr);
                Assig(c2, yr);
            }
        }
    }
    
    Assig(xr, answer.x);
    Assig(yr, answer.y);
    return answer;
}
void debug_curve_params() {
    std::cout << "=== Параметры кривой ===" << std::endl;
    std::cout << "p: " << NumToStringDigit(g_p) << std::endl;
    std::cout << "d: " << NumToStringDigit(g_d) << std::endl;
    std::cout << "e: " << NumToStringDigit(g_e) << std::endl;
    std::cout << "s: " << NumToStringDigit(g_s) << std::endl;
    std::cout << "t: " << NumToStringDigit(g_t) << std::endl;
}
int main(){
    Init();
    Digit k1[CD];
    point first_edv, vey;
    
    std::cout << "Контрольный пример 1\nВходные данные\n"; 
    
    Digit x_vey[CD], y_vey[CD];
    StringToNumber("91e38443a5e82c0d880923425712b2bb658b9196932e02c78b2582fe742daa28", x_vey);
    StringToNumber("32879423ab1a0375895786c4bb46e9565fde0b5344766740af268adb32322e5c", y_vey);
    
    VeyToEdv(x_vey, y_vey);
    Assig(g_u, first_edv.x);
    Assig(g_v, first_edv.y);
    
    std::cout << "Точка в форме Эдвардса:" << std::endl;
    print(first_edv);
    
    std::cout << "Коэффициент k: ";
    StringToNumber("e8c6740e58d616ca220db7da0d9c3e19b53e86e38bf3e8747774631452ec174c", k1);
    std::cout << NumToStringDigit(k1) << std::endl;

    point result_edv = multiply_edv(first_edv, k1);
    
    std::cout << "Результат в форме Эдвардса:" << std::endl;
    print(result_edv);
    
    EdvToVey(result_edv.x, result_edv.y);
    std::cout << "Результат в форме Вейерштрасса:" << std::endl;
    std::cout << NumToStringDigit(x) << std::endl;
    std::cout << NumToStringDigit(y) << std::endl;
    
    std::cout << "Контрольный пример 2\nВходные данные\n";
    StringToNumber("1d40c1676805f9518be1fb4c7ae460d3608581e477b07c2d0e7e1e265a6b3347", x_vey);
    StringToNumber("8291ace380fd8832baca29613ab5626c302d13348f204d727d30897a8e1f8934", y_vey);
    std::cout << "Коэффициент k: ";
    StringToNumber("c9cbaeefaabc51147130fc6fa1adbe72140e35c5911b7d54b12beecdf5848943", k1);
    std::cout << NumToStringDigit(k1) << std::endl;
    VeyToEdv(x_vey, y_vey);
    Assig(g_u, first_edv.x);
    Assig(g_v, first_edv.y);
    result_edv = multiply_edv(first_edv, k1);
    std::cout << "Результат в форме Эдвардса:" << std::endl;
    print(result_edv);
    EdvToVey(result_edv.x, result_edv.y);
    std::cout << "Результат в форме Вейерштрасса:" << std::endl;
    std::cout << NumToStringDigit(x) << std::endl;
    std::cout << NumToStringDigit(y) << std::endl;


    std::cout << "Вариант 8\nВходные данные\nТочка А:\n";
    StringToNumber("b216b37b9cc0f195906e3432c2a29c9f9a62ad46656bb509ac21801c1b03af1e", x_vey);
    StringToNumber("41a41af5f12805c26877356b6744cc1535f9f985021be36de6ae53e6d764a6b4", y_vey);
    std::cout << "Коэффициент k: ";
    StringToNumber("3399b9b2537b96450162b9ebe3d531a14b7e2521f1562bc2ec1be73583b483bf", k1);
    std::cout << NumToStringDigit(k1) << std::endl;
    VeyToEdv(x_vey, y_vey);
    Assig(g_u, first_edv.x);
    Assig(g_v, first_edv.y);
    result_edv = multiply_edv(first_edv, k1);
    std::cout << "Результат в форме Эдвардса:" << std::endl;
    print(result_edv);
    EdvToVey(result_edv.x, result_edv.y);
    std::cout << "Результат в форме Вейерштрасса:" << std::endl;
    std::cout << NumToStringDigit(x) << std::endl;
    std::cout << NumToStringDigit(y) << std::endl;

    std::cout << "Точка B\n";
    StringToNumber("7b104442f1af36cf5685cfc7684c7c1fa240edfcdf053f71d7224f85aa6e8141", x_vey);
    StringToNumber("45aabc4fb72b218b8f81044d5e839a64e65046d3514f666e6c3917949b8903d7", y_vey);
    VeyToEdv(x_vey, y_vey);
    Assig(g_u, first_edv.x);
    Assig(g_v, first_edv.y);
    result_edv = multiply_edv(first_edv, k1);
    std::cout << "Результат в форме Эдвардса:" << std::endl;
    print(result_edv);
    EdvToVey(result_edv.x, result_edv.y);
    std::cout << "Результат в форме Вейерштрасса:" << std::endl;
    std::cout << NumToStringDigit(x) << std::endl;
    std::cout << NumToStringDigit(y) << std::endl;


    std::cout <<"Тестирование функции multiply_vey\nКонтрольный пример 1:\n";
    StringToNumber("91e38443a5e82c0d880923425712b2bb658b9196932e02c78b2582fe742daa28", vey.x);
    StringToNumber("32879423ab1a0375895786c4bb46e9565fde0b5344766740af268adb32322e5c", vey.y);
    StringToNumber("e8c6740e58d616ca220db7da0d9c3e19b53e86e38bf3e8747774631452ec174c", k1);
    std::cout <<"Входные данные: \n";
    std::cout << NumToStringDigit(vey.x) << std::endl;
    std::cout << NumToStringDigit(vey.y) << std::endl;
    std::cout << NumToStringDigit(k1) << std::endl;
    auto result_vey = multiply_vey(vey, k1);
    std::cout << "Выходные данные:\n";
    std::cout << NumToStringDigit(result_vey.x) << std::endl;
    std::cout << NumToStringDigit(result_vey.y) << std::endl;

    std::cout << "Контрольный пример 2:\n";
    StringToNumber("1d40c1676805f9518be1fb4c7ae460d3608581e477b07c2d0e7e1e265a6b3347", vey.x);
    StringToNumber("8291ace380fd8832baca29613ab5626c302d13348f204d727d30897a8e1f8934", vey.y);
    StringToNumber("c9cbaeefaabc51147130fc6fa1adbe72140e35c5911b7d54b12beecdf5848943", k1);
    std::cout <<"Входные данные: \n";
    std::cout << NumToStringDigit(vey.x) << std::endl;
    std::cout << NumToStringDigit(vey.y) << std::endl;
    std::cout << NumToStringDigit(k1) << std::endl;
    result_vey = multiply_vey(vey, k1);
    std::cout << "Выходные данные:\n";
    std::cout << NumToStringDigit(result_vey.x) << std::endl;
    std::cout << NumToStringDigit(result_vey.y) << std::endl;

    std::cout << "Вариант 8:\nТочка А:";
    StringToNumber("b216b37b9cc0f195906e3432c2a29c9f9a62ad46656bb509ac21801c1b03af1e", vey.x);
    StringToNumber("41a41af5f12805c26877356b6744cc1535f9f985021be36de6ae53e6d764a6b4", vey.y);
    StringToNumber("3399b9b2537b96450162b9ebe3d531a14b7e2521f1562bc2ec1be73583b483bf", k1);
    std::cout <<"Входные данные: \n";
    std::cout << NumToStringDigit(vey.x) << std::endl;
    std::cout << NumToStringDigit(vey.y) << std::endl;
    std::cout << NumToStringDigit(k1) << std::endl;
    result_vey = multiply_vey(vey, k1);
    std::cout << "Выходные данные:\n";
    std::cout << NumToStringDigit(result_vey.x) << std::endl;
    std::cout << NumToStringDigit(result_vey.y) << std::endl;
    std::cout << "Точка B:\n";
    StringToNumber("7b104442f1af36cf5685cfc7684c7c1fa240edfcdf053f71d7224f85aa6e8141", vey.x);
    StringToNumber("45aabc4fb72b218b8f81044d5e839a64e65046d3514f666e6c3917949b8903d7", vey.y);
    std::cout <<"Входные данные: \n";
    std::cout << NumToStringDigit(vey.x) << std::endl;
    std::cout << NumToStringDigit(vey.y) << std::endl;
    std::cout << NumToStringDigit(k1) << std::endl;
    result_vey = multiply_vey(vey, k1);
    std::cout << "Выходные данные:\n";
    std::cout << NumToStringDigit(result_vey.x) << std::endl;
    std::cout << NumToStringDigit(result_vey.y) << std::endl;
    return 0;
}