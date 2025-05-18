#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Menu Principal
int menuPrincipal() {
  int escolha;
  printf("1.Cadastrar Pacientes\n"
         "2.Atendimento\n"
         "3.Pesquisa\n"
         "4.Desfazer\n"
         "5.Carregar\n"
         "6.Salvar\n"
         "7.Sobre\n"
         "8.Atendimento Prioritário\n"
         "0.Sair\n");
  printf("Selecione uma opção (0-8): ");
  scanf("%d", &escolha);
  printf("\n");
  return escolha;
}

// Menu de Cadastro
void menuCadastro(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, 
                 ABB *arvoreDia, ABB *arvoreIdade) {
  int escolha;
  printf("1-Cadastrar novo paciente\n"
         "2-Consultar paciente por RG\n"
         "3-Mostrar lista completa\n"
         "4-Atualizar dados de paciente\n"
         "5-Remover paciente\n");
  printf("Selecione uma opção: ");
  scanf("%d", &escolha);
  printf("\n");

  switch (escolha) {
    case 1:
      // Registrar novo paciente
      adicionarPaciente(lista, arvoreAno, arvoreMes, arvoreDia, arvoreIdade);
      break;
    case 2:
      // Buscar paciente por RG
      consultarPaciente(lista);
      break;
    case 3:
      // Exibir todos os pacientes
      listarPacientes(lista);
      break;
    case 4:
      // Modificar dados de paciente
      atualizarPaciente(lista);
      break;
    case 5:
      // Remover registro de paciente
      excluirPaciente(lista, arvoreAno, arvoreMes, arvoreDia, arvoreIdade);
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
}

// Menu de Atendimento
void menuAtendimento(Lista *lista, Fila *fila, Pilha *pilha, Registro *paciente) {
  int escolha;
  printf("1-Enfileirar paciente\n"
         "2-Desenfileirar paciente\n"
         "3-Mostrar fila\n");
  printf("Selecione uma opção: ");
  scanf("%d", &escolha);
  printf("\n");

  switch (escolha) {
    case 1:
      // Adicionar paciente à fila
      adicionarNaFila(lista, fila, pilha, paciente);
      break;
    case 2:
      // Atender próximo paciente
      removerDaFila(lista, fila, pilha, paciente);
      break;
    case 3:
      // Visualizar fila de espera
      exibirFila(fila);
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
}

// Menu de Atendimento Prioritário
void menuAtendimentoPrioritario(Lista *lista, HeapPrioridade *heap, Pilha *pilha) {
  int escolha;
  printf("1-Enfileirar paciente prioritário\n"
         "2-Desenfileirar paciente prioritário\n"
         "3-Mostrar fila prioritária\n");
  printf("Selecione uma opção: ");
  scanf("%d", &escolha);
  printf("\n");

  switch (escolha) {
    case 1:
      // Adicionar paciente à fila prioritária
      enfileirarPrioritario(lista, heap, pilha);
      break;
    case 2:
      // Atender próximo paciente prioritário
      desenfileirarPrioritario(heap, pilha);
      break;
    case 3:
      // Visualizar fila prioritária
      exibirFilaPrioritaria(heap);
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
}

// Menu de Pesquisa
void menuPesquisa(ABB *arvoreAno, ABB *arvoreMes, 
                 ABB *arvoreDia, ABB *arvoreIdade, Registro *paciente) {
  int escolha;
  printf("1-Mostrar pacientes ordenados por ano de registro\n"
         "2-Mostrar pacientes ordenados por mês de registro\n"
         "3-Mostrar pacientes ordenados por dia de registro\n"
         "4-Mostrar pacientes ordenados por idade\n");
  printf("Selecione uma opção: ");
  scanf("%d", &escolha);
  printf("\n");

  switch (escolha) {
    case 1:
      // Visualizar pacientes ordenados por ano
      percorrerEmOrdem(arvoreAno->raizArvore);
      break;
    case 2:
      // Visualizar pacientes ordenados por mês
      percorrerEmOrdem(arvoreMes->raizArvore);
      break;
    case 3:
      // Visualizar pacientes ordenados por dia
      percorrerEmOrdem(arvoreDia->raizArvore);
      break;
    case 4:
      // Visualizar pacientes ordenados por idade
      percorrerEmOrdem(arvoreIdade->raizArvore);
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
}

// Criar ficha de paciente
Registro *criarFichaPaciente(char *nome, int idade, char *documento, Data *data) {
  Registro *paciente = malloc(sizeof(Registro));
  strcpy(paciente->nomePaciente, nome);
  paciente->idadePaciente = idade;
  strcpy(paciente->documentoRG, documento);
  paciente->dataRegistro = data;
  return paciente;
}

// Criar nodo para lista
ELista *criarNodoLista(Registro *paciente) {
  ELista *nodo = malloc(sizeof(ELista));
  nodo->prox = NULL;
  nodo->dados = paciente;
  return nodo;
}

// Inicializar lista
Lista *inicializarLista() {
  Lista *lista = malloc(sizeof(Lista));
  lista->inicio = NULL;
  lista->tamanho = 0;
  return lista;
}

// Inicializar heap de prioridade
HeapPrioridade *inicializarHeap() {
  HeapPrioridade *heap = malloc(sizeof(HeapPrioridade));
  heap->quantidade = 0;
  return heap;
}

// Criar data de registro
Data *criarDataRegistro(int dia, int mes, int ano) {
  Data *data = malloc(sizeof(Data));
  data->diaMes = dia;
  data->mesAno = mes;
  data->anoData = ano;
  return data;
}

// Adicionar paciente
void adicionarPaciente(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, 
                      ABB *arvoreDia, ABB *arvoreIdade) {
  char nome[50];
  char documento[10];
  int idade = 0;
  limparBuffer();
  // Obter nome - Usando fgets para permitir nomes compostos
  printf("Digite o nome do paciente: ");
  fgets(nome, sizeof(nome), stdin);
  // Remover o caractere de nova linha do final
  nome[strcspn(nome, "\n")] = '\0';
  
  // Obter RG
  int documentoExistente;
  do {
    documentoExistente = 0;
    printf("Digite o RG do paciente: ");
    scanf("%s", documento); 
    limparBuffer();
    
    // Verificar se RG já existe
    ELista *atual = lista->inicio;
    while (atual != NULL) {
      if (strcmp(atual->dados->documentoRG, documento) == 0) {
        documentoExistente = 1;
        printf("Este RG já está cadastrado. Por favor, informe outro RG.\n");
        break;
      }
      atual = atual->prox;
    }
  } while (documentoExistente); 
  
  // Obter idade
  printf("Digite a idade do paciente: ");
  scanf("%d", &idade);
  
  // Obter data atual
  time_t t = time(NULL);              
  struct tm *dataAtual = localtime(&t);
  int dia = dataAtual->tm_mday;
  int mes = dataAtual->tm_mon + 1;
  int ano = dataAtual->tm_year + 1900;
  
  // Criar estruturas
  Data *data = criarDataRegistro(dia, mes, ano);
  Registro *paciente = criarFichaPaciente(nome, idade, documento, data);
  
  // Adicionar à lista
  ELista *novo = criarNodoLista(paciente);
  novo->prox = lista->inicio;
  lista->inicio = novo;
  lista->tamanho++;

  // Adicionar às árvores
  inserirPorAno(arvoreAno, paciente);
  inserirPorMes(arvoreMes, paciente);
  inserirPorDia(arvoreDia, paciente);
  inserirPorIdade(arvoreIdade, paciente);

  printf("\n");
  printf("Paciente registrado com sucesso!\n");
  printf("\n");
}

// Consultar paciente
void consultarPaciente(Lista *lista) {
  if (lista == NULL || lista->inicio == NULL) {
    printf("Nenhum paciente registrado no sistema.\n\n");
	  return;
  } 

  char documento[10];
  printf("Digite o RG do paciente a ser consultado: ");
  scanf("%s", documento);

  ELista *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->dados->documentoRG, documento) == 0) {
      printf("Nome: %s\n", atual->dados->nomePaciente);
      printf("RG: %s\n", atual->dados->documentoRG);
      printf("Idade: %d\n", atual->dados->idadePaciente);
      printf("Data de registro: %d/%d/%d\n", atual->dados->dataRegistro->diaMes,
             atual->dados->dataRegistro->mesAno, atual->dados->dataRegistro->anoData);
      printf("\n");
      return;
    }
    atual = atual->prox;
    printf("\n");
  }
  printf("Paciente não encontrado no sistema.\n");
}

// Listar todos os pacientes
void listarPacientes(Lista *lista) {
  if (lista == NULL || lista->inicio == NULL) {
    printf("Nenhum paciente registrado no sistema.\n");
    printf("\n");
    return;
  }
  
  ELista *atual = lista->inicio;
  while (atual != NULL) {
    Registro p = *atual->dados;
    printf("Nome: %s\n", p.nomePaciente);
    printf("Idade: %d\n", atual->dados->idadePaciente);
    printf("RG: %s\n", atual->dados->documentoRG);
    printf("Data: %d/%d/%d\n", atual->dados->dataRegistro->diaMes,
           atual->dados->dataRegistro->mesAno, atual->dados->dataRegistro->anoData);
    atual = atual->prox;
    printf("\n");
  }
  printf("\n");
}

// Atualizar dados do paciente
void atualizarPaciente(Lista *lista) {
  if (lista == NULL || lista->inicio == NULL) {
    printf("Nenhum paciente registrado no sistema.\n\n");
    return;
  }

  char documento[10];
  printf("Digite o RG do paciente a ser atualizado: ");
  scanf("%s", documento);
  printf("\n");
  
  // Buscar o paciente na lista
  ELista *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->dados->documentoRG, documento) == 0) {
      break;
    }
    atual = atual->prox;
  }
  
  if (atual == NULL) {
    printf("Paciente não encontrado no sistema.\n");
    return;
  }

  // Exibir dados atuais do paciente
  printf("Dados atuais do paciente:\n"); 
  printf("Nome: %s\n", atual->dados->nomePaciente);
  printf("RG: %s\n", atual->dados->documentoRG);
  printf("Idade: %d\n\n", atual->dados->idadePaciente);

  printf("Qual informação deseja atualizar?\n");
  printf("1-Nome\n2-RG\n3-Idade\n");
  int opcao;
  scanf("%d", &opcao);
  limparBuffer();

  switch (opcao) {
    case 1:
      printf("Digite o novo nome: ");
      // Usando fgets para permitir nomes compostos
      fgets(atual->dados->nomePaciente, 50, stdin);
      // Remover o caractere de nova linha do final
      atual->dados->nomePaciente[strcspn(atual->dados->nomePaciente, "\n")] = '\0';
      printf("Nome atualizado com sucesso!\n\n");
      break;

    case 2: {
      int documentoExistente;
      do {
        char novoDocumento[10];
        documentoExistente = 0;

        printf("Digite o novo RG: ");
        scanf("%s", novoDocumento);
        limparBuffer();

        // Verificar se RG já existe em outro paciente
        ELista *verificacao = lista->inicio;
        while (verificacao != NULL) {
          if (verificacao != atual &&
              strcmp(verificacao->dados->documentoRG, novoDocumento) == 0) {
            documentoExistente = 1;
            printf("Este RG já está cadastrado para outro paciente. Por favor, informe outro RG.\n");
            break;
          }
          verificacao = verificacao->prox;
        }

        if (!documentoExistente) {
          strcpy(atual->dados->documentoRG, novoDocumento);
          printf("RG atualizado com sucesso!\n\n");
        }

      } while (documentoExistente);
      break;
    }

    case 3:
      printf("Digite a nova idade: ");
      scanf("%d", &atual->dados->idadePaciente);
      limparBuffer();
      printf("Idade atualizada com sucesso!\n\n");
      break;

    default:
      printf("Opção inválida. Nenhuma informação foi atualizada.\n\n");
      break;
  }

  printf("Dados atualizados com sucesso!\n\n");
}

