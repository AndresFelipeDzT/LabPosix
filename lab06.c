/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Ejemplo de condicion y mutex donde un hilo le envia la señal a otra
 * Documentacion:
 * - Se iniciliaza tanto la var_cond como mutex 
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

/* --- VARIABLES GLOBALES --- */
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int valor = 100;
bool notificar = false;

/* --- FUNCIoN QUE ESPERA LA SENAL --- */
void *reportar(void *nada) {
    pthread_mutex_lock(&mutex);
    while (!notificar) {
        // cuando notificar es verdadero es su turno
        pthread_cond_wait(&var_cond, &mutex);
    }
    printf("El valor es: %d\n", valor);
    pthread_mutex_unlock(&mutex);

    return NULL; 
}

/* --- FUNCIÓN QUE ENVÍA LA SEÑAL --- */
void *asignar(void *nada) {
    valor = 20;

    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond); //Le indica al otro que ya es su turno
    pthread_mutex_unlock(&mutex);

    return NULL; 
}

/* --- FUNCIÓN PRINCIPAL --- */
int main() {
    pthread_t reporte, asigne;

    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    pthread_join(reporte, NULL);
    pthread_join(asigne, NULL);

    return 0;
}
