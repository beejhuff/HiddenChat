/*!
 * Simple programa de chat (lado del servidor).cpp - (https://github.com/Marcelorvp/Chat)
 *
 * Copyright (c) 2016 Marcelo Raúl Vázquez Pereyra
 */

#include <iostream>
#include <netinet/in.h> // Para implementar la estructura sockaddr_in
#include <stdlib.h> // exit()

using namespace std;

int main(){

  /* ---------- INITIALIZING VARIABLES ---------- */

  /*
     1. client/server son 2 descriptores de ficheros. Estas 2 variables
     almacenan los valores devueltos por la llamada al sistema de sockets
     y la aceptación de la llamada al sistema.
     2. numPuerto es una variable definida para almacenar el número del Puerto
     en el cual se aceptarán las conexiones. Ponemos 1500 dado que es el puerto
     que se encarga de usar el Protocolo de Control de Transmisión, protocolo
     principal en redes TCP/IP. Debe de ser el mismo tanto en cliente como en
     servidor.
     3. isExit es una variable booleana la cual usaremos para terminar el
     bucle
     4. El cliente leerá los caracteres de la conexión socket en una variable
     dinámica (buffer)
     5. sockaddr_in es una estructura que contiene una dirección de internet.
     Esta estructura está ya definida en la librería netinet/in.h, así que no
     es necesario declararla nuevamente.

      Definición de la estructura:

      struct sockaddr_in
      {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
      };
      6. server_direccion se encargará de contener la dirección del servidor
      7. socklen_t  es un tipo intr de una anchura de al menos 32 bits
  */

  int client, server;
  int numPuerto = 1500;
  bool isExit = false;
  int bufsize = 1024;
  char buffer[bufsize];

  struct sockaddr_in server_direccion;
  socklen_t size;

  /* ---------- Estableciendo las Conexiones Socket ----------*/
  /* --------------- socket() función ------------------*/

  client = socket(AF_INET, SOCK_STREAM, 0);

  if (client < 0)
  {
      cout << "\nError al establecer socket..." << endl;
      exit(1);
  }

  /*
      La función socket() crea un nuevo socket.
      Coge 3 argumento:,
          a. AF_INET: dirección de dominio del socket.
          b. SOCK_STREAM: Tipo de socket. Un stream socket en el cual los
          caracteres son leídos en transmisión continua (TCP)
          c. Protocolo de argumento: debería ser siempre 0. El sistema
          operativo se encargará de escoger el mejor protocolo.
          Esto devolverá un entero pequeño y será usado para todas las referencias
          al socket. Si la llamada al socket falla, nos devolverá -1.
  */

    cout << "\n=> Servidor socket creado..." << endl;

}