// Excluir paciente
void excluirPaciente(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, 
                    ABB *arvoreDia, ABB *arvoreIdade) {
  char documento[10];
  printf("Digite o RG do paciente a ser removido: ");
  scanf("%s", documento);
  printf("\n");
  
  ELista *atual = lista->inicio;
  ELista *anterior = NULL;
  
  while (atual != NULL && strcmp(atual->dados->documentoRG, documento) != 0) {
    anterior = atual;
    atual = atual->prox;
  }
  
  if (atual == NULL) {
    printf("Paciente não encontrado no sistema.\n");
    printf("\n");
  } else {
    if (anterior == NULL) {
      lista->inicio = atual->prox;
      lista->tamanho--;
    } else {
      anterior->prox = atual->prox;
      lista->tamanho--;
    }
    
    EABB *nodoRemoverAno = buscarNaArvoreAno(arvoreAno, atual->dados);
    EABB *nodoRemoverMes = buscarNaArvoreMes(arvoreMes, atual->dados);
    EABB *nodoRemoverDia = buscarNaArvoreDia(arvoreDia, atual->dados);
    EABB *nodoRemoverIdade = buscarNaArvoreIdade(arvoreIdade, atual->dados);
    
    removerDaArvoreAno(arvoreAno, nodoRemoverAno);
    removerDaArvoreMes(arvoreMes, nodoRemoverMes);
    removerDaArvoreDia(arvoreDia, nodoRemoverDia);
    removerDaArvoreIdade(arvoreIdade, nodoRemoverIdade);
    
    printf("Paciente removido com sucesso\n");
  }
}

