#include<iostream>

using namespace std;

class User
{
private:
    string name;
    int age;
    string cnic;
    string city;
public:
    void setname()
    {
        string n;
        cout<<"Enter Name: ";
        cin>>n;
        name=n;
    }
    void setage()
    {
        int a;
        cout<<"Enter Age: ";
        cin>>a;
        age=a;
    }
    void setcnic()
    {
        string nic;
        cout<<"Enter CNIC: ";
        cin>>nic;
        cnic=nic;
    }
    void setcity()
    {
        string c;
        cout<<"Enter City: ";
        cin>>c;
        city=c;
    }
    string getname()
    {
        return name;
    }
    int getage()
    {
        return age;
    }
    string getcnic()
    {
        return cnic;
    }
    string getcity()
    {
        return city;
    }
};