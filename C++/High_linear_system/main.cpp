#include <iostream>
#include<fstream>
#include "vecteur.hpp"
#include "matriceDense.hpp"
#include "blockmatrice.hpp"
#include"GradientConjugue.hpp"
#include "fonction.hpp"
#include <ctime>
#include<math.h>
#include <assert.h>
using namespace std;
int main(){

 cout<<"Saisir un entier pour le choix de la matrice (1 à 15)"<<endl;
 
 int numero;
 cin >> numero;
 assert(numero<=15 && numero>=0);//choix de la matrice par l'utilisateur

 DenseMatrix MMM(numero);//création de la matrice
 int n=MMM.row();

 Vecteur V1(n);//b
 Vecteur V2,V3;
 for(int i=0;i<V1.taille();i++)V1(i)=rand()%1000;//b est remplie aléatoirement

 vector<vector<int> >test=recouvrement(25,2,n);//recouvrement 
 vector<double>rcg,rpcg;
 
 MMM.cg(V2,V1,1E-7,10000);
 rcg=MMM.residu();//vecteur des résidus CG
 MMM.pcg(V3,V1,1E-7,10000,test);
 rpcg=MMM.residu();//vecteur des résidus PCG

 graph(rpcg,rcg);//ecriture du fichier pour le tracé des 2 courbes




 }

