#pragma once
#include<vector> 


class Vecteur{
private:
  int N_;
  std::vector<double> coef_;
public: 
  Vecteur (); //Constructeur par défault
  Vecteur (int N);//Construit un vecteur nul de taille N
  Vecteur (const Vecteur &v);//Constructeur par recopie
  ~Vecteur()=default;//Destructeur 
  int taille()const;//renvoie la taille du vecteur
  void affiche()const;//méthode d'affichage
  void permute(int i, int j);//permute les coefficients i et j du vecteur
  double norme()const;//calcul la norme d'un vecteur 
  double & operator()(int i);//accés a la ieme coordonnées du vecteur 
  double operator()(int i)const;
  Vecteur operator+(const Vecteur &v)const;//addition de deux vecteurs
  void operator+=(const Vecteur &v);
  Vecteur operator-(const Vecteur &v)const;//soustraction de deux vecteurs
  Vecteur operator*(double alpha) const;//multiplication d'un vecteur par un scalaire
  double operator*(const Vecteur &v)const;//produit scalaire
  void operator=(const Vecteur &v);//surcharge de l'opérateur par recopie
  
};
