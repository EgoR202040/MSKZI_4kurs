#include "lr2.h"
#include <memory>

Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD],
g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD], g_q[CD],
g_p_1[CD], g_4[CD], g_6[CD], g_1[CD], x[CD], y[CD];

void VeyToEdv(Digit x[], Digit y[]) {
    auto res = std::make_unique<Digit[]>(CD);
    auto sub_1 = std::make_unique<Digit[]>(CD);
    auto add_1 = std::make_unique<Digit[]>(CD);
    auto add_1_rev = std::make_unique<Digit[]>(CD);
    auto y_rev = std::make_unique<Digit[]>(CD);
    
    Sub(x, g_t, res.get());
    
    rev(y, y_rev.get());
    
    Mult(res.get(), y_rev.get(), g_u);
    
    Sub(res.get(), g_s, sub_1.get());
    Add(res.get(), g_s, add_1.get());
    rev(add_1.get(), add_1_rev.get());
    Mult(sub_1.get(), add_1_rev.get(), g_v);
}

void EdvToVey(Digit u[], Digit v[]) {
    auto res = std::make_unique<Digit[]>(CD);
    auto rev_sub = std::make_unique<Digit[]>(CD);
    auto temp_add = std::make_unique<Digit[]>(CD);
    auto temp_mult = std::make_unique<Digit[]>(CD);
    auto temp_sub = std::make_unique<Digit[]>(CD);
    auto res2 = std::make_unique<Digit[]>(CD);
    auto res2rv = std::make_unique<Digit[]>(CD);
    
    Add(g_1, v, temp_add.get());
    Mult(g_s, temp_add.get(), temp_mult.get());
    Sub(g_1, v, temp_sub.get());
    rev(temp_sub.get(), rev_sub.get());
    Mult(temp_mult.get(), rev_sub.get(), res.get());
    Add(res.get(), g_t, x);

    Mult(temp_sub.get(), u, res2.get());
    rev(res2.get(), res2rv.get());
    Mult(temp_mult.get(), res2rv.get(), y);
}