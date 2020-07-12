#include <cmath>
#include <cassert>
#include "cube.hpp"
#include <vector>
#include <algorithm>

using namespace std;


class Tetra // classe tétrahèdre

{
    
private :

    R3 A,B,C,D; // sommets du tétraèdres



public :

Tetra():A(),B(),C(),D(){} //constructor par défaut
Tetra(R3 a,R3 b,R3 c,R3 d) // constructor à partir de quatre R3
{
A=a;
B=b;
C=c;
D=d;
}
  
Tetra operator=(Tetra const &T) // constructor par copie
{
A = T.A;
B = T.B;
C = T.C;
D = T.D;
return *this;
    
}
bool operator!=(Tetra const &T)  // pour savoir si deux tétraèdres sont distincts
{
int p=0;
R3* T1;
R3* T2;
T1 = new R3[4];
T2 = new R3[4];
T1[0] = A;
T1[1] = B;
T1[2] = C;
T1[3] = D;
T2[0] = T.A;
T2[1] = T.B;
T2[2] = T.C;
T2[3] = T.D;
    
for (int i=0; i<4;++i)
    {
    for (int j=0; j<4; ++j)
        {
        if (T1[i]==T2[j]){++p;}
            
            
        }
    }

delete T1;
delete T2;
if (p==4)
{return false;}
else {return true;}
}


  

    

bool operator==(Tetra const T) // pour savoir si deux tétraèdres sont identiques
{
int p=0;
R3* T1;
R3* T2;
T1 = new R3[4];
T2 = new R3[4];
T1[0] = A;
T1[1] = B;
T1[2] = C;
T1[3] = D;
T2[0] = T.A;
T2[1] = T.B;
T2[2] = T.C;
T2[3] = T.D;
    
for (int i=0; i<4;++i)
    {
    for (int j=0; j<4; ++j)
        {
        if (T1[i]==T2[j]){++p;}
            
            
        }
    }

delete T1;
delete T2;
if (p==4)
{return true;}
else {return false;}
}


void printTetra() // Méthode d'affichage

{
A.print();
B.print();
C.print();
D.print();
}

R3 getA(){return A;} //pour avoir accès aux somets des tétras
R3 getB(){return B;}
R3 getC(){return C;}
R3 getD(){return D;}


 R3 operator[](int i) //idem
{
  if(i==0) {return A;}
  if(i==1) {return B;}
  if(i==2) {return C;}
  if(i==3) {return D;}
  else {return R3(0,0,0);}
}

friend ostream& operator<< (ostream& stream, const Tetra T) {
  stream<<NumSom(T.A)<<" "<<NumSom(T.B)<<" "<<NumSom(T.C)<<" "<<NumSom(T.D)<<" 0"<<endl; 
  return stream;     
       }

};





vector <R3> intersect(Tetra T1,Tetra T2) // renvoie les sommets communs de eux tétraèdes
{  



 vector<R3> inter;
 for(int i=0;i<4;i++){
   for(int j=0;j<4;j++){
     if(T1[i]==T2[j]){
       inter.push_back(T1[i]);
     }
   }
 }
 return inter;
}


double volume(Tetra T1) // calcul le volume d'un tétraèdre
{
  vector<R3>mat;
  int a=0;
  for(int i=1;i<4;i++){mat.push_back(T1[a]-T1[i]);}
  double A1=mat[0][0]*(mat[1][1]*mat[2][2]-(mat[2][1]*mat[1][2]));
  double B1=mat[0][1]*(mat[1][0]*mat[2][2]-(mat[2][0]*mat[1][2]));
  double C1=mat[0][2]*(mat[1][0]*mat[2][1]-(mat[2][0]*mat[1][1]));
  return abs((A1-B1+C1)/6);
	      
  
}
double volumetotal(vector<Tetra> T) // calcul le volume total de plusieurs détraèdres 
{
  double s=0;
  for(int i=0;i<T.size();i++) {

s=s+volume(T[i]);}
  return s;
}





