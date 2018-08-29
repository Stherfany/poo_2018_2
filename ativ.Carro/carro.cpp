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
    if(pass==passMax){
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
    if((pass>0) && (gas>0)){
        km=km+dist;
        gas=gas+(dist%10);
    }
    else {
        if(gas<=0){
            cout<<"fail: gasolina insuficiente"<<endl;
        }
        else {
            
        }
    }
}
};


int main(){
    Carro carro={0,10, 0,2,0};
    string op;
    int g;
    while (true){
        cin>>op;
        if(op=="show"){
            carro.show();
        }
        else {
            if(op=="passag"){
            carro.passag();
        }}
        if(op=="out"){
            carro.out();
        }
        if(op=="fuel"){
            float g;
            cin>>g;
            carro.fuel(g);
        }
    }
    return 0;
}