/*
Trabalho de Arquivos - Estrutura de Dados 1
Pedro Henrique Lima Cardoso - 22007061
Mark Davis Faria Almeida Junior - 22006093
*/

#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main()
{
    Pessoa cliente;
    int indexCadastro, indexUpdate = 0, n;
    system("cls");
    createFiles();
    //primeiro cadastro
    indexCadastro = cadastrarClientes(cliente, 0);
    system("cls");

    do
    {
        //MENU
        printf("1. Cadastrar novos clientes\n");
        printf("2. Gravar movimentacoes no arquivo \"Movimento\"\n");
        printf("3. Gerar arquivo de movimentacao a partir de data\n");
        printf("4. Atualizar cadastro a partir do arquivo \"Movimento\"\n");
        printf("5. Lista de depositos realizados a partir do numero da conta\n");
        printf("6. Consultar saldo a partir do numero da conta\n");
        printf("0. Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            indexCadastro = cadastrarClientes(cliente, indexCadastro);
            break;
        case 2:
            appendMovimento();
            break;
        case 3:
            relatorioMovimento();
            break;
        case 4:
            indexUpdate = updateCadastro(indexUpdate);
            break;
        case 5:
            listDeposito();
            break;
        case 6:
            buscaSaldo();
            break;
        case 0:
            exit(0);
            break;
        default:
            system("cls");
            printf("A opcao informada: %d e invalida\n", n);
        }

        printf("\n\nPressione qualquer tecla para continuar...");
        clean_stdin();
        getchar();
    } while (n != 0);

    return 0;
}

//TO-DO: Fazer procedure de consulta
//TO-DO: Check updateCadastro //Retirando ultima movimentacao 2 vezes