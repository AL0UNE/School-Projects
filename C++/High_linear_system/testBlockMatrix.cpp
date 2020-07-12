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
  cout<<"testBlockMatrix"<<endl;
  DenseMatrix D(6,6);
  D.test();
  vector<int>vec{1,2,3};
  vector<int>vec1{0,1,2,3,4};
  Block B(6,6,vec,vec);
  /////////
  BlockMatrix BM(5,5);
  cout<<"BM= " <<endl;  
  BM.affiche();
  BlockMatrix BM1(6,6);
  BM=BM1;
  cout<<"BM= "<<endl;
  BM.affiche();
  /////////
  BM+=B;
  BM.affiche();
  /////////
  Vecteur V(6);
  Vecteur V1(2);
  for(int i=0;i<6;i++)V(i)=1;
 vector<vector<int> >ok;
 vector<int>identite{0,1,2,3,4,5};
 ok.push_back(identite);
 BM1.Extract(D,ok);
 BM1.affiche();
 BM1.MinRes(V1,V,0.001);
 V1.affiche();


  


}

