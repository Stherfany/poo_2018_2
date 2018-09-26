#include <iostream>
#include <sstream>
using namespace std;

class Pet {
public:
    int energy;
    int hungry;
    int clean;
    int age;
    int diamonds;
    int energyMax;
    int hungryMax;
    int cleanMax;
    bool status;

    Pet(int energyMax = 20, int hungryMax = 10, int cleanMax = 15){
        this->energyMax = energyMax;
        this->hungryMax = hungryMax;
        this->cleanMax = cleanMax;
        this->energy = energyMax;
        this->hungry = hungryMax;
        this->clean = cleanMax;
        this-> age = 0;
        this-> diamonds = 0;
        this-> status = true;
    }

    bool verifica (){
        if (energy <= 0) {
            energy = 0;
            cout<<"fail: petinho morreu de fraqueza"<<endl;
            return false;
        }
        if (hungry <= 0) {
            hungry = 0;
            cout<<"fail: petinho morreu de fome"<<endl;
            return false;
        }
        if (clean <= 0) {
            clean = 0;
            cout<<"fail: petinho morreu de sujeira"<<endl;
            return false;
        }
        return true;
    }

    void show(){
        cout<<"E:"<<energy<<"/"<<energyMax<<", "<<"H:"<<hungry<<"/"<<hungryMax<<", "
            <<"C:"<<clean<<"/"<<cleanMax<<", "<<"D:"<<diamonds<<", "<<"A:"<<age<<endl;
    }

    void play(){
        energy -= 2;
        hungry -= 1;
        clean -= 3;
        age += 1;
        diamonds += 1;
        if(!verifica()) status = false;
    }

    void eat (){
        energy -= 1;
        if ((hungry += 4) > hungryMax){
            hungry=hungryMax;
        }
        clean -= 2;
        age += 1;
        if(!verifica()) status = false;
    }
    
    void sleep(){
        if ((energyMax - energy) >= 5){
            hungry -= 1;
            age += (energyMax-energy);
            energy = energyMax;
            if(!verifica()) status = false;
        }
        else cout<<"fail: pet nao esta com sono"<< endl;
    }

    void shower(){
        hungry -= 1;
        energy -= 3;
        age += 2;
        clean = cleanMax;
        if(!verifica()) status = false;
    }
};

int main (){
    Pet petinho;
    string op;
    while(true){
        cin>>op;
        if(op=="show"){
            petinho.show();
        }
        else if(op=="fim") break;
        else if (petinho.status){
            if(op=="init"){
                int energy,hungry,clean;
                cin >> energy >> hungry >> clean;
                petinho = Pet(energy,hungry,clean);
            }
            if(op=="brincar"){
                petinho.play();
            }
            else if(op=="comer"){
                petinho.eat();
            }
            else if(op=="dormir"){
                petinho.sleep();
            }
            else if(op=="banhar"){
                petinho.shower();
            }
        }
        else cout<<"fail: petinho morreu"<< endl;
    }
    return 0;
}