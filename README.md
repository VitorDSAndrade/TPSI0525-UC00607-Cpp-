# Mini-Sistema RH em C++

Este projeto consiste num mini-sistema simples de gestão de Recursos Humanos desenvolvido em C++.  
O objetivo é permitir gerir colaboradores, marcar férias e faltas, e visualizar um calendário mensal com todas as marcações.  
Toda a aplicação corre em consola e utiliza apenas bibliotecas padrão da linguagem.

---

## 📌 Objetivos do Projeto

O sistema foi desenvolvido com os seguintes propósitos:

- Praticar modularização em C++
- Utilizar `struct` e vetores dinâmicos (`std::vector`)
- Implementar validações de datas (ano bissexto, dias válidos, etc.)
- Criar persistência de dados num ficheiro CSV
- Usar uma cifra simples (XOR) para ofuscar nomes
- Gerar um calendário mensal formatado em modo texto

---

## 📁 Estrutura do Projeto

/src
├── main.cpp → Menu e lógica principal
├── colaborador.h/.cpp → Estruturas e funções para marcações
├── calendar.h/.cpp → Lógica do calendário mensal
├── storage.h/.cpp → Guardar e carregar CSV com cifra
└── utils.h → Cifra XOR e funções auxiliares

/data
└── dados_rh.csv → Ficheiro gerado automaticamente


---

## 🧍‍♂️ Funcionalidades Principais

### ✅ Adicionar colaborador
- Guarda o nome na lista.
- Se o colaborador já existir, o programa pede confirmação.

---

### ✅ Marcar Férias ou Falta
O utilizador escolhe:
- Ano  
- Mês  
- Dia  
- Tipo (`F` para férias, `X` para falta)

Validações incluídas:
- ❌ Não permite marcar fins-de-semana  
- ❌ Evita marcações duplicadas  
- ✅ Garante que o dia é válido para o mês/ano  
 
---

### ✅ Desmarcar marcação
Remove uma marcação existente para o dia selecionado.

---

### ✅ Ver calendário mensal
O calendário é apresentado em modo texto e inclui:
- Dias normais  
- `F` → Férias  
- `X` → Falta  
- `*` → Fim-de-semana  

Exemplo:

Seg Ter Qua Qui Sex Sab Dom
 1   2   3   4   5   6* 7*
 8   9   10  11  12  13* 14*


---

### ✅ Guardar dados automaticamente
Ao sair, todos os dados são guardados em:

data/dados_rh.csv

---

## 🔐 Cifra XOR

Para cumprir o requisito de “privacidade”, os nomes dos colaboradores são guardados cifrados.

Método: caracter XOR 0x05A

O mesmo processo reverte a operação ao carregar o ficheiro.

---

## 💾 Como Compilar

Dentro da pasta `/src`, executar:


g++ -std=c++17 -O2 -Wall -Wextra -pedantic \
  main.cpp colaborador.cpp calendar.cpp storage.cpp utils.cpp \
  -o ../rh_app


 Executar:
 antes de correr, habilita caracteres especiais, na powershell insere: chcp 65001

 ex: [ PS C:\Users\Vitor\ExCppRH\src> chcp 65001 ]

 (de preferencia na powershell apesar de tambem funcionar em cmd)

Windows: ..\\rh_app.exe


Linux/macOS: ../rh_app ( nao testado ) 


se houver problemas em mostrar caracteres especiais, abre a powershell e insere chcp 65001
depois corre o programa normalmente..\rh_app.exe ( so foi testado em Windows)

---

## ▶️ Como Usar

Abrir o programa

Carregar colaboradores (automático se o ficheiro existir)

Selecionar a opção desejada:

Adicionar colaborador

Marcar férias/falta

Desmarcar marcação

Ver calendário mensal

Ao sair, o programa grava automaticamente todos os dados
