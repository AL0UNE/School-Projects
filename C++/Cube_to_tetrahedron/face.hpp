#include <cmath>
#include <cassert>
#include "Tetra.hpp"
#include <cassert>
using namespace std;


class Face // classe face

{
    
private :

    R3 A,B,C; // sommets de la face



public :

Face():A(),B(),C(){}//constructeur par défaut

Face(R3 a,R3 b,R3 c)// constructeurr à partir de trois R3
{
A=a;
B=b;
C=c;

}
  
Face operator=(Face const &F) //constructeur par copie
{
A = F.A;
B = F.B;
C = F.C;
return *this;
    
}
  Face operator()(int i,Tetra T) //crée la face i du tétraèdre T
  {
    if(i==0)
{
	A = T[0];
	B = T[1];
	C = T[2];
    return *this;
  }
   if(i==1)
{
    A=T[1];
    B=T[2];
    C=T[3];
    return *this;
  }
   if(i==2)
{
    A=T[0];
    B=T[2];
    C=T[3];
    return *this;
  }
   if(i==3)
{
    A=T[0];
    B=T[1];
    C=T[3];
    return *this;
  }
  
  else 
  {return Face(R3(0,0,0),R3(0,0,0),R3(0,0,0));}
  }
 
 R3 operator[](int i) //renvoie le iéme sommets de la face
{
  if(i==0)return A;
  if(i==1)return B;
  if(i==2)return C;
  else return R3(0,0,0);

}
    
  

    
void printFace() // Méthode d'affichage

{
A.print();
B.print();
C.print();
}

R3 getA(){return A;} //pour avoir accès aux sommets des faces
R3 getB(){return B;}
R3 getC(){return C;}





bool operator==(Face const F) //savoir si deux faces sont égales
{
int p=0;
vector<R3>F1{ A,B,C };
vector<R3>F2{ F.A,F.B,F.C };
for (int i=0; i<F1.size();++i)
    {
    for (int j=0; j<F2.size(); ++j)
        {
        if (F1[i]==F2[j]){++p;}
            
            
        }
    }
if (p==3)
{return true;}
else {return false;}
}



};



vector<R3> intersectface(Face F1, Face F2) //renvoie l'intersection des sommets de deux faces
{
    vector<R3> pointersect;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (F1[i] == F2[j]) { pointersect.push_back(F1[i]); }
        }
    }return pointersect;
}


Tetra creeTetra(Face F, R3 S) //crée un tétraèdre à partir d'une face et d'un sommets
    {
        Tetra T(F[0], F[1], F[2], S);
        return T;
    }

    

bool AppartientPas(Face T, vector<Face> V) // pour savoir si Face T n'appartient pas à l'ensemble de Face V
{
	for (int i = 0; i < V.size(); ++i) {
		if (T == V[i]) { return false; }
	}
	return true;
}

bool Appartient(Face T, vector<Face> V) // pour savoir si Face T appartient a l'ensemble de Face V
{
	for (int i = 0; i < V.size(); ++i) {
		if (T == V[i]) { return true; }
	}

	return false;

}

bool PasDansUneFaceCarre(Face F, vector<Tetra> Carre)// pour savoir si la face F est incluse dans une face du Cube
{
int p=0;
int q=0;

vector<R3> F1;//sommets de F


F1.push_back(F[0]);
F1.push_back(F[1]);
F1.push_back(F[2]);

for (int i = 0; i < Carre.size(); ++ i) // On parcourt toutes les faces du cube
    {
    vector <R3> T2;
    T2.push_back(Carre[i][0]);
    T2.push_back(Carre[i][1]);
    T2.push_back(Carre[i][2]);
    T2.push_back(Carre[i][3]);
    for (int j= 0; j< F1.size(); ++ j)
        {
        if (not AppartientPas(F1[j],T2))
            {++p;}
        }
    if (p==3){++q;}
    p=0;
    }
if  (q==0){return true;}
else {return false;}
}




vector<Face> face_tetra(const Tetra T) //renvoie tout les faces d'un tétra
  {   
  vector<Face> F;
  Face F1;
  for(int i=0;i<4;i++)F.push_back(F1(i,T));

  return F;
  }

vector <Face> face_tetras(vector<Tetra> T) //renvoie tout les faces d'un ensemble de tétra
{
vector<Face> faces;
for (int i =0; i< T.size(); ++i)
    {
    vector<Face> f;
    f = face_tetra(T[i]);
    for (int j =0; j <f.size(); ++j)
        {faces.push_back(f[j]);}
    }
return faces;
}



  
Face inters(const Tetra T1, const Tetra T2)//renvoie la face commune de deux tétraèdres voisins. 
{
	vector<Face> F1 = face_tetra(T1);
	vector<Face> F2 = face_tetra(T2);
	Face commune;
	for (int i = 0; i < F1.size(); i++) 
    {
		for (int j = 0; j < F2.size(); j++) 
        {
			if (F1[i] == F2[j])commune = F1[i];
		}
	}return commune;
	
}


