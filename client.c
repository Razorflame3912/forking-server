#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo) {
  if (signo == SIGINT) {
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%d", getpid() );
    remove(buffer);
    exit(0);
  }
}


int main() {

  int to_server;
  int from_server;
  char buffer[BUFFER_SIZE];

  from_server = client_handshake( &to_server );

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
}
