/* TP, 2018/2019
*/
#include <iostream>
#include<stdexcept>
#include<new>
#include<iomanip>
using namespace std;
void UnistiMatricu(long long int **mat,int n){
    for(int i=0;i<n;i++)delete[] mat[i];
    delete[] mat;
}
long long int Stirling(int n,int k){
if(n==0 && k==0)return 1;
else if(n==0 || k>n || k==0)return 0;
else return k*Stirling(n-1,k)+Stirling(n-1,k-1);
}
long long int  **StirlingoviBrojeviV1(int n){
    if(n<0)throw domain_error("Parametar ne smije biti negativan");
    long long int **mat=nullptr;
    try{
        mat=new long long int *[n+1];
        try{
            for(int i=0;i<n+1;i++)
            mat[i]=new long long int[i+1];
        }
        catch(bad_alloc){
            //UnistiMatricu(mat,(n+1));
            delete[] mat;
            throw range_error("Parametar prevelik za raspolozivu memoriju");
        }
    }
    catch(bad_alloc){
        //UnistiMatricu(mat,(n+1));
        delete[] mat;
        throw range_error("Parametar prevelik za raspolozivu memoriju");
    }
    catch(domain_error){
        throw;
    }
    for(int i=0;i<n+1;i++){
        for(int j=0;j<i+1;j++){
            mat[i][j]=Stirling(i,j);
        }
    }
    
   return mat; 

}
long long int **StirlingoviBrojeviV2(int n){
    if(n<0)throw domain_error("Parametar ne smije biti negativan");
    long long int**mat=nullptr;
    int vel=0;
    try{
        mat=new long long int*[n+1];
        for(int i=0;i<n+1;i++)vel+=(i+1);
        try{
        mat[0]=new long long int[(n+1)*(n+1)];
        for(int i=1;i<n+1;i++)mat[i]=mat[i-1]+i;
    } 
    catch(bad_alloc){   
        //delete[] mat[0];
        delete[] mat;
        throw range_error("Parametar prevelik za raspolozivu memoriju");
    }
    }
     catch(bad_alloc){
         //delete[] mat[0];
         delete[] mat;
         throw range_error("Parametar prevelik za raspolozivu memoriju");
     }
    catch(domain_error){
        throw;
    }
        for(int i=0;i<n+1;i++){
            for(int j=0;j<i+1;j++)
            mat[i][j]=Stirling(i,j);
        }
       
        return mat;
    }
int main ()
{
    
    int n;
    cin>>n;
    bool ispisao=false;
    try{
    long long int **p=StirlingoviBrojeviV1(n);
   long long int **q=StirlingoviBrojeviV2(n);
    for(int i=0;i<n+1;i++){
       for(int j=0;j<i+1;j++)cout<<p[i][j]<<" ";
        cout<<endl;
    }
    for(int i=0;i<n+1;i++){
        for(int j=0;j<i+1;j++)cout<<q[i][j]<<" ";
        cout<<endl;
    }
    UnistiMatricu(p,n+1);
    delete[] q[0];
    delete[] q;
    }
    catch(range_error izuzetak){
        cout<<izuzetak.what()<<endl;
    }
    catch(domain_error izuzetak){
        cout<<izuzetak.what()<<endl;
    }
    catch(...){
        cout<<"Nema memorije";
    }
	return 0;
}