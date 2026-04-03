#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "estado.h"

pthread_mutex_t mutex_estado = PTHREAD_MUTEX_INITIALIZER;

// registrar usuario activo
void registrar_estado_activo(const char* usuario) {
    pthread_mutex_lock(&mutex_estado);

    FILE *f_check = fopen("data/conectados.txt", "r");
    char buffer[100];
    int ya_existe = 0;

    if (f_check != NULL) {
        while (fgets(buffer, sizeof(buffer), f_check)) {
            buffer[strcspn(buffer, "\n")] = 0;

            if (strcmp(buffer, usuario) == 0) {
                ya_existe = 1;
                break;
            }
        }
        fclose(f_check);
    }

    // Solo si no existe, lo agregamos y registramos en log
    if (!ya_existe) {
        FILE *f = fopen("data/conectados.txt", "a");
        if (f != NULL) {
            fprintf(f, "%s\n", usuario);
            fclose(f);
        }

        // LOG
        FILE *log = fopen("data/chat.log", "a");
        if (log != NULL) {
            time_t t = time(NULL);
            char *fecha = ctime(&t);
            fecha[strcspn(fecha, "\n")] = 0; // quitar salto de línea

            fprintf(log, "[%s] %s inició sesión (ACTIVO)\n", fecha, usuario);
            fclose(log);
        }
    }

    pthread_mutex_unlock(&mutex_estado);
}

// eliminar usuario activo (logout)
void eliminar_estado_activo(const char* usuario) {
    pthread_mutex_lock(&mutex_estado);

    FILE *f = fopen("data/conectados.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");

    char buffer[100];

    if (f != NULL && temp != NULL) {
        while (fgets(buffer, sizeof(buffer), f)) {
            buffer[strcspn(buffer, "\n")] = 0;

            if (strcmp(buffer, usuario) != 0) {
                fprintf(temp, "%s\n", buffer);
            }
        }
    }

    if (f) fclose(f);
    if (temp) fclose(temp);

    remove("data/conectados.txt");
    rename("data/temp.txt", "data/conectados.txt");

    pthread_mutex_unlock(&mutex_estado);
}

// verificar si usuario está activo
int usuario_esta_activo(const char* usuario) {
    pthread_mutex_lock(&mutex_estado);

    FILE *f = fopen("data/conectados.txt", "r");
    char buffer[100];

    if (f != NULL) {
        while (fgets(buffer, sizeof(buffer), f)) {
            buffer[strcspn(buffer, "\n")] = 0;

            if (strcmp(buffer, usuario) == 0) {
                fclose(f);
                pthread_mutex_unlock(&mutex_estado);
                return 1;
            }
        }
        fclose(f);
    }

    pthread_mutex_unlock(&mutex_estado);
    return 0;
}