#include "fonction.hpp";
using namespace std;

void affiche(vector<int>vec){
  int taille=vec.size();
  for(int i=0;i<taille;i++)cout<<vec[i]<<" ";
  cout<<endl;
}

vector<vector<int> >recouvrement(int l,int r,int n){
  assert((l<n)&(r<l));
  vector<vector<int> >partition;
  int qetoile=floor(n/l)-1;
  vector<int>I1,Iqe,Iq;
  for(int i=0;i<l+r;i++){I1.push_back(i);}
  partition.push_back(I1);
  for(int q=2;q<=qetoile;q++){
    Iqe.clear();
  for(int j=0;j<2*r+l+1;j++)Iqe.push_back(l*(q-1)-r+j-1);
   partition.push_back(Iqe);
   }
  for(int i=l*qetoile-1;i<n;i++)Iq.push_back(i);
  partition.push_back(Iq);
  return partition;
}
void graph(const vector<double> &v1,const vector<double> &v2){
     ofstream fichier1("graph.txt", ios::out);
if(fichier1)
 {
   fichier1<<"Niter"<<" "<<"Gc"<< " "<<"PGC"<<endl;
   int taille1=v1.size();
   int taille2=v2.size();
   if(taille1<taille2) {
   for(int i=0;i<int(v1.size());i++) fichier1<<i<<" "<<v2[i]<<" "<<v1[i]<<endl;
   for(int i=v1.size();i<int(v2.size());i++)fichier1<<i<<" "<<v2[i]<<" "<<" "<<endl;
 fichier1.close();
   }
   else{    
 for(int i=0;i<int(v2.size());i++) fichier1<<i<<" "<<v2[i]<<" "<<v1[i]<<endl;
 for(int i=v2.size();i<int(v1.size());i++)fichier1<<i<<" "<<v2[taille2-1]<<" "<<v1[i]<<endl;
 fichier1.close();
   }
   
 }
  
};
