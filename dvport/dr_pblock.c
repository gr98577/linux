#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <linux/portRB.h>

#define __NR_pblock 434

long pblock(int proto, int dir, unsigned short port){
  return syscall(__NR_pblock, proto, dir, port);
}

int main(int argc, char* argv[]){
  if(geteuid() != 0){
    perror("Insufficient privileges.\n");
    return -EACCES;
  }
  int proto, dir;
  unsigned short port;

  
  if(argc != 4){
    perror("Proper input: pblock protocol[tcp/udp] dir[in/out] port\n");
    return -1;
  }
  
  if(argv[1] == "tcp" || argv[1] == "udp"){
    if(argv[1] == "tcp")  proto = IPPROTO_TCP;
    else proto = IPPROTO_UDP;
  }
  else{
    perror("Proper input: pblock protocol[tcp/udp] dir[in/out] port\n");
    return -EINVAL;
  }
  
  if(argv[2] == "in" || argv[2] == "out"){
    if(argv[2] == "in") dir = 1;
    else dir = 0;
  }
  else{
    perror("Proper input: pblock protocol[tcp/udp] dir[in/out] port\n");
    return -EINVAL;
  }

  if(atoi(argv[3]) > 65535 || atoi(argv[3]) < 1){
    perror("Proper input: pblock protocol[tcp/udp] dir[in/out] port\n");
    return -EINVAL;
  }
  else{
    port = atoi(argv[3]);
  }

  if(!rbSearch(proto, dir, port)){
    rbInsert(&mytree, proto, dir, port);
    return 0;
  }
  else{
    perror("Entry already exists in list.\n");
    return -1;
  }
  
  
}
