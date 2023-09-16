#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
/*
1.- Implemente la función *createTreeMap* en el archivo treemap.c. Esta función recibe la función de comparación de claves y crea un mapa (TreeMap) inicializando sus variables. 
El siguiente código muestra como inicializar la función de comparación. Reserve memoria, inicialice el resto de variables y retorne el mapa.
*/

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {  
  TreeMap *mapa=(TreeMap*) malloc(sizeof(TreeMap));
  if(lower_than==NULL) return NULL;
  mapa->lower_than = lower_than;
  return mapa;
}
/*
3.- Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).

    void insertTreeMap(TreeMap* tree, void* key, void* value){
    }
*/

void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode *nuevo_nodo = createTreeNode(key,value);
  
  if (tree->root == NULL) {
    tree->root = nuevo_nodo;
    tree->current = nuevo_nodo;
    return;
  }

  tree->current = tree->root;
  
  while(1){
    
    if(tree->current==NULL) break;
    
    if (is_equal(tree, key, tree->current->pair->key)) return;

    //DERECHA
    if (tree->lower_than(key, tree->current->pair->key)!=1){
      if(tree->current->right==NULL){
        tree->current->right=nuevo_nodo;
        nuevo_nodo->parent=tree->current;
      }
      tree->current=tree->current->right;
    }
    //IZQUIERDA
    else{
    //if (tree-> lower_than(key, tree->current->pair->key) == 1){
      if (tree->current->left==NULL){
        tree->current->left=nuevo_nodo;
        nuevo_nodo->parent=tree->current;
      }
      tree->current=tree->current->left;
    }
  }
}
TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

/*
2.- Implemente la función Pair* searchTreeMap(TreeMap* tree, void* key), la cual busca el nodo con clave igual a key y retorna el **Pair** asociado al nodo. Si no se encuentra la clave retorna NULL.
Recuerde hacer que el current apunte al nodo encontrado.
    Pair* searchTreeMap(TreeMap* tree, void* key) {
        return NULL;
    }
*/


Pair* searchTreeMap(TreeMap* tree, void* key) {
  TreeNode* nodo=tree->root;

  while (nodo!=NULL) {
    if ((is_equal(tree,key, nodo->pair->key)) == 1) {
      tree->current=nodo;
      return nodo->pair;
    }
    if ((tree->lower_than(key, nodo->pair->key))==1) {
      nodo=nodo->left;
    }
    else{
      nodo=nodo->right;
    }
  }
  tree->current=NULL;
  return NULL;
}



Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
