/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Ejemplo mutex con inicializador para proteger el acumulado
 * Documentacion:
 * - Uso de PTHREAD_MUTEX_INITIALIZER para inicializar el mutex.
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

/* --- VARIABLES GLOBALES --- */
int acumulado = 0;
pthread_mutex_t acumulado_mutex = PTHREAD_MUTEX_INITIALIZER;

/* --- FUNCIÓN EJECUTADA POR CADA HILO --- */
void *cuadrado(void *x) {
    int xi = (intptr_t)x;

    pthread_mutex_lock(&acumulado_mutex);
    acumulado += xi * xi;
    pthread_mutex_unlock(&acumulado_mutex);

    return NULL;
}

/* --- FUNCIÓN PRINCIPAL --- */
int main() {
    pthread_t hilos[20]; //Espacio para los hilos
    int i;
//Bucle para crear hilos hasta llegar a 20
    for (i = 0; i < 20; i++) {
        pthread_create(&hilos[i], NULL, cuadrado, (void *)(intptr_t)(i + 1));
    }
//Esperar que todos terminen
    for (i = 0; i < 20; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Acumulado = %d\n", acumulado);

    return 0;
}
