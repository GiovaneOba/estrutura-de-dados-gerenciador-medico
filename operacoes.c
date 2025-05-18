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
  printf("Paciente %s foi atendido!\n\n", pacienteAtendido->nomePaciente);
  
  // Registrar operação na pilha
  empilhar(pilha, 2, pacienteAtendido);
  
  free(removido);
  return pacienteAtendido;
}

// Exibir fila de atendimento
void exibirFila(Fila *fila) {
  if (fila->inicio == NULL) {
    printf("A fila de atendimento está vazia\n");
    printf("\n");
    return;
  }
  
  EFila *atual = fila->inicio;
  int posicao = 1;
  
  while (atual != NULL) {
    Registro p = *atual->dados;
    printf("%d-Nome: %s\n", posicao, p.nomePaciente); 
    printf("%d-RG: %s\n", posicao, p.documentoRG); 
    printf("%d-Idade: %d\n", posicao, p.idadePaciente); 
    printf("Data de registro: %d/%d/%d\n", p.dataRegistro->diaMes, p.dataRegistro->mesAno, p.dataRegistro->anoData); 
    atual = atual->prox;
    posicao++;
    printf("\n");
  }
}

// Funções para heap de atendimento prioritário
void trocarPacientes(HeapPrioridade *heap, int i, int j) {
  Registro *temp = heap->dados[i];
  heap->dados[i] = heap->dados[j];
  heap->dados[j] = temp;
}

void subirNoHeap(HeapPrioridade *heap, int indice) {
  if (indice <= 0) return;
  
  int pai = (indice - 1) / 2;
  
  // Se a idade do pai for menor que a do filho, troca (heap máximo)
  if (heap->dados[pai]->idadePaciente < heap->dados[indice]->idadePaciente) {
    trocarPacientes(heap, pai, indice);
    subirNoHeap(heap, pai); // Continua subindo recursivamente
  }
}

void descerNoHeap(HeapPrioridade *heap, int indice) {
  int maior = indice;
  int esquerda = 2 * indice + 1;
  int direita = 2 * indice + 2;
  
  // Verifica se o filho da esquerda é maior que o nó atual
  if (esquerda < heap->quantidade && 
      heap->dados[esquerda]->idadePaciente > heap->dados[maior]->idadePaciente) {
    maior = esquerda;
  }
  
  // Verifica se o filho da direita é maior que o nó atual ou o filho da esquerda
  if (direita < heap->quantidade && 
      heap->dados[direita]->idadePaciente > heap->dados[maior]->idadePaciente) {
    maior = direita;
  }
  
  // Se o maior não é o nó atual, troca e continua descendo
  if (maior != indice) {
    trocarPacientes(heap, indice, maior);
    descerNoHeap(heap, maior);
  }
}

void enfileirarPrioritario(Lista *lista, HeapPrioridade *heap, Pilha *pilha) {
  if (heap->quantidade >= 20) {
    printf("Fila prioritária atingiu o limite máximo de 20 pacientes.\n");
    return;
  }
  
  char documento[10];
  printf("Digite o RG do paciente para atendimento prioritário: ");
  scanf("%s", documento);
  printf("\n");
  
  Registro *pacienteEncontrado = buscarPaciente(lista, documento);
  if (pacienteEncontrado == NULL) {
    return;
  }
  
  // Verificar se paciente já está na fila prioritária
  for (int i = 0; i < heap->quantidade; i++) {
    if (heap->dados[i] == pacienteEncontrado) {
      printf("Paciente já está na fila prioritária\n");
      printf("\n");
      return;
    }
  }
  
  // Adicionar paciente ao heap
  heap->dados[heap->quantidade] = pacienteEncontrado;
  int indice = heap->quantidade;
  heap->quantidade++;
  
  // Ajustar o heap (subir o elemento)
  subirNoHeap(heap, indice);
  
  printf("Paciente %s (idade: %d) adicionado à fila prioritária!\n", 
         pacienteEncontrado->nomePaciente, pacienteEncontrado->idadePaciente);
  printf("\n");
  
  // Registrar operação na pilha
  empilhar(pilha, 3, pacienteEncontrado);
}

