//TP 2018/2019: Zadaća 3, Zadatak 3
#include <iostream>
#include<iomanip>
#include<stdexcept>
#include<new>
#include<vector>
#include<iomanip>
using namespace std;
template<typename TipElemenata>
struct Matrica {
    int br_redova,br_kolona;
    TipElemenata **elementi=nullptr;
};
template<typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> mat)
{
    if(!mat.elementi)return;
    for(int i=0; i<mat.br_redova; i++)delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi=nullptr;
}
template<typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova,int br_kolona)
{
    Matrica<TipElemenata> mat;
    mat.br_redova=br_redova;
    mat.br_kolona=br_kolona;
    mat.elementi=new TipElemenata*[br_redova];
    for(int i=0; i<br_redova; i++)mat.elementi[i]=nullptr;
    try {
        for(int i=0; i<br_redova; i++)mat.elementi[i]=new TipElemenata[br_kolona];
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template<typename TipElemenata>
void UnesiMatricu(char ime_matrice,Matrica<TipElemenata> &mat)
{
    for(int i=0; i<mat.br_redova; i++)
        for(int j=0; j<mat.br_kolona; j++) {
            cout<<ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
            cin>>mat.elementi[i][j];
        }
}
template<typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat,int sirina_ispisa,int preciznost=6,bool treba_brisati=false)
{
    for(int i=0; i<mat.br_redova; i++) {
        for(int j=0; j<mat.br_kolona; j++)
            cout<<setw(sirina_ispisa)<<setprecision(preciznost)<<mat.elementi[i][j];
        cout<<endl;
    }
    if(treba_brisati==true)UnistiMatricu(mat);
}
template<typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2)
{
    if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona)
        throw domain_error("Matrice nemaju jednake dimenzije!");
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova,m1.br_kolona));
    for(int i=0; i<m1.br_redova; i++)
        for(int j=0; j<m1.br_kolona; j++)
            m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
    return m3;
}
template<typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2)
{
    if(m1.br_kolona!=m2.br_redova)throw domain_error("Matrice nisu saglasne za mnozenje!");
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova,m2.br_kolona));
    TipElemenata suma{};
    for(int i=0; i<m1.br_redova; i++) {
        for(int j=0; j<m2.br_kolona; j++) {
            m3.elementi[i][j]=0;
            for(int k=0; k<m1.br_kolona; k++) {
                m3.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
            }
        }
    }
    return m3;
}
template<typename TipElemenata>
Matrica<TipElemenata>PomnoziSaSkalarom(const Matrica<TipElemenata> &mat,int broj)
{
    auto mat1(StvoriMatricu<TipElemenata>(mat.br_redova,mat.br_kolona));
    for(int i=0; i<mat.br_redova; i++) {
        for(int j=0; j<mat.br_kolona; j++) {
            mat1.elementi[i][j]=mat.elementi[i][j]*broj;
        }
    }
    return mat1;
}
template<typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &mat1,vector<double> v)
{
    Matrica<TipElemenata>vracam,e,f,g,m,n,p;
    if(v.size()==0){
        auto v2(StvoriMatricu<TipElemenata>(mat1.br_redova,mat1.br_kolona));
        for(int i=0;i<mat1.br_redova;i++){ 
            for(int j=0;j<mat1.br_kolona;j++)
            v2.elementi[i][j]=0;   
        }    
        return v2;        
    }     
    for(int i=0;i<v.size();i++){
        if(i==0){
            auto jedinicna(StvoriMatricu<TipElemenata>(mat1.br_redova,mat1.br_kolona));
            for(int j=0;j<mat1.br_kolona;j++){
                for(int k=0;k<mat1.br_kolona;k++){
                    if(j==k)jedinicna.elementi[j][k]=1;
                    else
                    jedinicna.elementi[j][k]=0;
                }
            }
            f=jedinicna;
            e=PomnoziSaSkalarom(f,v.at(i));
            vracam=e;
            UnistiMatricu(jedinicna);
        }
        else if(i==1){
            e=PomnoziSaSkalarom(mat1,v.at(i));
            g=vracam;
            f=ZbirMatrica(e,g);
            vracam=f;
            UnistiMatricu(e);
            UnistiMatricu(g);
        }
        else{
            
            g=mat1;
            auto q(StvoriMatricu<TipElemenata>(mat1.br_redova,mat1.br_kolona));
            for(int k=0;k<mat1.br_redova;k++){
                for(int z=0;z<mat1.br_kolona;z++)
                q.elementi[k][z]=mat1.elementi[k][z];
            }
            Matrica<TipElemenata>h=mat1;
            //auto q(StvoriMatricu<TipElemenata>(mat1.br_redova,mat1.br_kolona));
            for(int k=1;k<i;k++){
               g=ProduktMatrica(q,mat1);
               for(int z=0;z<mat1.br_redova;z++){
                   for(int w=0;w<mat1.br_kolona;w++){
                       q.elementi[z][w]=g.elementi[z][w];
                   }
               }
               UnistiMatricu(g);
            }
            
            
            e=PomnoziSaSkalarom(q,v.at(i));
            m=e;
            n=vracam;
            f=ZbirMatrica(m,n);
            UnistiMatricu(e);
            UnistiMatricu(q);
            UnistiMatricu(n);
            vracam=f;
        }
    }
    return vracam;
}
int main ()
{
    Matrica<double> a,c;
    int m,red_polinoma;
    double n;
    cout<<"Unesite dimenziju kvadratne matrice: ";
    cin>>m;
    vector<double> koeficijenti_polinoma;
    try {
        a=StvoriMatricu<double>(m,m);
        cout<<"Unesite elemente matrice A: "<<endl;
        UnesiMatricu('A',a);
        cout<<"Unesite red polinoma: ";
        cin>>red_polinoma;
        cout<<"Unesite koeficijente polinoma: ";
        for(int i=0;i<red_polinoma+1;i++){
            cin>>n;
            koeficijenti_polinoma.push_back(n);
        }
       c=MatricniPolinom(a,koeficijenti_polinoma);
        IspisiMatricu(c,10,6);
        UnistiMatricu(a);
        UnistiMatricu(c);
    } catch(bad_alloc) {
        cout<<"Nema dovoljno memorije!\n";
    } 
    return 0;
}
