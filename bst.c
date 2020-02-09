#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// Functions
void bstree_insert_helper(BStree bst, int index, Key *key, Data data);
void bstree_traversal_helper(BStree bst, int index);

// Input: ’size’: size of an array
// Output: a pointer of type BStree,
//          i.e. a pointer to an allocated memory of BStree_struct type
// Effect: dynamically allocate memory of type BStree_struct
//          allocate memory for a Node array of size+1 for member tree_nodes
//          allocate memory for an unsigned int array of size+1 for member free_nodes
//          set member size to ’size’;
//          set entry free_nodes[i] to i
//          set member top to 1;
//          set member root to 0;
BStree bstree_ini(int size) {
    BStree bst = (BStree) malloc(sizeof(BStree_struct));
    (*bst).tree_nodes = (Node *) malloc((size+1)*sizeof(Node));
    (*bst).free_nodes = (unsigned int *) malloc((size+1)*sizeof(int));
    (*bst).size = size;
    for (int i = 0; i <= size; i++){
        (*bst).free_nodes[i] = i;
    }
    (*bst).top = 1;
    (*bst).root = 0;
    return bst;
}

// Input: ’bst’: a binary search tree
//          ’key’: a pointer to Key
//          ’data’: an integer
// Effect: ’data’ with ’key’ is inserted into ’bst’
//          if ’key’ is already in ’bst’, do nothing
void bstree_insert(BStree bst, Key *key, Data data) {
    bstree_insert_helper(bst, 1, key, data);
}

// Input: ’bst’: a binary search tree
//          ’key’: a pointer to Key
//          ’data’: an integer
//          'index': node position in tree node array - begins at 1 (the root node)
// Effect: ’data’ with ’key’ is inserted into ’bst’
//          if ’key’ is already in ’bst’, do nothing
void bstree_insert_helper(BStree bst, int index, Key *key, Data data){
    if (index >= (*bst).size){
        printf("Error: insertion is outside of array bound");
    } else {
        if ((*bst).free_nodes[index] == index){
            (*bst).tree_nodes[index].key = key;
            (*bst).tree_nodes[index].data = data;
            (*bst).tree_nodes[index].left = 2*index;
            (*bst).tree_nodes[index].right = (2*index)+1;
            (*bst).free_nodes[index] = 0;
            if (index >= (*bst).top){
                (*bst).top = index;
            }
        } else if ((key_comp(key, (*bst).tree_nodes[index].key)) < 0){
            bstree_insert_helper(bst, (*bst).tree_nodes[index].left, key, data);
        } else if ((key_comp(key, (*bst).tree_nodes[index].key)) > 0) {
            bstree_insert_helper(bst, (*bst).tree_nodes[index].right, key, data);
        }
    }
    
}

// Input: ’bst’: a binary search tree
// Effect: print all the nodes in bst using in order traversal
void bstree_traversal(BStree bst) {
    bstree_traversal_helper(bst, 1);
}

// Input: ’bst’: a binary search tree
//          'index' node position in tree node array - begins at 1 (the root node)
// Effect: print all the nodes in bst using in order traversal
void bstree_traversal_helper(BStree bst, int index) {
    if (index <= (*bst).top){
        if ((*bst).free_nodes[index] != index){
            bstree_traversal_helper(bst, (*bst).tree_nodes[index].left);
            print_node((*bst).tree_nodes[index]);
            bstree_traversal_helper(bst, (*bst).tree_nodes[index].right);
        }   
    }
}

// Input: ’bst’: a binary search tree
// Effect: all dynamic memory used by bst are freed
void bstree_free(BStree bst) {
    free((*bst).tree_nodes);
    free((*bst).free_nodes);
    free(bst);
}
