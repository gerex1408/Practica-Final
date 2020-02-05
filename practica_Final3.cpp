/*Entrada: Entrar 2 fitxers, un per pacients i l'altre per donants, un cop entrats els fitxers es demanara que s'entri una opcio
i l'usuari entrara la opcio que convingui fins que tenqui el programa entrant la opcio "SORTIR"*/
/*Sortida: Per a cada opcio que entri l'usuari s'hauran de mostrar diferents sortides per pantalla creant aixi un pool d'intercanvis de ronyó*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int MAX=1000;
const string EOS="SORTIR";

struct Pacient
{
    string codi;
    int dia;
    int mes;
    int any;
    string sang;
    string hospital;
    string ciutat;
    int compatibilitat;
};

struct Donant
{
    string codi;
    string sang;
    string codi_pacient;
    int compatibilitat;
};

struct Pacient_Donant
{
    string codi_pacient;
    int dia;
    int mes;
    int any;
    string sang_pacient;
    string hospital;
    string ciutat;
    string codi_donant;
    string sang_donant;
    int compatibilitat_pacient;
    int compatibilitat_donant;
};

typedef Pacient Vector_pacient[MAX];
typedef Donant Vector_donant[MAX];
typedef Pacient_Donant Vector_parella[MAX];

struct Taula_pacient
{
    Vector_pacient vector;
    int n;
};

struct Taula_donant
{
    Vector_donant vector;
    int n;
};

struct Taula_Parella
{
    Vector_parella vector;
    int n;
};

Pacient llegir_pacient(ifstream& f_entrada){
    //pre:cert
    //post: llegeix un pacient p de fitxer f_entrada
    Pacient p;
    f_entrada>>p.codi;
    f_entrada>>p.dia;
    f_entrada>>p.mes;
    f_entrada>>p.any;
    f_entrada>>p.sang;
    if(p.sang=="O")p.compatibilitat=1;
    else if(p.sang=="A")p.compatibilitat=2;
    else if(p.sang=="B")p.compatibilitat=3;
    else p.compatibilitat=6;
    f_entrada>>p.hospital;
    f_entrada>>p.ciutat;
    return p;
}

void llegir_fitxer_pacients(Taula_pacient& t_pacient,ifstream& f_entrada_pacients){
    //pre:que sigui fitxer de pacients i no de donants. 0<t_pacient.n<MAX
    //post:Es llegeix el fitxer de pacients des de f_entrada_pacients i es guarda a la tupla t_pacient
    t_pacient.n=0;
    Pacient pacient=llegir_pacient(f_entrada_pacients);
    while(t_pacient.n<MAX and not f_entrada_pacients.eof()){
        t_pacient.vector[t_pacient.n]=pacient;
        t_pacient.n++;
        pacient=llegir_pacient(f_entrada_pacients);
    }
}

void intercanvi_pacients(Pacient& x,Pacient& y){
    //pre: x==x y==y
    //post: x=y y=x
    Pacient aux=x;
    x=y;
    y=aux;
}

void ordenar_taula_per_codi(Taula_pacient& t_pacient){
    //pre:CERT
    //post: ordena la taula t_pacients.vector[0..t_pacient.n-1] per codi de pacient en ordre ascendent.
    for(int i=0;i<t_pacient.n-1;i++){
        for(int j=t_pacient.n-1;j>i;j--){
            if(t_pacient.vector[j].codi<t_pacient.vector[j-1].codi){
                intercanvi_pacients(t_pacient.vector[j],t_pacient.vector[j-1]);
            }
        }
    }
}

Donant llegir_donant(ifstream& f_entrada){
    //pre:cert
    //post: llegeix un donant
    Donant d;
    f_entrada>>d.codi;
    f_entrada>>d.sang;
    if(d.sang=="O")d.compatibilitat=1;
    else if(d.sang=="A")d.compatibilitat=2;
    else if(d.sang=="B")d.compatibilitat=3;
    else d.compatibilitat=6;
    f_entrada>>d.codi_pacient;
    return d;
}

void llegir_fitxer_donants(Taula_donant& t_donant,ifstream& f_entrada_donants){
    //pre: 0<t_donants.n<MAX
    //post: llegeix els donants del fitxer f_entrada_donants i si el pacient asociat al donant existeix, s'afegeix el codi donant a la taula del pacient. Altrament no es tindra en compte el donant
    t_donant.n=0;
    Donant donant=llegir_donant(f_entrada_donants);
    while(t_donant.n<MAX and not f_entrada_donants.eof()){
        t_donant.vector[t_donant.n]=donant;
        t_donant.n++;
        donant=llegir_donant(f_entrada_donants);
    }
}

void intercanvi_donants(Donant& x,Donant& y){
    //pre: x==x y==y
    //post: x=y y=x
    Donant aux=x;
    x=y;
    y=aux;
}

void ordenar_taula_per_codi_pacient(Taula_donant& t_donant){
    //pre: cert
    //post: ordena la taula per codi de pacient associat
        for(int i=0;i<t_donant.n-1;i++){
        for(int j=t_donant.n-1;j>i;j--){
            if(t_donant.vector[j].codi_pacient<t_donant.vector[j-1].codi_pacient){
                intercanvi_donants(t_donant.vector[j],t_donant.vector[j-1]);
            }
        }
    }
}

void afegir(Taula_Parella& t_parella,Pacient p,Donant d){
    //pre:cert
    //post:afegeix el donant i el pacient a la taula t_parella de la posicio t_parella.n
    t_parella.vector[t_parella.n].codi_pacient=p.codi;
    t_parella.vector[t_parella.n].dia=p.dia;
    t_parella.vector[t_parella.n].mes=p.mes;
    t_parella.vector[t_parella.n].any=p.any;
    t_parella.vector[t_parella.n].sang_pacient=p.sang;
    t_parella.vector[t_parella.n].hospital=p.hospital;
    t_parella.vector[t_parella.n].ciutat=p.ciutat;
    t_parella.vector[t_parella.n].codi_donant=d.codi;
    t_parella.vector[t_parella.n].sang_donant=d.sang;
    t_parella.vector[t_parella.n].compatibilitat_pacient=p.compatibilitat;
    t_parella.vector[t_parella.n].compatibilitat_donant=d.compatibilitat;
}

void interseccio_dels_vectors(Taula_Parella& t_parella,Taula_donant t_donant,Taula_pacient t_pacient){
    //pre:cert
    //post:fa l'interseccio de t_donant i t_pacient i agrupa nomes els pacients amb donants a la taula t_parella creant aici una taula correcta
    int i1=0;
    int i2=0;
    t_parella.n=0;
    while(i1<t_pacient.n and i2<t_donant.n){
        if(t_pacient.vector[i1].codi==t_donant.vector[i2].codi_pacient){
            afegir(t_parella,t_pacient.vector[i1],t_donant.vector[i2]);
            i1++;
            i2++;
            t_parella.n++;
        }
        else if(t_pacient.vector[i1].codi<t_donant.vector[i2].codi_pacient)i1++;
        else i2++;
    }
}

void intercanvi(Pacient_Donant& x,Pacient_Donant& y){
    //pre: x==x y==y
    //post: x=y y=x
    Pacient_Donant aux=x;
    x=y;
    y=aux;
}

void ordenar_taula_parella_per_codi(Taula_Parella& t_parella){
    //pre:CERT
    //post: ordena la taula t_parella.vector[0..t_parella.n-1] per codi de pacient en ordre ascendent.
    for(int i=0;i<t_parella.n-1;i++){
        for(int j=t_parella.n-1;j>i;j--){
            if(t_parella.vector[j].codi_pacient<t_parella.vector[j-1].codi_pacient)intercanvi(t_parella.vector[j],t_parella.vector[j-1]);
        }
    }
}

string llegir_opcio(){
    //pre:cert
    //post: llegeix l'opcio que s'ha de dur a terme i retorna un string
    string opcio;
    cout<<"ENTRA OPCIO:"<<endl;
    cin>>opcio;
    return opcio;
}

void inserir(Pacient_Donant p,int pos,Taula_Parella& t_parella){
    //pre: cert
    //post:s'insereix ordenadament una parella de pacient/donant a la taula t_parella
    for(int i=t_parella.n-1;i>=pos;i--){
        t_parella.vector[i+1]=t_parella.vector[i];
    }
    t_parella.n++;
    t_parella.vector[pos]=p;
}

void existeix_amb_posicio(string codi_pacient,Taula_Parella t_parella,int& pos,bool& existeix){
    //pre: cert
    //post: si el codi_pacient existeix a la t_parella retorna cert i la posicio on es troba, altrament retorna fals.
    int dret=t_parella.n-1;
    int esquerra=0;
    int mig=(dret+esquerra)/2;
    existeix=false;
    while(not existeix and esquerra<=dret){
        if(t_parella.vector[mig].codi_pacient>codi_pacient){
            dret=mig-1;
            mig=(dret+esquerra)/2;
        }
        else if(t_parella.vector[mig].codi_pacient<codi_pacient){
            esquerra=mig+1;
            mig=(dret+esquerra)/2;
        }
        else existeix=true;
    }
    if(existeix)pos=mig;
    else pos=esquerra;
}

void llegir_parella_per_teclat(Pacient_Donant& p){
    //pre:cert
    //post: llegeix una parella pacient/donant per teclat
    cin>>p.codi_pacient;
    cin>>p.dia;
    cin>>p.mes;
    cin>>p.any;
    cin>>p.sang_pacient;
    if(p.sang_pacient=="O")p.compatibilitat_pacient=1;
    else if(p.sang_pacient=="A")p.compatibilitat_pacient=2;
    else if(p.sang_pacient=="B")p.compatibilitat_pacient=3;
    else p.compatibilitat_pacient=6;
    cin>>p.hospital;
    cin>>p.ciutat;
    cin>>p.codi_donant;
    cin>>p.sang_donant;
    if(p.sang_donant=="O")p.compatibilitat_donant=1;
    else if(p.sang_donant=="A")p.compatibilitat_donant=2;
    else if(p.sang_donant=="B")p.compatibilitat_donant=3;
    else p.compatibilitat_donant=6;
}

void donar_d_alta(Taula_Parella& t_parella){
    //pre:cert
    //post:si el pacient existeix no es dona d'alta i es mostra un missatge per pantalla, altrament si es dona d'alta inserint-lo ordenat
    int pos_pacient;
    bool existeix_pacient;
    Pacient_Donant p;
    llegir_parella_per_teclat(p);
    existeix_amb_posicio(p.codi_pacient,t_parella,pos_pacient,existeix_pacient);
    if(existeix_pacient)cout<<"CODI EXISTENT"<<endl;
    else{
        inserir(p,pos_pacient,t_parella);
        cout<<"ALTA REALITZADA"<<endl;
    }
}

void eliminar_pacient(Taula_Parella& t_parella, int pos){
    //pre:pos<MAX
    //post: elimina el pacient de la posicio pos de t_parella.vector[0..t_parella.n-1]
    if(pos<MAX){
        for(int i=pos+1;i<t_parella.n;i++){
            t_parella.vector[i-1]=t_parella.vector[i];
        }
        t_parella.n--;
    }
}

void donar_de_baixa(Taula_Parella& t_parella){
    //pre:cert
    //post: Si el pacient existeix es dona de baixa ell i el seu donant asociat.
    string codi_pacient;
    cin>>codi_pacient;
    int pos_pacient;
    bool existeix_pacient;
    existeix_amb_posicio(codi_pacient,t_parella,pos_pacient,existeix_pacient);
    if(existeix_pacient){
        eliminar_pacient(t_parella,pos_pacient);
        cout<<"BAIXA REALITZADA"<<endl;
    }
    else cout<<"CODI INEXISTENT"<<endl;
}

void mostrar_pacient(Taula_Parella t_parella,int pos){
    //pre:cert
    //post: mostra l'nformacio del pacient de t_parella.vector[pos]
    cout<<t_parella.vector[pos].codi_pacient<<' '<<t_parella.vector[pos].dia<<' '<<t_parella.vector[pos].mes<<' '<<t_parella.vector[pos].any<<' '<<t_parella.vector[pos].sang_pacient<<' '<<t_parella.vector[pos].hospital<<' '<<t_parella.vector[pos].ciutat<<' '<<t_parella.vector[pos].codi_donant<<' '<<t_parella.vector[pos].sang_donant<<endl;
}

void consulta_d_un_pacient(Taula_Parella t_parella){
    //pre: cert
    //post: si el codi de pacient existeix, mostra la informacio del pacient.
    string codi_pacient;
    cin>>codi_pacient;
    int pos;
    bool existeix;
    existeix_amb_posicio(codi_pacient,t_parella,pos,existeix);
    if(existeix)mostrar_pacient(t_parella,pos);
    else cout<<"CODI INEXISTENT"<<endl;
}

void existeix_donant_amb_posicio(string codi_donant,Taula_Parella t_parella,int& pos,bool& existeix){
    //pre: cert
    //post: si el codi_pacient existeix a la t_parella retorna cert i la posicio on es troba, altrament retorna fals, tambe retorna la posicio.
    existeix=false;
    pos=0;
    while(pos<t_parella.n and not existeix){
        if(t_parella.vector[pos].codi_donant==codi_donant){
            existeix=true;
        }
        else pos++;
    }
}

void mostrar_donant(Taula_Parella t_parella,int pos){
    //pre: cert
    //post: mostra l'informacio del donant de la t_parella.vector[pos]
    cout<<t_parella.vector[pos].codi_donant<<' '<<t_parella.vector[pos].sang_donant<<' '<<t_parella.vector[pos].codi_pacient<<' '<<t_parella.vector[pos].dia<<' '<<t_parella.vector[pos].mes<<' '<<t_parella.vector[pos].any<<' '<<t_parella.vector[pos].sang_pacient<<' '<<t_parella.vector[pos].hospital<<' '<<t_parella.vector[pos].ciutat<<endl;

}

void consulta_d_un_donant(Taula_Parella t_parella){
    //pre:cert
    //post:si el codi de donant existeix mostra la informacio del donant i del seu pacient asociat, altrament mostra que el codi es inexistent
    string codi_donant;
    cin>>codi_donant;
    int pos_donant;
    bool existeix_donant;
    existeix_donant_amb_posicio(codi_donant,t_parella,pos_donant,existeix_donant);
    if(existeix_donant)mostrar_donant(t_parella,pos_donant);
    else cout<<"CODI INEXISTENT"<<endl;
}

void buscar_donants_compatibles(int compatibilitat,Taula_Parella t_parella,int& compt){
    //pre: cert
    //post:es busquen els donants compatibles de el codi de pacient i es mostren
    for(int i=0;i<t_parella.n;i++){
        if(compatibilitat%t_parella.vector[i].compatibilitat_donant==0){
            mostrar_donant(t_parella,i);
            compt++;
        }
    }

}

void possibles_donants(Taula_Parella t_parella){
    //pre:cert
    //post: mostra el possibles donants d'un pacient i els mostra ordenadament per codi ascendent
    string codi_pacient;
    cin>>codi_pacient;
    int pos;
    int compt=0;
    bool existeix;
    existeix_amb_posicio(codi_pacient,t_parella,pos,existeix);
    if(existeix){
        buscar_donants_compatibles(t_parella.vector[pos].compatibilitat_pacient,t_parella,compt);
        if(compt==0)cout<<"NO N'HI HA CAP"<<endl;
    }
    else cout<<"CODI INEXISTENT"<<endl;
}

bool menor_data(Pacient_Donant p,Pacient_Donant q){
    //pre: p.compatibilitat==q.compatibilitat
    //post: retorna true si la data d'entrada al pool de p es menor que la de q
    bool menor=false;
    if(p.any<q.any)menor=true;
    else if (p.any==q.any){
        if(p.mes<q.mes)menor=true;
        else if(p.mes==q.mes){
            if(p.dia<q.dia)menor=true;
        }
    }
    return menor;
}

bool es_menor(Pacient_Donant p,Pacient_Donant q){
    //pre:cert
    //post:retorna cert si el pacient p es menor que el pacient q segons el nostre criteri d'ordenacio
    bool menor=false;
    if(p.compatibilitat_pacient==q.compatibilitat_pacient)menor=menor_data(p,q);
    else if (p.compatibilitat_pacient<q.compatibilitat_pacient)menor=true;
    else menor=false;
    return menor;
}

void ordenar_taula_per_grup_sanguini(Taula_Parella& t_parella){
    //pre:cert
    //post:ordena la taula per grup sanguini en ordre ascendent i en cas d'empat s'ordena per data d'entrada al pool
    for(int i=0;i<t_parella.n-1;i++){
        for(int j=t_parella.n-1;j>i;j--){
            if(es_menor(t_parella.vector[j],t_parella.vector[j-1]))intercanvi(t_parella.vector[j],t_parella.vector[j-1]);
        }
    }
}

void buscar_possibles_receptors(int compatibilitat,Taula_Parella t_parella,int& compt){
    //pre:cert
    //post: busca els possibles receptors d'un donant i els mostra.
    for(int i=0;i<t_parella.n;i++){
        if(t_parella.vector[i].compatibilitat_pacient%compatibilitat==0){
            mostrar_pacient(t_parella,i);
            compt++;
        }
    }
}

void possibles_receptors(Taula_Parella t_parella){
    //pre: cert
    //post: mostra els possibles receptors ordenadament d'un donant entrat per teclat.
    string codi_donant;
    cin>>codi_donant;
    int pos,compatibilitat;
    int compt=0;
    bool existeix;
    existeix_donant_amb_posicio(codi_donant,t_parella,pos,existeix);
    if(existeix){
        compatibilitat=t_parella.vector[pos].compatibilitat_donant;
        ordenar_taula_per_grup_sanguini(t_parella);
        buscar_possibles_receptors(compatibilitat,t_parella,compt);
        if(compt==0)cout<<"NO N'HI HA CAP"<<endl;
    }
    else cout<<"CODI INEXISTENT"<<endl;
}

bool intercanvi_possible(Pacient_Donant p,Pacient_Donant q){
    //pre:cert
    //post:retorna cert si l'intercanvi es viable i falç altrament
    bool possible=false;
    if(p.compatibilitat_pacient%q.compatibilitat_donant==0){
        if(q.compatibilitat_pacient%p.compatibilitat_donant==0)possible=true;
    }
    return possible;
}

void intercanvi_viable(Taula_Parella t_parella){
    //pre:cert
    //post:retorna SI si l'intercanvi és viable i retorna NO altrament
    string p1,p2;
    cin>>p1>>p2;
    int pos1,pos2;
    bool existeix1,existeix2;
    existeix_amb_posicio(p1,t_parella,pos1,existeix1);
    existeix_amb_posicio(p2,t_parella,pos2,existeix2);
    if(not existeix1 or not existeix2)cout<<"CODI INEXISTENT"<<endl;
    else{
        bool intercanvi=intercanvi_possible(t_parella.vector[pos1],t_parella.vector[pos2]);
        if(intercanvi){
            cout<<"SI"<<endl;
        }
        else cout<<"NO"<<endl;
    }
}

void mostrar_parella(Pacient_Donant p,Pacient_Donant q){
    //pre:cert
    //post:mostra per pantalla l'intercanvi possible
    cout<<p.codi_pacient<<' '<<p.sang_pacient<<' '<<q.codi_pacient<<' '<<q.sang_pacient<<endl;
}

void llista_d_intercanvis_possibles(Taula_Parella t_parella){
    //pre:cert
    //post:mostra per pantalla tots els intercanvis possiles amb ordre.
    int comptador=0;
    for(int i=0;i<t_parella.n-1;i++){
        for(int j=i+1;j<t_parella.n;j++){
            if(t_parella.vector[i].compatibilitat_pacient%t_parella.vector[j].compatibilitat_donant==0){
                if(t_parella.vector[j].compatibilitat_pacient%t_parella.vector[i].compatibilitat_donant==0){
                    mostrar_parella(t_parella.vector[i],t_parella.vector[j]);
                    comptador++;
                }
            }
        }
    }
    if(comptador==0)cout<<"NO N'HI HA CAP"<<endl;
}

void gestio_del_pool(Taula_Parella& t_parella){
    //pre: t_parella.vector[0..t_parella.n-1] ha d'estar ordenades per codi ascendent
    //post: s'executen les diverses opcions que l'usuari entra per teclat fins que entra "SORTIR"
    string opcio=llegir_opcio();
    while(opcio!=EOS){
        if(opcio=="ALTA")donar_d_alta(t_parella);
        else if(opcio=="BAIXA")donar_de_baixa(t_parella);
        else if(opcio=="PACIENT")consulta_d_un_pacient(t_parella);
        else if(opcio=="DONANT")consulta_d_un_donant(t_parella);
        else if(opcio=="POSSIBLES_DONANTS")possibles_donants(t_parella);
        else if(opcio=="POSSIBLES_RECEPTORS")possibles_receptors(t_parella);
        else if(opcio=="INTERCANVI_VIABLE")intercanvi_viable(t_parella);
        else if(opcio=="LLISTAR_INTERCANVIS_POSSIBLES")llista_d_intercanvis_possibles(t_parella);
        cout<<endl;
        ordenar_taula_parella_per_codi(t_parella);
        opcio=llegir_opcio();
    }
}

int main()
{
    Taula_pacient t_pacient;
    Taula_donant t_donant;
    Taula_Parella t_parella;
    string fitxer_pacients;
    cout<<"INTRODUEIX NOM FITXER DE PACIENTS:"<<endl;
    cin>>fitxer_pacients;
    ifstream f_entrada_pacients(fitxer_pacients.c_str());
    if(not f_entrada_pacients.is_open())cout<<"ERROR OBERTURA FITXER"<<endl; //comprovar que el fitxer està obert o que existeix
    else{
        string fitxer_donants;
        cout<<"INTRODUEIX NOM FITXER DE DONANTS:"<<endl;
        cin>>fitxer_donants;
        ifstream f_entrada_donants(fitxer_donants.c_str());
        if(not f_entrada_donants.is_open())cout<<"ERROR OBERTURA FITXER"<<endl; //comprovar que el fitxer està obert o que existeix
        else{
            cout<<endl;
            llegir_fitxer_pacients(t_pacient,f_entrada_pacients);
            ordenar_taula_per_codi(t_pacient);
            llegir_fitxer_donants(t_donant,f_entrada_donants);
            ordenar_taula_per_codi_pacient(t_donant);
            interseccio_dels_vectors(t_parella,t_donant,t_pacient);
            gestio_del_pool(t_parella); //menú on es gestionen les opcions del usuari
        }
    }
    return 0;
}
