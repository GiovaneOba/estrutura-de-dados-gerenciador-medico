#include <stdio.h>
#include "estruturas.h"
#include "operacoes.c"

int main(void) {
  int opcao = -1;
  
  Lista *listaPacientes = inicializarLista();
  Fila *filaAtendimento = inicializarFila();

  ABB *arvoreAno = inicializarArvore();
  ABB *arvoreMes = inicializarArvore();
  ABB *arvoreDia = inicializarArvore();
  ABB *arvoreIdade = inicializarArvore();
  
  Registro pacienteAtual;
  
  while (1) {
        opcao = menuPrincipal();

        if (opcao == 0) {
            break;
        }
        switch (opcao) {
            case 1:
                menuCadastro(listaPacientes, arvoreAno, arvoreMes, arvoreDia, arvoreIdade);
                break;
            case 2:
                menuAtendimento(listaPacientes, filaAtendimento, &pacienteAtual);
                break;
            case 3:
                menuPesquisa(arvoreAno, arvoreMes, arvoreDia, arvoreIdade, &pacienteAtual);
                break;
            default:
                printf("⚠️  Opção inválida! Por favor, tente novamente.\n");
                break;
        }
    }

    return 0;
}
