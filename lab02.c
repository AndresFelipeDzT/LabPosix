/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Ejemplo de uso de condicionales y mutex para coordinar dos hilos que incrementan un contador.
 * Documentacion:
 * - Se usan dos mutex, uno para el contador y otro para la condicion.
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* --- VARIABLES GLOBALES Y CONSTANTES --- */
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

int count = 0;
#define COUNT_DONE 15
#define COUNT_HALT1 4
#define COUNT_HALT2 11

// Hilo 1 incrementa el contador, espera para saber si la condición esta en el rango esperado 
void *count01(void *arg) {
    for (;;) {
        pthread_mutex_lock(&condition_mutex);
        while (count >= COUNT_HALT1 && count <= COUNT_HALT2) {
            // si el contador esta entre COUNT_HALT1 y COUNT_HALT2 espera hasta que llegue la senal
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }
        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 01 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        if (count >= COUNT_DONE) return NULL; // Finaliza cuando el contador es igual a count_done
    }
}

// Hilo 2, incrementa el contador y le indica al otro hilo cuando actuar
void *count02(void *arg) {
    for (;;) {
        pthread_mutex_lock(&condition_mutex);
        if (count < COUNT_HALT1 || count > COUNT_HALT2) {
            pthread_cond_signal(&condition_cond); // indica al hilo en espera que esta en el rango
        }
        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 02 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        if (count >= COUNT_DONE) return NULL;
    }
}

/* --- MAIN --- */
int main() {
    pthread_t thread1, thread2;
//Crea los hilos
    pthread_create(&thread1, NULL, count01, NULL);
    pthread_create(&thread2, NULL, count02, NULL);
//Los une para que sepan de los otros
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(0);
}

