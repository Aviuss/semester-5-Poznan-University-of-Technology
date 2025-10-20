#include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <time.h>

  int main(void)
  {
    struct sockaddr_in sa;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
    time_t sec;
    sec=time(NULL);
    printf("%s",ctime(&sec));
    printf("Server Start");

    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(1100);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(SocketFD,(struct sockaddr *)&sa, sizeof sa) == -1) {
      perror("bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    if (listen(SocketFD, 10) == -1) {
      perror("listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

 for (;;) {
      int ConnectFD = accept(SocketFD, NULL, NULL);

      if (ConnectFD == -1) {
        perror("accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }

     char buff[256];
     time(&sec);
     struct tm *timeinfo=localtime(&sec);

     strftime(buff, sizeof(buff)-1,"%d.%m.%y_%H:%M:%S",timeinfo);
     write(ConnectFD,buff,strlen(buff));

     close(ConnectFD);
    }

    close(SocketFD);
    return EXIT_SUCCESS;  
}

// gcc -Wall daytimeServer.c -o server.out
