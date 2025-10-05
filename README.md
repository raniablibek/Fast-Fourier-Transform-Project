#            # Projet FFT - Multiplication de Polynômes

 



## Introduction:
Ce projet implémente la multiplication de polynômes à l'aide de l'algorithme FFT (Fast Fourier Transform).
 L'objectif global de ce projet  est d'explorer et de comparer les performances des algorithmes de multiplication de polynômes, en mettant en œuvre des concepts tels que les nombres complexes, la FFT, et en mesurant leur efficacité en fonction de la taille des polynômes.
 Les algorithmes utilisés sont : la multiplication naive  et la multiplication  avec fft.

 ## Compilation

Pour compiler le code, vous aurez besoin d'un compilateur C tel que gcc. Utilisez le fichier Makefile fourni en utilisant la commande suivante :

```bash
make
```

## Exécution

Une fois compilé, vous pouvez exécuter le programme en utilisant la commande suivante :


```bash
./programme
```

Lors de l'éxécution vous aurez un menu intéractif  qui permet de choisir l'operation à effectuer :
```bash
1. Multiplication naive 
2. multiplication avec FFT 
3. Test et temps execution
4. exit
```
Pour les deux premiers choix vous serez amenés à suivre les instructions du programme pour saisir les degrés et coefficients des polynômes, puis observez les résultats de la multiplication ainsi le temps pris par l'algorithme .
Voila ce qui vous sera affiché :
```bash
Entrez le degré du polynôme P
Saisissez les coefficients du polynôme Q, du terme constant au terme de plus haut degré
Entrez le degré du polynôme Q

Saisissez les coefficients du polynôme P, du terme constant au terme de plus haut degré
Résultat de la multiplication : 
La multiplication naive  a pris 
```

Parlons du choix 3 qui est **test et affichage** ; on génére des polynomes aléatoires  de la taille desirée à l'aide de la fonction 
**polynome_aleatoire** et par la suite faire la multiplication naive et avec fft ; le temps d'execution sera stocké dans deux fichiers **time_naive.txt** et  **time_fft.txt** et par la suite deux graphes seront affichés à l'utilisateur le temps pris par l'algorithme en fonction de la taille des polynomes et cette tache est effectuée par la fontion **time_affichage**.

# Nettoyage

Pour nettoyer les fichiers générés lors de la compilation, utilisez la commande suivante :

```bash

make clean
```

# Dépendances

Le projet dépend des bibliothèques standard C, il n'y a pas de dépendances externes.


# Auteur 

**IDRES AMINE**
**BLIBEK RANIA**  

   
