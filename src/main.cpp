#include <iostream>
#include <vector>
#include <limits>
#include "colaborador.h"
#include "calendar.h"
#include "storage.h"

using namespace std;

string CAMINHO = "../data/dados_rh.csv";

void esperar() {
    cout << "\nPressione ENTER...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int lerInt(const string &txt, int min, int max) {
    int valor;
    while (true) {
        cout << txt;
        if (cin >> valor && valor >= min && valor <= max) {
            return valor;
        }
        cout << "Valor inválido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int escolherColaborador(const vector<Colaborador> &lista) {
    if (lista.empty()) {
        cout << "\nNenhum colaborador registado.\n";
        return -1;
    }

    cout << "\n--- Lista de Colaboradores ---\n";
    for (size_t i = 0; i < lista.size(); i++) {
        cout << i+1 << ") " << lista[i].nome << "\n";
    }

    int escolha = lerInt("Escolha (0 = cancelar): ", 0, lista.size());
    if (escolha == 0) return -1;

    return escolha - 1;
}

bool fimDeSemana(int ano, int mes, int dia) {
    return (diaSemana(ano, mes, dia) >= 5);
}

int main() {
    vector<Colaborador> lista;

    if (carregar(CAMINHO, lista)) {
        cout << "Dados carregados.\n";
    } else {
        cout << "Sem ficheiro. Começar vazio.\n";
    }

    while (true) {
        cout << "\n===== Mini-Sistema RH =====\n";
        cout << "1) Adicionar colaborador\n";
        cout << "2) Listar colaboradores\n";
        cout << "3) Marcar férias/falta\n";
        cout << "4) Desmarcar férias/falta\n";
        cout << "5) Ver calendário\n";
        cout << "0) Sair\n";

        int op = lerInt("Opção: ", 0, 5);

        if (op == 0) {
            if (guardar(CAMINHO, lista)) cout << "Guardado.\n";
            else cout << "Erro ao guardar.\n";
            break;
        }

        if (op == 1) {
            cin.ignore();
            cout << "\nNome do colaborador: ";
            string nome;
            getline(cin, nome);

            if (nome.empty()) {
                cout << "Nome inválido.\n";
                continue;
            }

            int idx = procurarColaborador(lista, nome);
            if (idx >= 0) {
                cout << "Já existe. Adicionar mesmo? (s/N): ";
                char r;
                cin >> r;
                if (r != 's' && r != 'S') continue;
            }

            Colaborador c;
            c.nome = nome;
            lista.push_back(c);

            cout << "Adicionado.\n";
        }

        else if (op == 2) {
            escolherColaborador(lista);
            esperar();
        }

        else if (op == 3) {
            int i = escolherColaborador(lista);
            if (i < 0) continue;

            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mês: ", 1, 12);
            int dia = lerInt("Dia: ", 1, diasNoMes(ano, mes));

            if (fimDeSemana(ano, mes, dia)) {
                cout << "Não pode marcar ao fim-de-semana.\n";
                continue;
            }

            cout << "Tipo (F = Férias, X = Falta): ";
            char t;
            cin >> t;

            if (t == 'f' || t == 'F') t = 'F';
            else t = 'X';

            if (adicionarMarcacao(lista[i], ano, mes, dia, t))
                cout << "Marcado.\n";
            else
                cout << "Já existe marcação nesse dia.\n";
        }

        else if (op == 4) {
            int i = escolherColaborador(lista);
            if (i < 0) continue;

            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mês: ", 1, 12);
            int dia = lerInt("Dia: ", 1, diasNoMes(ano, mes));

            if (removerMarcacao(lista[i], ano, mes, dia))
                cout << "Desmarcado.\n";
            else
                cout << "Não existia marcação.\n";
        }

        else if (op == 5) {
            int i = escolherColaborador(lista);
            if (i < 0) continue;

            int ano = lerInt("Ano: ", 1900, 2100);
            int mes = lerInt("Mês: ", 1, 12);

            mostrarCalendario(lista[i], ano, mes);
            esperar();
        }
    }

    return 0;
}
