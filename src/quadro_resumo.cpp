#include "quadro_resumo.h"

#include <iostream>

#include "isolamento.h"
#include "funcao.h"
#include "refinamento.h"

std::string gera_quadro_resumo(const std::vector<double>& entradas, double err, double maxIter)
{
    std::cout.setstate(std::ios::failbit);

    const size_t linhas = entradas.size() + 1;
    const size_t colunas = 10;

    tabela t { linhas, colunas };
    t.define_cabecalho(1);
    t.define(1, 1, "a");
    t.define(1, 2, "d0");
    t.define(1, 3, "d1");
    t.define(1, 4, "err_adm");
    t.define(1, 5, "d_nr");
    t.define(1, 6, "err_nr");
    t.define(1, 7, "d_nm");
    t.define(1, 8, "err_nm");
    t.define(1, 9, "d_sc");
    t.define(1, 10, "err_sc");

    for (size_t i = 2; i <= entradas.size() + 1; i++)
    {
        const double A = entradas[i - 2];

        auto interv = isolamento_para_f_com_A_variado(A);
        const double d0 = interv.a;
        const double d1 = interv.b;

        auto resultado_newton = newton(d0, err, err, maxIter, A);
        auto resultado_newton_mod = newton_modificado(d0, err, err, maxIter, A);
        auto resultado_secante = secante(d0, d1, err, err, maxIter, A);
        
        t.define(i, 1, A);
        t.define(i, 2, d0);
        t.define(i, 3, d1);
        t.define(i, 4, err);
        t.define(i, 5, resultado_newton);
        t.define(i, 6, std::abs(f_a(resultado_newton, A)));
        t.define(i, 7, resultado_newton_mod);
        t.define(i, 8, std::abs(f_a(resultado_newton_mod, A)));
        t.define(i, 9, resultado_secante);
        t.define(i, 10, std::abs(f_a(resultado_secante, A)));
    }

    std::cout.clear();

    return t.gera();
}
