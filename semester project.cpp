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
        name = "";
        age = 0;
        city = "";
        cnic = "";
        role = "";
        password = "";
    }
    user(string n, int a, string c, string cn, string r, string p)
    {
        name = n;
        age = a;
        city = c;
        cnic = cn;
        role = r;
        password = p;
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
        role = r;
    }
    void setpassword(string p)
    {
        cout << "Set your Password: " << endl;
        cin >> p;
        password = p;
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
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "City: " << city << endl;
        cout << "Role: " << role << endl;
    }
    virtual void showrole() = 0;
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
            file << "----------" << endl;
            file.close();
            cout << "User data saved to file successfully." << endl;
        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    }
    void readAllUsers()
    {
        ifstream file("user.txt");
        string line;
        if (file.is_open())
        {
            cout << "\nAll Users from File:" << endl;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Error opening file for reading." << endl;
        }
    }
    ~user() {}
};

class candidate : public user
{
private:
    string electsymbol;
    int specialno;
public:
    candidate(string n, int a, string c, string cn, string r, string p, string es, int sn) :user(n, a, c, cn, r, p), specialno(sn), electsymbol(es) {};
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

    voter(string n, int a, string c, string cn, string r, string p, string vid, string assigned_area) : user(n, a, c, cn, r, p), voterID(vid), hasvoted(false) {}

        void sethasvoted(bool voted)
    {
        hasvoted = voted;
    }

    bool gethasvoted() const
    {
        return hasvoted;
    }
    string chooseElectionType()
    {
        int electionChoice;
        cout << "\nSelect the election type you want to vote in:" << endl;
        cout << "1. National Election" << endl;
        cout << "2. Provincial Election" << endl;
        cout << "3. District Election" << endl;
        cout << "4. Union Council Election" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> electionChoice;

        if (electionChoice == 1)
            return "National";
        else if (electionChoice == 2)
            return "Provincial";
        else if (electionChoice == 3)
            return "District";
        else if (electionChoice == 4)
            return "Union Council";
        else
        {
            cout << "Invalid election type selected!" << endl;
            return "";
        }
    }
    string selectCandidate(string electionType)
    {
        int candidateChoice;
        cout << "\nSelect a candidate for " << electionType << " election:" << endl;

        if (electionType == "National")
        {
            cout << "1. Imran Khan" << endl;
            cout << "2. Nawaz Sharif" << endl;
            cout << "3. Bilawal Bhutto" << endl;
        }
        else if (electionType == "Provincial")
        {
            cout << "1. Shahbaz Sharif" << endl;
            cout << "2. Mahmood Khan" << endl;
            cout << "3. Murad Ali Shah" << endl;
        }
        else if (electionType == "District")
        {
            cout << "1. District Leader A" << endl;
            cout << "2. District Leader B" << endl;
            cout << "3. District Leader C" << endl;
        }
        else if (electionType == "Union Council")
        {
            cout << "1. UC Leader A" << endl;
            cout << "2. UC Leader B" << endl;
            cout << "3. UC Leader C" << endl;
        }
        else
        {
            cout << "Invalid election type!" << endl;
            return "";
        }

        cout << "Enter your choice (1-3): ";
        cin >> candidateChoice;

        if (electionType == "National")
        {
            if (candidateChoice == 1) return "Imran Khan";
            else if (candidateChoice == 2) return "Nawaz Sharif";
            else if (candidateChoice == 3) return "Bilawal Bhutto";
        }
        else if (electionType == "Provincial")
        {
            if (candidateChoice == 1) return "Shahbaz Sharif";
            else if (candidateChoice == 2) return "Mahmood Khan";
            else if (candidateChoice == 3) return "Murad Ali Shah";
        }
        else if (electionType == "District")
        {
            if (candidateChoice == 1) return "District Leader A";
            else if (candidateChoice == 2) return "District Leader B";
            else if (candidateChoice == 3) return "District Leader C";
        }
        else if (electionType == "Union Council")
        {
            if (candidateChoice == 1) return "UC Leader A";
            else if (candidateChoice == 2) return "UC Leader B";
            else if (candidateChoice == 3) return "UC Leader C";
        }

        cout << "Invalid candidate selected!" << endl;
        return "";
    }
    void castvote(string entered_voter_id, string entered_area)
    {
        if (entered_voter_id != voterID)
        {
            cout << "Invalid Voter ID. Access Denied!" << endl;
            return;
        }
        if (area != entered_area)
        {
            cout << "Area mismatch! You can only vote in your registered area: " << area << endl;
            return;
        }
        if (hasvoted)
        {
            cout << getname() << ", you have already cast your vote!" << endl;
            return;
        }

        string electionType = chooseElectionType();
        if (electionType == "") return;

        string selectedCandidate = selectCandidate(electionType);
        if (selectedCandidate == "") return; 

        hasvoted = true; 

        cout << "\n" << getname() << " has successfully voted for " << selectedCandidate
            << " in the " << electionType << " election!" << endl;
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
