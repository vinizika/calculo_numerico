// estrutura queue
// head
// tail
// qtd

// estrutura celula
// anterior
// valor
// proximo

// enqueue
// 1: fila vazia
// fila -> qtd == 0
// fila -> head = novo;
// fila -> tail = novo;
// fila -> qtd++;

// 2: fila não vazia
// fila -> qtd > 0
// fila -> tail -> proximo = novo;
// novo -> anterior = fila -> tail;
// fila -> tail = novo;
// fila -> qtd++;

// dequeue

// fila -> qtd > 0;

// 1 Fila não unitária
// fila -> qtd > 1;
// int valor = fila -> head -> valor;
// Celula temp = fila -> head;
// fila -> head = fila -> head -> proximo;
// fila -> head -> anterior = NULL;
// free(temp);
// fila -> qtd--;
// return valor;

// 2 Fila unitária
// int valor = fila -> head -> valor;
// Celula temp = fila -> head;
// fila -> head = NULL;
// fila -> tail = NULL;
// free(temp);
// fila -> qtd--;
// return valor;

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct celula{
//   int valor;
//   struct celula *anterior;
//   struct celula *proximo;
// }Celula;

// typedef struct{
//   Celula *head;
//   Celula *tail;
//   int qtd;
// }Queue;

// Celula *cria_celula(int valor){
//   Celula *celula = malloc(sizeof(Celula));
//   celula->proximo = NULL;
//   celula->anterior = NULL;
//   celula->valor = valor;

//   return celula;
// }

// Queue *cria_queue(){
//   Queue *queue = malloc(sizeof(Queue));
//   queue->head = NULL;
//   queue->tail = NULL;
//   queue->qtd = 0;

//   return queue;
// }

// void enqueue(Queue *queue, int valor){
//   Celula *novo = cria_celula(valor);
//   if(queue->qtd == 0){
//     queue->head = novo;
//     queue->tail = novo;
//     queue->qtd++;
//   } else{
//     queue->tail->proximo = novo;
//     novo->anterior = queue->tail;
//     queue->tail = novo;
//     queue->qtd++;
//   }
// }

// int dequeue(Queue *queue){
//   if(queue->qtd == 0){
//     return -1;
//   }

//   int valor = queue->head->valor;
//   Celula *temp = queue->head;
//   queue->head = queue->head->proximo;
//   if(queue->qtd == 1){
//     queue->tail = NULL;
//   }else{
//     queue->head->anterior = NULL;
//   }
//   queue->qtd--;
//   free(temp);
//   return valor;
// }

// void show(Queue *queue){
//   Celula *atual = queue->head;
//   while(atual != NULL){
//     printf("%d ", atual->valor);
//     atual = atual->proximo;
//   }
//   printf("\n");
// }

// void show_invertido(Queue *queue){
//   Celula *atual = queue->tail;
//   while(atual != NULL){
//     printf("%d ", atual->valor);
//     atual = atual->anterior;
//   }
//   printf("\n");
// }

// int main(void){
//   Queue *queue = cria_queue();
//   for(int n = 89; n > 0; n-=7){
//     enqueue(queue, n);
//     show(queue);
//     show_invertido(queue);
//   }

//   for(int i = 0; i < 15; i++){
//     printf("Removido %d\n", dequeue(queue));
//     show(queue);
//     show_invertido(queue);
//   }

  
//   return 1;
// }

#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
  int valor;
  struct Celula *proximo;
  struct Celula *anterior;
} Celula;

typedef struct {
  Celula *head;
  Celula *tail;
  int qtde;
} Queue;

Celula *cria_celula(int valor){
  Celula *celula = malloc(sizeof(Celula));
  celula->proximo = NULL;
  celula->anterior = NULL;
  celula->valor = valor;

  return celula;
}

Queue *cria_queue(){
  Queue *queue = malloc(sizeof(Queue));
  queue->head = NULL;
  queue->tail = NULL;
  queue->qtde = 0;

  return queue;
}

void enqueue(Queue *queue, int valor){
  Celula *novo = cria_celula(valor);
    if(queue->qtde == 0){
      queue->head = novo;
      queue->tail = novo;
      queue->qtde++;
    } else{
      queue->tail->proximo = novo;
      novo->anterior = queue->tail;
      queue->tail = novo;
      queue->qtde++;
    }
  }

int dequeue(Queue *queue){
  if(queue->qtde == 0){
      return -1;
    }

    int valor = queue->head->valor;
    Celula *temp = queue->head;
    queue->head = queue->head->proximo;
    if(queue->qtde == 1){
      queue->tail = NULL;
    }else{
      queue->head->anterior = NULL;
    }
    queue->qtde--;
    free(temp);
    return valor;
}

void show(Queue *queue){
  Celula *atual = queue->head;
    while(atual != NULL){
      printf("%d", atual->valor);
      atual = atual->proximo;
    }
    printf("\n");
}

void show_invertido(Queue *queue){
   Celula *atual = queue->tail;
    while(atual != NULL){
      printf("%d", atual->valor);
      atual = atual->anterior;
    }
    printf("\n");
}

int main(void) {
  Queue *qnum1 = cria_queue();
  Queue *qnum2 = cria_queue();
  Queue *res = cria_queue();

  char num1[100];
  char num2[100];
  fgets(num1, sizeof(num1), stdin);
  fgets(num2, sizeof(num2), stdin);

  int i = 0;
  while(num1[i] != '\n'){		
    enqueue(qnum1, (int)(num1[i]) - 48);
    enqueue(qnum2, (int)(num2[i]) - 48);
    i++;
  }

  Celula *n1 = qnum1->tail;
  Celula *n2 = qnum2->tail;

  int c = 0;
  
  while(n1 != NULL && n2 != NULL){

    
    
    int temp1 = n1->valor;
    int temp2 = n2->valor;
    int soma = temp1 + temp2 + c;
    n1 = n1->anterior;
    n2 = n2->anterior;
    if(soma >= 10){
      enqueue(res, soma - 10);
      c = 1;
    }else{
      enqueue(res, soma);
      c = 0;
    }
  }
  if(c>0){
    enqueue(res, c);
  }

  show_invertido(res);
  return 1;
}
