#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Data {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct Registro {
  char nome[100];
  int idade;
  char rg[20];
  Data entrada;
} Registro;

typedef struct Elista {
  Registro dados;
  struct Elista *proximo;
} Elista;

typedef struct Lista {
  Elista *inicio;
  int quantidade;
} Lista;

typedef struct Efila {
  Registro dados;
  struct Efila *proximo;
} Efila;

typedef struct Fila {
  Efila *head;
  Efila *tail;
  int quantidade;
} Fila;

void inicializarLista(Lista *lista) {
  lista->inicio = NULL;
  lista->quantidade = 0;
}

void inicializarFila(Fila *fila) {
  fila->head = NULL;
  fila->tail = NULL;
  fila->quantidade = 0;
}

void enfileirarPaciente(Fila *fila, Registro dados) {
  Efila *novo = (Efila *)malloc(sizeof(Efila));
  if (novo == NULL) {
    printf("novo esta vazio\n");
    return;
  }
  novo->dados = dados;
  novo->proximo = NULL;

  if (fila->head == NULL) {
    fila->head = novo;
  } else {
    fila->tail->proximo = novo;
  }
  fila->tail = novo;
  fila->quantidade++;

  printf("Paciente inserido na fila de atendimento com sucesso.\n");
}

void desenfileirarPaciente(Fila *fila) {
  if (fila->head == NULL) {
    printf("Fila vazia\n");
    return;
  }

  Efila *remover = fila->head;
  fila->head = fila->head->proximo;
  if (fila->head == NULL) {
    fila->tail = NULL;
  }
  free(remover);
  fila->quantidade--;

  printf("Paciente removido da fila com sucesso\n");
}

void mostrarFila(Fila *fila) {
  if (fila->head == NULL) {
    printf("Fila vazia\n");
    return;
  }

  Efila *atual = fila->head;
  while (atual != NULL) {
    printf("\n*********************************\n");
    printf("Nome: %s\n", atual->dados.nome);
    printf("Idade: %d\n", atual->dados.idade);
    printf("RG: %s\n", atual->dados.rg);
    printf("Data de Entrada: %02d/%02d/%04d\n", atual->dados.entrada.dia,
           atual->dados.entrada.mes, atual->dados.entrada.ano);
    printf("*********************************\n");
    atual = atual->proximo;
  }
}

void menuAtendimento(Fila *fila, Lista *lista) {
  int opcao;
  do {
    printf("\n*********************************");
    printf("\nMenu de Atendimento:\n");
    printf("[1] Inserir paciente na fila\n");
    printf("[2] Remover paciente da fila\n");
    printf("[3] Mostrar fila\n");
    printf("[0] Voltar\n");
    printf("*********************************\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      char nome[100];
      printf("Digite o nome do paciente para inserir: ");
      getchar();
      fgets(nome, 100, stdin);
      nome[strcspn(nome, "\n")] = '\0';

      Elista *atual = lista->inicio;
      while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
          enfileirarPaciente(fila, atual->dados);
          break;
        }
        atual = atual->proximo;
      }
      if (atual == NULL) {
        printf("Paciente nao encontrado na lista\n");
      }
      break;
    }
    case 2:
      desenfileirarPaciente(fila);
      break;
    case 3:
      mostrarFila(fila);
      break;
    case 0:
      break;
    default:
      printf("escolha uma opcao valda!\n");
      break;
    }
  } while (opcao != 0);
}

void cadastrarNovoPaciente(Lista *lista) {
  Elista *novo = (Elista *)malloc(sizeof(Elista));
  if (novo == NULL) {
    printf("novo null\n");
    return;
  }

  printf("Digite o nome do paciente: ");
  getchar();
  fgets(novo->dados.nome, 100, stdin);
  novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

  printf("Digite a idade do paciente: ");
  scanf("%d", &novo->dados.idade);

  printf("Digite o RG do paciente: ");
  getchar();
  fgets(novo->dados.rg, 20, stdin);
  novo->dados.rg[strcspn(novo->dados.rg, "\n")] = '\0';

  printf("Digite a data de entrada (dia mes ano): ");
  scanf("%d %d %d", &novo->dados.entrada.dia, &novo->dados.entrada.mes,
        &novo->dados.entrada.ano);

  novo->proximo = lista->inicio;
  lista->inicio = novo;
  lista->quantidade++;

  printf("Paciente cadastrado com sucesso!\n");
}

void consultarPaciente(Lista *lista) {
  char nome[100];
  printf("Digite o nome do paciente para consulta: ");
  getchar();
  fgets(nome, 100, stdin);
  nome[strcspn(nome, "\n")] = '\0';

  Elista *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->dados.nome, nome) == 0) {
      printf("Paciente encontrado:\n");
      printf("Nome: %s\n", atual->dados.nome);
      printf("Idade: %d\n", atual->dados.idade);
      printf("RG: %s\n", atual->dados.rg);
      printf("Data de Entrada: %02d/%02d/%04d\n", atual->dados.entrada.dia,
             atual->dados.entrada.mes, atual->dados.entrada.ano);
      return;
    }
    atual = atual->proximo;
  }
  printf("Paciente nao encontrado.\n");
}