bool interface(Tetra T1,Tetra T2) // pour savoir si T1 et T2 sont voisins
{



vector<R3> V;
V = intersect(T1,T2);

if (V.size() != 3)
{return false;}

else
    {
    double d1;
    double d2;
    R3 t1;
    R3 t2;
    R3 v1=V[0];
    R3 v2=V[1];
    R3 v3=V[2];
    for (int i=0;i<4;++i)
        {
        if (T1[i] != v1 and T1[i] != v2 and T1[i] != v3)
            {t1 = T1[i];}
        if (T2[i] != v1 and T2[i] != v2 and T2[i] != v3)
            {t2 = T2[i];}
        }
        double a = v1.getx();
        double e = v1.gety();
        double i = v1.getz();
        double m = 1;
        double b = v2.getx();
        double f = v2.gety();
        double j = v2.getz();
        double n = 1;
        double c = v3.getx();
        double g = v3.gety();
        double k = v3.getz();
        double o = 1;
        double d = t1.getx();
        double h = t1.gety();
        double l = t1.getz();
        double p = 1;
        double q = t2.getx();
        double r = t2.gety();
        double s = t2.getz();
        d1 = (a*f*k*p) - (a*f*l*o) - (a*g*j*p) + (a*g*l*n) + (a*h*j*o) - (a*h*k*n) - (b*e*k*p) + (b*e*l*o) + (b*g*i*p) - (b*g*l*m) - (b*h*i*o) + (b*h*k*m) + (c*e*j*p) - (c*e*l*n) - (c*f*i*p) + (c*f*l*m) + (c*h*i*n) - (c*h*j*m) - (d*e*j*o) + (d*e*k*n) + (d*f*i*o) - (d*f*k*m) - (d*g*i*n) + (d*g*j*m);
        d2 = (a*f*k*p) - (a*f*s*o) - (a*g*j*p) + (a*g*s*n) + (a*r*j*o) - (a*r*k*n) - (b*e*k*p) + (b*e*s*o) + (b*g*i*p) - (b*g*s*m) - (b*r*i*o) + (b*r*k*m) + (c*e*j*p) - (c*e*s*n) - (c*f*i*p) + (c*f*s*m) + (c*r*i*n) - (c*r*j*m) - (q*e*j*o) + (q*e*k*n) + (q*f*i*o) - (q*f*k*m) - (q*g*i*n) + (q*g*j*m);
        if (d1*d2 > 0)
        {return false;}
        else {return true;}
        
        
    
  
        
    }
   
}


    
  

  
  
  
  
  vector<Tetra> inter_uneface(Tetra const T1,vector<Tetra> briques) //permet d'avoir tous les tétraèdres voisins de T1
 {
    vector<Tetra> inter;

for(int i=0;i<briques.size();i++)
{
  if(interface(T1,briques[i]))
      
   {inter.push_back(briques[i]);
  
}
}   //cout <<inter.size()<< endl;
 return inter;
  }



vector <Tetra> Decoupe1(Tetra T, vector <Tetra> briques) // renvoie les deux découpes à partie des tétraèdres de volume 1/3
{
vector <Tetra> decoup = inter_uneface(T, briques);
decoup.push_back(T);
return decoup;
}
 

   


    

bool AppartientPas(Tetra A, vector<Tetra> V) // pour savoir si tétraèdre A n'est pas dans le vector de tetra  V
    {
        for (int i = 0; i < V.size(); ++i)
        {
            if (A == V[i]) { return false; }

        }
    return true;
}


bool Appartient(Tetra T, vector<Tetra> V) // pour savoir si le tétraèdre T  est dans V
  {
      for (int i = 0; i < V.size(); ++i) {
          if (T == V[i]) { return true; }
      }

      return false;

}
    
    

    
vector<R3> Sommets(vector<Tetra> V) // pour avoir tous les sommets de tous les tétraèdres d'un vector<tetra> V 
{
vector<R3> som;
for (int i=0; i<V.size(); ++i)
    {
    for (int j =0; j<4; ++j)
        {
        som.push_back(V[i][j]);
        }
    }
return som;
}
    

vector <R3> Sommets_dispo (vector<Tetra> V, Cube Cu) // renvoie tous les sommets du cube Cu privés de tous les sommet de Sommets(V)
{
int p =0;
vector<R3> som_dispo;
vector<R3> sommets = Sommets(V);

for (int i =0; i <8; ++i)
    {
    for (int j = 0; j <sommets.size(); ++j)
        if (sommets[j]==Cu[i])
        {
        ++p;
        }
    
    if (p==0)
        {som_dispo.push_back(Cu[i]);}
            
    p =0;    
    }
return som_dispo;
}








    

bool inter_avec_cube(Tetra T1, vector<Tetra> Carre) // pour savoir si le tétra T1 s'intersecte avec une face du cube = un carré
{
	vector< vector<R3> > in;
	for (int i = 0; i < Carre.size(); i++) {
		in.push_back(intersect(T1, Carre[i]));
	}
	for (int j = 0; j < in.size(); j++) {
		if (in[j].size() == 3)return true;
	}return false;
}

    
bool memechemin(vector<Tetra> C1, vector<Tetra> C2)//compare si deux chemins sont identiques

{

int p =0;

for (int i=0; i < C1.size(); ++i)
    {
    for (int j=0; j< C2.size(); ++j)
        {
        if (C1[i]==C2[j])
            {++p;}
        }
    }
if (p == C1.size())
    {return true;}
else {return false;}

}
   
vector<vector<Tetra> > cheminsansdoublon (vector<vector<Tetra> > V)//prend toutes les découpes et enlève les doublons

{
int p = 0;
vector<vector<Tetra> > chemin;
chemin.push_back(V[0]);

for (int i= 1; i < V.size(); ++i)
    {
    for (int j = 0; j <chemin.size(); ++j)
        {
        if (memechemin(chemin[j],V[i]))
            {++p;}
        }
    if (p==0)
        {chemin.push_back(V[i]);}
    p=0;
    }
    

return chemin;
}
    
    
    

vector<vector<Tetra> > Extension1(Tetra T, vector<Tetra> briques) // créé la première extension pour un tétraèdre du coin
{
vector<vector<Tetra> > V;

vector<Tetra> test;
test = inter_uneface (T, briques);

for (int i = 0; i < test.size(); ++i)
    {
    vector <Tetra> A;
    A.push_back(T);
    A.push_back(test[i]);
    V.push_back(A);
    
    }

return cheminsansdoublon(V);
}
    

