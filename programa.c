#include <stdio.h>
#include "estruturas.h"
#include "operacoes.c"

int main(void) {
  char arquivoDados[] = "dados_pacientes";
  int opcao = -1;
  int contadorRegistros = 0;
  
  Lista *listaPacientes = inicializarLista();
  Fila *filaAtendimento = inicializarFila();
  Pilha *pilhaOperacoes = inicializarPilha();
  HeapPrioridade *heapPrioritario = inicializarHeap();

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
                menuAtendimento(listaPacientes, filaAtendimento, pilhaOperacoes, &pacienteAtual);
                break;
            case 3:
                menuPesquisa(arvoreAno, arvoreMes, arvoreDia, arvoreIdade, &pacienteAtual);
                break;
            case 4:
                desfazerUltimaOperacao(listaPacientes, filaAtendimento, pilhaOperacoes);
                break;
            case 5:
                contadorRegistros = carregarDados(listaPacientes, contadorRegistros, arquivoDados,
                                            arvoreAno, arvoreMes, arvoreDia, arvoreIdade);
                break;
            case 6:
                salvarDados(listaPacientes, arquivoDados);
                break;
            case 7:
                exibirInformacoesSistema();
                break;
            case 8:
                menuAtendimentoPrioritario(listaPacientes, heapPrioritario, pilhaOperacoes);
                break;
            default:
                printf("⚠️  Opção inválida! Por favor, tente novamente.\n");
                break;
        }
    }

    return 0;
}
