
#include<vector> 
#include"vecteur.hpp"
#include <ctime>
#include "matriceDense.hpp"


class Block{
private:
  int nr_;
  int nc_;
  std::vector<int> Ir_;
  std::vector<int> Ic_;
  DenseMatrix mat;
public: 
  Block(); //constructeur par défault
  Block (const int &nr,const int &nc,const std::vector<int> &Ir,const std::vector<int> &Ic);  
  Block (const Block &m); //constructeur par recopie
  void operator=(const Block &m); 
  void getMat(DenseMatrix m); //fonction qui récupère la matrice m et l'affecte à mat
  ~Block();//Destructeur
  void MvProd(const Vecteur &x,Vecteur &b);//effectue le produit matrice vecteur et stock le résultat dans b
  void MvProdInv(const Vecteur &x,Vecteur &b);//effectue le produit matrice vecteur avec l'inverse de la matrice et stock le résultat dans b
  void affiche()const;//méthode d'affichage
 
};
