#include <stdio.h>

// CASOS DE INSERCAO

// while(atual != NULL && novo -> valor >= atual -> valor){
//   anterior = atual;
//   atual = atual -> proximo;
//}

// lista vazia
/// lista -> primeiro == NULL
//// lista -> primeiro = novo

// inicio
/// anterior == NULL
//// lista -> primeiro = novo
//// novo -> proximo = atual
//// atual -> anterior = novo

// final
/// atual == NULL
//// anterior -> proximo = novo
//// novo -> anterior = anterior

// meio
/// atual != NULL
/// anterior != NULL
//// anterior -> proximo = novo
//// novo -> anterior = anterior
//// novo -> proximo = atual
//// atual -> anterior = novo

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// typedef struct Celula{
//   struct Celula *anterior;
//   int valor;
//   struct Celula *proximo;
// } Celula;

// typedef struct {
//   Celula *primeiro;
//   int qtde;
// } Lista;

// Celula *criar_celula(int valor){
//   Celula *celula = malloc(sizeof(Celula));
//   celula -> anterior = NULL;
//   celula -> valor = valor;
//   celula -> proximo = NULL;
//   return celula;
// }

// Lista *criar_lista(){
//   Lista *lista = malloc(sizeof(Lista));
//   lista -> primeiro = NULL;
//   lista -> qtde = 0;
//   return lista;
// }

// void inserir(Lista *lista, int valor){
//   Celula *novo = criar_celula(valor);
//   if(lista -> primeiro == NULL){ // lista vazia
//     lista -> primeiro = novo;
//   }else{
//     Celula *atual = lista -> primeiro;
//     Celula *anterior = NULL;
//     while(atual != NULL && atual -> valor <= novo ->valor){
//       anterior = atual;
//       atual = atual -> proximo;
//     }
//     if(anterior == NULL){ // inicio da lista
//       lista -> primeiro = novo;
//       novo -> proximo = atual;
//       atual -> anterior = novo;
//     } else if(atual == NULL){ // final da lista
//       anterior -> proximo = novo;
//       novo -> anterior = anterior;
//     } else{ // meio da lista
//       anterior -> proximo = novo;
//       novo -> anterior = anterior;
//       novo -> proximo = atual;
//       atual -> anterior = novo;
//     }
//   }
//   lista -> qtde++;
// }

// void mostrar(Lista *lista){
//   Celula *atual = lista -> primeiro;
//   printf("Início -> ");
//   while(atual != NULL){
//     printf("%d ", atual -> valor);
//     atual = atual -> proximo;
//   }
//   printf("<- Final");
// }

// void exibir_lista_invertida(Lista *lista){
//   Celula *atual = lista -> primeiro;
//   while(atual -> proximo != NULL){
//     atual = atual -> proximo;
//   }
//   printf("Início -> ");
//   while(atual != NULL){
//     printf("%d ", atual -> valor);
//     atual = atual -> anterior;
//   }
//   printf("<- Final");
// }

// void remover_valor(Lista *lista, int valor) {
//   Celula *atual = lista->primeiro;
//   Celula *anterior = NULL;
//     if(lista->qtde == 0) { // LISTA VAZIA
//         return;
//     }
//     while(atual != NULL && atual->valor != valor) {
//         anterior = atual;
//         atual = atual->proximo;
//     }
//     if(atual == NULL) { // NAO TEM
//         return;
//     }else{
//       if (anterior == NULL) { // INICIO
//         lista->primeiro = atual->proximo;
//         lista->primeiro->anterior = anterior;
//       } else if (atual->proximo == NULL) { // FINAL
//         anterior->proximo = NULL;
//       } else { // MEIO
//         anterior->proximo = atual->proximo;
//         atual->proximo->anterior = anterior;
//       }
//     }
//   lista->qtde--;
//   return;
// }


// int main(void) {
//   Lista *lista = criar_lista();
//   for(int n = 20; n > 0; n--){
//     inserir(lista, n);
//     mostrar(lista);
//     printf("\n");
//     exibir_lista_invertida(lista);
//     printf("\n");
//   }
//   printf("\n \n");
//   remover_valor(lista, 1);
//   remover_valor(lista, 3);
//   remover_valor(lista, 20);
//   mostrar(lista);
//   printf("\n");
//   exibir_lista_invertida(lista);
//   return 0;
// }

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó na lista duplamente encadeada
typedef struct No {
    struct No *anterior;
    int valor;
    struct No *proximo;
} No;