Registro *desenfileirarPrioritario(HeapPrioridade *heap, Pilha *pilha) {
  if (heap->quantidade <= 0) {
    printf("Fila prioritária vazia, nenhum paciente para atender.\n");
    return NULL;
  }
  
  // O paciente com maior prioridade está na raiz do heap (índice 0)
  Registro *pacienteAtendido = heap->dados[0];
  
  // Substitui a raiz pelo último elemento
  heap->dados[0] = heap->dados[heap->quantidade - 1];
  heap->quantidade--;
  
  // Reorganiza o heap
  if (heap->quantidade > 0) {
    descerNoHeap(heap, 0);
  }
  
  printf("Paciente prioritário %s (idade: %d) foi atendido!\n\n", 
         pacienteAtendido->nomePaciente, pacienteAtendido->idadePaciente);
  
  // Registrar operação na pilha
  empilhar(pilha, 4, pacienteAtendido);
  
  return pacienteAtendido;
}

void exibirFilaPrioritaria(HeapPrioridade *heap) {
  if (heap->quantidade <= 0) {
    printf("A fila prioritária está vazia\n");
    printf("\n");
    return;
  }
  
  printf("Fila de atendimento prioritário (ordenada por idade):\n\n");
  
  // Cria uma cópia do heap para não alterar o original
  HeapPrioridade tempHeap;
  tempHeap.quantidade = heap->quantidade;
  
  for (int i = 0; i < heap->quantidade; i++) {
    tempHeap.dados[i] = heap->dados[i];
  }
  
  // Remove os elementos um a um para mostrar em ordem de prioridade
  for (int i = 0; i < heap->quantidade; i++) {
    // O paciente com maior prioridade está na raiz
    Registro *paciente = tempHeap.dados[0];
    
    printf("Prioridade %d - Nome: %s\n", i+1, paciente->nomePaciente);
    printf("Prioridade %d - RG: %s\n", i+1, paciente->documentoRG);
    printf("Prioridade %d - Idade: %d\n", i+1, paciente->idadePaciente);
    printf("Data de registro: %d/%d/%d\n", 
           paciente->dataRegistro->diaMes, 
           paciente->dataRegistro->mesAno, 
           paciente->dataRegistro->anoData);
    printf("\n");
    
    // Substitui a raiz pelo último elemento
    tempHeap.dados[0] = tempHeap.dados[tempHeap.quantidade - 1];
    tempHeap.quantidade--;
    
    // Reorganiza o heap temporário
    if (tempHeap.quantidade > 0) {
      descerNoHeap(&tempHeap, 0);
    }
  }
}

// Funções para árvore
EABB *criarNodoArvore(Registro *paciente) {
  EABB *novo = malloc(sizeof(EABB));
  novo->esquerda = NULL;
  novo->direita = NULL;
  novo->superior = NULL;
  novo->dados = paciente;
  return novo;
}

ABB *inicializarArvore() {
  ABB *arvore = malloc(sizeof(ABB));
  arvore->raizArvore = NULL;
  arvore->tamanho = 0;
  return arvore;
}

void percorrerEmOrdem(EABB *raiz) {
  if (raiz != NULL) {
    percorrerEmOrdem(raiz->esquerda);
    printf("Nome: %s\n", raiz->dados->nomePaciente);
    printf("Idade: %d\n", raiz->dados->idadePaciente);
    printf("RG: %s\n", raiz->dados->documentoRG);
    printf("Data: %d/%d/%d\n", raiz->dados->dataRegistro->diaMes, raiz->dados->dataRegistro->mesAno, raiz->dados->dataRegistro->anoData);
    printf("\n");
    percorrerEmOrdem(raiz->direita);
  }
}

// Inserir na árvore por ano
void *inserirPorAno(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
  } else {
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
  }
  
  arvore->tamanho++;
  return novo;
}

// Inserir na árvore por mês
void *inserirPorMes(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
  } else {
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
  }
  
  arvore->tamanho++;
  return novo;
}

// Inserir na árvore por dia
void *inserirPorDia(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
  } else {
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
  }
  
  arvore->tamanho++;
  return novo;
}

