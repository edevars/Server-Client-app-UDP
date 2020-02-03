#!/bin/bash

if [ -z "$1" ]; then
    echo "Agregue un argumento para compilar los archivos"
else
    if [ $1 = "server" ]; then
        echo "Compilar el server"
        gcc server.c -o server
    else
        if [ $1 = "client" ]; then
            echo "Compilar el cliente"
            gcc client.c -o client
        else
            echo "Compilar ambos"
            gcc server.c -o server && gcc client.c -o client
        fi
    fi
fi
