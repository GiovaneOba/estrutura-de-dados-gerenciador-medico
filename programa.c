#include <stdio.h>
#include "1_estruturas.h"
#include "1_operacoes.c"

int main(void) {
  int opcao = -1;
  
  Lista *listaPacientes = inicializarLista();
  
  while (1) {
        opcao = menuPrincipal();

        if (opcao == 0) {
            break;
        }
        switch (opcao) {
            case 1:
                menuCadastro(listaPacientes);
                break;
            default:
                printf("⚠️  Opção inválida! Por favor, tente novamente.\n");
                break;
        }
    }

    return 0;
}
