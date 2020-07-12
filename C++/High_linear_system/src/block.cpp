#include<iostream> 
#include<vector>
#include "vecteur.hpp"
#include <assert.h>
#include "block.hpp"

using namespace std; 

Block::Block (const int &nr,const int &nc,const vector<int> &Ir,const vector<int> &Ic){
  assert((nr>=0)&(nc>=0));
  assert((Ir[Ir.size()-1]<=nr)&(Ic[Ic.size()-1]<=nc));
nr_=nr;nc_=nc;Ir_=Ir;Ic_=Ic;mat=DenseMatrix(Ir.size(),Ic.size());}

Block::Block (const Block &m){nr_=m.nr_;nc_=m.nc_;Ir_=m.Ir_;Ic_=m.Ic_;mat=m.mat;}

void Block::operator=(const Block &m){
  nr_=m.nr_;
  nc_=m.nc_;
  Ir_=m.Ir_;
  Ic_=m.Ic_;
  mat=m.mat ;
  
}
void Block::getMat(DenseMatrix m){
  mat=m;
}

Block::~Block()=default;

void Block::MvProd(const Vecteur &x,Vecteur &b){
  assert(x.taille()==nc_);
  b=Vecteur(nr_);
  int ic=Ic_.size();
  int ir=Ir_.size();
   Vecteur V1(ic);
  for(int i=0;i<ic;i++)V1(i)=x(Ic_[i]);
   Vecteur V2(ir);
   mat.MvProd(V1,V2);
   for(int i=0;i<ir;i++)b(Ir_[i])=V2(i);
}

void Block::MvProdInv(const Vecteur &x,Vecteur &b){
  assert(Ir_.size()==Ic_.size());
 assert(x.taille()==nc_);
  b=Vecteur(nr_);
  int ic=Ic_.size();
  int ir=Ir_.size();
  Vecteur y(ic);
  for(int i=0;i<ic;i++)y(i)=x(Ic_[i]);
  Vecteur z(ic);
  mat.LUSolve(z,y);
  for(int i=0;i<ir;i++)b(Ir_[i])=z(i);

}

void Block::affiche()const{
    for(int i=0;i<nr_;i++){
      for(int j=0;j<int(Ir_.size());j++){
	if(i==Ir_[j])cout<<1;
	else cout<<0;
      }cout<<endl;
    }
    cout<<endl;
 for(int i=0;i<nc_;i++){
   for(int j=0;j<int(Ic_.size());j++){
	if(i==Ic_[j])cout<<1;
	else cout<<0;
      }cout<<endl;
    }
 cout<<endl;
 mat.affiche();
}
 