// Funções para fila
EFila *criarNodoFila(Registro *paciente) {
  EFila *nodo = malloc(sizeof(EFila));
  nodo->prox = NULL;
  nodo->dados = paciente;
  return nodo;
}

Fila *inicializarFila() {
  Fila *fila = malloc(sizeof(Fila));
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;
  return fila;
}

Registro *buscarPaciente(Lista *lista, char *documento) {
  Registro *ficha = malloc(sizeof(Registro));
  ELista *atual = lista->inicio;
  ELista *anterior = NULL;
  
  while (atual != NULL && strcmp(atual->dados->documentoRG, documento) != 0) {
    anterior = atual;
    atual = atual->prox;
  }
  
  if (atual != NULL) {
    return atual->dados;
  } else {
    ficha = NULL;
    printf("Paciente não encontrado no sistema.\n");
    printf("\n");
    return ficha;
  }
}

// Adicionar paciente à fila
void adicionarNaFila(Lista *lista, Fila *fila, Pilha *pilha, Registro *paciente) {
  char documento[10];
  printf("Digite o RG do paciente: ");
  scanf("%s", documento);
  printf("\n");
  
  Registro *pacienteEncontrado = buscarPaciente(lista, documento);
  if (pacienteEncontrado == NULL) {
    return;
  }
  
  // Verificar se paciente já está na fila
  EFila *atual = fila->inicio;
  while (atual != NULL && atual->dados != pacienteEncontrado) {
    atual = atual->prox;
  }
  
  if (atual != NULL) {
    printf("Paciente já está na fila de atendimento\n");
    printf("\n");
    return;
  }
  
  // Adicionar paciente à fila
  EFila *novo = criarNodoFila(pacienteEncontrado);
  if (fila->tamanho == 0) {
    fila->inicio = novo;
  } else {
    fila->fim->prox = novo;
  }
  
  fila->fim = novo;
  fila->tamanho++;
  printf("Paciente %s adicionado à fila de atendimento!\n", pacienteEncontrado->nomePaciente);
  printf("\n");
  
  // Registrar operação na pilha
  empilhar(pilha, 1, pacienteEncontrado);
}

