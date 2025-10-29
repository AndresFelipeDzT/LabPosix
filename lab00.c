/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Fecha: 28/10/2025
 * Tema: Posix para la creacion de hilos concurrentes:
 * Alumno: Andres Felipe Diaz Torres
 * Descripcion:
 * Programa de ejemplo que crea dos hilos y cada hilo imprime un mensaje.
 * Documentacion:
 * - El programa crea dos hilos con pthread_create.
 * - Cada hilo ejecuta print_message_function y recibe un puntero a cadena.
 * - El main espera a que los hilos terminen con pthread_join.
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Funcion que ejecuta cada hilo, muestra los mensajes recibidos como parametros
void *print_message_function(void *ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s\n", message); /* imprime el mensaje pasado al hilo */
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;

    // Crea dos hilos independientes que ejecutan print_message_function
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void *) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void *) message2);

    printf("Thread 1 returns: %d\n", iret1); // muestra lo que retorna pthread_create
    printf("Thread 2 returns: %d\n", iret2);

    // Espera a que los hilos terminen para salirse
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    exit(0);

}
