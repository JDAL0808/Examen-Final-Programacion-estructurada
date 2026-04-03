#include "Funciones_server.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

// candados para que no choquen los datos si los hilos entran al mismo tiempo
pthread_mutex_t mutex_conectados = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_registrados = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_bitacora = PTHREAD_MUTEX_INITIALIZER;

// estructura para guardar en el archivo binario
typedef struct {
    char nombre[50];
    int pid_ultimo_ingreso;
} ClienteRegistrado;


// funcion para escribir en chat.log
void escribir_bitacora(const char *mensaje) {
    pthread_mutex_lock(&mutex_bitacora);
    
    FILE *archivo = fopen("data/chat.log", "a");
    if (archivo != NULL) {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        char fecha_hora[30];
        // le da formato a la hora tipo [2026-04-03 14:30:00]
        strftime(fecha_hora, sizeof(fecha_hora), "[%Y-%m-%d %H:%M:%S]", tm_info);
        
        fprintf(archivo, "%s %s\n", fecha_hora, mensaje);
        fclose(archivo);
    }
    
    pthread_mutex_unlock(&mutex_bitacora);
}


// funcion para meter usuarios al txt cuando hacen login
void agregar_usuario_conectado(const char *nombre, int pid) {
    pthread_mutex_lock(&mutex_conectados); 
    
    FILE *archivo = fopen("data/usuarios.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s|%d\n", nombre, pid);
        fclose(archivo);
    }
    
    pthread_mutex_unlock(&mutex_conectados); 
}


// funcion para limpiar el txt cuando el server se apaga
void vaciar_usuarios_conectados() {
    pthread_mutex_lock(&mutex_conectados);
    
    // w borra todo de un solo
    FILE *archivo = fopen("data/usuarios.txt", "w");
    if (archivo != NULL) {
        fclose(archivo);
    }
    
    pthread_mutex_unlock(&mutex_conectados);
}


// funcion para guardar el historico en binario
void registrar_cliente_binario(const char *nombre, int pid) {
    pthread_mutex_lock(&mutex_registrados);
    
    ClienteRegistrado nuevo;
    strcpy(nuevo.nombre, nombre);
    nuevo.pid_ultimo_ingreso = pid;

    FILE *archivo = fopen("data/registrados.dat", "ab");
    if (archivo != NULL) {
        fwrite(&nuevo, sizeof(ClienteRegistrado), 1, archivo);
        fclose(archivo);
    }
    
    pthread_mutex_unlock(&mutex_registrados);
}