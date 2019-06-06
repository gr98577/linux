#ifndef PORTRB_H_
#define PORTRB_H_

#include <linux/rbtree.h>
#include <stdbool.h>

struct rbNode{
  struct rb_node node;
  int proto, dir;
  unsigned short port;
};



struct rbNode *rbSearch(struct rb_root* root, int proto, int dir, unsigned short port){

  struct rb_node *node = root->rb_node;

  while(node){
    struct rbNode *data = container_of(node, struct rbNode, node);
    
    if(port > data->port){ node = node->rb_right; }
    else if(port < data->port){ node = node->rb_left; }
    else{ return data; }

  }
  return NULL;
  
}

bool rbInsert(struct rb_root* root, struct rbNode* data){
  struct rb_node **new = &(root->rb_node), *parent = NULL;

  while(*new){
    struct rbNode *this = container_of(*new, struct rbNode, node);

    parent = *new;
    if(data->port < this->port){ new = &((*new)->rb_left); }
    else if(data->port > this->port){ new = &((*new)->rb_right); }
    else{return false;}
  }

  rb_link_node(&(data->node), parent, new);
  rb_insert_color(&(data->node), root);

  return true;
  
}

void rbErase(struct rbNode* dt, struct rb_root *tree){
  struct rbNode *data = rbSearch(&mytree, dt->proto, dt->dir, dt->port);

  /*  if(data){
    rbErase(&(data), &mytree);
    free(data);
    }*/

}
#endif
