#include <stdio.h>
#include "2_estruturas.h"
#include "2_operacoes.c"

int main(void) {
  int opcao = -1;
  
  Lista *listaPacientes = inicializarLista();
  Fila *filaAtendimento = inicializarFila();
  
  Registro pacienteAtual;
  
  while (1) {
        opcao = menuPrincipal();

        if (opcao == 0) {
            break;
        }
        switch (opcao) {
            case 1:
                menuCadastro(listaPacientes);
                break;
            case 2:
                menuAtendimento(listaPacientes, filaAtendimento, &pacienteAtual);
                break;
            default:
                printf("⚠️  Opção inválida! Por favor, tente novamente.\n");
                break;
        }
    }

    return 0;
}