// Inserir na árvore por idade
void *inserirPorIdade(ABB *arvore, Registro *paciente) {
  EABB *novo = criarNodoArvore(paciente);
  
  if (arvore->raizArvore == NULL) {
    arvore->raizArvore = novo;
  } else {
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
  }
  
  arvore->tamanho++;
  return novo;
}

// Remover da árvore por ano
void removerDaArvoreAno(ABB *arvore, EABB *nodo) {
    if (arvore == NULL || nodo == NULL) return;
    
    Registro *remover = nodo->dados;
    EABB *atual = arvore->raizArvore;
    EABB *pai = NULL;
    
    // Buscar o nó a ser removido
    while (atual != NULL && (strcmp(nodo->dados->documentoRG, atual->dados->documentoRG) != 0)) {
        pai = atual;
        if (nodo->dados->dataRegistro->anoData < atual->dados->dataRegistro->anoData) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }
    
    if (atual == NULL) {
        return;
    }
    
    // Caso 1: Nó sem filhos
    if (nodo->esquerda == NULL && nodo->direita == NULL) {
        if (nodo == arvore->raizArvore) {
            arvore->raizArvore = NULL;
        } else {
            if (pai->esquerda == nodo) {
                pai->esquerda = NULL;
            } else {
                pai->direita = NULL;
            }
        }
        free(nodo);
        arvore->tamanho--;
        return;
    }
    
    // Caso 2: Nó com dois filhos
    if (nodo->esquerda != NULL && nodo->direita != NULL) {
        EABB *atual2 = nodo->esquerda;
        EABB *pai2 = nodo;
        
        while (atual2->direita != NULL) {
            pai2 = atual2;
            atual2 = atual2->direita;
        }
        
        nodo->dados = atual2->dados;
        
        if (pai2->direita == atual2) {
            pai2->direita = atual2->esquerda;
        } else {
            pai2->esquerda = atual2->esquerda;
        }
        
        if (atual2->esquerda != NULL) {
            atual2->esquerda->superior = pai;
        }
        
        removerDaArvoreIdade(arvore, atual2);
    }
    
    // Caso 3: Nó com um filho
    EABB *filho;
    if (nodo->esquerda != NULL) {
      filho = nodo->esquerda;
    } else {
      filho = nodo->direita;
    }
    
    if (nodo == arvore->raizArvore) {
        arvore->raizArvore = filho;
    } else if (pai->esquerda == nodo) {
        pai->esquerda = filho;
    } else {
        pai->direita = filho;
    }
    
    if (filho != NULL) {
        filho->superior = pai;
    }
    
    free(nodo);
    arvore->tamanho--;
}

// Remover da árvore por mês
void removerDaArvoreMes(ABB *arvore, EABB *nodo) {
    if (arvore == NULL || nodo == NULL) return;
    
    Registro *remover = nodo->dados;
    EABB *atual = arvore->raizArvore;
    EABB *pai = NULL;
    
    // Buscar o nó a ser removido
    while (atual != NULL && (strcmp(nodo->dados->documentoRG, atual->dados->documentoRG) != 0)) {
        pai = atual;
        if (nodo->dados->dataRegistro->mesAno < atual->dados->dataRegistro->mesAno) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }
    
    if (atual == NULL) {
        return;
    }
    
    // Caso 1: Nó sem filhos
    if (nodo->esquerda == NULL && nodo->direita == NULL) {
        if (nodo == arvore->raizArvore) {
            arvore->raizArvore = NULL;
        } else {
            if (pai->esquerda == nodo) {
                pai->esquerda = NULL;
            } else {
                pai->direita = NULL;
            }
        }
        free(nodo);
        arvore->tamanho--;
        return;
    }
    
    // Caso 2: Nó com dois filhos
    if (nodo->esquerda != NULL && nodo->direita != NULL) {
        EABB *atual2 = nodo->esquerda;
        EABB *pai2 = nodo;
        
        while (atual2->direita != NULL) {
            pai2 = atual2;
            atual2 = atual2->direita;
        }
        
        nodo->dados = atual2->dados;
        
        if (pai2->direita == atual2) {
            pai2->direita = atual2->esquerda;
        } else {
            pai2->esquerda = atual2->esquerda;
        }
        
        if (atual2->esquerda != NULL) {
            atual2->esquerda->superior = pai;
        }
        
        removerDaArvoreIdade(arvore, atual2);
    }
    
    // Caso 3: Nó com um filho
    EABB *filho;
    if (nodo->esquerda != NULL) {
      filho = nodo->esquerda;
    } else {
      filho = nodo->direita;
    }
    
    if (nodo == arvore->raizArvore) {
        arvore->raizArvore = filho;
    } else if (pai->esquerda == nodo) {
        pai->esquerda = filho;
    } else {
        pai->direita = filho;
    }
    
    if (filho != NULL) {
        filho->superior = pai;
    }
    
    free(nodo);
    arvore->tamanho--;
}

