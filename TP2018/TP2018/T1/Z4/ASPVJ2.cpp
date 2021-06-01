#include<iostream>
#define velicina_niza 1000
using namespace std;
template<typename Tip>
class Lista
{
public:
    Lista() {}
    Lista(const Lista<Tip> &l){}
    virtual ~Lista() {}
    virtual void obrisi()=0;
    virtual int brojElemenata()const=0;
    virtual Tip &trenutni()=0;
    virtual Tip &trenutni()const=0;
    virtual bool sljedeci()=0;
    virtual bool prethodni()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual Tip &operator[](int i)=0;
    virtual Tip &operator[](int i)const=0;
    virtual void dodajIspred(const Tip &el)=0;
    virtual void dodajIza(const Tip &el)=0;
};
template<typename Tip>
class  NizLista:public Lista<Tip>
{
    Tip** niz;
    int kapacitet,velicina;
    int tekuci;
public:
    NizLista():Lista<Tip>(),niz(new Tip*[velicina_niza]),kapacitet(velicina_niza),velicina(0),tekuci(0) {}
    ~NizLista()
    {
        for(int i=0; i<velicina; i++)delete niz[i];
        delete[] niz;
    }
    NizLista(NizLista<Tip> &n)
    {
        kapacitet=n.kapacitet;
        velicina=n.velicina;
        tekuci=n.tekuci;
       niz=new Tip*[n.kapacitet];
        for(int i=0; i<n.velicina; i++)
            
            niz[i]=new Tip(*n.niz[i]);

    }

    NizLista(NizLista<Tip> &&n)
    {
        kapacitet=n.kapacitet;
        velicina=n.velicina;
        tekuci=n.tekuci;
        niz=new Tip*[n.kapacitet];
        niz=n.niz;
        n.velicina=0;
        n.tekuci=0;
        n.niz=nullptr;
    }

    NizLista<Tip> &operator=(NizLista<Tip> &&n)
    {
        for(int i=0; i<velicina; i++)delete niz[i];
        delete[] niz;
        velicina=n.velicina;
        kapacitet=n.kapacitet;
        tekuci=n.tekuci;
        niz=new Tip[n.velicina];
        for(int i=0; i<velicina; i++)
            niz[i]=new Tip(n.niz[i]);
        n.velicina=0;
        n.niz=nullptr;
        return *this;
    }

    NizLista<Tip> &operator=( NizLista<Tip> &n)
    {
        if(this==&n)return *this;
        //for(int i=0;i<velicina;i++){delete niz[i];}
        delete[] niz;
        kapacitet=n.kapacitet;
        velicina=n.velicina;
        tekuci=n.tekuci;
       niz=new Tip*[n.kapacitet];
        for(int i=0; i<n.velicina; i++)
            niz[i]=new Tip(*n.niz[i]);
        return *this;
    }

    int brojElemenata()const
    {
        return velicina;
    }

    Tip &operator[](int i)
    {
        if(i<0 || i>velicina)throw "greska";
        return *niz[i];
    }



    Tip &operator[](int i)const
    {
        if(i<0 || i>velicina)throw "greska";
        return *niz[i];
    }

    Tip &trenutni()
    {
        if(velicina==0)throw "greska";
        return *niz[tekuci];
    }

    Tip &trenutni()const
    {
        if(velicina==0)throw "greska";
        return *niz[tekuci];
    }
    bool prethodni()
    {
        if(tekuci==0)return false;
        else {
            tekuci--;
            return true;
        }
    }

    bool sljedeci()
    {
        if(tekuci==velicina-1)return false;
        else {
            tekuci++;
            return true;
        }
    }

