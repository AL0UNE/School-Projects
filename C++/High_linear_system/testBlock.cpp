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
  cout<<"testBlock"<<endl;
  DenseMatrix D(5,5);
  D.test();
  vector<int>vec{1,2,3};
  vector<int>vec1{0,1,2,3,4};
  /////////
  Block B(4,5,vec,vec);
  cout<<"Block B = "<<endl;
  B.affiche();
  /////////
  Block B1(5,5,vec1,vec1);
  cout<<"Block B1 = "<<endl;
  B1.affiche();
  B=B1;
  cout<<"Block B = "<<endl;
  B.affiche();
  /////////
  B.getMat(D);
Vecteur V(5);
 for(int i=0;i<5;i++)V(i)=1;
  cout<<"V = ";
  V.affiche();
  Vecteur V1;
  B.MvProd(V,V1);
  cout<<"B*V = "<<endl;
  V1.affiche();
  cout<<endl;
  ///////////
 Block B2(15,15,vector<int>{1,2,3,4},vector<int>{1,2,3,4});
 B2.getMat(D);
 B2.affiche();
 cout<<endl;
 B.MvProdInv(V,V1);
 cout<<"Resultat de MvProd(V,V1)= ";
 V1.affiche();
 //V2.affiche();
 // test.clear();

  


}

