#ifndef EXAMEN_III_ESTADO_H
#define EXAMEN_III_ESTADO_H
#include <pthread.h>

extern pthread_mutex_t mutex_estado;
void registrar_estado_activo(const char* usuario);
void eliminar_estado_activo(const char* usuario);
int usuario_esta_activo(const char* usuario);

#endif //EXAMEN_III_ESTADO_H