// Remover da árvore por dia
void removerDaArvoreDia(ABB *arvore, EABB *nodo) {
    if (arvore == NULL || nodo == NULL) return;
    
    Registro *remover = nodo->dados;
    EABB *atual = arvore->raizArvore;
    EABB *pai = NULL;
    
    // Buscar o nó a ser removido
    while (atual != NULL && (strcmp(nodo->dados->documentoRG, atual->dados->documentoRG) != 0)) {
        pai = atual;
        if (nodo->dados->dataRegistro->diaMes < atual->dados->dataRegistro->diaMes) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }
    
    if (atual == NULL) {
        return;
    }
    
    // Caso 1: Nó sem filhos
    if (nodo->esquerda == NULL && nodo->direita == NULL) {
        if (nodo == arvore->raizArvore) {
            arvore->raizArvore = NULL;
        } else {
            if (pai->esquerda == nodo) {
                pai->esquerda = NULL;
            } else {
                pai->direita = NULL;
            }
        }
        free(nodo);
        arvore->tamanho--;
        return;
    }
    
    // Caso 2: Nó com dois filhos
    if (nodo->esquerda != NULL && nodo->direita != NULL) {
        EABB *atual2 = nodo->esquerda;
        EABB *pai2 = nodo;
        
        while (atual2->direita != NULL) {
            pai2 = atual2;
            atual2 = atual2->direita;
        }
        
        nodo->dados = atual2->dados;
        
        if (pai2->direita == atual2) {
            pai2->direita = atual2->esquerda;
        } else {
            pai2->esquerda = atual2->esquerda;
        }
        
        if (atual2->esquerda != NULL) {
            atual2->esquerda->superior = pai;
        }
        
        removerDaArvoreIdade(arvore, atual2);
    }
    
    // Caso 3: Nó com um filho
    EABB *filho;
    if (nodo->esquerda != NULL) {
      filho = nodo->esquerda;
    } else {
      filho = nodo->direita;
    }
    
    if (nodo == arvore->raizArvore) {
        arvore->raizArvore = filho;
    } else if (pai->esquerda == nodo) {
        pai->esquerda = filho;
    } else {
        pai->direita = filho;
    }
    
    if (filho != NULL) {
        filho->superior = pai;
    }
    
    free(nodo);
    arvore->tamanho--;
}

