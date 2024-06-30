// CSI 3131 - Assignment #2
// Name: Rina Osman
// Student ID: 300222206

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int a;
int b;
int turn;
pthread_mutex_t lock;

void *thread0(void *arg){
    for (int i = 0; i < a; i++)
    {
        while (turn != 0);
        pthread_mutex_lock(&lock);
        b = b + 1;
        printf("Thr0, (b=%d)\n", b);
        turn = (turn + 1) % 4;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread1(void *arg){
    for (int i = 0; i < a; i++)
    {
        while (turn != 1);
        pthread_mutex_lock(&lock);
        b = b + 2;
        printf("Thr1, (b=%d)\n", b);
        turn = (turn + 1) % 4;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread2(void *arg){
    for (int i = 0; i < a; i++)
    {
        while (turn != 2);
        pthread_mutex_lock(&lock);
        b = b + 3;
        printf("Thr2, (b=%d)\n", b);
        turn = (turn + 1) % 4;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread3(void *arg)
{    for (int i = 0; i < a; i++)
    {
        while (turn != 3); 
        pthread_mutex_lock(&lock);
        b = b + 4;
        printf("Thr3, (b=%d)\n", b);
        turn = (turn + 1) % 4;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t threads[4];
    pthread_mutex_init(&lock, NULL);

    printf("Enter integer a value: ");
    scanf("%d", &a);
    printf("Enter integer b value: ");
    scanf("%d", &b);
    printf("Enter the Thread # to start first (0 to 3): ");
    scanf("%d", &turn);

    pthread_create(&threads[0], NULL, thread0, NULL);
    pthread_create(&threads[1], NULL, thread1, NULL);
    pthread_create(&threads[2], NULL, thread2, NULL);
    pthread_create(&threads[3], NULL, thread3, NULL);


    for (int i = 0; i < 4; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Parent, (b=%d)\n", b);
    printf("The Fibonacci sequence for %d is:\n", b);
    int v1 = 1, v2 = 1, v3;
    if (b <= 1)
    {
        printf("%d\n", v1);
    }
    else
    {
        printf("%d %d", v1, v2);
        for (int i = 2; i < b; i++)
        {
            v3 = v1 + v2;
            v2 = v1;
            v1 = v3;
            printf(" %d", v3);
        }
        printf("\n");
    }

    pthread_mutex_destroy(&lock);
    return 0;
}