#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <linux/socket.h>


#define __NR_pblock 434

long pblock_syscall(int proto, int dir, unsigned short port){
  return syscall(__NR_pblock, proto, dir, port);
}

int main(int argc, char* argv[]){
  
  if(geteuid() != 0){
    perror("Insufficient privileges.\n");
    return -EACCES;
  }
  int proto, dir;
  unsigned short port;
  const char* tcp = "tcp";
  const char* udp = "udp";
  const char* in = "in";
  const char* out = "out";
  
  if(argc != 4){
    perror("Proper input: pblock protocol[tcp/udp] dir[in/out] port\n");
    return -1;
  }
  
  
  if(strcmp(argv[1],tcp) == 0 || strcmp(argv[1],udp) == 0){
    if(strcmp(argv[1],tcp) == 0)  proto = IPPROTO_TCP;
    else proto = IPPROTO_UDP;
  }
  else{
    perror("Proper input: pblock protocol[tcp/udp] dir[in/out] port\n");
    return -EINVAL;
  }
  
  if(strcmp(argv[2],in) == 0 || strcmp(argv[2],out) == 0){
    if(strcmp(argv[2],in)) dir = 1;
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

  pblock_syscall(proto, dir, port);
  
  
}
