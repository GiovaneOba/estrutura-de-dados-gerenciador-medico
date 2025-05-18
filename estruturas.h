#ifndef SISTEMA_CLINICA_H
#define SISTEMA_CLINICA_H
#include <stdio.h>

// Estrutura para armazenar informações temporais
typedef struct {
  int diaMes;
  int mesAno;
  int anoData;
} Data;

// Estrutura para armazenar dados do paciente
typedef struct {
  char nomePaciente[50];
  int idadePaciente;
  char documentoRG[10];
  Data *dataRegistro;
} Registro;

// Estrutura para lista encadeada - Cadastro
typedef struct ELista {
  Registro *dados;
  struct ELista *prox;
} ELista;

// Estrutura para gerenciar a lista
typedef struct {
  ELista *inicio;
  int tamanho;
} Lista;

// Estrutura para fila de atendimento
typedef struct EFila {
  Registro *dados;
  struct EFila *prox;
} EFila;

// Estrutura para gerenciar a fila
typedef struct {
  EFila *inicio;
  EFila *fim;
  int tamanho;
} Fila;

// Estrutura para árvore binária de busca - Pesquisa
typedef struct EABB {
  Registro *dados;
  struct EABB *esquerda;
  struct EABB *direita;
  struct EABB *superior;
} EABB;

// Estrutura para gerenciar a árvore
typedef struct {
  EABB *raizArvore;
  int tamanho;
} ABB;

// Estrutura para pilha - Histórico de operações
typedef struct EPilha {
  Registro *dados;
  int tipoOperacao;
  struct EPilha *prox;
  struct EPilha *ant;
} EPilha;

// Estrutura para gerenciar a pilha
typedef struct {
  EPilha *topo;
  int tamanho;
} Pilha;

// Estrutura para heap de máximo - Atendimento prioritário
typedef struct {
  Registro *dados[20]; // Capacidade máxima de 20 pacientes
  int quantidade;
} HeapPrioridade;

// Funções de menu
int menuPrincipal();
void menuCadastro(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, 
                 ABB *arvoreDia, ABB *arvoreIdade);
void menuAtendimento(Lista *lista, Fila *fila, Pilha *pilha, Registro *paciente);
void menuPesquisa(ABB *arvoreAno, ABB *arvoreMes, 
                 ABB *arvoreDia, ABB *arvoreIdade, Registro *paciente);
void menuAtendimentoPrioritario(Lista *lista, HeapPrioridade *heap, Pilha *pilha);

// Funções básicas para estruturas
Registro *criarFichaPaciente(char *nome, int idade, char *documento, Data *data);
ELista *criarNodoLista(Registro *paciente);
Lista *inicializarLista();
EFila *criarNodoFila(Registro *paciente);
Fila *inicializarFila();
EABB *criarNodoArvore(Registro *paciente);
ABB *inicializarArvore();
EPilha *criarNodoPilha(int operacao, Registro *paciente);
Pilha *inicializarPilha();
HeapPrioridade *inicializarHeap();

Registro *buscarPaciente(Lista *lista, char *documento);

// Funções de cadastro
Data *criarDataRegistro(int dia, int mes, int ano);
void adicionarPaciente(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, 
                      ABB *arvoreDia, ABB *arvoreIdade);
void consultarPaciente(Lista *lista);
void listarPacientes(Lista *lista);
void atualizarPaciente(Lista *lista);
void excluirPaciente(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, 
                    ABB *arvoreDia, ABB *arvoreIdade);

// Funções de atendimento
void adicionarNaFila(Lista *lista, Fila *fila, Pilha *pilha, Registro *paciente);
Registro *removerDaFila(Lista *lista, Fila *fila, Pilha *pilha, Registro *paciente);
void exibirFila(Fila *fila);

// Funções de atendimento prioritário (heap)
void enfileirarPrioritario(Lista *lista, HeapPrioridade *heap, Pilha *pilha);
Registro *desenfileirarPrioritario(HeapPrioridade *heap, Pilha *pilha);
void exibirFilaPrioritaria(HeapPrioridade *heap);
void trocarPacientes(HeapPrioridade *heap, int i, int j);
void subirNoHeap(HeapPrioridade *heap, int indice);
void descerNoHeap(HeapPrioridade *heap, int indice);

// Funções de pesquisa
void percorrerEmOrdem(EABB *raiz);
void *inserirPorAno(ABB *arvore, Registro *paciente);
void *inserirPorMes(ABB *arvore, Registro *paciente);
void *inserirPorDia(ABB *arvore, Registro *paciente);
void *inserirPorIdade(ABB *arvore, Registro *paciente);

// Funções de histórico
void empilhar(Pilha *pilha, int operacao, Registro *paciente);
void adicionarNaFilaAutomatico(Lista *lista, Fila *fila, Registro *paciente, Pilha *pilha);
void desfazerUltimaOperacao(Lista *lista, Fila *fila, Pilha *pilha);

void salvarDados(Lista *lista, char *nomeArquivo);
int carregarDados(Lista *lista, int contador, char *nomeArquivo, ABB *arvoreAno, 
                 ABB *arvoreMes, ABB *arvoreDia, ABB *arvoreIdade);
void exibirInformacoesSistema();

EABB* buscarNaArvoreAno(ABB *arvore, Registro *paciente);
EABB* buscarNaArvoreMes(ABB *arvore, Registro *paciente);
EABB* buscarNaArvoreDia(ABB *arvore, Registro *paciente);
EABB* buscarNaArvoreIdade(ABB *arvore, Registro *paciente);

void removerDaArvoreAno(ABB *arvore, EABB *nodo);
void removerDaArvoreMes(ABB *arvore, EABB *nodo);
void removerDaArvoreDia(ABB *arvore, EABB *nodo);
void removerDaArvoreIdade(ABB *arvore, EABB *nodo);

void limparBuffer();

#endif