    void pocetak()
    {
        if(velicina==0)throw "greska";
        tekuci=0;
    }
    void kraj()
    {
        if(velicina==0)throw "greska";
        tekuci=velicina-1;
    }
    void obrisi()
    {
        delete niz[tekuci];
        if(velicina==0)throw "greska";
        velicina--;
        for(int i=tekuci; i<velicina; i++)niz[i]=niz[i+1];
        if(tekuci==velicina && velicina>0)tekuci--;
        else if(velicina==0)tekuci=0;
        //else tekuci++;
    }
    void dodajIspred(const Tip &el)
    {

        if(velicina==kapacitet) {
            kapacitet=kapacitet*2;
            Tip **niz2=new Tip*[kapacitet];
            for(int i=0; i<velicina; i++)
                niz2[i]=niz[i];
            delete[] niz;
            niz=niz2;

        }

        else if(velicina==0) {
            niz[0]=new Tip(el);
            velicina++;
            tekuci=0;
            return;
        }
        for(int i=velicina; i>tekuci; i--)
            niz[i]=niz[i-1];
        niz[tekuci]=new Tip(el);
        velicina++;
        tekuci++;
    }

    void dodajIza(const Tip &el)
    {
        if(velicina==0) {
            niz[0]=new Tip(el);
            velicina++;
            tekuci=0;
            return;
        }
        if(velicina==kapacitet) {
            kapacitet*=2;
            Tip **niz2=new Tip*[kapacitet];
            for(int i=0; i<velicina; i++)
                niz2[i]=niz[i];
            delete[] niz;
            niz=niz2;
        }

        for(int i=velicina; i>tekuci+1; i--)
            niz[i]=niz[i-1];
        niz[tekuci+1]=new Tip(el);
        velicina++;


    }
};
template<typename Tip>

class JednostrukaLista:public Lista<Tip>
{
    struct Cvor {
        Tip el;
        Cvor *veza;
//Cvor(Tip &el,Cvor *veza):el(el),veza(veza){}
    };
    Cvor *pocetni;
    Cvor *krajnji;
    Cvor *tekuci;
    int velicina;
public:
    JednostrukaLista():Lista<Tip>(),pocetni(0),krajnji(0),tekuci(0),velicina(0) {}
    ~JednostrukaLista()
    {
        while(pocetni!=0) {
            tekuci=pocetni;
            pocetni=pocetni->veza;
            delete tekuci;
        }

    }
    JednostrukaLista(const JednostrukaLista<Tip> &l)
    {
        Cvor* pom(l.pocetni),pom2(0);
        while(pom!=0) {
            Cvor* novi=new Cvor;
            novi->el=pom->el;
            if(pom2==0) {
                pocetni=novi;
            } else {
                pom2->veza=novi;
            }
            pom2=novi;
            if(pom==l.tekuci) {
                tekuci=novi;
            }
            pom=pom->veza;

        }
        krajnji=pom2;

    }
    JednostrukaLista<Tip> &operator=(const JednostrukaLista<Tip> &l)
    {
        if(this==l)return *this;
        while(pocetni!=0) {
            tekuci=pocetni;
            pocetni=pocetni->veza;
            delete tekuci;
        }
        Cvor *pom(l.pocetni),pom2(0);
        while(pom!=0) {
            Cvor* novi=new Cvor;
            novi->el=pom->el;
            if(pom2==0) {
                pocetni=novi;
            } else {
                pom2->veza=novi;
            }
            pom2=novi;
            if(pom==l.tekuci)tekuci=novi;
            pom=pom->veza;
        }
        krajnji=pom2;
        return *this;


    }
    int brojElemenata()const
    {
        return velicina;
    }

    Tip& trenutni()
    {
        if(velicina==0)throw "greska";
        return tekuci->el;
    }

    Tip &trenutni()const
    {
        if(velicina==0)throw "greska";
        return tekuci->el;
    }

    bool prethodni()
    {
        if(velicina==0)throw "greska";
        if(tekuci==pocetni)return false;
        Cvor *pom(pocetni);
        while(pom->veza!=tekuci)
            pom=pom->veza;
        tekuci=pom;
        return true;
    }

    bool sljedeci()
    {
        if(velicina==0)throw "greska";
        if(tekuci->veza==0)return false;
        tekuci=tekuci->veza;
        return true;
    }
    void pocetak()
    {
        if(velicina==0)throw "greska";
        tekuci=pocetni;
    }

