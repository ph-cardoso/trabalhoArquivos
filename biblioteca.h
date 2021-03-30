#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "biblioteca.c"

typedef struct Movimento;                     //Declaração da Struct do tipo Movimento
typedef struct Pessoa;                        //Declaração da Struct do tipo Pessoa
void clean_stdin();                           //Procedure para limpar o buffer do teclado
int cadastrarClientes(Pessoa cliente, int i); //Função para cadastrar novos clientes
void appendMovimento();                       //Procedure para gravar dados no arquivo "Movimento"
void createFiles();                           //Procedure para criar os arquivos "Cadastro" e "Movimento" no formato .txt e .bin
void relatorioMovimento();                    //Gera um relatório de movimentações a partir de uma data
int updateCadastro(int indexUpdate);          //Atualiza o saldo do cadastro a partir do um arquivo "Movimento"
void listDeposito();                          //Lista todos os depositos feitos na conta de determinado cliente
void buscaSaldo();                            //Consulta o saldo

#endif