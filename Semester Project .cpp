#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void interface_logo()
{
    cout << "=====================================================================" << endl;
    cout << "#                   E - V O T I N G   S Y S T E M                   #" << endl;
    cout << "=====================================================================" << endl;
}

void login_page()
{
    int n;
    string entered_cnic, entered_pw;
    interface_logo();
    cout << "Enter Your CNIC: ";
    cin.ignore();
    getline(cin, entered_cnic);
    cout << "Select your Role: " << endl;
    cout << " 1. Voter \n 2. Candidate \n 3. Admin \n 0. Exit" << endl;
    cin >> n;
    cin.ignore();
    cout << "Enter Password: ";
    getline(cin, entered_pw);
    ifstream file("user.txt");
    string name, age, cnic, city, role, password, line;
    bool found = false;
    if (file.is_open())
    {
        while (getline(file, name))
        {
            getline(file, age);
            getline(file, cnic);
            getline(file, city);
            getline(file, role);
            getline(file, password);
            getline(file, line);
            if (cnic == entered_cnic && password == entered_pw)
            {
                found = true;
                if ((n == 1 && role == "Voter") ||
                    (n == 2 && role == "Candidate") ||
                    (n == 3 && role == "Admin"))
                {
                    cout << "Login successful! Welcome " << role << " " << name << "!" << endl;
                    if ((n == 1 && role == "Voter"))
                    {
                        //Voter Side function will be added When you make it
                    }
                    else if ((n == 2 && role == "Candidate"))
                    {
                        //Candidate Side function will be added When you make it
                    }
                    else if ((n == 3 && role == "Admin"))
                    {
                        //Admin Side function will be added When you make it
                    }
                }
                else
                {
                    cout << "Role mismatch. Access denied." << endl;
                }
                break;
            }
        }
        file.close();
    }
    else
    {
        cout << "Error opening user file." << endl;
    }
    if (!found)
    {
        cout << "CNIC or password incorrect." << endl;
    }
}


class user 
{
private:
    string name;
    int age;
    string city;
    string cnic;
    string role;//humain bataye ga kay user admin hai candidate hai ya voter hai
    string password;
public:
    user()
    {
        name="";
        age=0;
        city="";
        cnic="";
        role="";
        password="";
    }
    user(string n,int a,string c,string cn,string r,string p)
    {
        name=n;
        age=a;
        city=c;
        cnic=cn;
        role=r;
        password=p;
    }
    void setname(string n) 
    {
        cout << "Enter your name :" << endl;
        cin >> n;
        name = n;
    }
    void setage(int a) 
    {
        cout << "Enter your age :" << endl;
        cin >> a;
        age = a;
    }
    void setcity(string c) 
    {
        cout << "Enter city name :" << endl;
        cin >> c;
        city = c;
    }
    void setcnic(string cn) 
    {
        cout << "Enter your cnic :" << endl;
        cin >> cn;
        cnic = cn;
    }
    void setrole(string r) 
    {
        cout << "Enter your role :" << endl;
        cin >> r;
        role=r;
    }
    void setpassword(string p)
    {
        cout<<"Set your Password: "<<endl;
        cin>>p;
        password=p;
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
    string getcnic() 
    {
        return cnic;
    }
    string getrole()
    {
        return role;
    }
    string getpassword()
    {
        return password;
    }
    void displayuserinfo()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"CNIC: "<<cnic<<endl;
        cout<<"City: "<<city<<endl;
        cout<<"Role: "<<role<<endl;
    }
    virtual void showrole()=0;
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
            file <<"----------"<<endl;
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

class candidate : public user 
{
private:
    string electsymbol;
    int specialno;
public:
    candidate(string n, int a, string c, string cn, string r, string p, string es, int sn) :user(n, a, c, cn,r,p), specialno(sn), electsymbol(es) {};
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
    string area;
public:
    voter() : user(), voterID(""), hasvoted(false) {}

    voter(string n, int a, string c, string cn, string r, string p, string vid, string assigned_area): user(n, a, c, cn, r, p), voterID(vid), hasvoted(false), {}

    void sethasvoted(bool voted) 
    {
        hasvoted = voted;
    }

    bool gethasvoted() const 
    {
        return hasvoted;
    }

    void castvote(string entered_voter_id, string entered_area) 
    {
        if (entered_voter_id != voterid) {
            cout<<"invalid voter ID. Access Denied!" << endl;
        }
        if (area != entered_area) {
        cout << "Area mismatch! You can only vote in your registered area: " << area << endl;
        }
        if (hasvoted) 
        {
            hasvoted = false;
            cout << getname() << "You have already cast your vote!" << endl;
        } else 
        {
            hasvoted = true;
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

int main()
{
login_page();

return 0;
}
