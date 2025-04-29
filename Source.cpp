#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX_ELECTION = 10;

const string Red = "\033[31m";
const string Green = "\033[32m";
const string Blue = "\033[34m";
const string Yellow = "\033[33m";
const string Cyan = "\033[36m";
const string Magenta = "\033[35m";
const string Bold = "\033[1m";
const string Reset = "\033[0m";

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
class Election {

};

class user
{
protected:
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
        ofstream file("user.txt" );
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
            cout << "Error! Could Not open the file for writing" << endl;
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
            cout << "Error opening candidates file.\n";
        }
        // else
          //   {
           //  cout << "Error opening file for reading." << endl;
          //   }
      //~user() {}
    }
};


class admin : public user {
    Election* elections[MAX_ELECTION];
    int electionCount;

public:
    admin(string name = "", int age = 0, string city = "", string cnic = "", string role = "Admin", string password = "")
        : user(name, age, city, cnic, role, password), electionCount(0) {
    }

    void adminMenu() {
        int choice;
        do {
            system("cls");
            cout << "\t\t\t=========================================\n";
            cout << "\t\t\t              ADMIN MENU        \n";
            cout << "\t\t\t==========================================\n";
            cout << "\t\t\t1. Create Election \n";
            cout << "\t\t\t2. Add Candidate to Election \n";
            cout << "\t\t\t3. Add New Voter \n";
            cout << "\t\t\t4. Remove Candidate \n";
            cout << "\t\t\t5. Remove Voter \n";
            cout << "\t\t\t6. Show Results \n";
            cout << "\t\t\t7. Reset \n";
            cout << "\t\t\t8. Delete All Votes \n";
            cout << "\t\t\t9. Logout\n";
            cout << "\t\t\t===========================================\n";
            cin >> choice;

            switch (choice) {
            case 1: createElection(); break;
            case 2: addCandidate(); break;
            case 3: addNewVoter(); break;
            case 4: removeCandidate(); break;
            case 5: removeVoter(); break;
            case 6: showResults(); break;
            case 7: reset(); break;
            case 8: deleteAllVotes(); break;
            case 9: cout << Green << "Logging out....\n" << Reset; return;
            default: cout << Red << "Invalid choice, Please try again\n" << Reset;
            }
        } while (true);
    }

    void createElection() {
        // Logic to create an election
        cout << Green << "Election created successfully.\n" << Reset;
    }

    void addCandidate() {
        // Logic to add a candidate
        cout << Green << "Candidate added successfully.\n" << Reset;
    }

    void addNewVoter() {
        // Logic to add a new voter
        cout << Green << "New voter added successfully.\n" << Reset;
    }

    void removeCandidate() {
        // Logic to remove a candidate
        cout << Green << "Candidate removed successfully.\n" << Reset;
    }

    void removeVoter() {
        // Logic to remove a voter
        cout << Green << "Voter removed successfully.\n" << Reset;
    }

    void showResults() {
        // Logic to show results
        cout << Green << "Displaying election results...\n" << Reset;
    }

    void reset() {
        // Logic to reset election data
        cout << Green << "Election data has been reset.\n" << Reset;
    }

    void deleteAllVotes() {
        // Logic to delete all votes
        cout << Green << "All votes have been deleted.\n" << Reset;
    }

    void showrole() override {
        cout << "Role: Admin\n";
    }
};
class candidate : public user
{
private:
    string electsymbol;
    int specialno;
    string party;
    string symbol;
    string area;
    int votecount;
    bool eligibility;
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
    bool iseligble() {
        return eligibility && getage() >= 18;
    }
    void showrole() override {
        cout << "Role: Candidate (" << party << ")\n";
    }
    //candidate() : user(), party(""), symbol(""), area(""), votecount(0), eligibility(true) {}//agr kush enter nai karta to default values store hon gi
    void setDetails()
    {
        string n, p, s, c, a;
        int age;
        string cn, pw;
        cout << "Enter candidate details:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, n);
        setname(n);
        cout << "Age: ";
        cin >> age;
        setage(age);
        cout << "Party: ";
        cin.ignore();
        getline(cin, p);
        party = p;
        cout << "Symbol: ";
        getline(cin, s);
        symbol = s;
        cout << "City: ";
        getline(cin, c);
        setcity(c);
        cout << "Area: ";
        getline(cin, a);
        area = a;
        cout << "CNIC: ";
        getline(cin, cn);
        setcnic(cn);
        cout << "Password: ";
        getline(cin, pw);
        setpassword(pw);
    }
    void update()
    {
        int choice;
        cout << "what do you want to update" << endl;
        cout << "1.party\n2.symbol\n3.area\n4.eligibility:" << endl;
        cin >> choice;
        cin.ignore();
        string newvalue;
        switch (choice) {
        case 1:
            cout << "Enter new party: ";
            getline(cin, newvalue);
            party = newvalue;
            break;
        case 2:
            cout << "Enter new symbol: ";
            getline(cin, newvalue);
            party = newvalue;
            break;
        case 3:
            cout << "Enter new area: ";
            getline(cin, newvalue);
            party = newvalue;
            break;
        case 4:
            cout << "set eligibility:\n 1 for eligible\n 2 for not eligible  ";
            int e;
            cin >> e;
            eligibility = (e == 1);
            break;
        default:
            cout << "invalid choice plz enter correct choice \n";
        }
    }
    string getparty() {
        return party;
    }
    string getsymbol() {
        return symbol;
    }
    string getarea() {
        return area;
    }
    int getvotecount() {
        return votecount;
    }
    void incrementvote() {
        votecount++;
    }
    void resetvotecount() {
        votecount = 0;
    }
    void displaydetails() {
        user::displayuserinfo();
        cout << "\nCandidate Details:\n";

        cout << "Party: " << party << endl;
        cout << "Symbol: " << symbol << endl;

        cout << "Area: " << area << endl;

        cout << "Votes: " << votecount << endl;
        cout << "Eligible: " << (eligibility ? "Yes" : "No") << endl;
    }
    void displayshorts() {
        cout << getname() << " (" << party << ") - " << symbol << " - Votes: " << votecount << endl;
    }
    bool matcharea(const string& voterarea)
    {//copy constructor 
        if (area == voterarea)
        {
            return true;
        }
    }

    void saveToFile()
    {
        ofstream file("candidates.txt", ios::app);
        if (file.is_open())
        {
            file << getname() << endl;
            file << getage() << endl;
            file << getcnic() << endl;
            file << getcity() << endl;
            file << getrole() << endl;
            file << getpassword() << endl;
            file << party << endl;
            file << symbol << endl;
            file << area << endl;
            file << votecount << endl;
            file << eligibility << endl;
            file << "----------" << endl;
        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
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