#include <iostream>
using namespace std;
class user {
private:
    string name;
    int age;
    string city;
    int cnic;
public:
    void setname(string n) {
        cout << "enter your name :" << endl;
        cin >> n;
        name = n;
    }
    void setage(int a) {
        cout << "enter your age :" << endl;
        cin >> a;
        age = a;
    }
    void setcity(string c) {
        cout << "enter city name :" << endl;
        cin >> c;
        city = c;
    }
    void setcnic(int cn) {
        cout << "enter your cnic :" << endl;
        cin >> cn;
        cnic = cn;
    }
    string getname() const {
        return name;
    }
    int getage() {
        return age;
    }
    string getcity() {
        return city;
    }
    int getcnic() {
        return cnic;
    }
    void displayuserinfo() {
        
}
};
class candidate :public user {
private:
    string electsymbol;
    int specialno;
public:
    candidate(string n, int a, string c, int cn, string es, int sn) :user(n, a, c, cn), specialno(sn), electsymbol(es) {};
    int getspecialno() {
        return specialno;
    }
    string getelectsymbol() {
        return electsymbol;
    }

};
class voter :public user{
private:
    string votercnic;
    bool hasvoted;
public:
    voter() :user(), cnic(" "), hasvoted(false){}
    voter(string id, string n, string e, string c) :
        user(id, n, e), cnic(c), hasvoted(false) {}
    void setcnic(string c) {
        cnic = c;
    }
    void sethasvoted(bool voted) {
        hasvoted = voted;
    }
    string getcnic() {
        return cnic;
    }
    bool gethasvoted() {
        return hasvoted;
    }
    void castvote() {
        if (!hasvoted) {
            hasvoted = true;
            cout << name << "  has successfully voted!" << endl;
        }
        else {
            cout << name << " has successfully voted !" << endl;
        }
   }
    void disaplayinfo() const {
        displayuserinfo();
        cout << " voter cnic = " << votercnic << endl;
        cout << " hasvoted = " << (hasvoted ? "yes" : "no") << endl;
    }

};