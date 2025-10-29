/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Inicializa y destruye la condicion y mutex.
 * Documentacion:
 * - Inicializa mutex y condicion en el main 
 * - Luego los destruye como buena practica
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

/* --- VARIABLES GLOBALES --- */
pthread_cond_t var_cond;
pthread_mutex_t mutex;

int valor = 100;
bool notificar = false;

/* --- FUNCIÓN QUE ESPERA LA SEÑAL --- */
void *reportar(void *nada) {
    pthread_mutex_lock(&mutex);
    while (!notificar) {
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
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

/* --- FUNCIÓN PRINCIPAL --- */
int main() {
    pthread_t reporte, asigne;

    // LINEAS NUEVAS, inicializacion dinamica de mutex y condicion 
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&var_cond, NULL);

    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    pthread_join(reporte, NULL);
    pthread_join(asigne, NULL);

    // LINEAS NUEVAS, destruccion de recursos 
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&var_cond);

    return 0;
}
