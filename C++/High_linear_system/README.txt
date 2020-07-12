README 

Projet 4M053
Balendran Alan

//////////////////Contenu du projet/////////////////:

-un fichier main permettant de comparer la vitesse de convergence entre les deux méthodes grâce aux matrices disponibles

-un dossier mat contenant les 15 matrices de test

-un dossier src contenant 7 fichiers cpp:
   -vecteur.cpp modélisant les vecteurs
   -matriceDense.cpp modélisant les SparceMatrix
   -direct_solvers.cpp regroupant les algorithmes de résolution par remontée et descentes(nécessaire pour LU)
   -GradientConjugue.cpp permettant la résolution par la méthode du gradient conjugué
   -fonction.cpp contenant notamment la fonction qui construit le recouvrement de N ainsi que l'écriture du fichier pour tracer les 2 courbes
   -block.cpp modélisant la structure Block
   -blockmatrice.cpp modélisant la structure BlockMatrix

-un dossier include contenant les différents entêtes des fichiers .cpp
   
-un fichier MAKEFILE permettant de compiler les fichiers

-3 fichiers test permettant de tester les 3 structures


///////////////EXECUTION DU MAIN/////////
pour visualiser la différence entre les deux méthodes:
 -taper ./run.sh dans le terminal
 -choisir un entier en 1 et 1 et 15
 -ouvrir gnuplot avec la commande gnuplot
 -taper set logscale xy
 -taper set title "Comparaison PCG/CG"
 -taper plot "graph.txt" using 1:2 with linespoints title "Cg", "graph.txt" using 1:3 with linespoints title "Pcg" 




////////////////PARTIE TEST///////////
pour effectuer un test:
taper make dans le terminal puis bin/"le nom du fichier a tester"



