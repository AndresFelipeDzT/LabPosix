/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Version del ejemplo de 20 hilos que inicializa y destruye el mutex explicitamente.
 * Documentacion:
 * - Se muestra como inicializar y destruir un mutex.
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int acumulado = 0;
pthread_mutex_t mutex;

void *cuadrado(void *x) {
    int xi = (intptr_t)x;
    int valor = xi * xi;
//Mutex para el acumulador
    pthread_mutex_lock(&mutex);
    acumulado += valor;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t hilos[20];
    int i;

    // LINEA NUEVA 1, Inicializar el mutex explicitamente 
    pthread_mutex_init(&mutex, NULL);
//Bucle para crear hilos hasta llegar a 20
    for (i = 0; i < 20; i++) {
        pthread_create(&hilos[i], NULL, cuadrado, (void *)(intptr_t)(i + 1));
    }
//Esperar hasta que todos los hilos terminen
    for (i = 0; i < 20; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Acumulado = %d\n", acumulado);

    // LINEA NUEVA 2, Destruir el mutex al final 
    pthread_mutex_destroy(&mutex);

    return 0;
}
