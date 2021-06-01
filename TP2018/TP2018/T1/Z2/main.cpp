#include<iostream>
#include<cmath>
using std::cin;
using std::cout;
using std::endl;

int main() 
{
    double a,b,c; 
    cout<<"Unesite tri broja: ";
    cin>>a>>b>>c;
    if((a+b)>c && (b+c)>a && (a+c)>b) {
        double obim=a+b+c;
        cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<obim<<"."<<endl;
        double s=obim/2;
        double povrsina=sqrt(s*(s-a)*(s-b)*(s-c));
        cout<<"Njegova povrsina iznosi "<<povrsina<<"."<<endl;
        double alfa,beta,gama,min,ugao,stepeni,minute,sekunde;
        alfa=acos((b*b+c*c-a*a)/(2*b*c)); 
        beta=acos((a*a+c*c-b*b)/(2*a*c));
        gama=acos((a*a+b*b-c*c)/(2*a*b));
        if(alfa<=beta && alfa<=gama)min=alfa;
        if(beta<=alfa && beta<=gama)min=beta; 
        if(gama<=alfa && gama<=beta)min=gama;
        //slucaj jednakostranicnog trougla
        if(alfa==gama && alfa==beta && gama==beta)min=alfa;
        ugao=min*(180)/(4*atan(1));
        stepeni=(int)ugao;
        minute=(ugao-stepeni)*60;
        sekunde=(minute-(int)minute)*60;
        cout<<"Njegov najmanji ugao ima "<<stepeni<<" stepeni, "<<(int)minute<<" minuta i "<<(int)sekunde<<" sekundi."<<endl;
    } else
        cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!"<<endl;
    return 0;
}
