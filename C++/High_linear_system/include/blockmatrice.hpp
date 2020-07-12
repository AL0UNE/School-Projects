
#include<vector> 
#include"vecteur.hpp"
#include <ctime>
#include "matriceDense.hpp"
#include"block.hpp"


class BlockMatrix{
private:
  int nr_;
  int nc_;
  std::vector<Block>val_; 
public: 
  BlockMatrix();//Constructeur par défault
  ~BlockMatrix();//Destructeur
  BlockMatrix (const int &nr,const int &nc);//intialise nr_ et nc_ avec nr/nc et iniatilise val au vecteur vide
  BlockMatrix (const BlockMatrix &m); //Constructeur par recopie
  void operator=(const BlockMatrix &m);//surchage de l'opérateur par recopie
  void operator+=(const Block &b);//ajoute le Block b au vecteur val_
  void MinRes( Vecteur &x,const Vecteur &b,const double &tol);//résoud Ax=b par MinRes et stock le résultat dans x
  void MvProd(const Vecteur &x,Vecteur &b);//effectue le produit matrice Vecteur A*x et stock le résultat dans b
  void MvProdInv(const Vecteur &x,Vecteur &b);//effectue le produit matrice Vecteur (A')*x avec A' l'inverse de A et stock le résultat dans b
  void Extract(const DenseMatrix &m,const std::vector<std::vector<int> > &Iq);//rempli val avec des Block qui pour chaque element dans IQ va extraire la sous matrice de A 
  void affiche()const;//méthode d'affichage
};
