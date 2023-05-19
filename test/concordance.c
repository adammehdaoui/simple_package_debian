#include "concordance.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

node *create_node(char *word, node *left, node *right) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->left = left;
    new_node->right = right;
    new_node->word = (char *)malloc((strlen(word)+1)*sizeof(char));
    strcpy(new_node->word, word);
    return new_node;
}

int equal(char *s1, char *s2) {
    return strcmp(s1, s2) == 0;
}

int less(char *s1, char *s2) {
    return strcmp(s1, s2) < 0;
}

int more(char *s1, char *s2) {
    return strcmp(s1, s2) > 0;
}

node *insert_bst(node *t, char *word) { 
    if (t == NULL)
        t = create_node(word, NULL, NULL); 
    else if (less(word, t->word))
        t->left = insert_bst(t->left, word);
    else if (more(word, t->word))
        t->right = insert_bst(t->right, word);
    return t;
}

/* Choix d'un affichage de ordre infixe qui représente l'ordre lexicographique
pour une arbre binaire de recherche */
void display_lexico(node *t){
  if(t == NULL){
    return;
  }
  display_lexico(t->left);
  fprintf(stdout, "%s ", t->word);
  display_lexico(t->right);
}

void display_lexico_between(node *t, char *word1, char *word2){
    if(t == NULL){
        return;
    }
    display_lexico_between(t->left, word1, word2);
    if(more(t->word, word1) && less(t->word, word2)){
        fprintf(stdout, "%s ", t->word);
    }
    display_lexico_between(t->right, word1, word2);
}

/* Version des fonctions de visual_tree.c mais pour afficher des noeuds contenant
des chaînes de caractères */
FILE* write_begin(char *name) {
  FILE *f = fopen(name, "w");
  fprintf(f, "digraph tree {\n");
  fprintf(f, "  splines=false\n");
  fprintf(f, "  node [shape=record,height=.1]\n");
  fprintf(f, "  edge [tailclip=false, arrowtail=dot, dir=both];\n\n");
  return f;
}

void write_end(FILE *f) {
  fprintf(f, "\n}\n");
  fclose(f);
}

void write_node(FILE *f, node *n) {
  fprintf(f, "  n%p [label=\"<left> | <value> %s | <right>\"];\n", n, n->word);
}

void write_left_link(FILE *f, node *n) {
  fprintf(f, "  n%p:left:c -> n%p:value;\n", n, n->left);
}

void write_right_link(FILE *f, node *n) {
  fprintf(f, "  n%p:right:c -> n%p:value;\n", n, n->right);
}

void write_tree_aux(FILE *f, node *t) {
  if(t == NULL){
    return;
  }

  write_node(f,t);

  if(t->left != NULL){
    write_left_link(f,t);
    write_tree_aux(f,t->left);
  }

  if(t->right != NULL){
    write_right_link(f,t);
    write_tree_aux(f,t->right);
  }
}

void write_tree(node *t) {
  FILE *f;
  f = write_begin("current-tree.dot");
  write_tree_aux(f, t);
  write_end(f);
  system("dot -Tpdf current-tree.dot > current-tree.pdf");
}