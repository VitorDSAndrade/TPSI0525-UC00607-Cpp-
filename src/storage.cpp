#include "storage.h"
#include "utils.h"
#include <fstream>
#include <sstream>

using namespace std;

int procurarColaborador(const vector<Colaborador> &lista, const string &nome) {
    string n = minusculas(nome);
    for (size_t i = 0; i < lista.size(); i++) {
        if (minusculas(lista[i].nome) == n) return i;
    }
    return -1;
}

bool guardar(const string &ficheiro, const vector<Colaborador> &lista) {
    ofstream f(ficheiro, ios::binary);
    if (!f.is_open()) return false;

    for (const auto &c : lista) {
        f << "C;" << cifraXOR(c.nome) << "\n";

        for (const auto &m : c.lista) {
            f << "M;" << cifraXOR(c.nome) << ";"
              << m.ano << "-" << m.mes << "-" << m.dia << ";"
              << m.tipo << "\n";
        }
    }

    return true;
}

bool carregar(const string &ficheiro, vector<Colaborador> &lista) {
    ifstream f(ficheiro, ios::binary);
    if (!f.is_open()) return false;

    lista.clear();
    string linha;

    vector<string> nomesTemp;
    vector<string> eventosTemp;

    while (getline(f, linha)) {
        if (linha.rfind("C;", 0) == 0) {
            nomesTemp.push_back(cifraXOR(linha.substr(2)));
        } else if (linha.rfind("M;", 0) == 0) {
            eventosTemp.push_back(linha);
        }
    }

    for (auto &n : nomesTemp) {
        Colaborador c;
        c.nome = n;
        lista.push_back(c);
    }

    for (auto &e : eventosTemp) {
        string temp, nomeEnc, data, tipoStr;

        stringstream ss(e);
        getline(ss, temp, ';');
        getline(ss, nomeEnc, ';');
        getline(ss, data, ';');
        getline(ss, tipoStr, ';');

        string nome = cifraXOR(nomeEnc);
        int i = procurarColaborador(lista, nome);

        if (i < 0) continue;

        int ano, mes, dia;
        char separador;
        stringstream sd(data);
        sd >> ano >> separador >> mes >> separador >> dia;

        Marcacao m;
        m.ano = ano;
        m.mes = mes;
        m.dia = dia;
        m.tipo = tipoStr[0];

        lista[i].lista.push_back(m);
    }

    return true;
}
