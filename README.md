# Practica 1 | Aplicación Cliente/servidor

## Objetivo

Que al alumno implemente una aplicación cliente/servidor utilizando las bibliotecas que proporciona el lenguaje C para Linux.

Utilizando el lenguaje C para Linux, implemente un cliente UDP (SOCK_DGRAM) que envíe dos números cualesquiera a un servidor (uno a la vez), el cual realizará la suma del cuadrado de estos dos números y desplegará el resultado, posteriormente si la suma del cuadrado de los números es menor de 100 mandará un mensaje al cliente indicando que los datos son correctos, en caso contrario mandará un mensaje de datos incorrectos y pedirá al cliente que vuelva a mandar dos números, esto se repetirá hasta que la suma del cuadrado de nos números sea menor de 100.

## Antecedentes

### Programación por Sockets

La programación por sockets es una forma de de conectar dos nodos en una red para comunicarse entre si . Un socket (nodo) escucha un puerto IP, mientras que el otro socket se comunica para formar una conexión. 

> El Servidor actúa como escucha mientra el cliente alcanza la conexión con el servidor.

![Arquitectura básica de sockets](https://media.geeksforgeeks.org/wp-content/uploads/Socket_server.png)
### Creacion de un socket

```c
int sockfd = socket(domain, type, protocol)
```

**sockfd *(file-descirption)*:** Un entero que describe al archivo.  
**domain:** Describe el dominio de comunicaciones que usara, los mas comunes son:
 - AF_INET (IPv4 protocol) 
 - AF_INET6 (IPv6 protocol) .

**type:** El tipo de protocolo de comunicación que se usara.
- SOCK_STREAM: TCP(reliable, connection oriented)  
- SOCK_DGRAM: UDP(unreliable, connectionless)  

**protocol:** Valor para el protocolo IP,  que es 0. Los demás protocolos de comunicación en red que existen pueden ser referenciados en linux con:

```bash
cat /etc/protocols
```

## Creación de una aplicación cliente/servidor con SOCK_DGRAM (UDP)

En UDP el cliente no necesita formar una conexión con el servidor como en TCP, en vez de eso solo necesita enviar el datagrama. El servidor no necesita aceptar la conexión y solo espera a que el datagrama llegue. Los datagramas a la llegada contienen la dirección de su remitente que el servidor usa para enviar la información al cliente correcto.

![UDP Client/Server function calls](https://media.geeksforgeeks.org/wp-content/uploads/udpfuncdiag.png)

El proceso para crear este tipo de aplicación es el siguiente: 

**UDP Server :**

1.  Crear un socket UDP
2.  Enlazar el socket con la dirección del servidor
3.  Esperar a que el paquete llegue por parte del cliente.
4.  Procesar el datagrama y mandar una respuesta al cliente.
5.  Regresar al paso 3 y hacerlo de nuevo

**UDP Client :**

1.  Crear un socket UDP
2.  Enviar un mensaje al servidor
3.  Esperar hasta que el servidor de respuesta
4.  Procesar la respuesta y si es necesario regresar al paso 2.
5.  Cerrar el socket y salir.