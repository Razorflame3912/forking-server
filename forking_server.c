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
  signal(SIGINT,sighandler);
  while(1){
    int to_client;
    int wkp = server_setup();
    int f = fork();
    if(!f){
      subserver(wkp);
    }
    else{
    }
  }
}

void subserver(int from_client) {
  int downstream = server_connect(from_client);
  char buffer[BUFFER_SIZE];
  while(1){
    read(from_client, buffer, sizeof(buffer));
    process(buffer);
    write(downstream,buffer, sizeof(buffer));
  }
  
}

void process(char * s) {
  int i = 0;
  while(s[i]){
    s[i] = toupper(s[i]);
    i++;
  }
}