vector<Face> all_intersection(vector<Tetra> T)//renvoie tout les faces qui sont l'intersection de l'ensemble de tétra T 
{
vector<Face> all;
for (int i = 0; i <T.size(); ++i)
    for (int j = 0; j <T.size(); ++j)
    {
    if (interface(T[i],T[j]) and i!=j)
        {all.push_back(inters(T[i], T[j]));}
    }   

return all;
}

vector<Face> facedispo(vector<Tetra> T, vector<Tetra> Carre) //renvoie tout les faces des tétras qui sont "utilisable" afin de créer de nouveaux tétra 
{
    vector<Face> AllFace;
    vector<Face> NotWanted = all_intersection(T);
    vector<Face>faces = face_tetras(T);
    for (int i=0; i <faces.size(); ++i)
    {
    if (AppartientPas(faces[i],NotWanted) and PasDansUneFaceCarre(faces[i],Carre))
        {AllFace.push_back(faces[i]);}
    }
return AllFace;

}



vector<vector<Tetra> > Extension2(vector<vector<Tetra> > Extension, vector<Tetra> Carre, Cube Cu)// créé la deuxiéme extension a partir de extension1
{
vector<vector<Tetra> > Ext;

for (int i = 0; i <Extension.size(); ++i)
    {
    vector<Face> Pile1; // face dispo
    vector<R3> Pile2; // sommets dispo
    Pile1 = facedispo(Extension[i], Carre);
    Pile2 = Sommets_dispo(Extension[i], Cu);
    for (int j = 0; j <Pile1.size(); ++j)
        {
        for (int k = 0; k< Pile2.size(); ++k)
            {
            Tetra t;
            t = creeTetra(Pile1[j],Pile2[k]);
            if (volume(t) > 0.165 and volume(t) < 0.167 and AppartientPas(t,Extension[i])) 
                {
                vector <Tetra>T;
                T = Extension[i];
                T.push_back(t);
                Ext.push_back(T);
                }
            }
        
        }
    
    }
return Ext;
//return cheminsansdoublon(Ext); 
    
}
    
    

vector<vector<Tetra> > Extension3(vector<vector<Tetra> > Extension, vector<Tetra> Carre, Cube Cu)// créé la troisième extension a partir de extension2
{
vector<vector<Tetra> > Ext;

for (int i = 0; i <Extension.size(); ++i)
    {
    vector<Face> Pile1; // face dispo
    vector<R3> Pile2; // sommets dispo
    Pile1 = facedispo(Extension[i], Carre);
    Pile2 = Sommets_dispo(Extension[i], Cu);
    for (int j = 0; j < Pile1.size(); ++j)
    {
        for (int k = 0; k < Pile2.size(); ++k)
        {
            Tetra t;
            t = creeTetra(Pile1[j], Pile2[k]);
            for (int n = 0; n < Extension[i].size(); n++) {
                if (interface(t, Extension[i][n])) 
                {

                    if (volume(t) > 0.165 and volume(t) < 0.167)
                    {
                        vector <Tetra>T;
                        T = Extension[i];
                        T.push_back(t);
                        Ext.push_back(T);
                    }
                }

            }

        }
    }
    }
return Ext;
//return cheminsansdoublon(Ext); 


}
    

    


