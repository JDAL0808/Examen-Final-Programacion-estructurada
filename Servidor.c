#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork(); // Crear hijo una sola vez
    if (pid < 0) {
        perror("Fork falló");
        return 1;
    }

    if (pid == 0) {
        // Proceso hijo
        while (1) {
            // Aquí va la función del hijo (bitacora u otra lógica)
            sleep(1);
        }
    } else {
        // Proceso padre -> hilos y loop principal
        pthread_t hiloOutbox;
        pthread_t hiloInbox;

        // Crear hilos (sin lógica, solo estructura)
        pthread_create(&hiloOutbox, NULL, NULL, NULL);
        pthread_create(&hiloInbox, NULL, NULL, NULL);

        while (1) {
            printf("Hola mundo\n");
            sleep(1);

            // Los hilos están ejecutándose cada segundo
        }

        // Se termina con Ctrl+C
    }

    return 0;
}