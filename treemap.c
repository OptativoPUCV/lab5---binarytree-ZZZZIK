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
    if (tree-> lower_than(key, tree->current->pair->key) == 1){
      if (tree->current->left==NULL){
        tree->current->left=nuevo_nodo;
        nuevo_nodo->parent=tree->current;
      }
      tree->current=tree->current->left;
    }
  }
}

/*
4.- Implemente la función TreeNode * minimum(TreeNode * x). Esta función retorna el **nodo con la mínima clave** ubicado en el subárbol con raiz x. Para obtener el nodo tiene que, a partir del nodo x, irse por la rama izquierda hasta llegar al final del subárbol. Si x no tiene hijo izquierdo se retorna el mismo nodo.
   
    TreeNode * minimum(TreeNode * x){|
        return NULL;
    }
*/

TreeNode * minimum(TreeNode * x){
  if (x==NULL){
    return NULL;
  }
  while (x->left != NULL) {
    x = x->left;
  }  
  return x;
}

/*
5.- Implemente la función void removeNode(TreeMap * tree, TreeNode* node). Esta función elimina el nodo *node* del árbol *tree*. Recuerde que para eliminar un node existen 3 casos:
**Nodo sin hijos:** Se anula el puntero del padre que apuntaba al nodo
**Nodo con un hijo:** El padre del nodo pasa a ser padre de su hijo
**Nodo con dos hijos:** Descienda al hijo derecho y obtenga el menor nodo del subárbol (con la función minimum). Reemplace los datos (key,value) de *node* con los del nodo "minimum". Elimine el nodo minimum (para hacerlo puede usar la misma función *removeNode*).

    void removeNode(TreeMap * tree, TreeNode* node) {


    }

La función removeNode será usada por la función *eraseTreeMap* para eliminar datos del árbol usando la clave.

    void eraseTreeMap(TreeMap * tree, void* key){
        if (tree == NULL || tree->root == NULL) return;
        if (searchTreeMap(tree, key) == NULL) return;
        TreeNode* node = tree->current;
        removeNode(tree, node);
    } 


*/





void removeNode(TreeMap * tree, TreeNode* node) {
  if(node==NULL) return;

  // SIN HIJOS
  if(node->left==NULL&&node->right==NULL){
    
    if(node->parent==NULL) 
      tree->root=NULL;    
      
    else if (node->parent->left==node) 
      node->parent->left=NULL;
      
    else 
      node->parent->right=NULL;
  }

  // UN HIJO
  else if(node->left==NULL || node->right==NULL){
    TreeNode* aux_hijo=NULL;
    
    if (node->left!=NULL) 
      aux_hijo=node->left;
      
    else 
      aux_hijo=node->right;
    
    if(node->parent==NULL) 
      tree->root=aux_hijo;
      
    else if (node->parent->left==node) 
      node->parent->left= aux_hijo;
      
    else 
      node->parent->right=aux_hijo;

    if(aux_hijo!=NULL)
      aux_hijo->parent=node->parent;
  }
  
// DOS HIJOS
  else{
    while(node->right->left != NULL){
      node->right= node->right->left;
    }
    node->pair->key = node->right->pair->key;
    node->pair->value = node->right->pair->value;
    
    if(node->right->parent->left==node->right){
      node->right->parent->left= node->right->right;      
    }
    else{
      node->right->parent->right = node->right->right;
    }
    if(node->right->right!=NULL){
      node->right->right->parent=node->right->parent;
    }
  }
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

/*
7.- La función Pair* upperBound(TreeMap* tree, void* key) retorna el **Pair** con clave igual a key. En caso de no encontrarlo retorna el primer par asociado a una clave mayor o igual a key. 
Para implementarla puede realizar una búsqueda normal y usar un puntero a nodo auxiliar ub_node que vaya guardando el nodo con la menor clave *mayor o igual a key*. Finalmente retorne el par del nodo ub\_node.
    Pair* upperBound(TreeMap* tree, void* key){
    }
*/

Pair* upperBound(TreeMap* tree, void* key) {
  Pair *Nodo_ub=NULL;
  TreeNode *nodo=tree->root;
  
  while(nodo!=NULL){
    //if(nodo==NULL) return NULL;
    
    else{  
        if(tree->lower_than(nodo->pair->key,key)==0){
          Nodo_ub = nodo->pair;
          nodo = nodo->left;
        }else{
          nodo=nodo->right;
        }
    }
  }
  return Nodo_ub;
}

  
Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
