#include <iostream>
#include <ctime>
#include <string>
#include "MD5.h"
using namespace std;
int Chislo_p(){
    int p = 0;

    p = 10 + rand()%89;
    for(int i = 2;i <= p/2;i++){
        if(p%i == 0){
            return 0;
        }
    }
    return p;
}

int Chislo_q(){
    int q = 0;
    q = 10 + rand()%89;
    for(int i = 2;i <= q/2;i++){
        if(q%i == 0){
            return 0;
        }
    }
    return q;
}

int Chislo_e(){
    int e = 0;
    e = 2 + rand()%1000;
    return e;
}

int Evclid(int a, int b){
    int q = 0;
    int v = 0;
    do{
        q = a/b;
        v = a%b;
        a = b * q + v;
        a = b;
        b = v;
    }while(b!=0);
    return a;
}

int* Obratniy_q(int a, int b, int c, int d){
    int q = 0;
    int v = 0;
    int m_size = 0;
    do{
        q = a/b;
        v = a%b;
        a = b * q + v;
        a = b;
        b = v;
        m_size += 1;
    }while(b!=0);

    int *mass_q_el = new int[m_size];
    //cout << " 00000 "<< m_size << " 00000 " << endl;
    q = 0;
    v = 0;
    int i = 0;
    do{
        q = c/d;
        v = c%d;
        c = d * q + v;
        c = d;
        d = v;
        mass_q_el[i] = q;
        i++;
    }while(i < m_size);
    return mass_q_el;
}

int Obratniy_q_size(int a, int b, int c, int d){
    int q = 0;
    int v = 0;
    int m_size = 0;
    do{
        q = a/b;
        v = a%b;
        a = b * q + v;
        a = b;
        b = v;
        m_size += 1;
    }while(b!=0);
    //cout << " 00000 "<< m_size << " 00000 " << endl;
    return m_size;
}

int Obratniy_el(int f, int *mass_q_el, int q_size){

    int *mass_vk_el = new int[q_size+2];
    mass_vk_el[0] = 0;
    mass_vk_el[1] = 1;
    for(int i = 2; i <= q_size; i++){
        mass_vk_el[i] = mass_vk_el[i-2] - mass_vk_el[i-1] * mass_q_el[i-2];
    }
    int vk_el = 0;
    do{
        cout << mass_vk_el[vk_el] << " ";
        vk_el++;
    }while(vk_el != q_size+1);
    if(mass_vk_el[q_size] < 0){
        mass_vk_el[q_size] += f;
    }
    //delete[] mass_vk_el;
    return mass_vk_el[q_size];
}

int keys(int a, int b, int c){
    int r = a;
    for(int i = 1;i < b;i++){
        r*=a;
        while (r>=c){r-=c;}
    }
    return r;
}

int main(int argc, char* argv[])
{
    int p = 0;
    int q = 0;
    int n = 0;
    int f = 0;
    int e = 0;
    int ev = 0;
    int q_el = 0;
    int a = 0;
    srand(time(NULL));

    do{ p = Chislo_p();
    }while(p==0);

    do{ q = Chislo_q();
    }while(q==0 || q==p);

    n = p*q;

    f = (p-1)*(q-1);

    do{
        e = Chislo_e();
        ev = Evclid(f,e);
    }while(ev != 1);

    int *mass_q_el = Obratniy_q(f,e,f,e);
    int mass_q_el_size = Obratniy_q_size(f,e,f,e);

    cout << "Chislo p : " << p << endl;
    cout << "Chislo q : " << q << endl;
    cout << "Chislo n : " << n << endl;
    cout << "Chislo f : " << f << endl;
    cout << "Chislo e : " << e << endl;
    cout << "Chislo EVCLID(f,e) : " << ev << endl;
    cout << "Znachenia q* : " ;
    for (q_el = 0; q_el<mass_q_el_size; q_el++){
        cout << mass_q_el[q_el] << " ";
    }

    cout << endl;
    cout << "Chislo el q* : " << q_el << endl;
    cout << "Znachenia vk* : ";
    int Ob_el = Obratniy_el(f,mass_q_el,mass_q_el_size);
    cout << endl;
    cout << "Obratniy el : " << Ob_el << endl;

    int m = 5;
    int c = keys(m,e,n);
    int t = keys(c,Ob_el,n);
    cout << "text m: " << m << " ,text c: " << c << " ,text t: " << t << endl;
    if(t==m){
        cout << "ok";
    }



    cout << "############" << endl;
    cout << "Vvedite TEXT :" << endl;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::cout << md5(argv[i]) << std::endl;
        }
    }
    else {

        string line;
        cin >> line;
        cout << endl;
        cout << "HESH(TEXT) :" << endl;
        string hesh = md5(line);
        cout << hesh << endl;

        string text;
        text = hesh;
        int len_t = text.size();
        int *mass_text = new int[len_t];
        for(int i = 0; i < len_t; i++){
            mass_text[i] = int(text[i]);
            //cout << endl;
            //cout << text[i] << " = " << mass_text[i];
        }
        cout << endl;
        cout << endl;

        cout << "############" << endl;
        cout << "ELECT PODPIS(HESH) :" << endl;
        for(int i = 0; i < len_t; i++){
            mass_text[i] = int(text[i]);
            mass_text[i] = keys(mass_text[i],e,n);
            cout << mass_text[i] << " ";

        }
        cout << endl;
        cout << endl;

        cout << "############" << endl;
        cout << "Vvedite ZAKRT CLUCH :" << endl;
        int zak = 0;
        cin >> zak;
        cout << endl;
        cout << "############" << endl;
        cout << "HESH(TEXT) :" << endl;
        for(int i = 0; i < len_t; i++){
            mass_text[i] = keys(mass_text[i],zak,n);
            cout << char(mass_text[i]);
        }
        cout << endl;
        cout << endl;

        delete[] mass_q_el;
        delete[] mass_text;

    }


    return 0;
}