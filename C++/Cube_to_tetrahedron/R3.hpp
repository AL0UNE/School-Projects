#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;



class R3{

private:
    double x, y, z; // coordonées des sommets


public:

    R3(){x = y = z = 0;} // constructor pas défaut
    
    R3 (double a, double b, double c) {x = a; y = b; z = c;} // constructeur à partie de 3 doubles
    
    R3 operator=(R3 const &R) // constructeur par copie
    {
    x = R.x;
    y = R.y;
    z = R.z;
    return *this;}
    
    void print () // méthode d'affichage
    {
    cout<<x<<" "<<y<<" "<<z<<endl;
    }



    double getx () // fonction qui permet d'obtenir la première coordonée d'un sommet, x 
	{
	return x;
	}

    double gety () // fonction qui permet d'obtenir la deuxième coordonée d'un sommet, y 
	{return y;}

   double getz () // fonction qui permet d'obtenir la dernière coordonée d'un sommet, z 
	{return z;}
 
   
       const double & operator[](int i) const { if(i==0) {return x;} // fonction qui fait pareil de getx, gety, getx
        else if (i==1) {return y;}
        else if (i==2) {return z;}
        else {assert(0);exit(1);}
    }

    R3   operator+(R3 const &P)  // Loi + de l'espace vectoriel R3
        {
        R3 c;
        c.x = x + P.x;
        c.y = y + P.y;
        c.z = z + P.z;
        
        return c;
        }
  R3   operator-(R3 const &P)  //loi - comme précedement
        {
        R3 c;
        c.x = x - P.x;
        c.y = y - P.y;
        c.z = z - P.z;
        
        return c;
        }
    

    

    R3 operator*(double const &R) // loi externe de l'espace vectoriel R3
    {
    R3 c;
    c.x = x*R;
    c.y = y*R;
    c.z = z*R;
    
    return c;
    }
    
    

    
    double operator,(R3 const &P) // Produit scalaire
    {
    double a, b, c;
    a = x*P.x;
    b = y*P.y;
    c = z*P.z;
    
    return a+b+c;
    }
    
    bool operator == (R3 const &R) // pour comparer deux sommets (s'ils sont égaux)
    {
    if (x==R.x and y==R.y and z == R.z){return true;}
    else {return false;}
    }
    
        bool operator != (R3 const &R)  // pour comparer deux sommets (s'ils sont différents)
    {
    if (x!=R.x or y!=R.y or z != R.z){return true;}
    else {return false;}
    }
friend ostream& operator<< (ostream& stream, const R3 R) {
  stream<<R.x<<" "<<R.y<<" "<<R.z<<" 0"<<endl; 
  return stream;     
       }
        
   


};
int NumSom(R3 R){
R3 A(0,1,0);
R3 B(1,1,0);
R3 C(1,0,0);
R3 D(0,0,0);
R3 E(0,1,1);
R3 F(1,1,1);
R3 G(1,0,1);
R3 H(0,0,1);
if(R==A)return 1;
if(R==B)return 2;
if(R==C)return 3;
if(R==D)return 4;  
if(R==E)return 5;
if(R==F)return 6;  
if(R==G)return 7;
if(R==H)return 8;
else return 0;
}

double distance (R3 X, R3 Y) // distance entre X et Y 

{

double x1,x2,y1,y2,z1,z2;
x1 = X.getx();
y1 = X.gety();
z1 = X.getz();

x2 = Y.getx();
y2 = Y.gety();
z2 = Y.getz();

return sqrt( ((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)) + ((z2-z1)*(z2-z1)) );

}



bool AppartientPas(R3 A, vector<R3> V) // pour savoir si sommet A est dans le vector de tetra  V
    {
        for (int i = 0; i < V.size(); ++i)
        {
            if (A == V[i]) { return false; }

        }
    return true;
}