// Remover da árvore por idade
void removerDaArvoreIdade(ABB *arvore, EABB *nodo) {
    if (arvore == NULL || nodo == NULL) return;
    
    Registro *remover = nodo->dados;
    EABB *atual = arvore->raizArvore;
    EABB *pai = NULL;
    
    // Buscar o nó a ser removido
    while (atual != NULL && (strcmp(nodo->dados->documentoRG, atual->dados->documentoRG) != 0)) {
        pai = atual;
        if (nodo->dados->idadePaciente < atual->dados->idadePaciente) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }
    
    if (atual == NULL) {
        return;
    }
    
    // Caso 1: Nó sem filhos
    if (nodo->esquerda == NULL && nodo->direita == NULL) {
        if (nodo == arvore->raizArvore) {
            arvore->raizArvore = NULL;
        } else {
            if (pai->esquerda == nodo) {
                pai->esquerda = NULL;
            } else {
                pai->direita = NULL;
            }
        }
        free(nodo);
        arvore->tamanho--;
        return;
    }
    
    // Caso 2: Nó com dois filhos
    if (nodo->esquerda != NULL && nodo->direita != NULL) {
        EABB *atual2 = nodo->esquerda;
        EABB *pai2 = nodo;
        
        while (atual2->direita != NULL) {
            pai2 = atual2;
            atual2 = atual2->direita;
        }
        
        nodo->dados = atual2->dados;
        
        if (pai2->direita == atual2) {
            pai2->direita = atual2->esquerda;
        } else {
            pai2->esquerda = atual2->esquerda;
        }
        
        if (atual2->esquerda != NULL) {
            atual2->esquerda->superior = pai;
        }
        
        removerDaArvoreIdade(arvore, atual2);
    }
    
    // Caso 3: Nó com um filho
    EABB *filho;
    if (nodo->esquerda != NULL) {
      filho = nodo->esquerda;
    } else {
      filho = nodo->direita;
    }
    
    if (nodo == arvore->raizArvore) {
        arvore->raizArvore = filho;
    } else if (pai->esquerda == nodo) {
        pai->esquerda = filho;
    } else {
        pai->direita = filho;
    }
    
    if (filho != NULL) {
        filho->superior = pai;
    }
    
    free(nodo);
    arvore->tamanho--;
}

// Buscar na árvore por ano
EABB* buscarNaArvoreAno(ABB *arvore, Registro *paciente) {
  EABB* atual = arvore->raizArvore;
  EABB* anterior = NULL;
  
  while (atual != NULL && strcmp(paciente->documentoRG, atual->dados->documentoRG) != 0) {
    anterior = atual;
    if (paciente->dataRegistro->anoData < atual->dados->dataRegistro->anoData) {
        atual = atual->esquerda;
    } else {
        atual = atual->direita;
    }
  }
  
  if (atual != NULL) {
    return atual;
  } else {
    return NULL;
  }
}

// Buscar na árvore por mês
EABB* buscarNaArvoreMes(ABB *arvore, Registro *paciente) {
  EABB* atual = arvore->raizArvore;
  EABB* anterior = NULL;
  
  while (atual != NULL && strcmp(paciente->documentoRG, atual->dados->documentoRG) != 0) {
    anterior = atual;
    if (paciente->dataRegistro->mesAno < atual->dados->dataRegistro->mesAno) {
        atual = atual->esquerda;
    } else {
        atual = atual->direita;
    }
  }
  
  if (atual != NULL) {
    return atual;
  } else {
    return NULL;
  }
}

// Buscar na árvore por dia
EABB* buscarNaArvoreDia(ABB *arvore, Registro *paciente) {
  EABB* atual = arvore->raizArvore;
  EABB* anterior = NULL;
  
  while (atual != NULL && strcmp(paciente->documentoRG, atual->dados->documentoRG) != 0) {
    anterior = atual;
    if (paciente->dataRegistro->diaMes < atual->dados->dataRegistro->diaMes) {
        atual = atual->esquerda;
    } else {
        atual = atual->direita;
    }
  }
  
  if (atual != NULL) {
    return atual;
  } else {
    return NULL;
  }
}

// Buscar na árvore por idade
EABB* buscarNaArvoreIdade(ABB *arvore, Registro *paciente) {
  EABB* atual = arvore->raizArvore;
  EABB* anterior = NULL;
  
  while (atual != NULL && strcmp(paciente->documentoRG, atual->dados->documentoRG) != 0) {
    anterior = atual;
    if (paciente->idadePaciente < atual->dados->idadePaciente) {
        atual = atual->esquerda;
    } else {
        atual = atual->direita;
    }
  }
  
  if (atual != NULL) {
    return atual;
  } else {
    return NULL;
  }
}

// Funções para pilha
EPilha *criarNodoPilha(int operacao, Registro *paciente) {
  EPilha *nodo = malloc(sizeof(EPilha));
  if (nodo == NULL) {
    printf("Erro ao alocar memória\n");
    return NULL;
  }
  
  nodo->ant = NULL;
  nodo->prox = NULL;
  nodo->tipoOperacao = operacao;
  nodo->dados = paciente;
  return nodo;
}

