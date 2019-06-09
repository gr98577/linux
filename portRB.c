#include <linux/portRB.h>
#include <stdbool.h>


static struct rbNode *rbSearch(struct rb_root* root, int proto, int dir, unsigned short port){

  struct rb_node *node = root->rb_node;

  while(node){
    struct rbNode *data = container_of(node, struct rbNode, node);
    
    if(port > data->port && proto == data->proto && dir == data->dir){ node = node->rb_right; }
    else if(port < data->port && proto == data->proto && dir == data->dir){ node = node->rb_left; }
    else{ return data; }

  }
  return NULL;
  
}

static bool rbInsert(struct rb_root* root, struct rbNode data){
  struct rb_node **new = &(root->rb_node), *parent = NULL;

  while(*new){
    struct rbNode *this = container_of(*new, struct rbNode, node);

    parent = *new;
    if(data.port < this->port){ new = &((*new)->rb_left); }
    else if(data.port > this->port){ new = &((*new)->rb_right); }
    else{return false;}
  }

  rb_link_node(&(data.node), parent, new);
  rb_insert_color(&(data.node), root);

  return true;
  
}

static void rbErase(struct rbNode* dt, struct rb_root *tree){
  //  struct rbNode *data = rbSearch(&mytree, dt->proto, dt->dir, dt->port);

  /*  if(data){
    rbErase(&(data), &mytree);
    free(data);
    }*/

}

