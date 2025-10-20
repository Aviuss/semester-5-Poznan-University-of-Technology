// kompilacja: gcc <nazwa tego pliku> -Wall -o <nazwa pliku  wynikowego>
// nadanie uprawnieĹ do uruchomienia pliku wynikowego: chmod +x <nazwa pliku wynikowego>
// uruchomienie: ./<nazwa pliku wynikowego>

//TODO doĹÄczenie wymaganych plikĂłw nagĹĂłwkowych
// poszukaÄ w man <nazwa funkcji> i w man 7 ip
// ewentualnie przy kompilacji z -Wall moĹźe pojawiÄ siÄ 
// sugestia, wskazujÄca ktĂłrego pliku nagĹĂłwkowego brakuje

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
  // args: adres i port
  if (argc != 3) {
    perror("Wrong numbers of arguments. Type as first address, and second port. Eg. ./zadanie3.o 127.0.0.1 1100");
    exit(EXIT_FAILURE);
  }
  char* addr = argv[1];
  int port = atoi(argv[2]);

  // utworzyliśmy gniazdo
	int my_socket = socket(AF_INET, SOCK_STREAM, 0); // IPPROTO_TCP
  if (my_socket == -1) {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof server_addr); // wypełniamy zerami
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(addr);
  server_addr.sin_port = htons(port);

  if (connect(my_socket, (struct sockaddr *)&server_addr, sizeof server_addr) == -1) {
    perror("cannot connect");
    close(my_socket);
    exit(EXIT_FAILURE);
  } else {
    printf("Connected \n");
  }

  
  //read
  char buff[256];
  bzero(buff, 256);
  int n = read(my_socket, buff, sizeof buff);
  
  printf(" %i \n", n);
  printf(" %s \n", buff);

	close(my_socket);
  return EXIT_SUCCESS;
}

// gcc -Wall zadanie3.c -o zadanie3.o
// ./server.o (wymaga daytimeServer.c)
// ./zadanie3.o
// pokazuje dzisiejszą datę