vector<vector<Tetra> > Extension4(vector<vector<Tetra> > Extension, vector<Tetra> Carre, Cube Cu, vector <Tetra> tetracoin)// créé la quatriéme extension a partir de extension3
{
vector<vector<Tetra> > Ext;

for (int i = 0; i < Extension.size(); ++i)
{
    vector<Face> Pile1; // face dispo
    vector<R3> Pile2; // sommets dispo
    Pile1 = facedispo(Extension[i], Carre);
    Pile2 = Sommets_dispo(Extension[i], Cu);
        if (Pile1.size()==2) // cas1 où on a 2 faces dipo
        {
                Tetra t,y;
                t = creeTetra(Pile1[0], Pile2[0]); //cas1.1
                y = creeTetra(Pile1[1], Pile2[0]); //cas1.1
				
				vector<R3>TT = intersectface(Pile1[0], Pile1[1]); //on cherche les 2 points d'intersection qui vont nous servir pour cas1.2
				vector<R3>TTT;//vecteur qui va contenir les 2 points distincts pour le cas 1.3
				for (int a = 0; a < 3; a++) {
					if (AppartientPas(Pile1[0][a], TT)) {
						TT.push_back(Pile1[0][a]); //on ajoute le premier point distinct
						TTT.push_back(Pile1[0][a]); //pareil
					}
					if (AppartientPas(Pile1[1][a], TT)) {
						TT.push_back(Pile1[1][a]);//on ajoute le deuxième point distinct
						TTT.push_back(Pile1[1][a]);//pareil
					}
				}
				Tetra T4{ TT[0],TT[1],TT[2],TT[3] }; //tétra du cas1.2
				Tetra TT1{ TTT[0],TTT[1],Pile2[0],TT[0] };//tétra favorable au cas1.3
				Tetra TT2{ TTT[0],TTT[1],Pile2[0],TT[1] };//tétra favorable au cas1.3
				if (Appartient(TT1, tetracoin)) { //vérification si tétra coin ou pas 
					vector <Tetra>L;
					L = Extension[i];
					L.push_back(TT1);
					Ext.push_back(L);
				}
				if (Appartient(TT2, tetracoin)) { //vérification si tétra coin ou pas 
					vector <Tetra>H;
					H = Extension[i];
					H.push_back(TT2);
					Ext.push_back(H);
				}
				

                if (volume(t) > 0.165 and volume(t) < 0.167 and volume(y) > 0.165 and volume(y) < 0.167)
                {
                    vector <Tetra>T,Y,C; 
					C = Extension[i];
                    Y = Extension[i];
                    T = Extension[i];
					C.push_back(T4); //cas1.2
                    T.push_back(t);//cas1.1
                    Y.push_back(y);//cas1.1
					Ext.push_back(C);
                    Ext.push_back(T);
                    Ext.push_back(Y);
                }
            }


        if (Pile1.size() == 3) //cas 2 
        {
            Tetra T1 = creeTetra(Pile1[0], Pile2[0]); //cas2
            Tetra T2 = creeTetra(Pile1[1], Pile2[0]); //cas2	
            Tetra T3 = creeTetra(Pile1[2], Pile2[0]); //cas2

            if (Appartient(T1, tetracoin)) { //vérification si tétra coin ou pas 
                vector <Tetra>T;
                T = Extension[i];
                T.push_back(T1);
                Ext.push_back(T);

            }
            if (Appartient(T2, tetracoin)) { //vérification si tétra coin ou pas 
                vector <Tetra>T;
                T = Extension[i];
                T.push_back(T2);
                Ext.push_back(T);

            }
            if (Appartient(T3, tetracoin)) { //vérification si tétra coin ou pas 
                vector <Tetra>T;
                T = Extension[i];
                T.push_back(T3);
                Ext.push_back(T);

            }

        }

        }
return Ext;
//return cheminsansdoublon(Ext); 

}





    

    
    





vector<vector<Tetra> > Extension5(vector<vector<Tetra> > Extension, vector<Tetra> Carre, Cube Cu)// créé la dernière extension a partir de extension4
{
	vector<vector<Tetra> > Ext;

	for (int i = 0; i < Extension.size(); ++i)
	{
		vector<Face> Pile1; // face dispo
		vector<R3> Pile2; // sommets dispo  
		Pile1 = facedispo(Extension[i], Carre);
		Pile2 = Sommets_dispo(Extension[i], Cu);
		
		if (Pile1.size() == 1) //cas1
		{
			Tetra T1 = creeTetra(Pile1[0], Pile2[0]); //on cree le tetra à partir de la derniere face et du dernier sommet
				vector <Tetra>T;
				T = Extension[i];
				T.push_back(T1);
				Ext.push_back(T);

		}
		if (Pile1.size() == 2) //cas2
		{
			vector<R3>TT = intersectface(Pile1[0], Pile1[1]); //on cherche les deux points d'intersection
			for (int a = 0; a < 3; a++) {
				if (AppartientPas(Pile1[0][a], TT)) { //on rajoute le 1er point distinct
					TT.push_back(Pile1[0][a]);
				}
				if (AppartientPas(Pile1[1][a], TT)) {//on rajoute le 2eme point distinct
					TT.push_back(Pile1[1][a]);
				}
			}

			Tetra T4{ TT[0],TT[1],TT[2],TT[3] };
			vector <Tetra>T;
			T = Extension[i];
			T.push_back(T4);
			Ext.push_back(T);
		}
		if (Pile1.size() == 3) //cas3
		{
			vector<R3>S1{ Pile1[0][0],Pile1[0][1],Pile1[0][2] };//on prend la 1ere face comme base
			vector<R3>S2 = intersectface(Pile1[1], Pile1[2]);//on fait l'intersection des deux autres faces
			for (int v = 0; v < S2.size(); v++)  
			{
				if (AppartientPas(S2[v], S1)) { S1.push_back(S2[v]); } //on regarde lequel des points de S2 n'appartient pas à la 1ere face
			}
			Tetra T2{ S1[0],S1[1],S1[2],S1[3] };
			vector <Tetra>T;
			T = Extension[i];
			T.push_back(T2);
			Ext.push_back(T);
		}
	}return Ext;
	//return cheminsansdoublon(Ext);
}

	
	
	



vector<vector<Tetra> > Decoupe (Tetra T, vector<Tetra> Carre, Cube Cu, vector <Tetra> briques, vector <Tetra> tetracoin)//applique l'ensemble des extensions à un tétra du coin
{

vector<vector<Tetra> > extension1, extension2, extension3, extension4, extension5;
extension1 = Extension1(T,briques);
extension2 = Extension2(extension1,Carre,Cu);
extension3 = Extension3(extension2,Carre,Cu);
extension4 = Extension4(extension3,Carre,Cu,tetracoin);
extension5 = Extension5(extension4,Carre,Cu);

return extension5;


}

	


    
