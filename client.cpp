/*!
 * Simple programa de chat (lado del cliente).cpp - (https://github.com/Marcelorvp/Chat)
 *
 * Copyright (c) 2016 Marcelo Raúl Vázquez Pereyra
 */

#include <iostream>
#include <netinet/in.h> // Para implementar la estructura sockaddr_in

using namespace std;

int main(){

  /* ---------- INICIALIZACIÓN DE VARIABLES ---------- */

  /*
     1. client es un descriptor de ficheros hecho para almacenar los valores
     devueltos por la llamada al sistema de sockets y la aceptación de la
     llamada al sistema
     2. numPuerto es una variable definida para almacenar el número del Puerto
     en el cual se aceptarán las conexiones. Ponemos 1500 dado que es el puerto
     que se encarga de usar el Protocolo de Control de Transmisión, protocolo
     principal en redes TCP/IP. Debe de ser el mismo tanto en cliente como en
     servidor.
     3. estaFuera es una variable booleana la cual usaremos para terminar el
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
  */

  int client;
  int numPuerto = 1500;
  bool estaFuera = false; // Variable booleana que usaremos para terminar el bucle
  int bufsize = 1024;

  struct sockaddr_in server_direccion;

 }
