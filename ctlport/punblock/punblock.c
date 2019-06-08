//#include <stdio.h>
//#include <unistd.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(punblock, int, proto, int dir, unsigned short port){
  if(!rbSearch(&mytree, proto, dir, port)){
    return -ENOENT;
  }
    else{
      perrror("Only need to implement the free for the tree structure.\n");
      return 0;
    }
}
