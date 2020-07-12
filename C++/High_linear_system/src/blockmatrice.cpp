#include<iostream> 
#include<vector>
#include "vecteur.hpp"
#include <assert.h>
#include "blockmatrice.hpp"
#include"matriceDense.hpp"

using namespace std; 

BlockMatrix::BlockMatrix (const int &nr,const int &nc){
  assert((nr>=0)&(nc>=0));
nr_=nr;
nc_=nc;
 val_=vector<Block>{};
}
BlockMatrix::~BlockMatrix()=default;

BlockMatrix::BlockMatrix (const BlockMatrix &m){nr_=m.nr_;
nc_=m.nc_;
val_=m.val_;
}

void BlockMatrix::operator=(const BlockMatrix &m){
  nr_=m.nr_;
  nc_=m.nc_;
  val_=m.val_;
  }
void BlockMatrix::operator+=(const Block &b){
  val_.push_back(b);
}

void BlockMatrix::MvProd(const Vecteur &x,Vecteur &b){
  assert(x.taille()==nc_);
  Vecteur sol(nr_);
  b=Vecteur(nr_);
  int v=val_.size();
  for(int i=0;i<v;i++){
    val_[i].MvProd(x,sol);
    b+=sol;
  }
}

void BlockMatrix:: MinRes(Vecteur &x,const Vecteur &b,const double &tol){
  BlockMatrix B(*this);
  int N=b.taille();
  x=Vecteur(N);
  Vecteur r(b);
  Vecteur b1(b);
Vecteur vv(N);
  double r0=b.norme();
  int niter=0;
  double conditiondarret=1;
 while(conditiondarret>tol){

    B.MvProd(r,vv);
  double alpha=r*vv/(vv*vv);
  x = x + (r*alpha);
  B.MvProd(x,vv);
  r = b1-vv;
  niter++;
  conditiondarret=(r.norme()/r0);
  }
  }
 
  




void BlockMatrix::MvProdInv(const Vecteur &x,Vecteur &b){
 
  assert(x.taille()==nc_);
  Vecteur sol(nr_);
  b=Vecteur(nr_);
  int v=val_.size();
  for(int i=0;i<v;i++){
    val_[i].MvProdInv(x,sol);
    b+=sol;
  }
}

void BlockMatrix::Extract(const DenseMatrix &A,const vector<vector<int> > &Iq){
  int ind=Iq.size();
for(int i=0;i<ind;i++){
    Block B(A.row(),A.row(),Iq[i],Iq[i]);
    B.getMat(A(Iq[i],Iq[i]));
    val_.push_back(B);
  }
}
void BlockMatrix::affiche()const{
  int v=val_.size();
  for(int i=0;i<v;i++){
val_[i].affiche();
  }
}
 



