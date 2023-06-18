#include "HELPERS.h";

int main()
{
    // Declarando as dependências do AFD, mapa de transição, estado inicial, conjunto de estados finais. Além do nome do arquivo e um comando para adequação da ligua portuguesa
    setlocale(LC_ALL, "portuguese");
    map<string, map<char, string>> D;
    string init_state, name_file;
    set<string> F;

    int option;

    while (true)
    {
        // Exibe o menu
        cout << "Escolha um arquivo de teste para executar:" << endl;
        cout << "1. Arquivo 1" << endl;
        cout << "2. Arquivo 2" << endl;
        cout << "3. Arquivo 3" << endl;
        cout << "4. Arquivo 4" << endl;
        cout << "5. Arquivo 5" << endl;
        cout << "0. Sair" << endl;

        // Obtém a opção do usuário
        cout << "Opção: ";
        cin >> option;

        // Verifica a opção escolhida
        if (option == 0)
        {
            // Encerra o programa
            break;
        }
        else if (option >= 1 && option <= 5)
        {
            // Executa o teste correspondente à opção escolhida
            name_file = "arquivo" + to_string(option) + ".txt";
            read_arq(init_state, F, D, name_file);
        }
        else
        {
            cout << "Opção inválida. Tente novamente." << endl;
        }

        cout << endl;
    }

    // printmap(D);
    return 0;
}