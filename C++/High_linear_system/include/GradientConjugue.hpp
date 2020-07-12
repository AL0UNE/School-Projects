#pragma once
#include<vector> 
#include"vecteur.hpp"
class DenseMatrix;

class GradientConjugue{
private:
  int n_max;
  double tol;
  const DenseMatrix &A;
  const Vecteur &b;
  Vecteur x;
  int niter_;
  std::vector<double> resvec;
  double time;

 
public: 
  GradientConjugue();
  GradientConjugue(const DenseMatrix &A,const Vecteur &b,double tol,int maxit);
  int  niter()const;
  std::vector<double> residu()const;
  double temps()const;
  Vecteur solution ()const;
  void Solve();

 
};
