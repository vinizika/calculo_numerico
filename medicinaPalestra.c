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

typedef struct EABB {
    Registro *dados;
    struct EABB *esquerda;
    struct EABB *direita;
} EABB;

typedef struct ABB {
    EABB *raiz;
    int quantidade; 
} ABB;

typedef struct Operacao {
    char tipo[10]; 
    Registro dados;
} Operacao;

typedef struct NodoPilha {
    Operacao operacao;
    struct NodoPilha *proximo;
} NodoPilha;

typedef struct Pilha {
    NodoPilha *topo;
} Pilha;


void inicializarLista(Lista *lista) {
  lista->inicio = NULL;
  lista->quantidade = 0;
}

void inicializarFila(Fila *fila) {
  fila->head = NULL;
  fila->tail = NULL;
  fila->quantidade = 0;
}

void inicializarArvore(ABB *arvore) {
    arvore->raiz = NULL;
    arvore->quantidade = 0;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, Operacao operacao) {
    NodoPilha *novo = (NodoPilha *)malloc(sizeof(NodoPilha));
    if (novo == NULL) {
        printf("Erro ao alocar memória para a pilha.\n");
        return;
    }
    novo->operacao = operacao;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

Operacao desempilhar(Pilha *pilha) {
    Operacao operacaoVazia = { "", { "", 0, "", { 0, 0, 0 } } };
    if (pilha->topo == NULL) {
        printf("Pilha vazia! Nenhuma operação para desfazer.\n");
        return operacaoVazia;
    }
    NodoPilha *remover = pilha->topo;
    Operacao operacao = remover->operacao;
    pilha->topo = remover->proximo;
    free(remover);
    return operacao;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

void enfileirarPaciente(Fila *fila, Registro dados, Pilha *pilha) {
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

  Operacao operacao;
  strcpy(operacao.tipo, "inserir");
  operacao.dados = dados;
  empilhar(pilha, operacao);

  printf("%s inserido na fila de atendimento com sucesso.\n", novo->dados.nome);
}

void desenfileirarPaciente(Fila *fila, Pilha *pilha) {
  if (fila->head == NULL) {
    printf("Fila vazia\n");
    return;
  }

  Efila *remover = fila->head;
  fila->head = fila->head->proximo;
  if (fila->head == NULL) {
    fila->tail = NULL;
  }
  fila->quantidade--;

  Operacao operacao;
  strcpy(operacao.tipo, "remover");
  operacao.dados = remover->dados;
  empilhar(pilha, operacao);

  printf("%s removido da fila com sucesso\n", remover->dados.nome);

  free(remover);
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

void menuAtendimento(Fila *fila, Lista *lista, Pilha *pilha) {
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
          enfileirarPaciente(fila, atual->dados, pilha);
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
      desenfileirarPaciente(fila, pilha);
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

  printf("Digite a data de entrada (dia): ");
  scanf("%d", &novo->dados.entrada.dia);

  printf("Digite a data de entrada (mes): ");
  scanf("%d", &novo->dados.entrada.mes);

  printf("Digite a data de entrada (ano): ");
  scanf("%d", &novo->dados.entrada.ano);

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

      printf("\n*********************************\n");
      printf("Paciente encontrado:\n");
      printf("Nome: %s\n", atual->dados.nome);
      printf("Idade: %d\n", atual->dados.idade);
      printf("RG: %s\n", atual->dados.rg);
      printf("Data de Entrada: %02d/%02d/%04d\n", atual->dados.entrada.dia,
             atual->dados.entrada.mes, atual->dados.entrada.ano);

      printf("*********************************\n");
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

      printf("Digite a data de entrada (dia): ");
      scanf("%d", &atual->dados.entrada.dia);

      printf("Digite a data de entrada (mes): ");
      scanf("%d", &atual->dados.entrada.mes);

      printf("Digite a data de entrada (ano): ");
      scanf("%d", &atual->dados.entrada.ano);


      printf("\n*********************************\n");
      printf("Dados do paciente atualizados com sucesso!\n");
      printf("*********************************\n");
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
      printf("MENU PRINCIPAL");
      break;
    default:
      printf("Por favor, digite uma opcao valida dentre a lista!\n");
      break;
    }
  } while (opcao != 0);
}

void inserirNaArvore(EABB **noAtual, Registro *dados, int (*criterio)(Registro*, Registro*), ABB *arvore) {
    if (*noAtual == NULL) {
        *noAtual = (EABB*)malloc(sizeof(EABB));
        (*noAtual)->dados = dados;
        (*noAtual)->esquerda = NULL;
        (*noAtual)->direita = NULL;
        arvore->quantidade++; 
    } else {
        if (criterio(dados, (*noAtual)->dados) < 0) {
            inserirNaArvore(&((*noAtual)->esquerda), dados, criterio, arvore);
        } else {
            inserirNaArvore(&((*noAtual)->direita), dados, criterio, arvore);
        }
    }
}

void construirArvore(ABB *arvore, Lista *lista, int (*criterio)(Registro*, Registro*)) {
    inicializarArvore(arvore);
    Elista *atual = lista->inicio;

    while (atual != NULL) {
        inserirNaArvore(&(arvore->raiz), &(atual->dados), criterio, arvore);
        atual = atual->proximo;
    }
}

void percorrerEmOrdem(EABB *no) {
    if (no != NULL) {
      printf("\n*********************************\n");
        percorrerEmOrdem(no->esquerda);
        printf("Nome: %s\n", no->dados->nome);
        printf("Idade: %d\n", no->dados->idade);
        printf("RG: %s\n", no->dados->rg);
        printf("Data de Entrada: %02d/%02d/%04d\n",
               no->dados->entrada.dia,
               no->dados->entrada.mes,
               no->dados->entrada.ano);
      printf("\n*********************************\n");
        percorrerEmOrdem(no->direita);
    }
}

int OrdenarPorAno(Registro *a, Registro *b) {
    return a->entrada.ano - b->entrada.ano;
}

int OrdenarPorMes(Registro *a, Registro *b) {
    return a->entrada.mes - b->entrada.mes;
}

int OrdenarPorDia(Registro *a, Registro *b) {
    return a->entrada.dia - b->entrada.dia;
}

int OrdenarPorIdade(Registro *a, Registro *b) {
    return a->idade - b->idade;
}

void ordenarRegistros(Lista *lista) {
    ABB arvore;
    int opcao;

    printf("\n*********************************\n");
    printf("[1] Ordenar por Ano\n");
    printf("[2] Ordenar por Mês\n");
    printf("[3] Ordenar por Dia\n");
    printf("[4] Ordenar por Idade\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    int (*criterio)(Registro*, Registro*) = NULL;
    switch (opcao) {
        case 1:
            criterio = OrdenarPorAno;
            break;
        case 2:
            criterio = OrdenarPorMes;
            break;
        case 3:
            criterio = OrdenarPorDia;
            break;
        case 4:
            criterio = OrdenarPorIdade;
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    construirArvore(&arvore, lista, criterio);

    printf("\n*********************************\n");
    printf("Registros Ordenados\n");
    percorrerEmOrdem(arvore.raiz);
    printf("\nTotal de registros ordenados: %d\n", arvore.quantidade);
}

void desfazer(Fila *fila, Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Nenhuma operação para desfazer.\n");
        return;
    }

    Operacao ultimaOperacao = desempilhar(pilha);

    printf("Última operação: %s o paciente %s.\n", 
           ultimaOperacao.tipo, ultimaOperacao.dados.nome);
    printf("Deseja desfazer esta operação? (s/n): ");
    char confirmacao;
    getchar(); 
    scanf("%c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        if (strcmp(ultimaOperacao.tipo, "inserir") == 0) {
            desenfileirarPaciente(fila, pilha);
            printf("A operação de inserir foi desfeita.\n");
        } else if (strcmp(ultimaOperacao.tipo, "remover") == 0) {
            enfileirarPaciente(fila, ultimaOperacao.dados, pilha);
            printf("A operação de remover foi desfeita.\n");
        }
    } else {
        printf("Operação não desfeita.\n");
    }
}

void carregarPacientes(Lista *lista) {
    FILE *arquivo = fopen("palestra.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    while (!feof(arquivo)) {
        Elista *novo = (Elista *)malloc(sizeof(Elista));
        if (novo == NULL) {
            printf("Erro ao alocar memória para novo paciente.\n");
            fclose(arquivo);
            return;
        }

        if (fgets(novo->dados.nome, 100, arquivo) == NULL) {
            free(novo);
            break;
        }
        novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

        char idadeStr[10];
        if (fgets(idadeStr, 10, arquivo) == NULL) {
            free(novo);
            break;
        }
        novo->dados.idade = atoi(idadeStr);

        if (fgets(novo->dados.rg, 20, arquivo) == NULL) {
            free(novo);
            break;
        }
        novo->dados.rg[strcspn(novo->dados.rg, "\n")] = '\0';

        if (fscanf(arquivo, "%d %d %d\n",
                   &novo->dados.entrada.dia,
                   &novo->dados.entrada.mes,
                   &novo->dados.entrada.ano) != 3) {
            free(novo);
            break;
        }

        novo->proximo = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = novo;
        } else {
            Elista *temp = lista->inicio;
            while (temp->proximo != NULL) {
                temp = temp->proximo;
            }
            temp->proximo = novo;
        }
        lista->quantidade++;
    }

    fclose(arquivo);
    printf("Dados dos pacientes carregados com sucesso de 'palestra.txt'.\n");
}

