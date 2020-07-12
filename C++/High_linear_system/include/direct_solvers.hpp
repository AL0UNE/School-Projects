#pragma once
#include "vecteur.hpp"
#include"matriceDense.hpp" 
using namespace std;

Vecteur solve_triang_inf(const DenseMatrix &A,const Vecteur &b);
Vecteur solve_triang_sup(const DenseMatrix &A,const Vecteur &b);
Vecteur solve_triang_inf_id(const DenseMatrix &A,const Vecteur &b);

