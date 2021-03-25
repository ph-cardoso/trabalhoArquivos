#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CONTAS 2

typedef struct Pessoa{
    int numero_conta;
    char nome_cliente[32];
    int data_abertura;
    int tipo_conta;
    float limite;
    int data_vencimento;
    float saldo;
} Pessoa;

void clean_stdin();
int cadastrar(Pessoa cliente[],int i);
void criaMovimento(int data);

int main(){
    Pessoa cliente[CONTAS];
    int index, n;
    int data;

    index = cadastrar(cliente,0);
    system("cls");

    do {
        //MENU
        printf("1. Cadastrar mais clientes\n");
        printf("2. Gerar arquivo de movimentacao a partir de data\n");
        printf("3. Atualizar cadastro a partir de 'movimento'\n");
        printf("4. Lista de depositos realizados a partir do numero da conta\n");
        printf("5. Consultar saldo a partir do numero da conta\n");
        printf("6. Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &n);

        switch(n){
            case 1:
                system("cls");
                cadastrar(cliente, index);
            break;
            case 2:
                system("cls");
                printf("Insira a data para criar o arquivo Movimento: ");
                scanf("%d", &data);
                printf("\n\n");
                criaMovimento(data);
            break;
            case 3:
                system("cls");
                
            break;
            case 4:
                system("cls");
                
            break;
            case 5:
                system("cls");
                
            break;
            case 6:
                exit(0);
            break;
            default:
                system("cls");
                printf("A opcao informada: %d e invalida\n", n);
        }
        
        printf("\n\nPressione qualquer tecla para continuar...");
        clean_stdin();
        getchar();
    } while(n != 6);

    return 0;
}

void clean_stdin(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int cadastrar(Pessoa cliente[], int i){
    FILE *arq;
    FILE *arq2;
    int status;
    char c;
    
    arq = fopen("./arquivosBin/cadastros.bin", "wb");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arq2 = fopen("./arquivosTxt/cadastros.txt", "w");
    if(arq2 == NULL){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    while(1){
        printf("Digite as informacoes do cliente:\n");
        cliente[i].numero_conta = i+1;
        cliente[i].saldo = 0;
        printf("Nome do cliente: ");
        scanf("%[^\n]", cliente[i].nome_cliente);
        printf("Data de Abertura: ");
        scanf("%d", &cliente[i].data_abertura);
        printf("Tipo de conta (1 - Conta Simples; 2 - Conta Especial): ");
        scanf("%d", &cliente[i].tipo_conta);
        if(cliente[i].tipo_conta == 2){
            printf("Limite: ");
            scanf("%f", &cliente[i].limite);
            printf("Data de Vencimento: ");
            scanf("%d", &cliente[i].data_vencimento);
        }
        else{
            cliente[i].limite = 0;
            cliente[i].data_vencimento = 0;
        }
        //Gravando arquivo .bin
        status = fwrite(&cliente[i],sizeof(Pessoa),1,arq);
        if(status != 1)
            puts("Erro ao gravar o arquivo .bin!");
        else
            puts("Arquivo .bin gravado com sucesso!");

        //Gravando arquivo .txt
        fprintf(arq2, "Numero da conta: %d\n", cliente[i].numero_conta);
        fprintf(arq2, "Nome do cliente: %s\n", cliente[i].nome_cliente);
        fprintf(arq2, "Data de Abertura: %d\n", cliente[i].data_abertura);
        fprintf(arq2, "Tipo de conta: %d\n", cliente[i].tipo_conta);
        fprintf(arq2, "Limite: %.2f\n", cliente[i].limite);
        fprintf(arq2, "Data de Vencimento: %d\n", cliente[i].data_vencimento);
        puts("Arquivo .txt gravado com sucesso!");
        
        printf("\n\nPressione qualquer tecla para cadastrar o próximo cliente ou insira 9 para sair do cadastro...");
        clean_stdin();
        c = getchar();
        if(c == 57)
            break;
        clean_stdin();
        
        /*
        printf("\n\n\n");
        printf("Numero da conta: %d\n", cliente[i].numero_conta);
        printf("Nome do cliente: %s\n", cliente[i].nome_cliente);
        printf("Data de Abertura: %d\n", cliente[i].data_abertura);
        printf("Tipo de conta: %d\n", cliente[i].tipo_conta);
        printf("Limite: %.2f\n", cliente[i].limite);
        printf("Data de Vencimento: %d\n", cliente[i].data_vencimento);
        */

        i++;
    }

    fclose(arq2);
    fclose(arq);
    return i;
}

void criaMovimento(int data){
    FILE *arq, *arq2;
    int nConta, tipoOp, j;
    int status;
    char c;
    float valor;

    arq = fopen("./arquivosBin/movimento.bin", "wb");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    arq2 = fopen("./arquivosTxt/movimento.txt", "w");
    if(arq2 == NULL){
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
        
        fprintf(arq, "%d\n", data);
        fprintf(arq2, "%d\n", data);
    while(1){
        printf("Digite a conta do cliente: ");
        scanf("%d", &nConta);
        printf("Digite o tipo da operacao (1 - depósito, 2 - saque): ");
        scanf("%d", &tipoOp);
        printf("Digite o valor: ");
        scanf("%f", &valor);

        //Gravando arquivo .bin
        fprintf(arq, "%d; %d; %.2f\n", nConta, tipoOp, valor);
        
        //Gravando arquivo .txt
        fprintf(arq2, "%d; %d; %.2f\n", nConta, tipoOp, valor);
        
        printf("\n\nPressione qualquer tecla para inserir a proxima movimentacao ou insira 9 para sair ...");
        clean_stdin();
        c = getchar();
        if(c == 57)
            break;
        clean_stdin();

        j++;
    }
    puts("Arquivo .bin gravado com sucesso!");
    puts("Arquivo .txt gravado com sucesso!");

    fclose(arq);
    fclose(arq2);
}