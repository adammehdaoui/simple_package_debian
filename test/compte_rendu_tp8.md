# Compte-rendu TP8 : Arbres binaires de recherche

## Exercice 4 : Chronométrage

### 1. Créer une fonction qui insère N entiers aléatoires (entre 0 et 2*N, par exemple) dans un arbre vide. <br> Mesurer le temps utilisé et la hauteur de l'arbre créé. <br> Combien d'éléments pouvez-vous insérer en 10 secondes ?

En insertion aléatoire, on peut insérer environ 7.000.000 d'éléments avec une hauteur de 60 environ en 10 secondes.
La différence entre la valeur voulue d'insertion voulue (la valeur que l'on a indiqué dans le code est 6.250.000) s'explique par le fait que l'on peut tomber de fois sur la même valeur en tirant de manière aléatoire, or, on ne peut pas insérer deux fois la même valeur dans un arbre binaire de recherche.

### 2. Répondre à la même question en insérant les entiers 1, 2 jusqu'à N en ordre.

En insertion en ordre, on peut insérer environ 37.500 éléments avec une hauteur de 37.500 également en 10 secondes.

> Cette différence entre les deux insertions peut s'expliquer par le fait que l'insertion en ordre insert des valeurs de plus en plus grandes, la fonction doit donc descendre de plus en plus profondément dans l'arbre pour insérer les valeurs, ce qui prend plus de temps.