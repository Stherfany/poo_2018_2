#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

template<typename T>
struct Repositorio{
    map < string , T > rep;

    void add (string chave , T coisa){
        if(!existe(chave))
            rep[chave] = coisa;
        else
            cout << "usuario ja existe" << endl;
    }
    
    void rm (string chave){
        if(existe(chave)) rep.erase(chave);
    }

    bool existe (string chave){
        return rep.find(chave) != rep.end();
    }

    vector<T> getValue(){
        vector<T> vvalues;
        for (auto par : rep)
            vvalues.push_back(par.second);
        return vvalues;
    }

    T& get(string chave){
        auto it = rep.find(chave);
        if (it != rep.end())
            return it -> second;
        else 
            throw "funcionario nao existe";
    }
};

class Funcionario {
public:
    string nome;
    int max_diarias;
    int qtd_diarias = 0;
    int bonus;
    int salario;
    string cargo;

    Funcionario (string nome = " " , string cargo = " "){
        this -> nome = nome;
        this -> cargo = cargo;
    }

    virtual void set_Bonus (int bonus){
        this -> bonus = bonus;
    }

    virtual void addDiaria (){
            qtd_diarias++;
    }

    virtual void calcsalario () = 0;
    virtual string toString () = 0;
};

class Professor : public Funcionario {
public:
    char classe;
    int max_diarias = {2};
    
    Professor (string nome = " ", char classe = ' ') :
        Funcionario(nome, "Prof")
    {
        this -> classe = classe;
    }
    
    void calcsalario (){
        switch (classe) {
            case 'A': salario = 3000; break;
            case 'B': salario = 5000; break;
            case 'C': salario = 7000; break;
            case 'D': salario = 9000; break;
            case 'E': salario = 11000; break;
        }
        salario += (qtd_diarias*100) + bonus;
    }
    void addDiaria(){
        if(qtd_diarias < max_diarias){
            qtd_diarias++;
        }
        else 
            throw "limite de diarias atingido";
    }
    string toString(){
        string teacher;
        teacher = cargo + " " + nome + " classe " + classe + "\n";
        teacher += "salario " + to_string(salario);
        return teacher;
    }
};

class STA : public Funcionario {
public:
    int nivel;
    int max_diarias = {1};
    
    STA (string nome = " ", int nivel = 0) :
        Funcionario(nome, "STA")
    {
        this -> nivel = nivel;
    }
    
    void calcsalario (){
        salario = 3000 + (300*nivel) + (qtd_diarias*100) + bonus;
    }
    void addDiaria(){
        if(qtd_diarias < max_diarias){
            qtd_diarias++;
        }
        else 
            throw "limite de diarias atingido";
    }
    string toString(){
        string sta;
        sta = cargo + " " + nome + " " + to_string(nivel) + "\n";
        sta += "salario " + to_string(salario);
        return sta;
    }
};

class Terceirizado : public Funcionario {
public:
    int horas;
    bool insalubre = false;
    int max_diarias = {0};
    
    Terceirizado (string nome = " ", int horas = 0 , string ins = " ") :
        Funcionario(nome, "Ter")
    {
        if(ins == "sim") insalubre = true;
        this -> horas = horas;
    }
    
    void calcsalario (){
        if (insalubre) salario = (4 * horas) + 500 + (qtd_diarias*100) + bonus;
        salario = (4 * horas) + (qtd_diarias*100) + bonus;
    }

    string toString(){
        string ter;
        ter = cargo + " " + nome + " " + to_string(horas) + "h " ;
        if (insalubre) ter += "insalubre \n";
        else ter += "\n";
        ter += "salario " + to_string(salario);
        return ter;
    }
};

class Sistema{
    Repositorio <Funcionario*> repF;
public:

    void addP (string nome, char classe){
        repF.add(nome , new Professor (nome, classe));
    }
    
    void addSTA (string nome, int nivel){
        repF.add(nome , new STA (nome, nivel));
    }

    void addT (string nome, int horas, string ins){
        repF.add(nome , new Terceirizado (nome, horas, ins));
    }

    void rmF (string nome){
        auto fun = repF.get(nome);
        repF.rm(nome);
        cout << fun -> cargo + " " + fun -> nome + " removido\n";
    }

    void show (string nome){
        repF.get(nome) -> calcsalario();
        cout << repF.get(nome) -> toString() << endl;
    }

    void addBonus (int valor){
        int bonus = valor/repF.rep.size();
        for (auto func : repF.getValue()){
            func -> set_Bonus(bonus);
        }
    }

    void addDiaria (string nome){
        auto func = repF.get(nome);
        if(dynamic_cast <Terceirizado*> (func))
            throw "funcionario nao pode receber diaria";
        else func -> addDiaria();
    }
};

int main (){
    Sistema sis;

    sis.addP("ugo", 'B');
    sis.addT("dias", 45, "sim");
    sis.addSTA("gui", 6);
    sis.show("ugo");
    sis.show("dias");
    sis.show("gui");
    sis.addBonus(300);
    sis.show("ugo");
    sis.show("dias");
    sis.show("gui");
    try{sis.addDiaria("ugo");
    } catch (const char* e){
        cout << e << endl;
    }
    try{sis.addDiaria("dias");
    } catch(const char* e){
        cout << e << endl;
    }
    try{sis.addDiaria("gui");
    } catch (const char* e){
        cout << e << endl;
    }
    sis.show("ugo");
    sis.show("dias");
    sis.show("gui");
    sis.rmF("ugo");
    try{ sis.show("ugo");
    } catch (const char* e){
        cout << e << endl;
    }
    return 0;
}
