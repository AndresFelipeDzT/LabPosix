/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Crea 20 hilos; cada hilo calcula el cuadrado de su indice y lo acumula en una variable
 * global protegida por un mutex.
 * Documentacion:
 * - Uso de pthread_mutex para evitar condiciones de carrera.
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

int acumulado = 0; // Variable global compartida
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para acumulado

void *cuadrado(void *x) {
    int xi = (intptr_t)x;
    int valor = xi * xi;

    // Proteccion de la variable compartida
    pthread_mutex_lock(&mutex);
    acumulado += valor;
    pthread_mutex_unlock(&mutex);

    return NULL; 
}

int main(int argc, char *argv[]) {
    pthread_t hilos[20];
    int i;

    // Bucle que va creando hilos hasta llegar a 20
    for (i = 0; i < 20; i++) {
        pthread_create(&hilos[i], NULL, cuadrado, (void *)(intptr_t)(i + 1));
    }

    // Esperar hasta que todos los hilos hayan terminado
    for (i = 0; i < 20; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Acumulado = %d\n", acumulado);
    return 0;
}
