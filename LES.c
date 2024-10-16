// #include <stdio.h>
// #include <stdlib.h>

// #define TAM 10


// typedef struct {
//   int valores[TAM];
//   int qtde;
  
// } LES;

// void inserir(LES *les, int valor){
//   if(les->qtde == 0){
//     les->valores[0] = valor;
//     les->qtde++;
//   } else if(les->qtde < TAM){
//     for(int i = les->qtde; i > 0; i--){
//       les->valores[i] = les->valores[i-1];
//     }
//     les->valores[0] = valor;
//     les->qtde++;
//   }
// }

// void mostrar(LES *les){
//   for(int i =0; i < les->qtde; i++){
//     printf("%d ", les->valores[i]);
//   }
//   printf("\n");
// }


// int main(void) {
//   LES *les = malloc(sizeof(LES));
//   les->qtde = 0;
//   inserir(les, 6);
//   inserir(les, 3);
//   inserir(les, 5);
//   inserir(les, 8);
//   mostrar(les);
//   return 0;
// }

#include <stdio.h>

#define TAMANHO 10

typedef struct {
    int valores[TAMANHO];
    int n;
} Lista;

/**
 * @brief Verifica se a lista está cheia.
 * 
 * @param lista Ponteiro para a lista.
 * @return int Retorna 1 se a lista estiver cheia, caso contrário, retorna 0.
 */
int esta_cheia(Lista *lista) {
    if(lista->n >= TAMANHO) {
        return 1;
    }else{
      return 0;
    }
}

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param lista Ponteiro para a lista.
 * @return int Retorna 1 se a lista estiver vazia, caso contrário, retorna 0.
 */
int esta_vazia(Lista *lista) {
    return lista->n == 0;
}

/**
 * @brief Encontra a posição onde um valor deve ser inserido na lista ordenada.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser inserido.
 * @return int Retorna o índice onde o valor deve ser inserido.
 */
int encontrar_posicao(Lista *lista, int valor) {
    for(int i = 0; i < lista->n; i++){
      if(lista->valores[i] == valor){
        return i;
      }
    }
  return -1;
}

/**
 * @brief Move os elementos da lista para a direita a partir de um índice, criando espaço para um novo valor.
 * 
 * @param lista Ponteiro para a lista.
 * @param indice O índice a partir do qual os elementos serão movidos.
 */
void deslocar_direita(Lista *lista, int indice) {
    for(int i = lista->n; i > indice; i--){
      if(i >= indice){
        lista->valores[i] = lista->valores[i-1];
      }
    }
}

/**
 * @brief Move os elementos da lista para a esquerda a partir de um índice, removendo um valor.
 * 
 * @param lista Ponteiro para a lista.
 * @param indice O índice a partir do qual os elementos serão movidos.
 */
void deslocar_esquerda(Lista *lista, int indice) {
    for(int i = indice; i < lista->n - 1; i++){
      lista->valores[i] = lista->valores[i+1];
    }
}

/**
 * @brief Insere um valor na lista em sua posição ordenada.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser inserido.
 * @return int Retorna 1 se a inserção for bem-sucedida, ou 0 se a lista estiver cheia.
 */
int inserir(Lista *lista, int valor) {
  if(esta_cheia(lista)){
    return 0;
  }else{
    // int posicao = encontrar_posicao(lista, valor);
    // deslocar_direita(lista, posicao);
    // lista->valores[posicao] = valor;
    // return 1;

    for(int i = 0; i < lista->n; i++){
      if(lista->valores[i] > valor){
        deslocar_direita(lista, i);
        lista->valores[i] = valor;
        lista->n++;
        return 1;
      }
    }
    lista->valores[lista->n] = valor;
    lista->n++;
    return 1;
  }
  return 0;
}

/**
 * @brief Remove um valor da lista.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser removido.
 * @return int Retorna o valor removido se a remoção for bem-sucedida, ou -1 se a lista estiver vazia.
 */
int remover(Lista *lista, int valor) {
    if(!esta_vazia(lista)){
      int i = encontrar_posicao(lista, valor);
      deslocar_esquerda(lista, i);
      lista->n--;
      return 1;
    }
  return 0;
}

/**
 * @brief Exibe todos os valores da lista.
 * 
 * @param lista Ponteiro para a lista.
 */
void exibir_lista(const Lista *lista) {
    for(int i = 0; i < lista->n; i++){
      printf("%d ", lista->valores[i]);
    }
  printf("\n");
}

int main(void) {
    Lista lista = { .n = 0 };
    Lista *pl = &lista;
    int valores[] = {21, 14, 13, 10, 87, 35, 27, 56, 85, 29};

    for (int i = 0; i < TAMANHO; i++) {
        inserir(pl, valores[i]);
        exibir_lista(pl);
    }

    for (int i = 0; i < TAMANHO; i++) {
        printf("O valor %d está na posição %d\n", valores[i], encontrar_posicao(pl, valores[i]));
    }

    for (int i = 0; i < TAMANHO; i++) {
        remover(pl, valores[i]);
        exibir_lista(pl);
    }

    return 0;
}
