#ifndef FUNCIONES_SERVER_H
#define FUNCIONES_SERVER_H

void escribir_bitacora(const char *mensaje);
void agregar_usuario_conectado(const char *nombre, int pid);
void vaciar_usuarios_conectados();
void registrar_cliente_binario(const char *nombre, int pid);

#endif