#include <iostream>
using namespace std;

struct Carro{
    float gas; 
    float gasMax;
    int pass;
    int passMax;
    float km;

void show(){
    cout<<"pass: "<< pass <<", gas: "<< gas<<", km: "<< km<< endl;
}
void passag(){
    if(pass>=passMax){
        cout<< "fail: limite de passageiros atingido"<<endl;
    }
    else {
        pass++;
        cout<< "done"<< endl;
    }
}
void out(){
    if(pass > 0){
        pass--;
    }
    else {
        cout<< "fail: nao ha ninguem no carro"<< endl;
    }
}
void fuel(int b){
    if(b>gasMax){
        gas=gasMax;
        cout<<"done"<<endl;
    }
    else {
        gas=gas+b;
        cout<<"done"<<endl;
    }
}
void drive(int dist){
    if(pass==0){
        cout<<"fail: nao ha passageiros"<<endl;
    }
    else{
        if(gas<dist/10){
            cout<<"fail: gasolina insuficiente"<<endl;
        }
        else {
            km=km+dist;
            gas=gas-(dist/10);
            cout<<"done"<<endl;
        }
    }
}
};

int main(){
    Carro carro={0,10, 0,2,0};
    string op;
    while (true){
        cin>>op;
        if(op=="show"){
            carro.show();
        }
        if(op=="fim"){
            break;
        }
        if(op=="passag"){
            carro.passag();
        }
        if(op=="out"){
            carro.out();
        }
        if(op=="fuel"){
            float g;
            cin>>g;
            carro.fuel(g);
        }
        if(op=="drive"){
            float d;
            cin>>d;
            carro.drive(d);
        }
    }
    return 0;
}