cmake_minimum_required(VERSION 3.28)
project(Examen_III C)

set(CMAKE_C_STANDARD 11)

add_executable(Examen_III Servidor.c
        verificacion.c
        verificacion.h
        estado.c
        estado.h
        Funciones_server.c)
