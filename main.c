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
} Pessoa;

void clean_stdin();
void cadastrar(Pessoa cliente[]);

int main(){
    Pessoa cliente[CONTAS];
    
    cadastrar(cliente);




    return 0;
}

void cadastrar(Pessoa cliente[]){
    FILE *arq;
    FILE *arq2;
    int i = 0, status;
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

    while(c!=27){
        printf("Digite as informacoes do cliente:\n");
        cliente[i].numero_conta = i+1;
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
        
        printf("\n\nPressione qualquer tecla para cadastrar o próximo cliente ou ESC para sair do cadastro...");
        clean_stdin();
        c = getchar();
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
}

void clean_stdin(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}