Pilha *inicializarPilha() {
  Pilha *pilha = malloc(sizeof(Pilha));
  pilha->tamanho = 0;
  pilha->topo = NULL;
  return pilha;
}

// Empilhar operação
void empilhar(Pilha *pilha, int operacao, Registro *paciente) {
  EPilha *novo = criarNodoPilha(operacao, paciente);
  
  if (pilha->tamanho > 0) {
    novo->ant = pilha->topo;
    pilha->topo->prox = novo;
  }
  
  pilha->topo = novo;
  pilha->tamanho++;
}

// Adicionar paciente à fila automaticamente (para desfazer operação)
void adicionarNaFilaAutomatico(Lista *lista, Fila *fila, Registro *pacienteRemovido, Pilha *pilha) {
  char *documento = pacienteRemovido->documentoRG;
  Registro *paciente = buscarPaciente(lista, documento);
  
  if (paciente == NULL) {
    return;
  } else {
    // Verificar se paciente já está na fila
    EFila *atual = fila->inicio;
    while (atual != NULL && atual->dados != paciente) {
      atual = atual->prox;
    }
    
    if (atual != NULL) {
      printf("Paciente já está na fila de atendimento\n");
      printf("\n");
      return;
    }
  }
  
  EFila *novo = criarNodoFila(paciente);
  if (fila->tamanho == 0) {
    fila->inicio = novo;
    fila->fim = novo;
  } else {
    novo->prox = fila->inicio;
    fila->inicio = novo;
  }
  
  fila->fim = novo;
  fila->tamanho++;
}

// Desfazer última operação
void desfazerUltimaOperacao(Lista *lista, Fila *fila, Pilha *pilha) {
  if (pilha->tamanho == 0) {
    printf("Não há operações para desfazer\n");
    return;
  }
  
  int operacao = pilha->topo->tipoOperacao;
  char resposta[10];

  // Desfazer "adicionar à fila"
  if (operacao == 1) {
    Registro *paciente = pilha->topo->dados;
    printf("Deseja desfazer a operação de adicionar o paciente %s à fila de atendimento? (S/N): ", paciente->nomePaciente);
    scanf("%s", resposta);
    
    if (strcmp(resposta, "S") == 0 || strcmp(resposta, "s") == 0) { 
      // Remover paciente da fila
      if (fila->inicio == NULL) {
          printf("A fila já está vazia, não há operações para desfazer.\n");
          return;
      }
      
      // Remove o último elemento da fila (fim)
      EFila *atual = fila->inicio;
      if (atual == fila->fim) { // apenas um elemento na fila
        free(fila->fim);
        fila->inicio = fila->fim = NULL;
      } else {
        // Percorre até o penúltimo elemento
        while (atual->prox != fila->fim) {
          atual = atual->prox;
        }
        free(fila->fim);
        fila->fim = atual;
        fila->fim->prox = NULL;
      }
      
      fila->tamanho--;
      printf("O paciente %s foi removido da fila de atendimento.\n", paciente->nomePaciente);

      // Remove o topo da pilha
      EPilha *temp = pilha->topo;
      pilha->topo = pilha->topo->ant;
      
      if (pilha->tamanho > 1) {
        pilha->topo->prox = NULL;
      }
      
      free(temp);
      pilha->tamanho--;
    } else {
      printf("Operação de desfazer cancelada\n");
    }
  }
  
  // Desfazer "remover da fila"
  if (operacao == 2) {
    Registro *pacienteRemovido = pilha->topo->dados;
    printf("Deseja desfazer a operação de atender o paciente %s? (S/N): ", pacienteRemovido->nomePaciente);
    scanf("%s", resposta);
    
    if (strcmp(resposta, "S") == 0 || strcmp(resposta, "s") == 0) {
      adicionarNaFilaAutomatico(lista, fila, pacienteRemovido, pilha);
      
      // Remove o topo da pilha
      EPilha *temp = pilha->topo;
      pilha->topo = pilha->topo->ant;
      
      if (pilha->tamanho > 1) {
        pilha->topo->prox = NULL;
      }
      
      free(temp);
      pilha->tamanho--;
    }
  }
  
  // Desfazer "adicionar à fila prioritária"
  if (operacao == 3) {
    Registro *paciente = pilha->topo->dados;
    printf("Deseja desfazer a operação de adicionar o paciente %s à fila prioritária? (S/N): ", paciente->nomePaciente);
    scanf("%s", resposta);
    
    if (strcmp(resposta, "S") == 0 || strcmp(resposta, "s") == 0) { 
      printf("Operação de desfazer adição à fila prioritária não implementada.\n");
      
      // Remove o topo da pilha
      EPilha *temp = pilha->topo;
      pilha->topo = pilha->topo->ant;
      
      if (pilha->tamanho > 1) {
        pilha->topo->prox = NULL;
      }
      
      free(temp);
      pilha->tamanho--;
    } else {
      printf("Operação de desfazer cancelada\n");
    }
  }
  
  // Desfazer "remover da fila prioritária"
  if (operacao == 4) {
    Registro *pacienteRemovido = pilha->topo->dados;
    printf("Deseja desfazer a operação de atender o paciente prioritário %s? (S/N): ", pacienteRemovido->nomePaciente);
    scanf("%s", resposta);
    
    if (strcmp(resposta, "S") == 0 || strcmp(resposta, "s") == 0) {
      printf("Operação de desfazer remoção da fila prioritária não implementada.\n");
      
      // Remove o topo da pilha
      EPilha *temp = pilha->topo;
      pilha->topo = pilha->topo->ant;
      
      if (pilha->tamanho > 1) {
        pilha->topo->prox = NULL;
      }
      
      free(temp);
      pilha->tamanho--;
    }
  }
}

