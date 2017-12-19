#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  int to_client;
  int wkp = server_setup();
  int f = fork();
  if(!f){
    subserver(server_handshake(&to_client));
  }
  else{
    wkp = server_setup();
  }
}

void subserver(int from_client) {
  int downstream = server_connect(from_client);
  while(1){
    read(from_client, buffer, BUFFER_SIZE);
    process(buffer);
    write(downstream,buffer, BUFFER_SIZE);
  }
  
}

void process(char * s) {
  int i = 0;
  while(s[i]){
    s[i] = toupper(s[i]);
    i++;
  }
}
