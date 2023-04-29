#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap *arbol = (TreeMap*)malloc(sizeof(TreeMap));
  if(arbol == NULL) return NULL;
  arbol->lower_than = lower_than;
  return arbol;
    //new->lower_than = lower_than;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  tree->current = tree->root;
  if(tree->current == NULL)
  {
    tree->current = createTreeNode(key,value);
  }
  while(tree->current != NULL)
    {
      if(is_equal(tree,tree->current->pair->key, key)== 1) return;

      if(tree->lower_than(tree->current->pair->key,key)==1)
      {
        if(tree->current->right == NULL)
        {
          tree->current->right = createTreeNode(key,value);
          tree->current->right->parent = tree->current;
          tree->current = tree->current->right;
          return;
        }
        tree->current = tree->current->right;
      }
      else
      {
        if(tree->current->left == NULL)
        {
          tree->current->left = createTreeNode(key,value);
          tree->current->left->parent = tree->current;
          tree->current = tree->current->left;
          return;
        }
        tree->current = tree->current->left;
      }
    }
  //tree->current = createTreeNode(key,value);
}

TreeNode * minimum(TreeNode * x){
  
  while(x != NULL)
    {
      if(x->left == NULL) return x;
      x = x->left;
    }
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node->left == NULL && node->right == NULL)
  {
    node->parent = NULL;
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  if(tree->current == NULL) return NULL;
  while(tree->current != NULL)
    {
      if(is_equal(tree, key, tree->current->pair->key)== 1) return tree->current->pair;
      if(tree->lower_than(key,tree->current->pair->key)==1)
      {
        tree->current = tree->current->left;
      }
      else
      {
        tree->current = tree->current->right;
      }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  tree->current = tree->root;
  Pair *aux = NULL;
  while(tree->current != NULL)
    {
      if(tree->lower_than(tree->current->pair->key,key)!=1)
      {
        aux = tree->current->pair;
        tree->current = tree->current->left;
      }
      else
      {
        tree->current = tree->current->right;
      }
    }
  return aux;
  //return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  
  tree->current = tree->root;
  while(true)
    {
      if(tree->current->left == NULL)return tree->current->pair;
      tree->current = tree->current->left;
    }
  
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
  if (tree == NULL) return NULL;
  
  if(tree->current->right != NULL)
  {
    tree->current = tree->current->right;
    return tree->current->pair;
  }
  else
  {
    while(tree->current->parent != NULL)
      {
        if(tree->current->parent == NULL) return NULL;
        else if(tree->lower_than(tree->current->pair->key,tree->current->parent->pair->key)== 1)
        {
          tree->current = tree->current->parent;
          return tree->current->pair;
        }
        else if (tree->lower_than(tree->current->pair->key,tree->current->parent->pair->key)== 1)
        {
          tree->current = tree->current->parent;
        }
        else{
          return tree->current->pair;
        }
      }
  }
  if(tree->current == tree->root)
  {
    return tree->current->left->pair;
  }
    return NULL;
}