// Atender próximo paciente
Registro *removerDaFila(Lista *lista, Fila *fila, Pilha *pilha, Registro *paciente) {
  if (fila->inicio == NULL) {
    printf("Fila de atendimento vazia, nenhum paciente para atender.\n");
    return NULL;
  }
  
  EFila *removido = fila->inicio;
  Registro *pacienteAtendido = removido->dados;
  
  fila->inicio = fila->inicio->prox;
  if (fila->inicio == NULL) {
    fila->fim = NULL;
  }
  
  fila->tamanho--;
  printf("Paciente %s foi atendido e removido da fila.\n", pacienteAtendido->nomePaciente);
  printf("\n");
  
  // Registrar operação na pilha
  empilhar(pilha, 2, pacienteAtendido);
  
  free(removido);
  return pacienteAtendido;
}

// Exibir fila de atendimento
void exibirFila(Fila *fila) {
  if (fila->inicio == NULL) {
    printf("Fila de atendimento vazia.\n");
    printf("\n");
    return;
  }
  
  printf("Fila de atendimento atual:\n");
  EFila *atual = fila->inicio;
  int posicao = 1;
  
  while (atual != NULL) {
    printf("%d. %s (RG: %s)\n", posicao, atual->dados->nomePaciente, atual->dados->documentoRG);
    atual = atual->prox;
    posicao++;
  }
  printf("\n");
}

// Funções para árvore
EABB *criarNodoArvore(Registro *paciente) {
  EABB *nodo = malloc(sizeof(EABB));
  nodo->dados = paciente;
  nodo->esquerda = NULL;
  nodo->direita = NULL;
  nodo->superior = NULL;
  return nodo;
}

ABB *inicializarArvore() {
  ABB *arvore = malloc(sizeof(ABB));
  arvore->raizArvore = NULL;
  arvore->tamanho = 0;
  return arvore;
}

// Percorrer árvore em ordem
void percorrerEmOrdem(EABB *raiz) {
  if (raiz != NULL) {
    percorrerEmOrdem(raiz->esquerda);
    printf("Nome: %s\n", raiz->dados->nomePaciente);
    printf("RG: %s\n", raiz->dados->documentoRG);
    printf("Idade: %d\n", raiz->dados->idadePaciente);
    printf("Data: %d/%d/%d\n\n", raiz->dados->dataRegistro->diaMes,
           raiz->dados->dataRegistro->mesAno, raiz->dados->dataRegistro->anoData);
    percorrerEmOrdem(raiz->direita);
  }
}

// Inserir por ano
void *inserirPorAno(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
    arvore->tamanho++;
    return NULL;
  }
  
  EABB *atual = arvore->raizArvore;
  EABB *anterior = NULL;
  
  while (atual != NULL) {
    anterior = atual;
    
    if (paciente->dataRegistro->anoData < atual->dados->dataRegistro->anoData) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  novo->superior = anterior;
  
  if (paciente->dataRegistro->anoData < anterior->dados->dataRegistro->anoData) {
    anterior->esquerda = novo;
  } else {
    anterior->direita = novo;
  }
  
  arvore->tamanho++;
  return NULL;
}

