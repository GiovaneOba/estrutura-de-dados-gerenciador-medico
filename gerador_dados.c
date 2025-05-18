#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estruturas idênticas às do sistema principal
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct {
  char nome[50];
  int idade;
  char rg[10];
  Data *entrada;
} Registro;

int main() {
    FILE *arquivo = fopen("dados_pacientes", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de dados.\n");
        return 1;
    }
    
    // Nomes fictícios para os registros
    char nomes[15][50] = {
        "Ana Silva", "Carlos Oliveira", "Maria Santos", "João Pereira", "Lucia Ferreira",
        "Roberto Almeida", "Patricia Costa", "Fernando Souza", "Juliana Lima", "Ricardo Gomes",
        "Camila Rodrigues", "Bruno Martins", "Fernanda Carvalho", "Marcelo Ribeiro", "Daniela Alves"
    };
    
    // RGs fictícios (garantindo que sejam únicos)
    char rgs[15][10] = {
        "1234567", "2345678", "3456789", "4567890", "5678901",
        "6789012", "7890123", "8901234", "9012345", "0123456",
        "1122334", "2233445", "3344556", "4455667", "5566778"
    };
    
    // Gerar dados aleatórios para cada registro
    srand(time(NULL));
    
    for (int i = 0; i < 15; i++) {
        Registro paciente;
        Data data;
        
        // Preencher dados do paciente
        strcpy(paciente.nome, nomes[i]);
        paciente.idade = 20 + (rand() % 60); // Idades entre 20 e 79
        strcpy(paciente.rg, rgs[i]);
        
        // Gerar data de registro aleatória nos últimos 2 anos
        data.dia = 1 + (rand() % 28);
        data.mes = 1 + (rand() % 12);
        data.ano = 2023 + (rand() % 3); // Entre 2023 e 2025
        
        // Escrever no arquivo
        fwrite(&paciente, sizeof(Registro), 1, arquivo);
        fwrite(&data, sizeof(Data), 1, arquivo);
        
        printf("Registro %d: %s, %d anos, RG: %s, Data: %d/%d/%d\n", 
               i+1, paciente.nome, paciente.idade, paciente.rg, 
               data.dia, data.mes, data.ano);
    }
    
    fclose(arquivo);
    printf("\nArquivo de dados criado com sucesso: dados_pacientes\n");
    printf("Contém 15 registros prontos para serem carregados no sistema.\n");
    
    return 0;
}
