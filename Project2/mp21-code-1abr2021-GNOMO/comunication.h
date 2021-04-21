#include <stdio.h>

typedef struct {
    int i; //número universal único do pedido(gerado pelo Client)
    int t; //inteiro entre 1..9
    pid_t pid; //identificador process
    pid_t tid; //identificador thread
    int res; //Client = -1 ; Server = ? ou -1 caso o serviço esteja encerrado
}message;

void generate