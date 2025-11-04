#include "colaborador.h"

bool existeMarcacao(const Colaborador &c, int ano, int mes, int dia, char *tipoEncontrado) {
    for (const auto &m : c.lista) {
        if (m.ano == ano && m.mes == mes && m.dia == dia) {
            if (tipoEncontrado != nullptr) {
                *tipoEncontrado = m.tipo;
            }
            return true;
        }
    }
    return false;
}

bool adicionarMarcacao(Colaborador &c, int ano, int mes, int dia, char tipo) {
    char t;
    if (existeMarcacao(c, ano, mes, dia, &t)) {
        return false;
    }

    Marcacao m;
    m.ano = ano;
    m.mes = mes;
    m.dia = dia;
    m.tipo = tipo;

    c.lista.push_back(m);
    return true;
}

bool removerMarcacao(Colaborador &c, int ano, int mes, int dia) {
    for (size_t i = 0; i < c.lista.size(); i++) {
        if (c.lista[i].ano == ano && c.lista[i].mes == mes && c.lista[i].dia == dia) {
            c.lista.erase(c.lista.begin() + i);
            return true;
        }
    }
    return false;
}
