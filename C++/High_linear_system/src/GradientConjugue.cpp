#include<iostream> 
#include<vector>
#include"GradientConjugue.hpp"
#include"matriceDense.hpp"
#include "vecteur.hpp"
#include <assert.h>
#include <cmath>
#include<ctime>
#include"direct_solvers.hpp"
using namespace std; 

GradientConjugue::GradientConjugue(const DenseMatrix &A1,const Vecteur &b1,double tol1,int maxit1):A(A1),b(b1){
  tol=tol1;n_max=maxit1;}

int GradientConjugue:: niter()const{return niter_;}
vector<double> GradientConjugue::residu()const{return resvec;}
Vecteur GradientConjugue::solution()const{return x;}
double GradientConjugue::temps()const{return time;}
void GradientConjugue::Solve(){
  clock_t start,end;
   start=clock();
  int N=A.row();
  x=Vecteur(N);
  Vecteur r(b);
  Vecteur p(r);
  double r0=b.norme();
  niter_=0;
  double conditiondarret=1;

   while (conditiondarret > tol && niter_<n_max){
 double normeR=r*r;
     Vecteur vv(N);
    A.MvProd(p,vv);
    double rr=p*vv;
    double alpha=normeR/rr;
  x = x + (p*alpha);
  r = r - ((vv)*alpha);
  double beta = (r*r)/normeR;
  p = r + (p*beta);
  resvec.push_back(r.norme());
  niter_++;
  conditiondarret=abs((r.norme()/r0));
  }
   end=clock();
    time=static_cast<double>(end - start) / CLOCKS_PER_SEC ;

    }


  







