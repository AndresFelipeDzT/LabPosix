/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Programa que crea NTHREADS hilos; cada hilo incrementa un contador global protegido por mutex.
 * Documentacion:
 * - Uso de mutex para evitar condiciones de carrera
 * - Se pasa por puntero una copia del indice para evitar colisiones con la variable de loop.
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

// Funcion para todos los hilos, imprime el numero y aumenta el contador global 
void *thread_function(void *arg) {
    int i = *(int *)(arg); // Recibe el indice
    printf("Thread number: %d | Thread ID: %p\n", i, (void *)pthread_self());
    pthread_mutex_lock(&mutex1); 
    counter++;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

int main() {
    pthread_t thread_id[NTHREADS];
    int i;

    for (i = 0; i < NTHREADS; i++) {
        int *arg = malloc(sizeof(*arg)); // Reserva de memoria con malloc
        *arg = i;
        pthread_create(&thread_id[i], NULL, thread_function, arg);
    }

    for (i = 0; i < NTHREADS; i++) {
        pthread_join(thread_id[i], NULL); // Que terminen todos los hilos
    }

    printf("Final counter value: %d\n", counter);
    return 0;
}
