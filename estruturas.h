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

// Funções de menu
int menuPrincipal();
void menuCadastro(Lista *lista);
void menuAtendimento(Lista *lista, Fila *fila, Registro *paciente);

// Funções básicas para estruturas
Registro *criarFichaPaciente(char *nome, int idade, char *documento, Data *data);
ELista *criarNodoLista(Registro *paciente);
Lista *inicializarLista();
EFila *criarNodoFila(Registro *paciente);
Fila *inicializarFila();

Registro *buscarPaciente(Lista *lista, char *documento);

// Funções de cadastro
Data *criarDataRegistro(int dia, int mes, int ano);
void adicionarPaciente(Lista *lista);
void consultarPaciente(Lista *lista);
void listarPacientes(Lista *lista);
void atualizarPaciente(Lista *lista);
void excluirPaciente(Lista *lista);

// Funções de atendimento
void adicionarNaFila(Lista *lista, Fila *fila, Registro *paciente);
Registro *removerDaFila(Lista *lista, Fila *fila, Registro *paciente);
void exibirFila(Fila *fila);

void limparBuffer();

#endif
