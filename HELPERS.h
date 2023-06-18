#ifndef HELPERS_H
#define HELPERS_H

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <locale.h>

using namespace std;

// Uma função para transformar uma string em um vetor char
vector<char> strfvector(const string &word)
{
    vector<char> vet_word;
    // Preenche o vetor com os caracteres da string
    for (char c : word)
    {
        vet_word.push_back(c);
    }
    return vet_word;
}

// Função auxiliar para debug durante o desenvolvimento (printando um vetor)
void printvector(const vector<string> &vetor)
{
    for (const auto &element : vetor)
    {
        cout << element << " \n";
    }
    cout << endl;
}

// Função para remover os espaços da linha do arquivo, para evitar vetores com elementos com espaço
string removespace(const string &str)
{
    string result;

    for (char c : str)
    {
        if (c != ' ')
        {
            result += c;
        }
    }

    return result;
}

// Função auxiliar para visualização do mapa completo
void printmap(const map<string, map<char, string>> &mapa)
{
    for (const auto &outerPair : mapa)
    {
        cout << outerPair.first << ": ";

        for (const auto &innerPair : outerPair.second)
        {
            cout << "{" << innerPair.first << ", " << innerPair.second << "} ";
        }

        cout << endl;
    }
}

// Função que pega um caracter de um vetor de acordo com sua posição ṕassada como parâmetro
char prox(vector<char> &vet_word, int position)
{
    if (position < vet_word.size())
    {
        return vet_word[position];
    }
    else
    {
        return 'f';
    }
}

// Algoritmo que irá simular o AFD
string simulate_afd(string i, set<string> F, map<string, map<char, string>> D, string word)
{

    vector<char> vet_word;

    string e = i;
    int position = 0;
    vet_word = strfvector(word);

    char s = prox(vet_word, position);

    while (s != 'f')
    {
        cout << e << " -> " << s << " -> ";
        e = D[e][s];
        if (e.empty())
        {
            return "Esta palavra não foi aceita pelo AFD! (Vazio)";
        }
        position += 1;
        s = prox(vet_word, position);
    }

    if (F.count(e) > 0)
    {
        cout << e << " ";
        return "Esta palavra foi aceita pelo AFD!";
    }
    else
    {
        return "Esta palavra não foi aceita pelo AFD!";
    }
}


// Função que contém a lógica para leitura dos arquivos de testes dos AFDs 
void read_arq(string init_state, set<string> F, map<string, map<char, string>> D, string name_file)
{
    string arquivo_escolhido = "../arquivos_teste/" + name_file;
    ifstream arquivo(arquivo_escolhido);

    string line;
    // Contador principal que irá controlar em qual linha do arquivo estamos situados
    int count = 0;
    // Contador auxiliar que obtém a quantidade de estados
    int state_aux = 0;
    // Contador auxiliar que a cada linha de transição entre estados será incrementado para stopar a coonstrução do mapa de estados
    int aux = 0;
    int number_tests;

    // Declaração dos vetores que serão utilizados para construção do mapa
    vector<char> vet_states, vet_alfabeto, vet_transition, vet_aux_finals_states;
    // Vetor que contém todas as palavras de testes
    vector<string> vet_testes;

    if (arquivo.is_open())
    { // Verifica se o arquivo foi aberto com sucesso

        while (getline(arquivo, line))
        {
            // Removendo os espaços da linha do arquivo
            line = removespace(line);
            if (count == 0)
            {
                // Caso estiver na primeira linha do arquivo, armazena todo o conteúdo em um vetor que conterá os estados
                vet_states = strfvector(line);
                count++;
            }
            else if (count == 1)
            {
                // Caso estiver na segunda linha armazena o alfabeto em um vetor
                vet_alfabeto = strfvector(line);
                count++;
            }
            else if (count > 1 && aux < vet_states.size())
            {
                // Nesta condição confere se a quantidade de linhas de transição do arquivo são iguais ao tamanho do vetor de estados e constrói o mapa para utilização do afd
                vet_transition = strfvector(line);
                for (int j = 0; j < vet_alfabeto.size(); j++)
                {
                    string state(1, vet_states[state_aux]);
                    string valor(1, vet_transition[j]);
                    // cout << "Estado: " << state << " Valor: " << valor << " Alfabeto: " << vet_alfabeto[j] << endl;
                    D[state][vet_alfabeto[j]] = valor;
                }
                state_aux++;
                aux++;
                count++;
            }
            else if (count == vet_states.size() + 2)
            {
                // Armazena o estado inicial do afd
                init_state = line;
                count++;
            }
            else if (count == vet_states.size() + 3)
            {
                // Armazena o conjunto de estados finais
                vet_aux_finals_states = strfvector(line);

                for (char line : vet_aux_finals_states)
                {
                    string elemento(1, line);
                    F.insert(elemento);
                }
                count++;
            }
            else if (count == vet_states.size() + 4)
            {
                // Armazena o número de testes que serão executados (Não está sendo utilizado, mas a título de marcação foi optado por armazená-lo)
                number_tests = stoi(line);
                count++;
            }
            else
            {
                // Depois de ter percorrido por todas as regras, a quantidade de linhas restantes serão as palavras de teste que são armazenadas em um vetor
                vet_testes.push_back(line);
                count++;
            }
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo." << endl;
    }
    // Neste trecho é percorrido o vetor de testes e chamado a função para simular o afd para a palavra do indice do vetor de teste
    for (int i = 0; i < vet_testes.size(); i++)
    {
        string resultado = simulate_afd(init_state, F, D, vet_testes[i]);
        cout << resultado << endl;
    }
}

#endif