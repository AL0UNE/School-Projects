#include "direct_solvers.hpp"
#include<iostream>
using namespace std;

Vecteur solve_triang_inf_id(const DenseMatrix &A, const Vecteur& b){
 int N=b.taille();  
Vecteur V(N);
 for(int i=0;i<N;i++){
   double s=0;  
   for(int j=0;j<=i;j++){
     s+=A(i,j)*V(j);}
 
 V(i)=(b(i)-s);
 }
 return V;
}

Vecteur solve_triang_sup(const DenseMatrix &A,const Vecteur &b){
  int N=b.taille();  
Vecteur V(N);
 for(int i=N-1;i>=0;i--){
   double s=0;  
   for(int j=N-1;j>=i;j--){
     s+=A(i,j)*V(j);
  }
 
 V(i)=(b(i)-s)/A(i,i);
 }
 return V;
 }
