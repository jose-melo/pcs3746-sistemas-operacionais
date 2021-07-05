#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "semaphore.h"
#define NUM_THREADS 2
#define MAX_BUFFER 2
typedef unsigned int sem_id;

//Declarando buffer compartilhado
int buffer[MAX_BUFFER];
int count = 0;
//Declarando semáforo
sem_id sem_full;  //= 0;
sem_id sem_empty; //= MAX_BUFFER;
sem_id sem_rc;    //= 1;

void *producer(void *args)
{
  int num = 1;
  while (1)
  {
    //Produce
    num += 2;
    //Bloquear região crítica
    printf("[USER] PRODUTOR KINOSHI ~ QUERO PRODUZIR count = %d   num = %d\n", count, num);
    down(sem_empty);
    printf("[USER] PRODUTOR KINOSHI ~ POSSO PRODUZIR\n");

    printf("[USER] PRODUTOR KINOSHI ~ QUERO ENTRAR NA REGIÃO CRITICA\n");
    down(sem_rc);
    printf("[USER] PRODUTOR KINOSHI ~ ENTREI NA REGIÃO CRITICA\n");

    buffer[count] = num;
    count++;

    printf("[USER] PRODUTOR KINOSHI ~ ESTOU FELIZ, PRODUZI ESSE PRODUTO = %d\n", num);

    //Desbloquear região crítica
    printf("[USER] PRODUTOR KINOSHI ~ VOU LIBERAR A REGIÃO CRITICA PARA GERAL\n");
    up(sem_rc);
    printf("[USER]  PRODUTOR KINOSHI ~ REGIÃO CRITICA LIBERADA\n");

    printf("[USER]  PRODUTOR KINOSHI ~ VOU AVISAR QUE AUMENTEI O FULL\n");
    up(sem_full);
    printf("[USER]  PRODUTOR KINOSHI ~ AVISEI QUE AUMENTEI O FULL\n");
  }
}

void *producer2(void *args)
{
  int num = 0;
  while (1)
  {
    //Produce
    num += 2;
    //Bloquear região crítica
    printf("[USER] PRODUTOR 2 ~ QUERO PRODUZIR count = %d   num = %d\n", count, num);
    down(sem_empty);
    printf("[USER] PRODUTOR 2 ~ POSSO PRODUZIR\n");

    printf("[USER] PRODUTOR 2 ~ QUERO ENTRAR NA REGIÃO CRITICA\n");
    down(sem_rc);
    printf("[USER] PRODUTOR 2 ~ ENTREI NA REGIÃO CRITICA\n");

    buffer[count] = num;
    count++;

    printf("[USER] PRODUTOR 2 ~ ESTOU FELIZ, PRODUZI ESSE PRODUTO = %d\n", num);

    //Desbloquear região crítica
    printf("[USER] PRODUTOR 2 ~ VOU LIBERAR A REGIÃO CRITICA PARA GERAL\n");
    up(sem_rc);
    printf("[USER]  PRODUTOR 2 ~ REGIÃO CRITICA LIBERADA\n");

    printf("[USER]  PRODUTOR 2 ~ VOU AVISAR QUE AUMENTEI O FULL\n");
    up(sem_full);
    printf("[USER]  PRODUTOR 2 ~ AVISEI QUE AUMENTEI O FULL\n");
  }
}

void *consumer(void *args)
{
  while (1)
  {
    int produto;
    //Consume
    //Bloquear região crítica
    printf("[USER] CONSUMIDOR ~ QUERO CONSUMIR count = %d  \n", count);
    down(sem_full);
    printf("[USER] CONSUMIDOR ~ POSSO CONSUMIR\n");

    printf("[USER] CONSUMIDOR ~ QUERO ENTRAR NA REGIÃO CRITICA\n");
    down(sem_rc);
    printf("[USER] CONSUMIDOR ~ ENTREI NA REGIÃO CRITICA\n");

    produto = buffer[count - 1];
    count--;
    printf("[USER]  CONSUMIDOR ~ ESTOU FELIZ, CONSUMI ESSE PRODUTO AQUI: %d \n", produto);
    //Desbloquear região crítica

    printf("[USER]  CONSUMIDOR ~ VOU LIBERAR A REGIÃO CRITICA PARA GERAL\n");
    up(sem_rc);
    printf("[USER] CONSUMIDOR ~ REGIÃO CRITICA LIBERADA\n");

    printf("[USER]  CONSUMIDOR ~ VOU AVISAR QUE AUMENTEI O EMPTY\n");
    up(sem_empty);
    printf("[USER]  CONSUMIDOR ~ AUMENTEI O EMPTY\n");
  }
}

int main()
{
  //Criar variáveis para semáforo
  while (1)
  {
    //Inicializar os três semáforos
    printf("[USER] MAIN ~ Inicialização dos semáforos\n");
    sem_rc = init_semaphore(1);
    sem_full = init_semaphore(0);
    sem_empty = init_semaphore(MAX_BUFFER);

    printf("[USER] MAIN id do sem_rc = %d \n", sem_rc);
    printf("[USER] MAIN id do sem_full = %d \n", sem_full);
    printf("[USER] MAIN id do sem_empty = %d \n", sem_empty);
    //Inicialização dos semáforos completa
    //Inicializando as threads
    pthread_t th[NUM_THREADS];
    if (pthread_create(&th[0], NULL, &producer, NULL) != 0)
    {
      perror("[USER] MAIN ~ Falha na criação de thread do produtor");
    }

    if (pthread_create(&th[1], NULL, &consumer, NULL) != 0)
    {
      perror("[USER] MAIN ~ Falha na criação de thread do consumidor");
    }

    // if (pthread_create(&th[2], NULL, &producer2, NULL) != 0)
    // {
    //   perror("[USER] MAIN ~ Falha na criação de thread do produtor kinoshi");
    // }

    for (int i = 0; i < NUM_THREADS; i++)
    {
      if (pthread_join(th[i], NULL) != 0)
      {
        perror("[USER] MAIN ~ Falha join thread");
      }
    }
    // Finalizar semáforos
  }
}
