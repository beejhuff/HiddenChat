/*!
 * Simple programa de chat (lado del servidor).cpp - (https://github.com/Marcelorvp/Chat)
 *
 * Copyright (c) 2016 Marcelo Raúl Vázquez Pereyra
 */

#include <iostream>
#include <netinet/in.h> // Para implementar la estructura sockaddr_in
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // inet_ntoa
#include <stdlib.h> // exit()
#include <string.h> // strcpy()
#include <unistd.h> // close()

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
      Coge 3 argumentos:
          a. AF_INET: dirección de dominio del socket.
          b. SOCK_STREAM: Tipo de socket. Un stream socket en el cual los
          caracteres son leídos en transmisión continua (TCP)
          c. Protocolo de argumento: debería ser siempre 0. El sistema
          operativo se encargará de escoger el mejor protocolo.
          Esto devolverá un entero pequeño y será usado para todas las referencias
          al socket. Si la llamada al socket falla, nos devolverá -1.
  */

    cout << "\n=> Servidor socket creado..." << endl;

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
    server_direccion.sin_addr.s_addr = htons(INADDR_ANY);
    server_direccion.sin_port = htons(numPuerto);

    /* ---------- Uniendo los Sockets ---------- */
    /* ---------------- Unión() ---------------- */


    if ((bind(client, (struct sockaddr*)&server_direccion,sizeof(server_direccion))) < 0)
    {
        cout << "=> Error al unir conexión, los sockets ya han sido establecidos..." << endl;
        return -1;
    }

    /*
        La llamada a Unión() une el socket a una dirección, en este caso la
        dirección del host actual y el número del puerto en el cual el servidor
        va a ser iniciado. Este coge 3 argumentos. EL segundo argumento es
        un puntero a una estructura de tipo sockaddr, The second argument is a pointer
        to a structure of type sockaddr, esto hará que se convierta en el tipo
        correcto.
    */

    size = sizeof(server_direccion);
    cout << "=> Buscando clientes..." << endl;

    listen(client, 1);

    /*
        La llamada a listen permite al proceso escuchar al socket para las
        conexiones.
        El programa lo que hará será permanecer inactivo si no hay ninguna conexión
        entrante.
        El primer argumento es el archivo descriptor del socket, el segundo es
        el tamaño para el número de clientes, es decir, el número de conexiones
        que el servidor es capaz de manejar mientras el proceso está manejando
        una conexión particular. El máximo tamaño permitido por muchos sistemas
        es 5.
    */

    /* ------------- Aceptando Clientes  ------------- */
    /* ----------------- listen() ------------------- */

    /*
        La llamada a la aceptación() causa que el proceso se bloquee hasta que
        un cliente se conecte al servidor. Por lo tanto, despierta un proceso
        cuando la conexión del cliente ha sido correctamente establecida.
        Este devuelve un nuevo fichero descriptivo, y todas las comunicaciones
        en esta conexión deberían funcionar usando el nuevo archivo descriptivo.
        El segundo argumento es una referencia puntero a la dirección del cliente
        en el otro extremo de la conexión, y un tercer argumento que corresponde
        al tamaño de la estructura.
    */

    int clientContador = 1;
    server = accept(client,(struct sockaddr *)&server_direccion,&size);

    // Primero comprueba si es váildo o no
    if (server < 0) cout << "=> Error de aceptación..." << endl;

    while (server > 0)
    {
        strcpy(buffer, "=> Servidor conectado...\n");
        send(server, buffer, bufsize, 0);
        cout << "=> Conectado con el cliente #" << clientContador << ", puedes proceder..." << endl;
        cout << "\n\n=> Escribe # para terminar la conexión\n" << endl;
        cout << "-------------------------------------------------------------------------" << endl << endl;
        cout << "********************************************" << endl;
        cout << "                HIDDEN CHAT                 " << endl;
        cout << "********************************************" << endl << endl;

        /*
            Importante recordar que sólo llegaremos a este punto siempre que el
            cliente se haya conectado al servidor correctamente. Esto lo lee
            desde el socket. La lectura se parará hasta que haya algo que leer en
            el socket, es decir, después de que el cliente haya ejecutado el
            envío(). Leerá ya sea el número total de caracteres en el socket
            o 1024
        */
        cout << endl;
        cout << "Cliente: ";
        do {
            recv(server, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');

        do {
            cout << endl;
            cout << "\nServidor: ";
            do {
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if (*buffer == '#') {
                    send(server, buffer, bufsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');
            cout << endl;
            cout << "Cliente: ";
            do {
                recv(server, buffer, bufsize, 0);
                cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer == '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);

        /*
            Una vez que la conexión ya ha sido establecida, ambos extremos pueden
            leer y escribir en la conexión. Naturalmente, cualquier cosa escrita por el
            cliente será leido por el servidor, y cualquier cosa escrita por el servidor
            será leida por el cliente.

        /* ------------ Llamada de Cierre ------------- */
        /* ----------------- close() --------------- */

        /*
            Una vez que el servidor presione # para terminar la conexión, el bucle se
            romperá y la conexión con el servidor socket y la conexión con el cliente
            se acabará.
        */

        // inet_ntoa convierte datos de paquetes en IP, las cuales han sido tomadas del cliente
        cout << "\n\n=> Conexión terminada con la IP " << inet_ntoa(server_direccion.sin_addr);
        close(server);
        cout << "\nHasta luego..." << endl;
        isExit = false;
        exit(1);
    }

    close(client);
    return 0;
}
