//#include <stdio.h>
//#include <unistd.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/portRB.h>

SYSCALL_DEFINE3(pblock, int, proto, int, dir, unsigned short, port){
  struct rbNode tmp;
  tmp.proto = proto;
  tmp.dir = dir;
  tmp.port = port;
  if (!rbSearch(&mytree, proto, dir, port)){
    rbInsert(&mytree, tmp);
  }
  else{
    printk("Already in there.");
    return -1;
  }
}
