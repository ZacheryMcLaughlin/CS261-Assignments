/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Zachery McLaughlin
 * Email: mclaughz@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* tree = (struct bst*) malloc(sizeof(struct bst));
  tree->root = NULL;
  return tree;
}

/* 
 * This function recursively traverses the left and right side of the BST
 * in order to free all of the keys. The bst node is then freed at the very
 * end
 * 
 * Params:
 *  node - the bst_node to traverse the actual keys in the bst
*/
void free_node(struct bst_node* node){
  if(node == NULL)
    return;
  free_node(node->left);
  free_node(node->right);

  free(node);
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should free up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  free_node(bst->root);
  free(bst);
  return;
}

/* 
 * This function traverses the bst and indexes the number of keys
 * in it to deduce the size of the bst. The function then returns
 * the size of the bst back to the user.
 * 
 * Params:
 *  node - the nodes in the bst to be traversed and indexed.
*/
int bst_findsize(struct bst_node* node){
  int l = 0;
  int r = 0;
  //printf("N: %d\n", node->key);
  if (node->left){
     l = bst_findsize(node->left);
  }
  if (node->right){
     r = bst_findsize(node->right);
  } 
  return r + l + 1;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  if (bst->root) {
    return bst_findsize(bst->root);
  } 
  else {
    return 0;
  }
}

/*
 * This function inserts keys and their values into different nodes
 * in the bst. This function recursively inserts keys by checking if other
 * nodes are already filled and then it checks if the new key being entered
 * is less than or greater than the key it is at. The key/value pair will
 * be entered when it reaches a NULL value.
 * 
 * Params:
 *  node - the individual bst node that will habour a key/value pair.
 *  key - the key to be checked to see if is not NULL
 *  value - the value held within the key
*/
void bst_insertkey(struct bst_node* node, int key, void* value){
  if (node){
    if (node->key > key){
      if (node->left){
        //printf("left\n");
        bst_insertkey(node->left, key, value);
      } else {
        node->left = (struct bst_node*) malloc(sizeof(struct bst_node));
        node->left->key = key;
        node->left->value = value;
      }
    } 
    else {
      if (node->right){
        //printf("right\n");
        bst_insertkey(node->right, key, value);
      } else {
        node->right = (struct bst_node*) malloc(sizeof(struct bst_node));
        node->right->key = key;
        node->right->value = value;
      }
    }
  }
  else {
    node = (struct bst_node*) malloc(sizeof(struct bst_node));
    node->key = key;
    node->value = value;
  }

 
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
 
  if (!bst->root) {
     //printf("made root\n");
     bst->root = (struct bst_node*) malloc(sizeof(struct bst_node));
     bst->root->key = key;
     bst->root->value = value;
  } else {
    //printf("1");
    bst_insertkey(bst->root, key, value);
  }
  //printf("%d", bst->root == NULL);
  
  return;
}

/*
 * This function retreives the specific keys and values within
 * different nodes. Helper function to main function bst_get.
 * 
 * Params:
 *  node - The specific node whose information is to be retreived.
 *  key - The specific key to be checked against.
*/
struct bst_node* _bst_getNode(struct bst_node* node, int key){
  if (node->key == key){
    return node;
  }
  if (node->key > key){
    if (node->left){
      return _bst_getNode(node->left, key);
    } else {
      return NULL;
    }
  } else {
     if (node->right){
      return _bst_getNode(node->right, key);
    } else {
      return NULL;
    }
  }

}

/*
 * This function finds the minimum value node and returns it.
 * 
 * Params:
 *  node - the node to be acquired and used to traverse the bst.
*/
struct bst_node* minValueNode(struct bst_node* node) 
{ 
    struct bst_node* cur = node; 
  
    /* loop down to find the leftmost leaf */
    while (cur && cur->left != NULL) 
        cur = cur->left; 
  
    return cur; 
} 

/*
 * This function removes specific keys within the bst and replaces them 
 * with the correct key below them. Helper function to bst_remove.
 * 
 * Params:
 *  node - the nodes to be used in order to traverse the BST and find
 *         correct keys to remove and replace.
 *  key - Used to check the node keys against in order to help the program
 *        to decide whether to move left or right in order to remove/replace.
*/
struct bst_node* bst_removekey(struct bst_node* node, int key){
  if(node == NULL){
    return node;
  }
  if(key < node->key){
    node->left = bst_removekey(node->left, key);
  }
  else if(key > node->key){
    node->right = bst_removekey(node->right, key);
  }
  else{
    if(node->left == NULL){
      struct bst_node *temp = node->right;\
      free(node);
      return temp;
    }
    else if(node->right == NULL){
      struct bst_node *temp = node->left;\
      free(node);
      return temp;
    }
    struct bst_node* temp = minValueNode(node->right);
    node->key = temp->key;
    node->value = temp->value;
    node->right = bst_removekey(node->right, temp->key);
  }
  return node;
}

//DEFUNCT REMOVE FUNCTION//

/*void bst_removekey(struct bst_node* rnode, struct bst_node* cnode){
  //printf("C: %d\n", cnode->key);
    //printf("R: %d\n", rnode->key);
  if (rnode == cnode){
    //printf("rigth\n");
    if(cnode->right){
      bst_removekey(rnode, cnode->right);
    }
    else if (cnode->left){
       bst_removekey(rnode, cnode->left);
    }
    else{
      //printf("p");
      rnode->key = cnode->key;
      rnode->value = cnode->value;
      
      free(cnode);
    }
  }    
  else{
    if(cnode->left){
      bst_removekey(rnode, cnode->left);
    }
    else if (cnode->right){
      bst_removekey(rnode, cnode->right);
    }
    else{
      //printf("k");
      rnode->key = cnode->key;
      rnode->value = cnode->value;
      
      free(cnode);
    }
  }
}*/

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  //printf("call\n");
  bst_removekey(bst->root, key);
}


/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  struct bst_node* b = _bst_getNode(bst->root, key);
  if (b){
    return b->value;
  } else {
    return NULL;
  }
 
}


  