// Definição da estrutura da lista duplamente encadeada
typedef struct {
    No *primeiro;
    int qtde;
} ListaDuplamenteEncadeada;

/**
 * Cria uma nova lista duplamente encadeada e a inicializa.
 *
 * @return Um ponteiro para a nova lista criada.
 */
ListaDuplamenteEncadeada *criar_lista() {
    ListaDuplamenteEncadeada *lista = malloc(sizeof(ListaDuplamenteEncadeada));
    lista->primeiro = NULL;
    lista->qtde = 0;
    return lista;
}

/**
 * Cria um novo nó contendo o valor especificado.
 *
 * @param valor O valor a ser armazenado no nó.
 * @return Um ponteiro para o novo nó criado.
 */
No *criar_no(int valor) {
    No *celula = malloc(sizeof(No));
    celula->anterior = NULL;
    celula->valor = valor;
    celula->proximo = NULL;
    return celula;
}

/**
 * Insere um valor na lista de forma ordenada.
 *
 * @param lista Ponteiro para a lista onde o valor será inserido.
 * @param valor O valor a ser inserido na lista.
 */
void inserir_valor(ListaDuplamenteEncadeada *lista, int valor) {
    No *novo = criar_no(valor);
    if (lista->primeiro == NULL) { // lista vazia
        lista->primeiro = novo;
    } else {
        No *atual = lista->primeiro;
        No *anterior = NULL;
        while (atual != NULL && atual->valor <= novo->valor) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (anterior == NULL) {
            novo->proximo = lista->primeiro;
            lista->primeiro->anterior = novo;
            lista->primeiro = novo;
        }
        else if (atual == NULL) {
            anterior->proximo = novo;
            novo->anterior = anterior;
        }
        else {
            anterior->proximo = novo;
            novo->anterior = anterior;
            novo->proximo = atual;
            atual->anterior = novo;
        }
    }
    lista->qtde++;
}

/**
 * Exibe os valores da lista em ordem crescente.
 *
 * @param lista Ponteiro para a lista a ser exibida.
 */
void exibir_lista(ListaDuplamenteEncadeada *lista) {
    No *atual = lista->primeiro;
    printf("Início -> ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("<- Final\n");
}

/**
 * Exibe os valores da lista em ordem decrescente.
 *
 * @param lista Ponteiro para a lista a ser exibida.
 */
void exibir_lista_invertida(ListaDuplamenteEncadeada *lista) {
    No *atual = lista->primeiro;
    if (atual == NULL) {
        printf("Início -> <- Final\n");
        return;
    }
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    printf("Final -> ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
    printf("<- Início\n");
}

/**
 * Remove o nó que contém o valor especificado da lista.
 *
 * @param lista Ponteiro para a lista de onde o valor será removido.
 * @param valor O valor a ser removido da lista.
 */
void remover_valor(ListaDuplamenteEncadeada *lista, int valor) {
    No *atual = lista->primeiro;
    No *anterior = NULL;
    if (lista->qtde == 0) {
        return;
    }
    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        return;
    } else {
        if (anterior == NULL) { //INICIO
            lista->primeiro = atual->proximo;
            if (lista->primeiro != NULL) {
                lista->primeiro->anterior = NULL;
            }
        } else if (atual->proximo == NULL) { //FINAL
            anterior->proximo = NULL;
        } else { // MEIO
            anterior->proximo = atual->proximo;
            atual->proximo->anterior = anterior;
        }
        free(atual);
    }
    lista->qtde--;
}

int main(void) {
    ListaDuplamenteEncadeada *lista = criar_lista();

    inserir_valor(lista, 10);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 5);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 20);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 15);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 5);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 15);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 20);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 10);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    for (int i = 1; i <= 10; i++) {
        inserir_valor(lista, i);
    }
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    for (int i = 1; i <= 10; i++) {
        remover_valor(lista, i);
    }
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 100);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 10);
    inserir_valor(lista, 10);
    inserir_valor(lista, 10);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    return 0;
}

