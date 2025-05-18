#include "2_estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Menu Principal
int menuPrincipal() {
  int escolha;
  printf("1.Cadastrar Pacientes\n"
         "2.Atendimento\n"
         "0.Sair\n");
  printf("Selecione uma opção (0-2): ");
  scanf("%d", &escolha);
  printf("\n");
  return escolha;
}

// Menu de Cadastro
void menuCadastro(Lista *lista) {
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
      adicionarPaciente(lista);
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
      excluirPaciente(lista);
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
}

// Menu de Atendimento
void menuAtendimento(Lista *lista, Fila *fila, Registro *paciente) {
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
      adicionarNaFila(lista, fila, paciente);
      break;
    case 2:
      // Atender próximo paciente
      removerDaFila(lista, fila, paciente);
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

// Criar data de registro
Data *criarDataRegistro(int dia, int mes, int ano) {
  Data *data = malloc(sizeof(Data));
  data->diaMes = dia;
  data->mesAno = mes;
  data->anoData = ano;
  return data;
}

// Adicionar paciente
void adicionarPaciente(Lista *lista) {
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
void excluirPaciente(Lista *lista) {
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
void adicionarNaFila(Lista *lista, Fila *fila, Registro *paciente) {
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
}

// Atender próximo paciente
Registro *removerDaFila(Lista *lista, Fila *fila, Registro *paciente) {
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

void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}
