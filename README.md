# trabalhoArquivos

Trabalho de arquivos da faculdade - Orientações:
Utilizando o conceito de arquivos em C, realize a criação um arquivo que contenha o registros de operações de um banco.
Esse banco mantém um cadastro de clientes (clientes) contendo:

O número da conta (inteiro, entre 1 e 5OO);
Nome do cliente (32 caracteres);
Data de abertura da conta (ddmmaa);
Tipo da conta (1 - simples ou 2 - especial);
Em caso de conta especial:
Limite (real);
Data de vencimento (ddmmaa);

O banco possui um arquivo de movimento (movimento), cujo primeiro registro contém a data do movimento e os demais registros contém o número da conta, o tipo da operação (1 - depósito, 2 - saque) e o valor.

Pede-se:
A) Implemente uma rotina que gere o cadastro de clientes - os dados de cada cliente deverão ser armazenados na posição do arquivo igual ao seu número de conta e a geração do arquivo deverá acontecer de forma direta;

B) Escreva um subprograma que gere o arquivo movimento referente a um determinado dia;

C) Desenvolva uma rotina que atualize o cadastro dos clientes a partir de um arquivo movimento e emita um relatório com o saldo atualizado de cada cliente segundo o intervalo informado;

D) Escreva uma rotina que liste todos os depósitos realizados na conta de um determinado cliente;

E) Construa uma rotina que atenda um número indeterminado de consultas de saldo - em cada consulta deverá ser fornecido um número da conta e deverá ser devolvido o saldo ou uma mensagem de conta inexistente.
