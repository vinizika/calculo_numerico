// // MODELO

// // arranjo (int); <dados>
// // head (int); <posicao remocao> no inicio: 0
// // tail (int); <posicao insercao> no inicio: 0
// // qtd (int); <quantidade> no inicio: 0
// // capacidade pre-definida
// // metodo enqueue -> enfileirar
// // metodo dequeue -> desenfileirar

// // is_full
// // se tail == capacidade
// // or
// // qtd == capacidade

// // enqueue
// // Array dados = new Array();
// // dados[tail] = valor;
// // tail++
// // qtd++

// // is_empty
// // se head == tail
// // or
// // qtd == 0

// // dequeue
// // valor = dados[head];
// // head++
// // qtd--

// // podemos fazer um if no enqueue e no dequeue, verificando se tail == capacidade. se for, entao a fila esta cheia e tail = 0.

// // fila estatica circular
// // enqueue = dados[tail%capacidade] = valor;
// // dequeue = valor = dados[head%capacidade];



// #include <stdio.h>
// #define CAP 10

// typedef struct{
//   int dados[CAP];
//   int head;
//   int tail;
//   int qtd;
// } Queue;

// void inicializar(Queue *queue){
//   queue -> head = 0;
//   queue -> tail = 0;
//   queue -> qtd = 0;
// }

// int is_full(Queue *queue){
// //    return queue->qtd == CAP;
//   if(queue->qtd == CAP){
//     return 1;
//   }else{
//     return 0;
//   }
// }

// int enqueue(Queue *queue, int valor){
//   if(is_full(queue)){
//     return 0;
//   }

//   queue->dados[queue->tail%CAP] = valor;
//   queue->tail++;
//   queue->qtd++;
//   return 1;
// }

// void mostrar(Queue *queue){
//   for(int i = queue->head; i < queue->tail; i++){
    
//     printf("%d ", queue->dados[i%CAP]);
    
//   }
// } 

// int is_empty(Queue *queue){
//   if(queue->qtd == 0){
//     return 1;
//   }else{
//     return 0;
//   }
// }

// int dequeue(Queue *queue){
//   if(is_empty(queue)){
//     return 0;
//   }

//   queue->qtd--;
//   return queue->dados[queue->head++];
// }

// int main(void) {
//   Queue queue;
//   inicializar(&queue);
//   for(int n = 89; n > 0; n-=7){
//     enqueue(&queue, n);
//     printf("HEAD -> ");
//     mostrar(&queue); 
//     printf("<- TAIL\n");
//   }

//   for(int i = 0; i < 15; i++){
//     printf("Valor removido: %d\n", dequeue(&queue));
//     mostrar(&queue);
//   }
//   return 0;
// }

#include <stdio.h>

#define LEN 100

typedef struct {
  char data[LEN];
  int head;
  int tail;
  int qtde;
} Queue;

int is_full(Queue *queue){
//    return queue->qtd == CAP;
  if(queue->qtde == LEN){
    return 1;
  }else{
    return 0;
  }
}

int is_empty(Queue *queue){
  if(queue->qtde == 0){
    return 1;
  }else{
    return 0;
  }
}

void enqueue(Queue *queue, char caracter) {
  if(is_full(queue) == 1){
      return;
    }

    queue->data[queue->tail%LEN] = caracter;
    queue->tail++;
    queue->qtde++;
    return;
}

int dequeue(Queue *queue){
  if(is_empty(queue)){
    return 0;
  }

  queue->qtde--;
  return queue->data[queue->head++];
}

void show(Queue *queue) {
  for(int i = queue->head; i < queue->tail; i++){

      printf("%c", queue->data[i%LEN]);

    }
}

int validar(Queue *queue){
  int abre = 0;
  int fecha = 0;

  if(queue->data[queue->head] == '('){
    abre++;
  }


  dequeue(queue);
  for(int i = queue->head; i < queue->tail; i++){
    if(fecha > abre){
      return 0;
    }else{
      show(queue);
      if(queue->data[i%LEN] == '('){
        abre++;
      } else if(queue->data[i%LEN] == ')'){
        fecha++;
      }
    }
    dequeue(queue);
  }
  if(abre == fecha){
    return 1;
  } else{
    return 0;
  }
}

void start_queue(Queue *queue) {
  queue -> head = 0;
  queue -> tail = 0;
  queue -> qtde = 0;
}

int main(void) {
  char s[LEN];
  Queue queue;
  start_queue(&queue);

  fgets(s, sizeof(s), stdin);

  for(int i = 0; s[i] != '\0'; i++){
    enqueue(&queue, s[i]);
  }

  // show(&queue);

  if(validar(&queue) == 1){
    printf("correto");
  }else{
    printf("incorreto");
  }

  return 0;
}
