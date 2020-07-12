#include <cmath>
#include <cassert>
#include "R3.hpp"


using namespace std;



class Cube{
private:

  R3 A,B,C,D,E,F,G,H; // sommets du cube

public:
  Cube():A(),B(),C(),D(),E(),F(),G(),H(){} //construcor par défaut
  Cube(R3 a,R3 b,R3 c,R3 d,R3 e,R3 f,R3 g,R3 h):A(a),B(b),C(c),D(d),E(e),F(f),G(g),H(h){} //constructeur à partir de huit R3
  
  
 R3 operator[](int i) // pour avoir accès au ième sommet
{
  if(i==0) {return A;}
  if(i==1) {return B;}
  if(i==2) {return C;}
  if(i==3) {return D;}
  if(i==4) {return E;}
  if(i==5) {return F;}
  if(i==6) {return G;}
  if(i==7) {return H;}
  else {return R3(0,0,0);}
}
    
  
};