    void kraj()
    {
        if(velicina==0)throw "greska";
        tekuci=krajnji;
    }

    void obrisi()
    {
        if(velicina==0)throw "greska";
        velicina--;
        if(tekuci==pocetni) {
            pocetni=pocetni->veza;
            delete tekuci;
            tekuci=pocetni;
        } else if(velicina==0)krajnji=0;
        else {
            Cvor *pom(pocetni);
            while(pom->veza!=tekuci)
                pom=pom->veza;
            pom->veza=tekuci->veza;
            delete tekuci;
            tekuci=pom->veza;
            if(tekuci==0) {
                krajnji=pom;
                tekuci=pom;
            }
        }


    }

    void dodajIza(const Tip &element)
    {
        Cvor *novi=new Cvor();
        novi->el=element;
        velicina++;
        if(pocetni==0) {
            pocetni=krajnji=tekuci=novi;
            novi->veza=0;
        } else {
            novi->veza=tekuci->veza;
            tekuci->veza=novi;
            if(krajnji==tekuci)krajnji=novi;
        }
    }

    void dodajIspred(const Tip &element)
    {
        Cvor *novi=new Cvor();
        novi->el=element;
        velicina++;
        if(pocetni==0) {
            pocetni=krajnji=tekuci=novi;
            novi->veza=0;
        } else if(tekuci==pocetni) {
            novi->veza=pocetni;
            pocetni=novi;
        } else {
            Cvor *pom=pocetni;
            while(pom->veza!=tekuci)
                pom=pom->veza;
            novi->veza=pom->veza;
            pom->veza=novi;

        }

    }


    Tip &operator[](int i)
    {
        if(i<0 || i>velicina)throw "greska";
        Cvor *pom(pocetni);
        for(int j=0; j<i; j++)pom=pom->veza;
        return pom->el;
    }

    Tip &operator[](int i)const
    {
        if(i<0 || i>velicina)throw "greska";
        Cvor *pom(pocetni);
        for(int j=0; j<i; j++)pom=pom->veza;
        return pom->el;
    }

};
int main()
{
    NizLista<int> l;
    NizLista<int> l1;
    NizLista<int> l2;
    for(int i=0;i<5;i++)l.dodajIspred(i);
    for(int i=0;i<5;i++){l1.dodajIza(i);l2.dodajIspred(i);}
   // l2=l;
    cout<<l.trenutni()<<" "<<l.prethodni()<<" "<<l.sljedeci()<<endl;
    cout<<l1.trenutni()<<" "<<l1.prethodni()<<" "<<l1.sljedeci()<<endl;
    l.obrisi();
    l2.obrisi();
    l1.obrisi();
    l.sljedeci();
    l2.prethodni();
    cout<<l.trenutni()<<" "<<l1.trenutni()<<" "<<l2.trenutni()<<endl;
    cout<<l.brojElemenata()<<endl;
    cout<<l2[2]<<endl;
    l.dodajIza(10);
    cout<<l.trenutni()<<" "<<l.brojElemenata()<<endl;
    l.pocetak();
    cout<<l.trenutni();
    l1.kraj();
    cout<<" "<<l1.trenutni()<<endl;
    JednostrukaLista<int> jl;
    for(int i=0;i<5;i++)jl.dodajIspred(i);
    JednostrukaLista<int> jl2;
    for(int i=0;i<5;i++)jl2.dodajIza(i);
    cout<<jl.trenutni()<<" "<<jl.prethodni()<<" "<<jl.sljedeci()<<endl;
    cout<<jl2.trenutni()<<" "<<jl2.prethodni()<<" "<<jl2.sljedeci()<<endl;
    jl.obrisi();
    jl2.obrisi();
    cout<<jl.trenutni()<<" "<<jl2.trenutni()<<endl;
    cout<<jl[2]<<" "<<jl2[0]<<endl;
    jl.prethodni();
    jl2.sljedeci();
    cout<<jl.trenutni()<<" "<<jl2.trenutni()<<endl;
    
    
    return 0;
}
