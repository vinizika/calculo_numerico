#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
  int valor;
  struct Celula *proximo;
} Celula;

typedef struct {
  Celula *primeiro;
  int qtde;
} Lista;

Lista *inicializa_lista() {
  Lista *lista = malloc(sizeof(Lista));
  lista->primeiro = NULL;
  lista->qtde = 0;
  return lista;
}

Celula *inicializa_celula(int valor) {
  Celula *celula = malloc(sizeof(Celula));
  celula->valor = valor;
  celula->proximo = NULL;
  return celula;
}

void inserir(Lista *lista, int valor) {
  Celula *nova = inicializa_celula(valor);
  Celula *atual = lista->primeiro;
  Celula *anterior = NULL;
  if (lista->qtde == 0) {
    lista->primeiro = nova;
    lista->qtde++;
  } else {
      while (atual != NULL && atual->valor < valor) {
        anterior = atual;
        atual = atual->proximo;
      }
      if (anterior == NULL) {
        nova->proximo = atual;
        lista->primeiro = nova;
        lista->qtde++;
      } else if (atual == NULL) {
        anterior->proximo = nova;
        lista->qtde++;
      } else {
        anterior->proximo = nova;
        nova->proximo = atual;
        lista->qtde++;
      }
  }
}

// void inserir(Lista *lista, int valor) {
//   Celula *nova = inicializa_celula(valor);
//   Celula *atual = lista->primeiro;
//   Celula *anterior = NULL;
//   if (lista->qtde = 0) {
//     lista->primeiro = nova;
//     lista->qtde++;
//   } else {
//     if (valor % 2 == 1) {
//       while (atual != NULL && atual->valor < valor && atual->valor % 2 == 1) {
//         anterior = atual;
//         atual = atual->proximo;
//       }
//       if (anterior == NULL) {
//         nova->proximo = atual;
//         lista->primeiro = nova;
//         lista->qtde++;
//       } else if (atual == NULL) {
//         anterior->proximo = nova;
//         lista->qtde++;
//       } else {
//         anterior->proximo = nova;
//         nova->proximo = atual;
//         lista->qtde++;
//       }
//     } else {
//       while (atual != NULL && atual->valor > valor || atual->valor % 2 == 1) {
//         anterior = atual;
//         atual = atual->proximo;
//       }

//       if (anterior == NULL) {
//         nova->proximo = atual;
//         lista->primeiro = nova;
//         lista->qtde++;
//       } else if (atual == NULL) {
//         anterior->proximo = nova;
//         lista->qtde++;
//       } else {
//         anterior->proximo = nova;
//         nova->proximo = atual;
//         lista->qtde++;
//       }
//     }
//   }
// }

void remover(Lista *lista, int valor) {
  Celula *atual = lista->primeiro;
  Celula *anterior = NULL;

  while(atual != NULL && atual->valor != valor){
    anterior = atual;
    atual = atual->proximo;
  }

  if(atual == NULL){
    printf("Valor %d não encontrado na lista\n", valor);
    return;
  }

  if(anterior == NULL){
    lista->primeiro = atual->proximo;
  } else if(atual->proximo == NULL){
    anterior->proximo = NULL;
  } else{
    anterior->proximo = atual->proximo;
  }

  lista->qtde--;
  
}


void mostrar(Lista *lista) {
  Celula *atual = lista->primeiro;
  while (atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }
  printf("\n");
}



int main(void) {
  Lista *lista = inicializa_lista();
  inserir(lista, 8);
  inserir(lista, 5);
  inserir(lista, 12);
  inserir(lista, 1);
  inserir(lista, 7);
  inserir(lista, 2);
  inserir(lista, 45);
  inserir(lista, 99);
  inserir(lista, 0);
  inserir(lista, 11);
  inserir(lista, 4);
  remover(lista, 99);
  mostrar(lista);
  return 0;
}