void salvarPacientes(Lista *lista) {
    FILE *arquivo = fopen("palestra.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    Elista *atual = lista->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s\n", atual->dados.nome);
        fprintf(arquivo, "%d\n", atual->dados.idade);
        fprintf(arquivo, "%s\n", atual->dados.rg);
        fprintf(arquivo, "%d %d %d\n",
                atual->dados.entrada.dia,
                atual->dados.entrada.mes,
                atual->dados.entrada.ano);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Dados dos pacientes salvos com sucesso em 'palestra.txt'.\n");
}

void carregarSalvar(Lista *lista) {
    int opcao;
    do {
        printf("\n*********************************\n");
        printf("[1] Carregar dados dos pacientes\n");
        printf("[2] Salvar dados dos pacientes\n");
        printf("[0] Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                carregarPacientes(lista);
                break;
            case 2:
                salvarPacientes(lista);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}

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

void atendimento(Fila *fila, Lista *lista, Pilha *pilha) { menuAtendimento(fila, lista, pilha); }

int main() {
  Lista lista;
  inicializarLista(&lista);
  Fila fila;
  inicializarFila(&fila);
  Pilha pilha;
  inicializarPilha(&pilha);

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
      atendimento(&fila, &lista, &pilha);
      break;
    case 3:
      ordenarRegistros(&lista);
      break;
    case 4:
      desfazer(&fila, &pilha);
      break;
    case 5:
      carregarSalvar(&lista);
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
