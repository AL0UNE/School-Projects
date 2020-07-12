#pragma once
#include<vector> 
#include <iostream>
#include <fstream>
#include"vecteur.hpp"
#include <ctime>
#include<math.h>
#include"GradientConjugue.hpp"


std::vector<std::vector<int> >recouvrement(int l,int r,int n);
class DenseMatrix{
private:
  int nr_;
  int nc_;
  std::vector<double> val_;
  std::vector<double> resvec;
  double time;
public: 
  DenseMatrix();// Constructeur par défault
  DenseMatrix (const int &nr,const int &nc); 
  DenseMatrix (const DenseMatrix &M); // Constructeur par recopie
  DenseMatrix(const int &nr,const int &nc,const std::vector<double> &val);
  DenseMatrix(const int &numberMat);//Constructeur a partir d'un fichier
  void operator=(const DenseMatrix &m); //surcharge de l'operateur +
  ~DenseMatrix(); // Destructeur
  int row()const;//renvoie valeur de nr_
  int col()const;//renvoie valeur de nc_
  std::vector<double> residu()const;//renvoie le vecteur des résidus pour la méthode cg et pcg
  double temps()const;//renvoie le temps CPU pour cg et pcg
  double & operator()(int i,int j);//operateur d'accès 
  double operator()(int i,int j)const;
  friend std::ostream& operator<<(std::ostream &f,const DenseMatrix &D);//affichage
  DenseMatrix operator()(std::vector<int>Ir,std::vector<int>Ic)const;//Renvoie la sous-matrice extraite grâce à Ir/Ic
  void affiche()const;//Methode d'affichage
  void MvProd(const Vecteur &x,Vecteur &b)const;//stock dans b le produit de la matrice et de x
  void LUSolve(Vecteur &x,const Vecteur &b)const;//résoud Ax=b par la méthode Lu et stock le résultat dans x
  void test();// fonction permettant de construire la matrice de Laplace
  void cg(Vecteur &x,const Vecteur &b,double tol,int maxit);//résoud Ax=b par la méthode du gradient conjugué et stock le résultat dans x
  void pcg(Vecteur &x,const Vecteur &b,double tol,int maxit,const std::vector<std::vector<int> > &inc);//résoud Ax=b par la méthode du gradient conjugué précondionné et stock le résultat dans x
  DenseMatrix operator*(const double &alpha);//multiplication de la matrice par un scalaire
 
};