// Inserir por mês
void *inserirPorMes(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
    arvore->tamanho++;
    return NULL;
  }
  
  EABB *atual = arvore->raizArvore;
  EABB *anterior = NULL;
  
  while (atual != NULL) {
    anterior = atual;
    
    if (paciente->dataRegistro->mesAno < atual->dados->dataRegistro->mesAno) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  novo->superior = anterior;
  
  if (paciente->dataRegistro->mesAno < anterior->dados->dataRegistro->mesAno) {
    anterior->esquerda = novo;
  } else {
    anterior->direita = novo;
  }
  
  arvore->tamanho++;
  return NULL;
}

// Inserir por dia
void *inserirPorDia(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
    arvore->tamanho++;
    return NULL;
  }
  
  EABB *atual = arvore->raizArvore;
  EABB *anterior = NULL;
  
  while (atual != NULL) {
    anterior = atual;
    
    if (paciente->dataRegistro->diaMes < atual->dados->dataRegistro->diaMes) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  novo->superior = anterior;
  
  if (paciente->dataRegistro->diaMes < anterior->dados->dataRegistro->diaMes) {
    anterior->esquerda = novo;
  } else {
    anterior->direita = novo;
  }
  
  arvore->tamanho++;
  return NULL;
}

// Inserir por idade
void *inserirPorIdade(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
    arvore->tamanho++;
    return NULL;
  }
  
  EABB *atual = arvore->raizArvore;
  EABB *anterior = NULL;
  
  while (atual != NULL) {
    anterior = atual;
    
    if (paciente->idadePaciente < atual->dados->idadePaciente) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  novo->superior = anterior;
  
  if (paciente->idadePaciente < anterior->dados->idadePaciente) {
    anterior->esquerda = novo;
  } else {
    anterior->direita = novo;
  }
  
  arvore->tamanho++;
  return NULL;
}

