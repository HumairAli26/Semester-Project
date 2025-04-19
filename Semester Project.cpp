#include <iostream>
using namespace std;
class user 
{
private:
    string name;
    int age;
    string city;
    int cnic;
public:
    user()
    {
        name="";
        age=0;
        city="";
        cnic=0;
    }
    user(string n,int a,string c,int cn)
    {
        name=n;
        age=a;
        city=c;
        cnic=cn;
    }
    void setname(string n) 
    {
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

class candidate :public user 
{
private:
    string electsymbol;
    int specialno;
public:
    candidate(string n, int a, string c, int cn, string es, int sn) :user(n, a, c, cn), specialno(sn), electsymbol(es) {};
    int getspecialno() 
    {
        return specialno;
    }
    string getelectsymbol() 
    {
        return electsymbol;
    }
};

class voter : public user
{
private:
    string voterID;
    bool hasvoted;
public:
    voter() : user(), voterID(""), hasvoted(false) {}

    voter(string n, int a, string c, int cn, string vid): user(n, a, c, cn), voterID(vid), hasvoted(false) {}

    void sethasvoted(bool voted) 
    {
        hasvoted = voted;
    }

    bool gethasvoted() const 
    {
        return hasvoted;
    }

    void castvote() 
    {
        if (!hasvoted) 
        {
            hasvoted = true;
            cout << getname() << " has successfully voted!" << endl;
        } else 
        {
            cout << getname() << " has already voted!" << endl;
        }
    }

    void displayinfo()
    {
        cout << "Name: " << getname() << endl;
        cout << "Age: " << getage() << endl;
        cout << "City: " << getcity() << endl;
        cout << "CNIC: " << getcnic() << endl;
        cout << "Voter ID: " << voterID << endl;
        cout << "Has Voted: " << (hasvoted ? "Yes" : "No") << endl;
    }
};
