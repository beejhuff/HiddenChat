/*!
 * Simple programa de chat (lado del cliente).cpp - (https://github.com/Marcelorvp/Chat)
 *
 * Copyright (c) 2016 Marcelo Raúl Vázquez Pereyra
 */

#include <iostream>
#include <netinet/in.h> // Para implementar la estructura sockaddr_in
#include <stdlib.h> // exit()


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
  */

  int client;
  int numPuerto = 1500;
  bool isExit = false;
  int bufsize = 1024;
  char buffer[bufsize];
  char* ip = "127.0.0.1";

  struct sockaddr_in server_direccion;

  client = socket(AF_INET, SOCK_STREAM, 0);

  /* ----------Estableciendo conexión con sockets ----------*/
  /* --------------- socket() función ------------------*/

  if (client < 0)
  {
      cout << "\nError estableciendo sockets..." << endl;
      exit(1);
  }

  /*
      La función socket() crea un nuevo socket.
      Coge 3 argumentos:
          a. AF_INET: dirección de dominio del socket.
          b. SOCK_STREAM: Tipo de socket. Un stream socket en el cual los
          caracteres son leídos en transmisión continua (TCP)
          c. Protocolo de argumento: debería ser siempre 0. El sistema
          operativo se encargará de escoger el mejor protocolo.
          Esto devolverá un entero pequeño y será usado para todas las referencias
          al socket. Si la llamada al socket falla, nos devolverá -1.
  */

  cout << "\n=> Los sockets del cliente han sido creados..." << endl;

  /*
      La variable server_direccion es una estructura de sockaddr_in.
      sin_family contiene un código para la dirección familia.
      Siempre se debe de establecer en AF_INET.
      INADDR_ANY contiene la dirección IP del host. Para el código del
      servidor, siempre será la dirección IP de la máquina en la cual el
      servidor está siendo ejecutado.
      htons() convierte el número del puerto desde una orden byte del anfitrión
      (host) hasta un número de puerto en una orden byte de la red (network).
  */

  server_direccion.sin_family = AF_INET;
  server_direccion.sin_port = htons(numPuerto);

  // esta función nos retorna un 1 si la IP es válida
  // y 0 si es inválida
  // inet_pton convierte la IP en paquetes
  // inet_ntoa convierte de nuevo la IP en paquetes
  //inet_pton(AF_INET, ip, &server_direccion.sin_addr);

  /*if (connect(client,(struct sockaddr *)&server_direccion, sizeof(server_direccion)) == 0)
      cout << "=> Conexión con el Servidor" << inet_ntoa(server_direccion.sin_addr) << " con número de puerto: " << numPuerto << endl;*/


  /* ---------- Conectando los Sockets ---------- */
  /* ---------------- Conexión() ---------------- */

  if (connect(client,(struct sockaddr *)&server_direccion, sizeof(server_direccion)) == 0)
      cout << "=> Connection to the server port number: " << numPuerto << endl;

      /*
          La función de conexión es llamada por el cliente para establecer la
          conexión con el servidor. Tiene 3 argumentos, el archivo descriptor
          del socket, la dirección del host en donde se quiere conectar
          (incluyendo el número del purto), y el tamaño de la dirección.
          Esta función retorna un 0 si todo sale bien y un -1 si algo sale
          mal
          Importante tener en cuenta que el cliente necesita saber el número del
          puerto del servidor pero no su propio puerto.
      */

    cout << "=> Esperando confirmación del servidor..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> Conexión confirmada, listo para proceder...";

 }