// Salvar dados em arquivo
void salvarDados(Lista *lista, char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "wb");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo");
    return;
  }
  
  ELista *atual = lista->inicio;
  while (atual != NULL) {
    fwrite(atual->dados, sizeof(Registro), 1, arquivo); 
    fwrite(atual->dados->dataRegistro, sizeof(Data), 1, arquivo); 
    atual = atual->prox;
  }
  
  fclose(arquivo);
  printf("Dados salvos com sucesso!\n");
  printf("\n");
}

// Carregar dados de arquivo
int carregarDados(Lista *lista, int contador, char *nomeArquivo, ABB *arvoreAno, 
                 ABB *arvoreMes, ABB *arvoreDia, ABB *arvoreIdade) {
  if (contador == 0) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
      printf("Falha ao abrir o arquivo");
      return -1;
    }
    
    Registro ficha;
    Data data;
    
    while (fread(&ficha, sizeof(Registro), 1, arquivo) == 1) { 
        fread(&data, sizeof(Data), 1, arquivo); 
        
        Data *novaData = criarDataRegistro(data.diaMes, data.mesAno, data.anoData);
        Registro *paciente = criarFichaPaciente(ficha.nomePaciente, ficha.idadePaciente, ficha.documentoRG, novaData);
        
        if (paciente != NULL) {
           ELista *novo = criarNodoLista(paciente);
           
           // Adicionar no final da lista
           if (lista->inicio == NULL) {
             lista->inicio = novo;
           } else {
             ELista *atual = lista->inicio;
             ELista *anterior = NULL;
             
             while (atual != NULL) {
               anterior = atual;
               atual = atual->prox;
             }
             
             anterior->prox = novo;
           }
           
          lista->tamanho++;
          
          // Adicionar nas árvores
          inserirPorAno(arvoreAno, paciente);
          inserirPorMes(arvoreMes, paciente);
          inserirPorDia(arvoreDia, paciente);
          inserirPorIdade(arvoreIdade, paciente);
        }
    }
    
    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
    printf("\n");
    contador++;
    return contador;
  } else {
    printf("Arquivo já foi carregado\n");
    printf("\n");
    return contador;
  }
}

// Exibir informações do sistema
void exibirInformacoesSistema() {
  printf(
      "Desenvolvedores: GIOVANE CONTRERAS OBA e GUSTAVO TROVO RAMOS DE SOUZA\n"
      "Ciclo: 4° período\n"
      "Curso: Ciencia da Computação\n"
      "Disciplina: Estrutura de dados\n"
      "Data de conclusão: 18/05/2025\n");
}

// Limpar buffer do teclado
void limparBuffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}
