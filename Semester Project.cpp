#include <iostream>
#include <fstream>

using namespace std;
class user 
{
private:
    string name;
    int age;
    string city;
    int cnic;
    string role;//humain bataye ga kay user admin hai candidate hai ya voter hai
public:
    user()
    {
        name="";
        age=0;
        city="";
        cnic=0;
        role="";
    }
    user(string n,int a,string c,int cn,string r)
    {
        name=n;
        age=a;
        city=c;
        cnic=cn;
        role=r;
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
    void setrole(string r) 
    {
        cout << "enter your role :" << endl;
        cin >> r;
        role=r;
    }
    string getname() const 
    {
        return name;
    }
    int getage() 
    {
        return age;
    }
    string getcity() 
    {
        return city;
    }
    int getcnic() 
    {
        return cnic;
    }
    string getrole()
    {
        return role;
    }
    void displayuserinfo()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"CNIC: "<<cnic<<endl;
        cout<<"City: "<<city<<endl;
        cout<<"Role: "<<role<<endl;
    }
    virtual void showrole() //ye function override ho ga sari classes main hain
    {
        cout<<"Role: "<<role<<endl;
    }
    void saveToFile() 
    {
        ofstream file("user.txt", ios::app);
        if (file.is_open()) 
        {
            file << name << endl;
            file << age << endl;
            file << cnic << endl;
            file << city << endl;
            file << role << endl;
            file.close();
            cout << "User data saved to file successfully."<<endl;
        } 
        else 
        {
            cout << "Error opening file for writing."<<endl;
        }
    }
    void readAllUsers() 
    {
        ifstream file("user.txt");
        string line;
        if (file.is_open()) 
        {
            cout << "\nAll Users from File:"<<endl;
            while (getline(file, line)) 
            {
                cout << line << endl;
            }
            file.close();
        } 
        else 
        {
            cout << "Error opening file for reading."<<endl;
        }
    }
    ~user(){}
};

class candidate :public user 
{
private:
    string electsymbol;
    int specialno;
public:
    candidate(string n, int a, string c, int cn, string r, string es, int sn) :user(n, a, c, cn,r), specialno(sn), electsymbol(es) {};
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

    voter(string n, int a, string c, int cn, string r, string vid): user(n, a, c, cn, r), voterID(vid), hasvoted(false) {}

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
