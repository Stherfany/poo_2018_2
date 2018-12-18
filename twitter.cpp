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
    
    bool existe (string chave){
        return rep.find(chave) != rep.end();
    }

    vector<T> getValue(){
        vector<T> vvalues;
        for (auto par : rep)
            vvalues.push_back(par.second);
        return vvalues;
    }

    T* get(string chave){
        auto it = rep.find(chave);
        if (it != rep.end())
            return &it -> second;
        else 
            throw"usuario nao existe";
    }
};

class Tweet{
public:
    int id;
    string username;
    string tweet;
    vector<string> likes;
    Tweet(int id = 0 , string username = "" , string tweet = ""){
        this -> id = id;
        this -> username = username;
        this -> tweet = tweet;
    }

    void Like (string username){
            likes.push_back(username);
    }

   string toString (){
       string vlike;
       for (auto like : likes)
            vlike += like + " ";
       return to_string(id) + " " + username + ": " + tweet + " {" + vlike + "}";
   }
};

class TweetGenerator {
public:
    int nextId = 0;
    Repositorio <Tweet>* repTweet;

    TweetGenerator (Repositorio<Tweet>* repTweet){
        this -> repTweet = repTweet;
    }

    Tweet* gerar (string username, string tweet){
        repTweet -> add (to_string(nextId) , Tweet(nextId, username, tweet));
        nextId++;
        return repTweet -> get(to_string(nextId - 1));
    }

};

class User{
public:
    string username;
    int notRead;
    vector<Tweet*> timeline;
    vector<Tweet*> mytweets;
    vector<User*> seguidores;
    vector<User*> seguidos;

    User(string username = "" , int notRead = 0){
        this -> username = username;
        this -> notRead = notRead;
    }

    void seguir (User* seguido){
        seguidos.push_back(seguido);
        seguido -> seguidores.push_back(this);
    }

    void newT (Tweet* tw){
        mytweets.push_back(tw);
        for (auto seguidor : seguidores){
            seguidor -> timeline.push_back(tw);
            seguidor -> notRead++;
        }
    }

    string toString(){
        string um;
        string dois;
        for (auto user : seguidos)
            um = um + user -> username + " ";
        for (auto user : seguidores)
            dois = dois + user -> username + " ";
        return username + "\n " + 
            "seguidos" + "[" + um + "]" + "\n " +
            "seguidores" + "[" + dois + "]" + "\n";
    }

    string show_timeline (){
        string lista;
        if (timeline.size() == 0)
            throw "nao ha tweet";
        for (auto it = timeline.end()-1; it >= timeline.begin(); it--) {
            lista += (*it) -> toString() + "\n";
        }
        notRead = 0;
        return lista;
    }

    string show_meus (){
        string mine;
        if (mytweets.size() == 0)
            throw "nao ha tweet";
        for (auto it = mytweets.end() -1; it >= mytweets.begin(); it--) {
            mine += (*it) -> toString() + "\n";
        }
        return mine;
    }

    string nao_lidos (){
        string nRead;
        for (auto i = 1; i <= notRead ; i++)
            nRead += timeline[timeline.size()-i] -> toString() + "\n";
        notRead = 0;
        return nRead;
    }

    bool dar_like (string username, int id){
        for (auto t : timeline){
            if (t->id == id){
                t ->  Like (username);
                return true;
            }
        }
        throw "tweet nao existe";
    }
};

class Twitter {
public:
    Repositorio<User>* repu;
    Repositorio<Tweet>* rept;
    TweetGenerator* gerador;

    Twitter(){
        repu = new Repositorio<User>;
        rept = new Repositorio<Tweet>;
        gerador = new TweetGenerator (rept);
    }
    
    void addU (string username){
        repu -> add(username, User(username));
    }

    void listarUsers (){
        for (auto user : repu -> getValue())
            cout << user.toString();
    }

    void seguir (string us1 , string us2){
        repu -> get(us1) -> seguir(repu -> get(us2));
    }
    
    void twittar (string username, string tweet){
        auto tw = gerador -> gerar(username, tweet);
        repu -> get(username) -> newT (tw);
    }

    void timeline_user (string username){
        cout << repu -> get(username) -> show_timeline();
    }

    void my_profile (string username) {
        cout << repu -> get(username) -> show_meus();
    }

    void like (string username, int idt){
        repu -> get(username) -> dar_like(username, idt);
    }

    void nao_lidos (string username){
        cout << repu -> get(username) -> nao_lidos();
    }
};

int main(){
    Twitter twitter;

    twitter.addU("maysla");
    twitter.addU("maysla");
    twitter.addU("dada");
    twitter.addU("davi");
    twitter.addU("sther");
    twitter.listarUsers();

    twitter.seguir("sther","davi");
    twitter.seguir("sther","dada");
    twitter.seguir("dada","maysla");
    twitter.seguir("davi","dada");
    twitter.seguir("sther","maysla");
    twitter.listarUsers();

    twitter.twittar("sther","sera que vou conseguir?");
    twitter.twittar("davi","mee");
    twitter.twittar("sther","love u, mj <3");
    twitter.nao_lidos("sther");
    twitter.timeline_user("sther");
    twitter.my_profile("sther");
    twitter.my_profile("davi");
    try {twitter.like("sther", 1);}
    catch (const char* e) {
        cout<< e <<  endl;
    }
    twitter.my_profile("davi");

    return 0;
}