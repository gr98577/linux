#ifndef PORTRB_H_
#define PORTRB_H_

#include <linux/rbtree.h>
#include <stdbool.h>


static struct rb_root mytree = RB_ROOT;

struct rbNode{
  struct rb_node node;
  int proto, dir;
  unsigned short port;
};



static struct rbNode *rbSearch(struct rb_root* root, int proto, int dir, unsigned short port);

static bool rbInsert(struct rb_root* root, struct rbNode data);

static void rbErase(struct rbNode* dt, struct rb_root *tree);
#endif
