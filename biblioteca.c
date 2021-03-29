#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

//Declaração da Struct do tipo Movimento
typedef struct
{
    int dt_movimentacao;
    int nConta;
    int tipoMovimentacao;
    float valor;
} Movimento;

//Declaração da Struct do tipo Pessoa
typedef struct
{
    int numeroConta;
    char nomeCliente[32];
    int dt_abertura;
    int tipoConta;
    float limite;
    int dt_vencimento;
    float saldo;
} Pessoa;

//Procedure para limpar o buffer do teclado
void clean_stdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//Função para cadastrar novos clientes
int cadastrarClientes(Pessoa cliente, int i)
{
    system("cls");
    FILE *arq;
    FILE *arq2;
    int status;
    char c;

    //TO-DO: Verify account limit

    arq = fopen("./arquivosBin/cadastros.bin", "ab");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arq2 = fopen("./arquivosTxt/cadastros.txt", "a");
    if (arq2 == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    while (1)
    {
        printf("Digite as informacoes do cliente:\n");
        cliente.numeroConta = i + 1;
        cliente.saldo = 0;
        while (1)
        {
            printf("Tipo de conta (1 - Conta Simples; 2 - Conta Especial): ");
            scanf("%d", &cliente.tipoConta);
            if (cliente.tipoConta == 1 || cliente.tipoConta == 2)
                break;
            else
                printf("\nTipo de conta invalido! Insira novamente...\n\n");
        }
        printf("Nome do cliente: ");
        clean_stdin();
        fgets(cliente.nomeCliente, 32, stdin);
        printf("Data de Abertura (DDMMYY): ");
        scanf("%d", &cliente.dt_abertura);
        if (cliente.tipoConta == 2)
        {
            printf("Limite: ");
            scanf("%f", &cliente.limite);
            printf("Data de Vencimento (DDMMYY): ");
            scanf("%d", &cliente.dt_vencimento);
        }
        else
        {
            cliente.limite = -1;
            cliente.dt_vencimento = -1;
        }
        //Gravando arquivo .bin
        status = fwrite(&cliente, sizeof(Pessoa), 1, arq);
        if (status != 1)
            puts("Erro ao gravar o arquivo .bin!");
        else
            puts("\nArquivo .bin gravado com sucesso!");

        //Gravando arquivo .txt
        fprintf(arq2, "Numero da conta: %d\n", cliente.numeroConta);
        fprintf(arq2, "Nome do cliente: %s", cliente.nomeCliente);
        fprintf(arq2, "Data de Abertura: %d\n", cliente.dt_abertura);
        fprintf(arq2, "Tipo de conta: %d\n", cliente.tipoConta);
        fprintf(arq2, "Limite: %.2f\n", cliente.limite);
        fprintf(arq2, "Data de Vencimento: %d\n", cliente.dt_vencimento);
        fprintf(arq2, "Saldo: %.2f\n\n", cliente.saldo);
        puts("Arquivo .txt gravado com sucesso!");

        printf("\n\nPressione qualquer tecla para cadastrar o proximo cliente ou insira 0 para sair do cadastro...");
        clean_stdin();
        i++;
        c = getchar();
        if (c == 48)
            break;
        system("cls");
    }

    fclose(arq2);
    fclose(arq);
    return i;
}

//Procedure para gravar dados no arquivo "Movimento"
void appendMovimento()
{
    system("cls");
    FILE *arq, *arq2;
    Movimento mv;
    int status, n;
    char c = 1;
    float valor;

    //Processo de gravação no arquivo "Movimentacao"
    arq = fopen("./arquivosBin/movimento.bin", "ab");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arq2 = fopen("./arquivosTxt/movimento.txt", "a");
    if (arq2 == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    while (1)
    {
        printf("Digite a data da operacao: ");
        scanf("%d", &mv.dt_movimentacao);
        if (c == 1)
            fprintf(arq2, "%d\n", mv.dt_movimentacao);
        else
            fprintf(arq2, "\n%d\n", mv.dt_movimentacao);

        while (1)
        {

            printf("Digite o numero da conta do cliente: ");
            scanf("%d", &mv.nConta);
            printf("Digite o tipo da operacao (1 - deposito, 2 - saque): ");
            scanf("%d", &mv.tipoMovimentacao);
            printf("Digite o valor: ");
            scanf("%f", &mv.valor);

            //Append no arquivo movimento.bin
            status = fwrite(&mv, sizeof(Movimento), 1, arq);
            if (status != 1)
                puts("Erro ao gravar no arquivo movimento.bin!");

            //Append no arquivo movimento.txt
            fprintf(arq2, "%d; %d; %.2f\n", mv.nConta, mv.tipoMovimentacao, mv.valor);

            printf("\n\nPressione:\n");
            printf("Qualquer tecla para inserir outra movimentacao na mesma data\n");
            printf("1 - Inserir movimentacao em outra data\n");
            printf("0 - Voltar\n");

            clean_stdin();
            c = getchar();
            if (c == 49 || c == 48)
                break;
        }
        if (c == 48)
            break;
    }

    puts("Arquivo .bin gravado com sucesso!");
    puts("Arquivo .txt gravado com sucesso!");
    fclose(arq);
    fclose(arq2);

    printf("\n\nGostaria de gerar um relatorio de movimentacoes a partir de uma data? (1 - Sim; 2 - Nao)");
    printf("\nOpcao: ");
    scanf("%d", &n);
    if (n == 1)
        relatorioMovimento();
}

//Procedure para criar os arquivos "Cadastro" e "Movimento" no formato .txt e .bin
void createFiles()
{
    FILE *arq, *arq2;

    //Arquivo "Cadastro"
    arq = fopen("./arquivosBin/cadastros.bin", "wb");
    if (arq == NULL)
    {
        perror("Erro ao criar o arquivo");
        exit(1);
    }
    arq2 = fopen("./arquivosTxt/cadastros.txt", "w");
    if (arq2 == NULL)
    {
        perror("Erro ao criar o arquivo");
        exit(1);
    }
    fclose(arq);
    fclose(arq2);

    //Arquivo "Movimento"
    arq = fopen("./arquivosBin/movimento.bin", "wb");
    if (arq == NULL)
    {
        perror("Erro ao criar o arquivo");
        exit(1);
    }
    arq2 = fopen("./arquivosTxt/movimento.txt", "w");
    if (arq2 == NULL)
    {
        perror("Erro ao criar o arquivo");
        exit(1);
    }
    fclose(arq);
    fclose(arq2);
}

//Gera um relatório de movimentações a partir de uma data
void relatorioMovimento()
{
    system("cls");
    FILE *arqWrite, *arqRead;
    Movimento mv;
    int data;

    arqWrite = fopen("./relatorios/relatorio_movimentacao.txt", "w");
    arqRead = fopen("./arquivosBin/movimento.bin", "rb");
    printf("Digite a data do relatorio: ");
    scanf("%d", &data);
    fprintf(arqWrite, "Movimentacoes do dia %d\n", data);
    while (1)
    {
        fread(&mv, sizeof(Movimento), 1, arqRead);
        if (feof(arqRead))
            break;
        if (mv.dt_movimentacao == data)
            fprintf(arqWrite, "conta: %d; operacao: %d; valor: %.2f\n", mv.nConta, mv.tipoMovimentacao, mv.valor);
    }
    puts("\nRelatorio gerado com sucesso");
    fclose(arqWrite);
    fclose(arqRead);
}

//Atualiza o saldo do cadastro a partir de um arquivo "Movimento"
int updateCadastro(int indexUpdate)
{
    system("cls");
    int n, data, j = indexUpdate;
    FILE *arq, *arqCopy, *arqMovimento, *arqTxt, *arqRelatorio;
    Pessoa cliente;
    Movimento mv;

    arqMovimento = fopen("./arquivosBin/movimento.bin", "rb");
    if (arqMovimento == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arq = fopen("./arquivosBin/cadastro.bin", "rb");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arqCopy = fopen("./arquivosBin/cadastroTemp.bin", "w+b");
    if (arqCopy == NULL)
    {
        perror("Erro ao criar o arquivo");
        exit(1);
    }
    arqTxt = fopen("./arquivosTxt/cadastro.txt", "w");
    if (arqTxt == NULL)
    {
        perror("Erro ao recriar o arquivo");
        exit(1);
    }
    arqRelatorio = fopen("./relatorios/relatorio_saldo_atualizado.txt", "w");
    if (arqRelatorio == NULL)
    {
        perror("Erro ao criar o arquivo");
        exit(1);
    }

    while (1)
    {
        printf("1 - Atualizar cadastro com base em TODAS as movimentacoes\n");
        printf("2 - Atualizar cadastro com base nas movimentacoes de uma data especifica\n");
        printf("Opcao: ");
        scanf("%d", &n);

        if (n == 1)
        {
            while (1)
            {
                fread(&cliente, sizeof(Pessoa), 1, arq);
                while (1)
                {
                    j = indexUpdate;
                    fread(&mv, sizeof(Movimento), 1, arqMovimento);
                    if (mv.nConta == cliente.numeroConta)
                    {
                        if (mv.tipoMovimentacao == 1)
                            cliente.saldo += mv.valor;
                        if (mv.tipoMovimentacao == 2)
                            cliente.saldo -= mv.valor;
                    }
                    j++;
                    if (feof(arqMovimento))
                        break;
                }
                fseek(arqMovimento, sizeof(Movimento) * indexUpdate, SEEK_SET); //Volta para o começo do arquivo movimento.bin

                //Gravando no arquivo "cadastroTemp.bin"
                fwrite(&cliente, sizeof(Pessoa), 1, arqCopy);

                //Regravando no arquivo "cadastro.txt"
                fprintf(arqTxt, "Numero da conta: %d\n", cliente.numeroConta);
                fprintf(arqTxt, "Nome do cliente: %s", cliente.nomeCliente);
                fprintf(arqTxt, "Data de Abertura: %d\n", cliente.dt_abertura);
                fprintf(arqTxt, "Tipo de conta: %d\n", cliente.tipoConta);
                fprintf(arqTxt, "Limite: %.2f\n", cliente.limite);
                fprintf(arqTxt, "Data de Vencimento: %d\n", cliente.dt_vencimento);
                fprintf(arqTxt, "Saldo: %.2f\n\n", cliente.saldo);

                //Gerando relatório de saldo atualizado
                fprintf(arqRelatorio, "Numero da conta: %d\n", cliente.numeroConta);
                fprintf(arqRelatorio, "Nome do cliente: %s", cliente.nomeCliente);
                fprintf(arqRelatorio, "Saldo: %.2f\n\n", cliente.saldo);

                if (feof(arq))
                    break;
            }

            //Passando informações de "cadastroTemp.bin" para "cadastro.bin"
            fclose(arq);
            arq = fopen("./arquivosBin/cadastro.bin", "wb");
            fseek(arqCopy, 0, SEEK_SET); //Volta para o começo do arquivo cadastroTemp.bin

            while (1)
            {
                fread(&cliente, sizeof(Pessoa), 1, arqCopy);
                fwrite(&cliente, sizeof(Pessoa), 1, arq);
                if (feof(arqCopy))
                    break;
            }

            break;
        }
        if (n == 2)
        {
            printf("Digite a data: ");
            scanf("%d", &data);
            while (1)
            {
                fread(&cliente, sizeof(Pessoa), 1, arq);
                while (1)
                {
                    fread(&mv, sizeof(Movimento), 1, arqMovimento);
                    if (mv.nConta == cliente.numeroConta && mv.dt_movimentacao == data)
                    {
                        if (mv.tipoMovimentacao == 1)
                            cliente.saldo += mv.valor;
                        if (mv.tipoMovimentacao == 2)
                            cliente.saldo -= mv.valor;
                    }
                    if (feof(arqMovimento))
                        break;
                }
                fseek(arqMovimento, 0, SEEK_SET); //Volta para o começo do arquivo movimento.bin

                //Gravando no arquivo "cadastroTemp.bin"
                fwrite(&cliente, sizeof(Pessoa), 1, arqCopy);

                //Regravando no arquivo "cadastro.txt"
                fprintf(arqTxt, "Numero da conta: %d\n", cliente.numeroConta);
                fprintf(arqTxt, "Nome do cliente: %s", cliente.nomeCliente);
                fprintf(arqTxt, "Data de Abertura: %d\n", cliente.dt_abertura);
                fprintf(arqTxt, "Tipo de conta: %d\n", cliente.tipoConta);
                fprintf(arqTxt, "Limite: %.2f\n", cliente.limite);
                fprintf(arqTxt, "Data de Vencimento: %d\n", cliente.dt_vencimento);
                fprintf(arqTxt, "Saldo: %.2f\n\n", cliente.saldo);

                //Gerando relatório de saldo atualizado
                fprintf(arqRelatorio, "Numero da conta: %d\n", cliente.numeroConta);
                fprintf(arqRelatorio, "Nome do cliente: %s", cliente.nomeCliente);
                fprintf(arqRelatorio, "Saldo: %.2f\n\n", cliente.saldo);

                if (feof(arq))
                    break;
            }

            //Passando informações de "cadastroTemp.bin" para "cadastro.bin"
            fclose(arq);
            arq = fopen("./arquivosBin/cadastro.bin", "wb");
            fseek(arqCopy, 0, SEEK_SET); //Volta para o começo do arquivo cadastroTemp.bin

            while (1)
            {
                fread(&cliente, sizeof(Pessoa), 1, arqCopy);
                fwrite(&cliente, sizeof(Pessoa), 1, arq);
                if (feof(arqCopy))
                    break;
            }

            break;
        }

        puts("\nOpcao invalida! Insira novamente...\n\n");
    }

    puts("\nCadastro atualizado com sucesso!");
    puts("Relatorio gerado com sucesso");

    fclose(arqCopy);
    fclose(arq);
    fclose(arqTxt);
    fclose(arqMovimento);
    remove("./arquivosBin/cadastroTemp.bin"); //Apaga o arquivo temporário "cadastroTemp.bin"
    return j;
}

void listDeposito()
{
    system("cls");
    FILE *arq, *arq2, *arq3;
    Pessoa cliente;
    Movimento mv;
    int numero_conta;

    arq = fopen("./arquivosBin/movimento.bin", "rb");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arq2 = fopen("./relatorios/relatorio_depositos.txt", "w");
    if (arq2 == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arq3 = fopen("./arquivosBin/cadastro.bin", "rb");
    if (arq3 == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    printf("Digite o numero da conta a ser consultada: ");
    scanf("%d", &numero_conta);

    //Achar o nome do cliente a partir do numero da conta
    while (1)
    {
        fread(&cliente, sizeof(Pessoa), 1, arq3);
        if (numero_conta == cliente.numeroConta)
            break;
        if (feof(arq3))
            break;
    }
    fclose(arq3);

    //Cabeçalho
    fprintf(arq2, "Informacao referente a conta: %d\n", numero_conta);
    printf("Informacao referente a conta: %d\n", numero_conta);
    fprintf(arq2, "Cliente: %s", cliente.nomeCliente);
    printf("Cliente: %s", cliente.nomeCliente);

    //Dados dos depositos
    while (1)
    {
        fread(&mv, sizeof(Movimento), 1, arq);
        if (mv.nConta == numero_conta && mv.tipoMovimentacao == 1)
        {
            fprintf(arq2, "Conta: %d; tipoOperacao: %d; Valor: %.2f\n", mv.nConta, mv.tipoMovimentacao, mv.valor);
            printf("Conta: %d; tipoOperacao: %d; Valor: %.2f\n", mv.nConta, mv.tipoMovimentacao, mv.valor);
        }
        if (feof(arq))
            break;
    }

    fclose(arq);
    fclose(arq2);
}