# 🏥 Gerenciador-Médico - Projeto de Estrutura de Dados

Este projeto é um sistema de gerenciamento médico implementado em C. O sistema permite o cadastro, pesquisa, atendimento e organização de pacientes, com suporte a operações como histórico de ações, prioridade de atendimento e persistência em arquivo.

## 👨‍💻 Desenvolvedores

- **Gustavo Trovó R de Souza** — RA: 22.223.018-7  
- **Giovane Contreras Oba** — RA: 22.223.012-0  

## 📚 Objetivo do Projeto

Aplicar os principais conceitos de **Estrutura de Dados** em um sistema realista, simulando a gestão de pacientes em uma clínica médica. O projeto foi desenvolvido como atividade prática da disciplina de Estrutura de Dados, com ênfase em modularização, legibilidade e eficiência.

## 🧠 Estruturas Utilizadas

- **Lista Encadeada**: Armazena todos os pacientes cadastrados.
- **Fila**: Controla a ordem de atendimento dos pacientes.
- **Pilha**: Gerencia o histórico de operações (inserção, remoção, etc).
- **Árvore Binária de Busca (ABB)**: Utilizada para pesquisas eficientes por:
  - Ano
  - Mês
  - Dia
  - Idade
- **Heap de Máximo**: Utilizado para atendimento prioritário (pacientes com idade mais avançada).

## 🔧 Funcionalidades

- **Cadastro de Pacientes**  
  - Inserção com verificação de dados
  - Atualização e exclusão
  - Registro automático de data
- **Atendimento**
  - Enfileira lista de atendimento
  - Desenfileira lista de atendimento (Atende paciente)
  - Mostra fila de atendimento
- **Atendimento Prioritário**
  - Enfileira lista de atendimento prioritário com base na idade, quanto mais velho mais prioridade
  - Desenfileira lista de atendimento prioritário (Atende paciente)
  - Mostra fila de atendimento com base na idade
- **Pesquisa**
  - Buscar por data (dia, mes e ano) ou idade via árvore binária
- **Histórico**
  - Acompanhamento e desfazer de operações com pilha (apenas para fila de atendimento)
- **Persistência em Arquivo**
  - Salvar e carregar dados em binário (`dados_pacientes`)
