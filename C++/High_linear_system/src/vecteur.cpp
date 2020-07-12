#include<iostream> 
#include<vector>
#include"vecteur.hpp"
#include<cmath>
#include<cassert>
using namespace std; 

Vecteur::Vecteur(){N_=0;}
Vecteur::Vecteur (int N){assert(N>=0);N_=N;coef_.resize(N,0);}
Vecteur::Vecteur (const Vecteur &v){N_=v.N_;coef_=v.coef_;}
//Vecteur::~Vecteur()=default; 
int Vecteur:: taille()const{return N_;}
void Vecteur:: affiche()const{
for(int i=0;i<N_;i++)cout<<coef_[i]<<" ";
 cout<<endl;}
double Vecteur::norme()const{
  double n=0;
 for(int i=0;i<N_;i++)n+=(coef_[i]*coef_[i]);
 return sqrt(n);
}
void Vecteur::operator=(const Vecteur &v){
  assert(v.N_>=0);
  N_=v.N_;
  coef_=v.coef_;
}
double & Vecteur:: operator()(int i){
  assert((i>=0) & (i<N_));
return coef_[i];}
double Vecteur:: operator()(int i)const{
  assert((i>=0) & (i<N_));
return coef_[i];}
Vecteur Vecteur:: operator+(const Vecteur &v)const{
  assert(v.taille()==N_);
    Vecteur w(*this);
    for(int i=0;i<w.taille();i++)w(i)+=v(i);
    return w;
  }
void Vecteur:: operator+=(const Vecteur &v){
 assert(v.taille()==N_);
 for(int i=0;i<v.taille();i++)coef_[i]+=v(i);
}

Vecteur Vecteur:: operator-(const Vecteur &v)const{
  assert(v.taille()==N_);
    Vecteur w(*this);
    for(int i=0;i<w.taille();i++)w(i)-=v(i);
    return w;
  }
Vecteur Vecteur:: operator*(double alpha) const{
Vecteur w((*this));
 for(int i=0;i<w.taille();i++){w(i)=w(i)*alpha;}
 return w;

  }
double Vecteur:: operator*(const Vecteur &v)const{
  assert(N_==v.taille());
  double scal;
  for(int i=0;i<N_;i++)scal+=(coef_[i]*v(i));
  return scal;
}
void Vecteur:: permute(int i,int j){
  assert((i>=0)&(j>=0));
  assert((i<N_) & (j<N_));
Vecteur &v = *this;
 double t=v(i);
 v(i)=v(j);
 v(j)=t;
}

