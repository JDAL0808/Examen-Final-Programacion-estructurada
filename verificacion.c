#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "verificacion.h"

// mutex externo (para compartir con otros módulos)
pthread_mutex_t mutex_verificacion = PTHREAD_MUTEX_INITIALIZER;


// HILO revisa mensajes recibidos (CLIENTE)
void* hilo_verificar_inbox(void* arg) {
    char buffer[256];

    while (1) {
        pthread_mutex_lock(&mutex_verificacion);

        FILE *f = fopen("data/inbox.txt", "r");

        if (f != NULL) {
            while (fgets(buffer, sizeof(buffer), f)) {
                printf("\n Mensaje recibido: %s", buffer);
            }
            fclose(f);

            // limpiar archivo después de leer
            f = fopen("data/inbox.txt", "w");
            if (f != NULL) fclose(f);
        }

        pthread_mutex_unlock(&mutex_verificacion);

        sleep(2);
    }

    return NULL;
}


// HILO revisa respuestas del servidor (CLIENTE)
void* hilo_verificar_respuestas(void* arg) {
    char buffer[256];

    while (1) {
        pthread_mutex_lock(&mutex_verificacion);

        FILE *f = fopen("data/response.txt", "r");

        if (f != NULL) {
            while (fgets(buffer, sizeof(buffer), f)) {
                printf("\n Respuesta del servidor: %s", buffer);
            }
            fclose(f);

            f = fopen("data/response.txt", "w");
            if (f != NULL) fclose(f);
        }

        pthread_mutex_unlock(&mutex_verificacion);

        sleep(2);
    }

    return NULL;
}


//HILO revisa solicitudes de clientes (SERVIDOR)
void* hilo_verificar_pedidos(void* arg) {
    char buffer[256];

    while (1) {
        pthread_mutex_lock(&mutex_verificacion);

        FILE *f = fopen("data/request.txt", "r");

        if (f != NULL) {
            while (fgets(buffer, sizeof(buffer), f)) {
                printf("Request recibido: %s", buffer);

                // aquí luego tu compañero puede procesar:
                // LOGIN, MSG_PRIVADO, MSG_GLOBAL, etc.
            }
            fclose(f);

            f = fopen("data/request.txt", "w");
            if (f != NULL) fclose(f);
        }

        pthread_mutex_unlock(&mutex_verificacion);

        sleep(2);
    }

    return NULL;
}