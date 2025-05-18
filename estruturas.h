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

// Funções de menu
int menuPrincipal();
void menuCadastro(Lista *lista, ABB *arvoreAno, ABB *arvoreMes, 
                 ABB *arvoreDia, ABB *arvoreIdade);
void menuAtendimento(Lista *lista, Fila *fila, Registro *paciente);
void menuPesquisa(ABB *arvoreAno, ABB *arvoreMes, 
                 ABB *arvoreDia, ABB *arvoreIdade, Registro *paciente);

// Funções básicas para estruturas
Registro *criarFichaPaciente(char *nome, int idade, char *documento, Data *data);
ELista *criarNodoLista(Registro *paciente);
Lista *inicializarLista();
EFila *criarNodoFila(Registro *paciente);
Fila *inicializarFila();
EABB *criarNodoArvore(Registro *paciente);
ABB *inicializarArvore();

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
void adicionarNaFila(Lista *lista, Fila *fila, Registro *paciente);
Registro *removerDaFila(Lista *lista, Fila *fila, Registro *paciente);
void exibirFila(Fila *fila);

// Funções de pesquisa
void percorrerEmOrdem(EABB *raiz);
void *inserirPorAno(ABB *arvore, Registro *paciente);
void *inserirPorMes(ABB *arvore, Registro *paciente);
void *inserirPorDia(ABB *arvore, Registro *paciente);
void *inserirPorIdade(ABB *arvore, Registro *paciente);

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
