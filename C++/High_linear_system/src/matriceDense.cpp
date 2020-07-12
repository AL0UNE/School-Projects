#include<iostream> 
#include <fstream>
#include<vector>
#include"matriceDense.hpp"
#include"direct_solvers.hpp"
#include "vecteur.hpp"
#include"blockmatrice.hpp"
#include <assert.h>
#include <cmath>
#include<ctime>
class BlockMatrix;
using namespace std; 
DenseMatrix::DenseMatrix(){};
DenseMatrix::DenseMatrix (const int &nr,const int &nc){
  assert((nr>=0) & (nc>=0));
  nr_=nr;nc_=nc;val_.resize(nr*nc,0);}
DenseMatrix::DenseMatrix (const DenseMatrix &m){nr_=m.nr_;nc_=m.nc_;val_=m.val_;}
DenseMatrix::DenseMatrix(const int &nr,const int &nc,const vector<double> &val){
 assert((nr>=0) & (nc>=0));
  nr_=nr;
  nc_=nc;
  val_=val;
}

DenseMatrix::DenseMatrix(const int &numberMat){
string mat="MAt/matrix";
 string extension =".txt";
 string name = mat+to_string(numberMat)+extension;
 
string mot1,mot2;
 int n, m;
 vector<double>val;
 double num;

 ifstream fichier(name.c_str(), ios::in);
if(fichier)
 {
 fichier >> mot1>> n >> m>>mot2; 
 while (fichier>> num) { val.push_back(num); }
 fichier.close();
}
 nr_=n;
 nc_=m;
 val_=val;

}
DenseMatrix::~DenseMatrix()=default;

int DenseMatrix::row()const{return nr_;}

int DenseMatrix::col()const{return nc_;}
double DenseMatrix::temps()const{return time;}
vector<double> DenseMatrix::residu()const{return resvec;}
void DenseMatrix:: affiche()const{
  for(int i=0;i<nr_;i++){
    for(int j=0;j<nc_;j++){
      cout<<val_[j+i*nr_]<<" ";}
   cout<<endl;
  }
}

void DenseMatrix::operator=(const DenseMatrix &m){
  nr_=m.nr_;
  nc_=m.nc_;
  val_=m.val_;
}

double & DenseMatrix:: operator()(int i,int j){
  assert((i>=0)&(j>=0));
  assert((i<nr_)&(j<nc_));
return val_[j+i*nr_];}

double DenseMatrix:: operator()(int i,int j)const{
  assert((i>=0)&(j>=0));
  assert((i<nr_)&(j<nc_));
return val_[j+i*nr_];}

DenseMatrix DenseMatrix:: operator*(const double &alpha){

  DenseMatrix w(*this);
  for(int i=0;i<nr_;i++)
      for(int j=0;j<nc_;j++)
	w(i,j)=w(i,j)*alpha;
	  return w;
}

ostream& operator <<(ostream& f,const DenseMatrix & D){
  for (int i=0;i<D.row();i++){
    for (int j=0;j<D.col();j++){
            f<<D(i,j)<<"\t";
        }
        f<<endl;
    }
    return f;
}

void DenseMatrix::MvProd(const Vecteur &x,Vecteur &b)const{
  assert(x.taille()==nc_);
  b=Vecteur(nr_);
  DenseMatrix w(*this);
 for(int i=0;i<nr_;i++)
     for(int k=0;k<nc_;k++)
       b(i)=b(i)+w(i,k)*x(k);
 }
DenseMatrix DenseMatrix:: operator()(vector<int>Ir,vector<int>Ic)const{
  assert((Ir[Ir.size()-1]<=nr_)&(Ic[Ic.size()-1]<=nc_));
  DenseMatrix v(*this);
  int ir=Ir.size();
  int ic=Ic.size();
  DenseMatrix w(Ir.size(),Ic.size());
  for(int i=0;i<ir;i++){
    for(int j=0;j<ic;j++){
      w.val_[j+i*Ir.size()]=v(Ir[i],Ic[j]);
    }
  }return w;
}
void DenseMatrix::LUSolve(Vecteur &x,const Vecteur &b)const{
  assert(nr_==nc_);
  assert(b.taille()==nc_);
  x=Vecteur(nc_);
  DenseMatrix w(*this);
  for(int k=0;k<nr_-1;k++){
    if(w(k,k)!=0){
     for(int i=k+1;i<nr_;i++){
double li=w(i,k)/w(k,k);
      for(int j=k;j<nr_;j++){
        w(i,j)=w(i,j)-li*w(k,j);
}
 w(i,k)=li;
}
}
}
  Vecteur Y(solve_triang_inf_id(w,b));
  x=solve_triang_sup(w,Y);
}
void DenseMatrix::cg(Vecteur &x,const Vecteur &b,double tol,int maxit){
  assert(nc_==nr_);
  assert(b.taille()==nc_);
  DenseMatrix w(*this);  
  GradientConjugue Gc(w,b,tol,maxit);
  Gc.Solve();
  x=Gc.solution();
  resvec=Gc.residu();
  time=Gc.temps();
  cout<<"Nombre d'itérations Gradient conjugue : "<<Gc.niter()<<endl;
  cout<<"Temps CPU = "<<time<<endl;
}

void DenseMatrix::pcg(Vecteur &x,const Vecteur &b,double tol,int maxit,const vector<vector<int> >&inc){
  assert(nc_==nr_);
  assert(b.taille()==nc_);
int niter=0;
clock_t start,end;
 start=clock();
DenseMatrix w(*this);
BlockMatrix BM(w.row(),w.col());
 BM.Extract(w,inc);
  x=Vecteur(w.row());
  Vecteur r(b);
 Vecteur z(w.row());
  BM.MvProdInv(r,z);
  Vecteur p(z);
  resvec.clear();
  double r0=b.norme();
  double conditiondarret=1;
   while(conditiondarret>tol && niter<maxit){
    double gamma=r*z;
    Vecteur v(w.row());
    w.MvProd(p,v);
    double alpha=gamma/(p*v);
    x=x+(p*alpha);
    r=r-(v*alpha);
    BM.MvProdInv(r,z);
    double beta=(r*z)/gamma;
    p=z+(p*beta);
     resvec.push_back(r.norme());
    niter++;
    conditiondarret=(r.norme()/r0);
    }
  end=clock();
cout<<"Nombre d'itérations Gradient conjugue Preconditionnee : "<<niter<<endl;
 time=static_cast<double>(end - start) / CLOCKS_PER_SEC ;
 cout<<"Temps CPU = "<<time<<endl;
}

void DenseMatrix::test(){
DenseMatrix &w = *this;
   for(int i=0;i<nr_;i++){
     for(int j=0;j<nc_;j++){
       if(i==j)w(i,j)=2;
       if(j==i+1 or j==i-1)w(i,j)=-1;
     }
   }
}


