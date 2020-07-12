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
  cout<<"testMatrix"<<endl;
  DenseMatrix A(4,5);
  cout<<"A = "<<endl;
  cout<<A<<endl;
  ///////
  DenseMatrix B(5,5);
  B(0,1)=4;
  cout<<"B = "<<endl;
  cout<<B<<endl;
  A=B;
  cout<<"A=B ="<<endl;
  cout <<A<<endl;
  ////////
  Vecteur V(5);
  V(0)=1;
  V(1)=1;
  V(2)=1;
  V(3)=1;
  V(4)=1;
  Vecteur V1(4);
  A.MvProd(V,V1);
  cout<<"V= ";
  V.affiche();
  cout<<"V1= ";
  V1.affiche();
  //////////
  A.test();
  A.LUSolve(V1,V);
  cout<<"x avec LU= ";
  V1.affiche();
  A.MvProd(V1,V);
  cout<<"A*x exacte =";
  V.affiche();
  ///////////
  vector<vector<int> >test=recouvrement(5,2,20);
  cout<<"recouvrement pour n=20,l=5 et r=3 "<<endl;
  for(int i=0;i<int(test.size());i++)affiche(test[i]);

}

