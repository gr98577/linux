//#include <stdio.h>
//#include <unistd.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(pblock, int, proto, int, dir, unsigned short, port){
  if (!rbSearch(&mytree, proto, dir, port)){
    rbInsert(&mytree, proto, dir, port);
  }
  else{
    perror("Port w/ direction and protocol already exist in block list.\n");
    return -1;
  }
  
}
