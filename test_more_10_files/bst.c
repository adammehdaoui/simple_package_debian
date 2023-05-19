#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

node *find_bst(node*t, int elt){
    if(t == NULL){
        return NULL;
    }
    if(elt == t->data){
        return t;
    }
    else if(elt > t->data){
        return find_bst(t->right, elt);
    }
    else if(elt < t->data){
        return find_bst(t->left, elt);
    }
    return NULL;
}

node *insert_bst(node *t, int elt) { 
    if (t == NULL)
        t = create_node(elt, NULL, NULL); 
    else if (t->data > elt)
        t->left = insert_bst(t->left, elt); 
    else if (t->data < elt)
        t->right = insert_bst(t->right, elt); 
    return t;
}

node *random_bst(long N){
    long range = 2*N;
    node *bst = NULL;
    
    for(long i=0; i<N; i++){
        bst = insert_bst(bst, rand()%range);
    }

    return bst;
}

node *in_order_bst(long N){
    node *bst = NULL;

    for(int i=0; i<N; i++){
        bst = insert_bst(bst, i);
    }

    return bst;
}

node *extract_min_bst(node *t, node **min){
    if(t == NULL){
        return t;
    }

    if(t->left == NULL){
        *min = t;
        return t->right;
    }

    t->left = extract_min_bst(t->left, min);

    return t;
}

node *remove_bst(node *t, int elt){
    if(t == NULL){
        return t;
    }

    if(t->data == elt){
        if(t->left == NULL){
            node *tmp = t->right;
            free(t);
            return tmp;
        }
        else if(t->right == NULL){
            node *tmp = t->left;
            free(t);
            return tmp;
        }
        else{
            node *min = NULL;
            t->right = extract_min_bst(t->right, &min);
            min->left = t->left;
            min->right = t->right;
            free(t);
            return min;
        }
    }
    else if(t->data > elt){
        t->left = remove_bst(t->left, elt);
    }
    else if(t->data < elt){
        t->right = remove_bst(t->right, elt);
    }

    return t;
}
