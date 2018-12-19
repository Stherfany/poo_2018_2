#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Pass{
public:
    virtual string getId() = 0;
    virtual string toString() = 0;
    virtual ~Pass(){};
};

class Pess : public Pass{
private:
    string Id;
public: 
    Pess(string Id = " ") :
        Id(Id)
    {
    }

    string getId (){
        return Id;
    }

    string toString (){
        return Id;
    }

    ~Pess(){
    }
};

class Carga : public Pass{
private:
    string Id;
    float peso;
public: 
    Carga(string Id = " ", float peso = 0) :
        Id(Id), peso(peso)
    {
    }

    string getId (){
        return Id;
    }

    float getPeso (){
        return peso;
    }

    string toString (){
        return Id + ":" + to_string(peso);
    }

    ~Carga(){
    }
};

class Vagao{
public:
    virtual bool embarcar (Pass* pass) = 0;
    virtual bool desembarcar (string idpass) = 0;
    virtual bool existe (string idpass) = 0;
    virtual string toString () = 0;
    virtual ~Vagao(){};
};

class VagaoP : public Vagao{
private:
    vector<Pess*> vagaoP;
public:
    VagaoP(int capacidade = 0) :
        vagaoP(capacidade, nullptr)
    {
        /*for (int i = 0; i < capacidade; i++)
            vagaoP.push_back(nullptr);*/
    }
    
    ~VagaoP(){
        for(auto pess : vagaoP){
            delete pess;
        }
    }

    bool embarcar(Pass* pass){
        if (Pess* pess = dynamic_cast<Pess*>(pass)){
            for(unsigned int i = 0; i < vagaoP.size(); i++){
                if(vagaoP[i] == nullptr){
                    if(!existe(pess -> getId())){
                        vagaoP[i] = pess;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool desembarcar (string idpess){
        for(unsigned int i = 0; i < vagaoP.size(); i++){
            if(vagaoP[i] != nullptr && vagaoP[i] -> getId() == idpess){
                vagaoP[i] = nullptr;
                return true;
            }
        }
        return false;
    }

    bool existe (string id){
        for (auto pess : vagaoP){
            if (pess != nullptr && pess -> getId() == id)
                return true;
        }
        return false;
    }

    string toString (){
        string vagao;
        for (auto pessoa : vagaoP){
            if (pessoa == nullptr)
                vagao += "- ";
            else vagao += pessoa -> getId() + " ";
        }
        return "[ " + vagao + "]";
    }
};

class VagaoC : public Vagao{
private:
    map<string, Carga*> vagaoC;
    int pesoMax;
public:
    VagaoC(int pesoMax = 0){
        this -> pesoMax = pesoMax;
    }
    
    ~VagaoC(){
        for(auto carga : vagaoC){
            delete carga.second;
        }
    }

    bool existe (string chave){
        if(vagaoC.find(chave) != vagaoC.end())
            return true;
        else return false;
    }

    bool embarcar(Pass* pass){
        if (Carga* carga = dynamic_cast<Carga*>(pass)){
            if(carga -> getPeso() <= pesoMax){
                if(!existe(carga -> getId())){
                    vagaoC[carga -> getId()] = carga;
                    pesoMax -= carga -> getPeso();
                    return true;
                }
            }

        }
        return false;
    }

    bool desembarcar(string idC){
        if(existe(idC)){
            pesoMax += vagaoC.find(idC) -> second -> getPeso();
            vagaoC.erase(vagaoC.find(idC));
            return true;
        }
        return false;
    }

    string toString(){
        string vagaocar;
        vagaocar = "( ";
        for (auto par : vagaoC){
            vagaocar += par.second -> toString() + " ";
        }
        vagaocar += "_" + to_string(pesoMax) + " )";
        return vagaocar;
    }
};

class Trem{
private:
    int maxVagoes;
    vector <Vagao*> vagoes;

public:
    Trem(int maxVagoes = 0) :
        maxVagoes(maxVagoes)
    {
    }
    
    ~Trem(){
        for(auto vagao : vagoes){
            delete vagao;
        }
    }
    
    bool addV (Vagao* vag){
        if ((int) vagoes.size() < maxVagoes) {
            vagoes.push_back(vag);
            return true;
        }
        return false;
    }

    bool embarcar (Pass* coisa){
        for (auto vagao : vagoes){
            if (vagao -> embarcar(coisa))
                return true;
        }
        return false;
    }

    bool desembarcar (string idE){
        for (auto vagao : vagoes){
            if (vagao -> desembarcar(idE))
                return true;
        }
        return false;
    }

    string toString (){
        string trem;
        trem = "Trem ";
        for (auto vagao : vagoes){
            trem += vagao -> toString() + " ";
        }
        return trem;
    }
};

template<typename T>
T read (stringstream& ss){
    T value;
    ss >> value;
    return value;
}

class Controller{
private:
    Trem trem;
public:
    Controller(){
    }

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "init"){
            trem = Trem(read<int>(ss));
        } else if(op == "addvp"){
            Vagao* vagao = new VagaoP (read<int>(ss));
                if(!trem.addV(vagao))
                    delete vagao;
        } else if(op == "embP"){
            Pess* pess = new Pess (read<string>(ss));
            trem.embarcar(pess);
        } else if(op == "des"){
            if(!trem.desembarcar(read<string>(ss)))
                cout << "fail: nao esta no trem" << endl;
        } else if (op == "mostrar"){
            cout << trem.toString() << endl;
        } else if(op == "addvc"){
            Vagao* vagao = new VagaoC (read<float>(ss));
                if(!trem.addV(vagao))
                    delete vagao;
        } else if(op == "embC"){
            Carga* carga = new Carga (read<string>(ss),read<float>(ss));
            trem.embarcar(carga);
        } else cout << "comando invalido" << endl;
    }

    void exec (){
        string line;
        while (true){
            getline(cin, line);
            if(line == "end")
                break;
            shell(line);
        }
    }
};

int main(){
    Controller contr;
    contr.exec();
    return 0;
}