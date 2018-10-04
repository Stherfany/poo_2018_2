#include <iostream>
#include <vector>

using namespace std;

class Cliente{
public:
    string id;
    string fone;
    bool existe;

    Cliente(string id = " ", string fone = " ", bool existe = false){
        this -> id = id;
        this -> fone = fone;
        this -> existe = existe;
    }

    void toString(){
        cout << id << ":" << fone;
    }
};

class Cinema{
public:
    vector<Cliente> cadeiras;
    
    Cinema (int tam = 0){
        for(int i=0; i<tam; i++){
            cadeiras.push_back(Cliente());
        }
    }

    void toString(){
        cout << "[";
        for(int i = 0; i<(int)cadeiras.size(); i++){
            if(cadeiras[i].existe == true){
                cadeiras[i].toString();
            }
            else cout<< " -";
        }
        cout << " ]" << endl;
    }

    bool reservar(string id, string fone, int ind) {
        if(cadeiras[ind].existe == true){
            cout << "fail: cadeira ja esta ocupada" << endl;
            return false;
        }
        for(auto cliente : cadeiras){
            if (cliente.id == id){
                cout << "fail: cliente ja esta na sala" << endl;
                return false;
            }
        }
        cadeiras[ind] = Cliente(id,fone,true);
        return true;
    }
    bool cancelar (string id){
        for(int i = 0; i < (int)cadeiras.size(); i++){
            if (cadeiras[i].id == id){
                cadeiras[i] = Cliente();
                return true;
            }
        }
        cout << "fail: cliente nao esta na sala";
        return false;
    }
};

int main(){
    Cinema sala;
    string op;
    while(true){
        cin >> op;
        if(op == "init"){
            int tam;
            cin>> tam;
            sala = Cinema(tam);
        }
        else if(op == "show"){
            sala.toString();
        }
        else if(op == "reservar"){
            string id, fone;
            int ind;
            cin >> id >> fone >> ind;
            sala.reservar(id,fone,ind);
        }
        else if(op == "cancelar"){
            string id;
            cin >> id;
            sala.cancelar(id);
        }
    }
    return 0;
}