void atualizarDadosPaciente(Lista *lista) {
  char nome[100];
  printf("Digite o nome do paciente para atualizar: ");
  getchar();
  fgets(nome, 100, stdin);
  nome[strcspn(nome, "\n")] = '\0';

  Elista *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->dados.nome, nome) == 0) {
      printf("Paciente encontrado. Digite os novos dados:\n");
      printf("Digite a idade do paciente: ");
      scanf("%d", &atual->dados.idade);

      printf("Digite o RG do paciente: ");
      getchar();
      fgets(atual->dados.rg, 20, stdin);
      atual->dados.rg[strcspn(atual->dados.rg, "\n")] = '\0';

      printf("Digite a data de entrada (dia mes ano): ");
      scanf("%d %d %d", &atual->dados.entrada.dia, &atual->dados.entrada.mes,
            &atual->dados.entrada.ano);

      printf("Dados do paciente atualizados com sucesso!\n");
      return;
    }
    atual = atual->proximo;
  }
  printf("Paciente nao encontrado.\n");
}

void removerPaciente(Lista *lista) {
  char nome[100];
  printf("Digite o nome do paciente para remover: ");
  getchar();
  fgets(nome, 100, stdin);
  nome[strcspn(nome, "\n")] = '\0';

  Elista *atual = lista->inicio;
  Elista *anterior = NULL;

  while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
    anterior = atual;
    atual = atual->proximo;
  }

  if (atual == NULL) {
    printf("Paciente nao encontrado.\n");
    return;
  }

  if (anterior == NULL) {
    lista->inicio = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }

  free(atual);
  lista->quantidade--;
  printf("Paciente removido com sucesso!\n");
}

void exibirPacientes(Lista *lista) {
  if (lista->inicio == NULL) {
    printf("Nenhum paciente cadastrado.\n");
    return;
  }

  Elista *atual = lista->inicio;
  while (atual != NULL) {
    printf("Nome: %s\n", atual->dados.nome);
    printf("Idade: %d\n", atual->dados.idade);
    printf("RG: %s\n", atual->dados.rg);
    printf("Data de Entrada: %02d/%02d/%04d\n", atual->dados.entrada.dia,
           atual->dados.entrada.mes, atual->dados.entrada.ano);
    printf("---------------------------\n");
    atual = atual->proximo;
  }
}

void menuCadastroPacientes(Lista *lista) {
  int opcao;
  do {
    printf("\nMenu de Cadastro de Pacientes:\n");
    printf("[1] Cadastrar novo paciente\n");
    printf("[2] Consultar paciente cadastrado\n");
    printf("[3] Mostrar lista completa\n");
    printf("[4] Atualizar dados de paciente\n");
    printf("[5] Remover paciente\n");
    printf("[0] Voltar\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      cadastrarNovoPaciente(lista);
      break;
    case 2:
      consultarPaciente(lista);
      break;
    case 3:
      exibirPacientes(lista);
      break;
    case 4:
      atualizarDadosPaciente(lista);
      break;
    case 5:
      removerPaciente(lista);
      break;
    case 0:
      printf("Voltando ao menu principal...\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  } while (opcao != 0);
}

void atendimento(Fila *fila, Lista *lista) { menuAtendimento(fila, lista); }

void pesquisa() { printf("Funcao de Pesquisa chamada.\n"); }

void desfazer() { printf("Funcao de Desfazer chamada.\n"); }

void carregarSalvar() { printf("Funcao de Carregar / Salvar chamada.\n"); }

void sobre() {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("\n****************************\n");
  printf("Vinícius de Castro Duarte\n");
  printf("4º ciclo\n");
  printf("Ciências da Computação\n");
  printf("CC4652 - ESTRUTURA DE DADOS\n");
  printf("Ultima versao - 03/11/2024\n");
  printf("Gerado em %02d/%02d/%04d %02d:%02d\n", tm.tm_mday, tm.tm_mon + 1,
         tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
  printf("****************************\n");
}

int main() {
  Lista lista;
  inicializarLista(&lista);
  Fila fila;
  inicializarFila(&fila);

  int opcao;

  printf("Bem-vindo ao Palestra Medicina\n");
  do {
    printf("\n*********************************\n");
    printf("Escolha uma opcao do menu abaixo:\n");
    printf("[1] Cadastro de Pacientes\n");
    printf("[2] Atendimento\n");
    printf("[3] Pesquisa\n");
    printf("[4] Desfazer\n");
    printf("[5] Carregar / Salvar\n");
    printf("[6] Sobre\n");
    printf("[0] Sair\n");
    printf("*********************************\n");

    printf("Digite sua opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      menuCadastroPacientes(&lista);
      break;
    case 2:
      atendimento(&fila, &lista);
      break;
    case 3:
      pesquisa();
      break;
    case 4:
      desfazer();
      break;
    case 5:
      carregarSalvar();
      break;
    case 6:
      sobre();
      break;
    case 0:
      printf("Ate mais, Avanti Palestra!\n");
      break;
    default:
      printf("Por favor escolha uma opcao valida\n");
      break;
    }
  } while (opcao != 0);

  return 0;
}
