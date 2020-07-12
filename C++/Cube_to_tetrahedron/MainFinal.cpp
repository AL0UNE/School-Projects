#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include "face.hpp"


int main()

{
int a,c,e,g;//variables pour récupérer les coordonnées de toutes les combinaisons de 4 points possibles
char b,d,f;//séparateur

double x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4;//variables utilisées  pour afficher la N-èeme découpe

int N=0; //
cout <<"Choisir un N entier entre  0 et 69 pour votre decoupe"<<endl;
cin >> N;


//les 8 sommets du cube
R3 A(0,1,0);
R3 B(1,1,0);
R3 C(1,0,0);
R3 D(0,0,0);
R3 E(0,1,1);
R3 F(1,1,1);
R3 G(1,0,1);
R3 H(0,0,1);

Cube Cu(A,B,C,D,E,F,G,H); //le cube


vector<Tetra> CarreOuRectangle;//va contenir les faces du carrée ainsi que les rectangles du cube

vector <Tetra> Carre; //les faces du cube 
Carre.push_back(Tetra(A,B,C,D));
Carre.push_back(Tetra(B,C,F,G));
Carre.push_back(Tetra(A,E,D,H));
Carre.push_back(Tetra(E,F,G,H));
Carre.push_back(Tetra(A,E,F,B));
Carre.push_back(Tetra(D,H,C,G));


vector<Tetra> briques;// tout les tétraèdres possibles (les 58)



vector <Tetra> S; // Les 70 quadruplets de sommets distincts du sommets 



vector<R3> Omega{A,B,C,D,E,F,G,H};


ifstream fichier ("combinaisons.txt"); // on parcourt le fichier combinaisons.txt
    if (fichier);
            {
            string ligne;
                while (getline(fichier, ligne))
                {
                istringstream totalSString(ligne);
                totalSString>>a>>b>>c>>d>>e>>f>>g;
                //cout << a<<c<<e<<g<< endl;
                S.push_back(Tetra(Omega[a-1],Omega[c-1],Omega[e-1],Omega[g-1]));
                //cout << atoi(mot)<< ligne[2]<<endl;
                //Omega[atoi(ligne)].print();
                }

            }


for (int j=0;j<S.size();++j) //On remplis CarreouRectangle
    {
    double somme;
    R3 v1 = S[j].getA();
    R3 v2 = S[j].getB();
    R3 v3 = S[j].getC();
    R3 v4 = S[j].getD();
    double a,b,c,d,e,f,g,h,i;
    a = v2.getx() - v1.getx();
    b = v3.getx() - v1.getx();
    c = v4.getx() - v1.getx();
    d = v2.gety() - v1.gety();
    e = v3.gety() - v1.gety();
    f = v4.gety() - v1.gety();
    g = v2.getz() - v1.getz();
    h = v3.getz() - v1.getz();
    i = v4.getz() - v1.getz();
    somme = (a*e*i) - (a*f*h) + (b*f*g) - (b*d*i) + (c*d*h) - (c*e*g);
    if (somme == 0)
        {CarreOuRectangle.push_back(S[j]);}
    }


for (int c1=0; c1<S.size();++c1) //On ne garde que les tétraèdres
    {
        if (AppartientPas(S[c1],CarreOuRectangle)){briques.push_back(S[c1]);}
   
    }

          

Tetra TA;
TA = Tetra(A,C,F,H); // 1er tetra de volume 1/3


Tetra TB;
TB = Tetra(B,D,E,G); // 2eme tetra de volume 1/3

//les 8 tetras coin
Tetra tetra1 = Tetra(A,B,D,E);
Tetra tetra2 = Tetra(A,E,F,H);
Tetra tetra3 = Tetra(E,F,B,G);
Tetra tetra4 = Tetra(A,D,H,C);
Tetra tetra5 = Tetra(D,C,G,B);
Tetra tetra6 = Tetra(C,G,H,F);
Tetra tetra7 = Tetra(G,H,D,E);
Tetra tetra8 = Tetra(A,B,F,C);

vector <Tetra> tetracoin{tetra1,tetra2,tetra3,tetra4,tetra5,tetra6,tetra7,tetra8};

vector <Tetra> briques2; //tous les tétraèdres de volume 1/6

for (int i=0; i<58; ++i)
    {if (briques[i] != TA and briques[i] != TB){briques2.push_back(briques[i]);}}

        
//cout << briques2.size()<<endl;
        
        
 
 
vector<vector<Tetra>> DecoupeTout;

for (int i=0; i <tetracoin.size();++i)
{
vector<vector<Tetra>> test;
test = Decoupe(tetracoin[i],Carre,Cu,briques2,tetracoin);//decoupe à partir d'un tetra coin
//cout <<cheminsansdoublon(test).size()<<endl;

for (int j=0; j<test.size(); ++j)
    {DecoupeTout.push_back(test[j]);}
}


vector<vector<Tetra>> Decoupefinale = cheminsansdoublon(DecoupeTout); // on enlève les doublons




Decoupefinale.push_back(Decoupe1(TA,briques2)); // on ajoute les découpes à partir des tétraèdres de volume 1/3
Decoupefinale.push_back(Decoupe1(TB,briques2));



vector <Tetra> DecoupeN = Decoupefinale[N]; // on va tracer la N eme decoupe 

//ecriture du fichier maillage pour medit

 ofstream myfile;
 myfile.open("output.mesh");
 myfile<<"MeshVersionFormatted 1"<<endl;
 myfile<<"Dimension\n"<<"3\n\n"<<"Vertices\n"<<"8\n";
 for(int i=0;i<8;i++)myfile<<Cu[i];
 myfile<<"\nTetrahedra\n"<<DecoupeN.size()<<"\n";
 for(int i=0;i<DecoupeN.size();i++)
    myfile<<DecoupeN[i];
 myfile<<"\nend";

 
 

  
return 0;
}
