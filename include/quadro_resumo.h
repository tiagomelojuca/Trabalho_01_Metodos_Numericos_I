#ifndef QUADRO_RESUMO_H_
#define QUADRO_RESUMO_H_

#include <string>
#include <sstream>
#include <vector>

#include <cstdint>
#include <limits>
#include <iomanip>

template <typename T>
class matriz
{
public:
    class linha_matriz
    {
    public:
        linha_matriz(T* ptrLinha) : _ptr(ptrLinha) {}

        T& operator[](size_t coluna)
        {
            return _ptr[coluna - 1];
        }

    private:
        T* _ptr = nullptr;
    };

    matriz(size_t linhas, size_t colunas) : _linhas(linhas), _colunas(colunas)
    {
        _matriz = new T*[_linhas];
        for (size_t linha = 0; linha < _linhas; linha++)
        {
            _matriz[linha] = new T[_colunas];
        }
    }

    matriz(const matriz&) = delete;
    matriz(matriz&&) = delete;
    matriz& operator=(const matriz&) = delete;

    ~matriz()
    {
        for (size_t linha = 0; linha < _linhas; linha++)
        {
            delete[] _matriz[linha];
        }

        delete[] _matriz;
    }

    void init(const T& valorPadrao)
    {
        for (size_t linha = 0; linha < _linhas; linha++)
        {
            for (size_t coluna = 0; coluna < _colunas; coluna++)
            {
                _matriz[linha][coluna] = valorPadrao;
            }
        }
    }

    linha_matriz operator[](size_t linha)
    {
        return linha_matriz(_matriz[linha - 1]);
    }

protected:
    size_t _linhas;
    size_t _colunas;

    T** _matriz;
};

// --------------------------------------------------------------------------

class tabela : public matriz<std::string>
{
public:
    tabela(
        size_t linhas,
        size_t colunas,
        size_t tam_cels = 7u
    ) :
        matriz(linhas, colunas),
        tam_cels(tam_cels),
        linha_cab(-1)
    {
        init(cel_vazia());
    }

    void define(size_t linha, size_t coluna, const std::string& valor)
    {
        (*this)[linha][coluna] = formata_celula(valor);
    }

    void define(size_t linha, size_t coluna, double valor)
    {
        define(linha, coluna, formata_celula(valor));
    }

    void define_cabecalho(size_t linha)
    {
        linha_cab = linha - 1;
    }

    std::string gera() const
    {
        std::stringstream ss;

        for (size_t linha = 0; linha < _linhas; linha++)
        {
            ss << "|";

            for (size_t coluna = 0; coluna < _colunas; coluna++)
            {
                ss << _matriz[linha][coluna] << "|";
            }

            ss << std::endl;

            if (linha == linha_cab)
            {
                ss << divisoria() << std::endl;
            }
        }

        return ss.str();
    }

private:
    std::string cel_vazia() const
    {
        const size_t tamanhoPaddings = 2u;
        const size_t tamanho = tam_cels + tamanhoPaddings;

        std::string cel_vazia;
        for (size_t i = 0; i < tamanho; i++) cel_vazia += " ";

        return cel_vazia;
    }

    std::string divisoria() const
    {
        const size_t nCols = tam_linha(_colunas, tam_cels);

        std::stringstream ss;
        for (size_t i = 0; i < nCols; i++) ss << '-';

        return ss.str();
    }

    std::string formata_celula(const std::string& str) const
    {
        return normaliza_celula(str, tam_cels);
    }

    std::string formata_celula(double val) const
    {
        return val != std::numeric_limits<double>::max() ? std::to_string(val) : "nan";
    }

    std::string normaliza_celula(double val, size_t tam = 5u) const
    {
        return normaliza_celula(std::to_string(val), tam);
    }

    std::string normaliza_celula(const std::string& str, size_t tam = 7u) const
    {
        // Essa impl eh extremamente estupida, mas como eh so pra imprimir
        // a tabela e vai rodar poucas vezes, preferi deixar assim. Provavelmente
        // percorrer de tras pra frente seria muito melhor, mas essa impl ingenua
        // ja ta de bom tamanho
        std::stringstream ss;
        ss << std::right << std::setw(tam) << std::fixed << std::setprecision(tam) << str;

        const std::string str_alinhada = ss.str();
        std::string result_trim;
        for (int i = 0; i < str_alinhada.length(); i++) {
            if (str_alinhada[i] != ' ')
            {
                result_trim += str_alinhada[i];
            }
        }

        while (result_trim.length() < tam)
        {
            std::string novoResultado = " " + result_trim;
            result_trim = novoResultado;
        }

        const size_t tam_buf = tam + 1;
        char* buf = new char[tam_buf];
        for (size_t i = 0; i < tam; i++) buf[i] = result_trim[i];
        buf[tam] = '\0';

        std::string celula;

        celula += " ";
        celula += buf;
        celula += " ";

        delete buf;

        return celula;
    }

    constexpr size_t tam_linha(size_t qtdCelulas, size_t tamanhoCelula = 5u) const
    {
        return qtdCelulas * (tamanhoCelula + 2u) + (qtdCelulas + 1u);
    }

    size_t tam_cels;
    size_t linha_cab;
};

// --------------------------------------------------------------------------

std::string gera_quadro_resumo(
    const std::vector<double>& entradas,
    double d0,
    double d1,
    double err,
    double maxIter
);

// --------------------------------------------------------------------------

#endif