// Buscar na árvore por ano
EABB* buscarNaArvoreAno(ABB *arvore, Registro *paciente) {
  EABB *atual = arvore->raizArvore;
  
  while (atual != NULL) {
    if (atual->dados == paciente) {
      return atual;
    }
    
    if (paciente->dataRegistro->anoData < atual->dados->dataRegistro->anoData) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  return NULL;
}

// Buscar na árvore por mês
EABB* buscarNaArvoreMes(ABB *arvore, Registro *paciente) {
  EABB *atual = arvore->raizArvore;
  
  while (atual != NULL) {
    if (atual->dados == paciente) {
      return atual;
    }
    
    if (paciente->dataRegistro->mesAno < atual->dados->dataRegistro->mesAno) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  return NULL;
}

// Buscar na árvore por dia
EABB* buscarNaArvoreDia(ABB *arvore, Registro *paciente) {
  EABB *atual = arvore->raizArvore;
  
  while (atual != NULL) {
    if (atual->dados == paciente) {
      return atual;
    }
    
    if (paciente->dataRegistro->diaMes < atual->dados->dataRegistro->diaMes) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  return NULL;
}

// Buscar na árvore por idade
EABB* buscarNaArvoreIdade(ABB *arvore, Registro *paciente) {
  EABB *atual = arvore->raizArvore;
  
  while (atual != NULL) {
    if (atual->dados == paciente) {
      return atual;
    }
    
    if (paciente->idadePaciente < atual->dados->idadePaciente) {
      atual = atual->esquerda;
    } else {
      atual = atual->direita;
    }
  }
  
  return NULL;
}

// Remover da árvore por ano
void removerDaArvoreAno(ABB *arvore, EABB *nodo) {
  if (nodo == NULL) {
    return;
  }
  
  // Caso 1: Nodo é folha
  if (nodo->esquerda == NULL && nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = NULL;
    } else {
      nodo->superior->direita = NULL;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 2: Nodo tem apenas um filho
  else if (nodo->esquerda == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->direita;
      nodo->direita->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->direita;
      nodo->direita->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->direita;
      nodo->direita->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  else if (nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->esquerda;
      nodo->esquerda->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 3: Nodo tem dois filhos
  else {
    EABB *sucessor = nodo->direita;
    while (sucessor->esquerda != NULL) {
      sucessor = sucessor->esquerda;
    }
    
    nodo->dados = sucessor->dados;
    
    if (sucessor->superior == nodo) {
      nodo->direita = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = nodo;
      }
    } else {
      sucessor->superior->esquerda = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = sucessor->superior;
      }
    }
    
    free(sucessor);
    arvore->tamanho--;
  }
}

// Remover da árvore por mês
void removerDaArvoreMes(ABB *arvore, EABB *nodo) {
  if (nodo == NULL) {
    return;
  }
  
  // Caso 1: Nodo é folha
  if (nodo->esquerda == NULL && nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = NULL;
    } else {
      nodo->superior->direita = NULL;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 2: Nodo tem apenas um filho
  else if (nodo->esquerda == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->direita;
      nodo->direita->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->direita;
      nodo->direita->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->direita;
      nodo->direita->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  else if (nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->esquerda;
      nodo->esquerda->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 3: Nodo tem dois filhos
  else {
    EABB *sucessor = nodo->direita;
    while (sucessor->esquerda != NULL) {
      sucessor = sucessor->esquerda;
    }
    
    nodo->dados = sucessor->dados;
    
    if (sucessor->superior == nodo) {
      nodo->direita = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = nodo;
      }
    } else {
      sucessor->superior->esquerda = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = sucessor->superior;
      }
    }
    
    free(sucessor);
    arvore->tamanho--;
  }
}

// Remover da árvore por dia
void removerDaArvoreDia(ABB *arvore, EABB *nodo) {
  if (nodo == NULL) {
    return;
  }
  
  // Caso 1: Nodo é folha
  if (nodo->esquerda == NULL && nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = NULL;
    } else {
      nodo->superior->direita = NULL;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 2: Nodo tem apenas um filho
  else if (nodo->esquerda == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->direita;
      nodo->direita->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->direita;
      nodo->direita->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->direita;
      nodo->direita->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  else if (nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->esquerda;
      nodo->esquerda->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 3: Nodo tem dois filhos
  else {
    EABB *sucessor = nodo->direita;
    while (sucessor->esquerda != NULL) {
      sucessor = sucessor->esquerda;
    }
    
    nodo->dados = sucessor->dados;
    
    if (sucessor->superior == nodo) {
      nodo->direita = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = nodo;
      }
    } else {
      sucessor->superior->esquerda = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = sucessor->superior;
      }
    }
    
    free(sucessor);
    arvore->tamanho--;
  }
}

// Remover da árvore por idade
void removerDaArvoreIdade(ABB *arvore, EABB *nodo) {
  if (nodo == NULL) {
    return;
  }
  
  // Caso 1: Nodo é folha
  if (nodo->esquerda == NULL && nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = NULL;
    } else {
      nodo->superior->direita = NULL;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 2: Nodo tem apenas um filho
  else if (nodo->esquerda == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->direita;
      nodo->direita->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->direita;
      nodo->direita->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->direita;
      nodo->direita->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  else if (nodo->direita == NULL) {
    if (nodo->superior == NULL) {
      arvore->raizArvore = nodo->esquerda;
      nodo->esquerda->superior = NULL;
    } else if (nodo == nodo->superior->esquerda) {
      nodo->superior->esquerda = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    } else {
      nodo->superior->direita = nodo->esquerda;
      nodo->esquerda->superior = nodo->superior;
    }
    free(nodo);
    arvore->tamanho--;
  }
  // Caso 3: Nodo tem dois filhos
  else {
    EABB *sucessor = nodo->direita;
    while (sucessor->esquerda != NULL) {
      sucessor = sucessor->esquerda;
    }
    
    nodo->dados = sucessor->dados;
    
    if (sucessor->superior == nodo) {
      nodo->direita = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = nodo;
      }
    } else {
      sucessor->superior->esquerda = sucessor->direita;
      if (sucessor->direita != NULL) {
        sucessor->direita->superior = sucessor->superior;
      }
    }
    
    free(sucessor);
    arvore->tamanho--;
  }
}

// Funções para pilha
EPilha *criarNodoPilha(int operacao, Registro *paciente) {
  EPilha *nodo = malloc(sizeof(EPilha));
  nodo->dados = paciente;
  nodo->tipoOperacao = operacao;
  nodo->prox = NULL;
  nodo->ant = NULL;
  return nodo;
}

Pilha *inicializarPilha() {
  Pilha *pilha = malloc(sizeof(Pilha));
  pilha->topo = NULL;
  pilha->tamanho = 0;
  return pilha;
}

// Empilhar operação
void empilhar(Pilha *pilha, int operacao, Registro *paciente) {
  EPilha *novo = criarNodoPilha(operacao, paciente);
  
  if (pilha->tamanho == 0) {
    pilha->topo = novo;
  } else {
    novo->prox = pilha->topo;
    pilha->topo->ant = novo;
    pilha->topo = novo;
  }
  
  pilha->tamanho++;
}

// Desfazer última operação
void desfazerUltimaOperacao(Lista *lista, Fila *fila, Pilha *pilha) {
  if (pilha->topo == NULL) {
    printf("Nenhuma operação para desfazer.\n");
    return;
  }
  
  EPilha *operacao = pilha->topo;
  
  // Verificar tipo de operação
  if (operacao->tipoOperacao == 1) {
    // Desfazer adição à fila
    printf("Desfazendo adição do paciente %s à fila.\n", operacao->dados->nomePaciente);
    
    // Remover da fila
    if (fila->inicio != NULL) {
      EFila *atual = fila->inicio;
      EFila *anterior = NULL;
      
      while (atual != NULL && atual->dados != operacao->dados) {
        anterior = atual;
        atual = atual->prox;
      }
      
      if (atual != NULL) {
        if (anterior == NULL) {
          fila->inicio = atual->prox;
        } else {
          anterior->prox = atual->prox;
        }
        
        if (atual == fila->fim) {
          fila->fim = anterior;
        }
        
        free(atual);
        fila->tamanho--;
      }
    }
  } else if (operacao->tipoOperacao == 2) {
    // Desfazer remoção da fila
    printf("Desfazendo remoção do paciente %s da fila.\n", operacao->dados->nomePaciente);
    
    // Adicionar de volta à fila (no início)
    adicionarNaFilaAutomatico(lista, fila, operacao->dados, pilha);
  }
  
  // Remover operação da pilha
  pilha->topo = operacao->prox;
  if (pilha->topo != NULL) {
    pilha->topo->ant = NULL;
  }
  
  free(operacao);
  pilha->tamanho--;
}

// Adicionar paciente à fila automaticamente (sem registrar na pilha)
void adicionarNaFilaAutomatico(Lista *lista, Fila *fila, Registro *paciente, Pilha *pilha) {
  // Verificar se paciente já está na fila
  EFila *atual = fila->inicio;
  while (atual != NULL && atual->dados != paciente) {
    atual = atual->prox;
  }
  
  if (atual != NULL) {
    printf("Paciente já está na fila de atendimento\n");
    return;
  }
  
  // Adicionar paciente à fila (no início)
  EFila *novo = criarNodoFila(paciente);
  novo->prox = fila->inicio;
  fila->inicio = novo;
  
  if (fila->fim == NULL) {
    fila->fim = novo;
  }
  
  fila->tamanho++;
  printf("Paciente %s readicionado à fila de atendimento!\n", paciente->nomePaciente);
}

// Funções para heap de prioridade
void trocarPacientes(HeapPrioridade *heap, int i, int j) {
  Registro *temp = heap->dados[i];
  heap->dados[i] = heap->dados[j];
  heap->dados[j] = temp;
}

void subirNoHeap(HeapPrioridade *heap, int indice) {
  int pai = (indice - 1) / 2;
  
  if (indice > 0 && heap->dados[indice]->idadePaciente > heap->dados[pai]->idadePaciente) {
    trocarPacientes(heap, indice, pai);
    subirNoHeap(heap, pai);
  }
}

void descerNoHeap(HeapPrioridade *heap, int indice) {
  int maior = indice;
  int esquerda = 2 * indice + 1;
  int direita = 2 * indice + 2;
  
  if (esquerda < heap->quantidade && 
      heap->dados[esquerda]->idadePaciente > heap->dados[maior]->idadePaciente) {
    maior = esquerda;
  }
  
  if (direita < heap->quantidade && 
      heap->dados[direita]->idadePaciente > heap->dados[maior]->idadePaciente) {
    maior = direita;
  }
  
  if (maior != indice) {
    trocarPacientes(heap, indice, maior);
    descerNoHeap(heap, maior);
  }
}

void enfileirarPrioritario(Lista *lista, HeapPrioridade *heap, Pilha *pilha) {
  if (heap->quantidade >= 20) {
    printf("Fila prioritária está cheia (máximo 20 pacientes).\n");
    return;
  }
  
  char documento[10];
  printf("Digite o RG do paciente: ");
  scanf("%s", documento);
  printf("\n");
  
  Registro *pacienteEncontrado = buscarPaciente(lista, documento);
  if (pacienteEncontrado == NULL) {
    return;
  }
  
  // Verificar se paciente já está na fila prioritária
  for (int i = 0; i < heap->quantidade; i++) {
    if (heap->dados[i] == pacienteEncontrado) {
      printf("Paciente já está na fila prioritária.\n");
      return;
    }
  }
  
  // Adicionar ao heap
  heap->dados[heap->quantidade] = pacienteEncontrado;
  subirNoHeap(heap, heap->quantidade);
  heap->quantidade++;
  
  printf("Paciente %s adicionado à fila prioritária!\n", pacienteEncontrado->nomePaciente);
  printf("Prioridade baseada na idade: %d anos\n", pacienteEncontrado->idadePaciente);
  
  // Registrar operação na pilha
  empilhar(pilha, 3, pacienteEncontrado);
}

Registro *desenfileirarPrioritario(HeapPrioridade *heap, Pilha *pilha) {
  if (heap->quantidade == 0) {
    printf("Fila prioritária vazia, nenhum paciente para atender.\n");
    return NULL;
  }
  
  Registro *pacienteAtendido = heap->dados[0];
  
  // Remover o paciente de maior prioridade
  heap->dados[0] = heap->dados[heap->quantidade - 1];
  heap->quantidade--;
  
  if (heap->quantidade > 0) {
    descerNoHeap(heap, 0);
  }
  
  printf("Paciente prioritário %s foi atendido e removido da fila.\n", pacienteAtendido->nomePaciente);
  printf("Idade: %d anos\n", pacienteAtendido->idadePaciente);
  
  // Registrar operação na pilha
  empilhar(pilha, 4, pacienteAtendido);
  
  return pacienteAtendido;
}

void exibirFilaPrioritaria(HeapPrioridade *heap) {
  if (heap->quantidade == 0) {
    printf("Fila prioritária vazia.\n");
    return;
  }
  
  printf("Fila prioritária atual (ordenada por idade):\n");
  
  // Criar cópia do heap para não alterar a estrutura original
  HeapPrioridade tempHeap = *heap;
  
  for (int i = 0; i < heap->quantidade; i++) {
    Registro *paciente = tempHeap.dados[0];
    printf("%d. %s (RG: %s, Idade: %d)\n", i+1, paciente->nomePaciente, 
           paciente->documentoRG, paciente->idadePaciente);
    
    // Remover o paciente de maior prioridade para exibir o próximo
    tempHeap.dados[0] = tempHeap.dados[tempHeap.quantidade - 1];
    tempHeap.quantidade--;
    
    if (tempHeap.quantidade > 0) {
      descerNoHeap(&tempHeap, 0);
    }
  }
  printf("\n");
}

// Salvar dados em arquivo
void salvarDados(Lista *lista, char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "wb");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo para salvar dados.\n");
    return;
  }
  
  int contador = 0;
  ELista *atual = lista->inicio;
  
  while (atual != NULL) {
    fwrite(atual->dados, sizeof(Registro), 1, arquivo);
    fwrite(atual->dados->dataRegistro, sizeof(Data), 1, arquivo);
    contador++;
    atual = atual->prox;
  }
  
  fclose(arquivo);
  printf("Dados salvos com sucesso! Total de %d registros.\n", contador);
}

// Carregar dados de arquivo
int carregarDados(Lista *lista, int contador, char *nomeArquivo, ABB *arvoreAno, 
                 ABB *arvoreMes, ABB *arvoreDia, ABB *arvoreIdade) {
  FILE *arquivo = fopen(nomeArquivo, "rb");
  if (arquivo == NULL) {
    printf("Arquivo de dados não encontrado.\n");
    return contador;
  }
  
  Registro paciente;
  Data data;
  int registrosCarregados = 0;
  
  while (fread(&paciente, sizeof(Registro), 1, arquivo) == 1) {
    if (fread(&data, sizeof(Data), 1, arquivo) != 1) {
      break;
    }
    
    // Verificar se RG já existe
    int documentoExistente = 0;
    ELista *verificacao = lista->inicio;
    
    while (verificacao != NULL) {
      if (strcmp(verificacao->dados->documentoRG, paciente.documentoRG) == 0) {
        documentoExistente = 1;
        break;
      }
      verificacao = verificacao->prox;
    }
    
    if (!documentoExistente) {
      // Criar cópias dos dados lidos
      Data *novaDdata = criarDataRegistro(data.diaMes, data.mesAno, data.anoData);
      Registro *novoPaciente = criarFichaPaciente(paciente.nomePaciente, 
                                                paciente.idadePaciente, 
                                                paciente.documentoRG, 
                                                novaDdata);
      
      // Adicionar à lista
      ELista *novo = criarNodoLista(novoPaciente);
      novo->prox = lista->inicio;
      lista->inicio = novo;
      lista->tamanho++;
      
      // Adicionar às árvores
      inserirPorAno(arvoreAno, novoPaciente);
      inserirPorMes(arvoreMes, novoPaciente);
      inserirPorDia(arvoreDia, novoPaciente);
      inserirPorIdade(arvoreIdade, novoPaciente);
      
      registrosCarregados++;
      contador++;
    }
  }
  
  fclose(arquivo);
  printf("Dados carregados com sucesso! %d novos registros adicionados.\n", registrosCarregados);
  return contador;
}

// Exibir informações do sistema
void exibirInformacoesSistema() {
  printf("Sistema de Gerenciamento de Clínica\n");
  printf("Versão 1.0\n\n");
  printf("Este sistema permite:\n");
  printf("- Cadastro de pacientes\n");
  printf("- Gerenciamento de fila de atendimento\n");
  printf("- Pesquisa de pacientes por diferentes critérios\n");
  printf("- Atendimento prioritário baseado em idade\n");
  printf("- Histórico de operações com possibilidade de desfazer\n");
  printf("- Persistência de dados em arquivo\n\n");
  printf("Desenvolvido como projeto educacional para demonstrar\n");
  printf("o uso de diferentes estruturas de dados em C.\n\n");
}

void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}
