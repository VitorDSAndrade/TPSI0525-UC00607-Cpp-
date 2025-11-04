#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <vector>

struct Marcacao {
    int ano;
    int mes;
    int dia;
    char tipo;   // 'F' = Férias, 'X' = Falta
};

struct Colaborador {
    std::string nome;            // Nome já desencriptado
    std::vector<Marcacao> lista; // Lista de marcações
};

// Funções úteis
bool existeMarcacao(const Colaborador &c, int ano, int mes, int dia, char *tipoEncontrado = nullptr);
bool adicionarMarcacao(Colaborador &c, int ano, int mes, int dia, char tipo);
bool removerMarcacao(Colaborador &c, int ano, int mes, int dia);

#endif
