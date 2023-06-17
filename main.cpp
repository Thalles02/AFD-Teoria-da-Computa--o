#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

vector<char> stringParaVetor(const string& palavra) {
    vector<char> vet_palavra;

    // Preenche o vetor com os caracteres da string
    for (char c : palavra) {
        vet_palavra.push_back(c);
    }

    return vet_palavra;
}

char prox(vector<char>& vet_palavra, int position){
    if (position < vet_palavra.size()){
        return vet_palavra[position];
    }else{
        return 'f';
    }
}

string simular_AFD(string i, set<string> F, map<string, map<char, string>> D, string palavra) {
    
    vector<char> vet_palavra;
    
    string e = i;
    int posicao = 0;
    vet_palavra = stringParaVetor(palavra);

    char s = prox(vet_palavra, posicao);
    //cout << "e antes do looping = " << e << endl;

    while (s != 'f') {
        e = D[e][s];
        //cout << "e depois do looping = " << e << endl;
        if (e.empty()) {
            return "não";
        }
        posicao += 1;
        s = prox(vet_palavra, posicao);
    }

    if (F.count(e) > 0) {
        return "sim";
    } else {
        return "não";
    }
}


int main() {
    map<string, map<char, string>> D;

    // Adiciona os elementos ao dicionário
    D["q0"] = {{'0', "q1"}, {'1', "q0"}};
    D["q1"] = {{'0', "q1"}, {'1', "q2"}};
    D["q2"] = {{'0', "q2"}, {'1', "q2"}};

    set<string> F = {"q2"};
    string i = "q0";
    string palavra = "111";

    string resultado = simular_AFD(i, F, D, palavra);
    cout << resultado << endl;

    cout << endl;
    return 0;
}