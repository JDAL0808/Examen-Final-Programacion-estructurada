#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int main() {
    pthread_t hiloInbox;
    pthread_t hiloOutbox;

    // Crear hilos (solo estructura, sin lógica)
    pthread_create(&hiloInbox, NULL, NULL, NULL);
    pthread_create(&hiloOutbox, NULL, NULL, NULL);

    char Nombre[50];
    char comando[100];

    // Pedir nombre solo una vez
    printf("Escriba su nombre: \n");
    scanf("%49s", Nombre);

    // Mostrar comandos solo una vez
    printf("Comandos: \n");
    printf("/privado (enviar mensaje a alguien)\n");
    printf("/global (mensaje a todos)\n");
    printf("/salir (sale del chat)\n");

    while (1) {
        // Leer comando del usuario
        scanf("%99s", comando);

        if (strcmp(comando, "/salir") == 0) {
            break; // termina todo si el usuario escribe /salir
        }

        // Los hilos siguen corriendo cada segundo en paralelo
        sleep(1);
    }

    printf("Se terminó el chat\n");
    return 0;
}