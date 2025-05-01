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

string isOnlyDigitsAndHyphen(const string& input) 
{
    while (true) 
    {
        bool valid = true;
        for (char ch : input) 
        {
            if (!isdigit(ch) && ch != '-') 
            {
                valid = false;
                break;
            }
        }
        if (valid && !input.empty()) 
        {
            return input;
        } 
        else 
        {
            cout << Red << "Invalid input! Only numbers and '-' are allowed.\n" << Reset;
        }
    }
}

string isonlyAlphabet(const string& input) 
{
    while (true) 
    {
        bool hasDigit = false;
        for (char ch : input) 
        {
            if (isdigit(ch)) {
                hasDigit = true;
                break;
            }
        }
        if (hasDigit) 
        {
            cout << Red << "You entered wrong data! Digits are not allowed.\n" << Reset;
        } 
        else if (input.empty()) 
        {
            cout << Red << "Input cannot be empty.\n" << Reset;
        } else 
        {
            return input;
        }
    }
}


void interface_logo()
{
    cout << "=====================================================================" << endl;
    cout << "#                   E - V O T I N G   S Y S T E M                   #" << endl;
    cout << "=====================================================================" << endl;
}

class user
{
private:
    string name;
    int age;
    string city;
    string cnic;
    string role; // humain bataye ga kay user admin hai candidate hai ya voter hai
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
        isonlyAlphabet(n);
        name = n;
    }
    void setage(int a)
    {
        age = a;
    }
    void setcity(string c)
    {
        isonlyAlphabet(c);
        city = c;
    }
    void setcnic(string cn)
    {
        isOnlyDigitsAndHyphen(cn);
        cnic = cn;
    }
    void setrole(string r)
    {
        isonlyAlphabet(r);
        role = r;
    }
    void setpassword(string p)
    {
        password = p;
    }
    string getname() const
    {
        return name;
    }
    int getage() const
    {
        return age;
    }
    string getcity() const
    {
        return city;
    }
    string getcnic() const
    {
        return cnic;
    }
    string getrole() const
    {
        return role;
    }
    string getpassword() const
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

class candidate :virtual public user
{
protected:
    string electsymbol;
    string CandidateID;
    string party;
    string symbol;
    string area;
    int votecount;
    bool eligibility;

public:
    candidate() : user(), party(""), symbol(""), area(""), votecount(0), eligibility(true) {}
    candidate(string n, int a, string c, string cn, string r, string p, string es, string cID) : user(n, a, c, cn, r, p), CandidateID(cID), electsymbol(es) {};
    string getCandidateID()
    {
        return CandidateID;
    }
    string getelectsymbol()
    {
        return electsymbol;
    }
    bool iseligble()
    {
        return eligibility && getage() >= 18;
    }
    void showrole() override
    {
        cout << "Role: Candidate (" << party << ")\n";
    }
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
        cout << "Candidate ID: ";
        getline(cin, CandidateID);
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

    void update() {
        string targetCandidateID;
        cout << "Enter the Candidate ID of the person you want to update: ";
        cin.ignore();
        getline(cin, targetCandidateID);
    
        ifstream fin("candidates.txt");
        ofstream fout("temp.txt");
    
        if (!fin || !fout) {
            cout << Red << "Error opening file." << Reset << endl;
            return;
        }
    
        string name, age, cnic, city, role, password, candidateID, party, symbol, area, votes, eligibility, sep;
        bool found = false;
    
        while (getline(fin, name)) {
            getline(fin, age);
            getline(fin, cnic);
            getline(fin, city);
            getline(fin, role);
            getline(fin, password);
            getline(fin, candidateID);
            getline(fin, party);
            getline(fin, symbol);
            getline(fin, area);
            getline(fin, votes);
            getline(fin, eligibility);
            getline(fin, sep); // ----------
    
            if (candidateID == targetCandidateID) 
            {
                found = true;
                int choice;
                cout << "\nMatch Found!\nUpdate Options:\n1. Area\n2. Password\n3. City\n4. CNIC\nEnter choice: ";
                cin >> choice;
                cin.ignore();
    
                string newval;
                switch (choice) {
                case 1:
                    cout << "Enter new Area: ";
                    getline(cin, area);
                    break;
                case 2:
                    cout << "Enter new Password: ";
                    getline(cin, password);
                    break;
                case 3:
                    cout << "Enter new City: ";
                    getline(cin, city);
                    break;
                case 4:
                    cout << "Enter new CNIC: ";
                    getline(cin, cnic);
                    break;
                default:
                    cout << "Invalid choice. No changes made.\n";
                }
                cout << Green << "Information updated successfully.\n" << Reset;
            }
    
            fout << name << endl;
            fout << age << endl;
            fout << cnic << endl;
            fout << city << endl;
            fout << role << endl;
            fout << password << endl;
            fout << candidateID << endl;
            fout << party << endl;
            fout << symbol << endl;
            fout << area << endl;
            fout << votes << endl;
            fout << eligibility << endl;
            fout << "----------" << endl;
        }
    
        fin.close();
        fout.close();
    
        remove("candidates.txt");
        rename("temp.txt", "candidates.txt");
    
        if (!found) 
        {
            cout << Red << "No Candidate found with ID: " << targetCandidateID << Reset << endl;
        }
    }    

    void setparty(string p) { party = p; }
    void setsymbol(string s) { symbol = s; }
    void setarea(string a) { area = a; }
    void setvotecount(int v) { votecount = v; }
    string getparty() const
    {
        return party;
    }
    string getsymbol() const
    {
        return symbol;
    }
    string getarea() const
    {
        return area;
    }
    int getvotecount() const
    {
        return votecount;
    }
    void incrementvote()
    {
        votecount++;
    }
    void resetvotecount()
    {
        votecount = 0;
    }
    void displaydetails()
    {
        user::displayuserinfo();
        cout << "\nCandidate Details:\n";
        cout << "Party: " << party << endl;
        cout << "Symbol: " << symbol << endl;
        cout << "Area: " << area << endl;
        cout << "Votes: " << votecount << endl;
        cout << "Eligible: " << (eligibility ? "Yes" : "No") << endl;
    }
    void displayshorts()
    {
        cout << getname() << " (" << party << ") - " << symbol << " - Votes: " << votecount << endl;
    }
    bool matcharea(const string& voterarea)
    { // copy constructor
        if (area == voterarea)
        {
            return true;
        }
    }

    void removeCandidate()
    {
        string targetCandidateID;
        cout << "Enter the Candidate ID to remove: ";
        cin.ignore();
        getline(cin, targetCandidateID);

        ifstream fin("candidate.txt");
        ofstream fout("temp.txt");

        if (!fin || !fout)
        {
            cout << Red << "Error opening file." << Reset << endl;
            return;
        }

        string name, age, cnic, city, role, password, CandidateID, party, symbol, area, votes, eligible, sep;
        bool found = false;

        while (getline(fin, name))
        {
            getline(fin, age);
            getline(fin, cnic);
            getline(fin, city);
            getline(fin, role);
            getline(fin, password);
            getline(fin, party);
            getline(fin, symbol);
            getline(fin,CandidateID);
            getline(fin, area);
            getline(fin, votes);
            getline(fin, eligible);
            getline(fin, sep);

            if (CandidateID != targetCandidateID)
            {
                fout << name << endl;
                fout << age << endl;
                fout << cnic << endl;
                fout << city << endl;
                fout << role << endl;
                fout << password << endl;
                fout << party << endl;
                fout << symbol << endl;
                fout << area << endl;
                fout << votes << endl;
                fout << eligible << endl;
                fout << "----------" << endl;
            }
            else
            {
                found = true;
                cout << Yellow << "Candidate with ID " << targetCandidateID << " removed successfully." << Reset << endl;
            }
        }

        fin.close();
        fout.close();
        remove("candidate.txt");
        rename("temp.txt", "candidate.txt");
        if (!found)
        {
            cout << Red << "No candidate found with ID: " << targetCandidateID << Reset << endl;
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
            file << CandidateID << endl;
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

class voter : virtual public user 
{
private:
    string voterID;
    bool hasvoted;
    string area;

public:
    // Constructors
    voter() : user(), voterID(""), hasvoted(false), area("") {}
    voter(string n, int a, string c, string cn, string r, string p, string vid, string assigned_area)
        : user(n, a, c, cn, r, p), voterID(vid), hasvoted(false), area(assigned_area) {
    }

    // Setters/Getters
    void sethasvoted(bool voted) { hasvoted = voted; }
    bool gethasvoted() const { return hasvoted; }
    string getVoterID() const { return voterID; }
    string getArea() const { return area; }

    // Function to input voter details
    void setDetails()
    {
        string n, c, cn, pw, r = "Voter";
        int age;
        cout << "Enter voter details:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, n);
        setname(n);
        cout << "Age: ";
        cin >> age;
        setage(age);
        cin.ignore();
        cout << "City: ";
        getline(cin, c);
        setcity(c);
        cout << "CNIC: ";
        getline(cin, cn);
        setcnic(cn);
        cout << "Password: ";
        getline(cin, pw);
        setpassword(pw);
        cout << "Voter ID: ";
        getline(cin, voterID);
        cout << "Area: ";
        getline(cin, area);
        setrole(r);
        hasvoted = false;
    }

    // Update voter info
    void update() {
        string targetVoterID;
        cout << "Enter the Voter ID of the person you want to update: ";
        cin.ignore();
        getline(cin, targetVoterID);

        ifstream fin("voter.txt");
        ofstream fout("temp.txt");

        if (!fin || !fout) {
            cout << Red << "Error opening file." << Reset << endl;
            return;
        }

        string name, age, cnic, city, role, password, voterID, area, hasvoted, sep;
        bool found = false;

        while (getline(fin, name)) {
            getline(fin, age);
            getline(fin, cnic);
            getline(fin, city);
            getline(fin, role);
            getline(fin, password);
            getline(fin, voterID);
            getline(fin, area);
            getline(fin, hasvoted);
            getline(fin, sep);

            if (voterID == targetVoterID) {
                found = true;
                int choice;
                cout << "\nMatch Found!\nUpdate Options:\n1. Area\n2. Password\n3. City\n4. CNIC\nEnter choice: ";
                cin >> choice;
                cin.ignore();

                string newval;
                switch (choice) {
                case 1:
                    cout << "Enter new Area: ";
                    getline(cin, area);
                    break;
                case 2:
                    cout << "Enter new Password: ";
                    getline(cin, password);
                    break;
                case 3:
                    cout << "Enter new City: ";
                    getline(cin, city);
                    break;
                case 4:
                    cout << "Enter new CNIC: ";
                    getline(cin, cnic);
                    break;
                default:
                    cout << "Invalid choice. No changes made.\n";
                }
                cout << Green << "Information updated successfully.\n" << Reset;
            }

            // Write the record (updated or not)
            fout << name << endl;
            fout << age << endl;
            fout << cnic << endl;
            fout << city << endl;
            fout << role << endl;
            fout << password << endl;
            fout << voterID << endl;
            fout << area << endl;
            fout << hasvoted << endl;
            fout << "----------" << endl;
        }

        fin.close();
        fout.close();

        // Replace original file
        remove("voter.txt");
        rename("temp.txt", "voter.txt");

        if (!found) {
            cout << Red << "No voter found with ID: " << targetVoterID << Reset << endl;
        }
    }

    void cast_vote(const string& voterID_loggedIn) 
    {
        if (hasvoted) 
        {
            cout << Red << "You have already cast your vote. Multiple votes are not allowed." << Reset << endl;
            return;
        }
    
        ifstream efile("elections.txt");
        if (!efile.is_open()) 
        {
            cout << Red << "No election has been created yet." << Reset << endl;
            return;
        }
    
        int electionCount = 0;
        string line;
        while (getline(efile, line)) electionCount++;
        efile.close();
    
        if (electionCount == 0) 
        {
            cout << Red << "No elections available." << Reset << endl;
            return;
        }
    
        string* elections = new string[electionCount];
        ifstream efile2("elections.txt");
        cout << Bold << "\nAvailable Elections:\n" << Reset;
        for (int i = 0; i < electionCount; i++) 
        {
            getline(efile2, elections[i]);
            cout << i + 1 << ". " << elections[i] << endl;
        }
        efile2.close();
    
        int choice;
        cout << "Enter the number of the election you want to vote in: ";
        cin >> choice;
        cin.ignore();
    
        if (choice < 1 || choice > electionCount) 
        {
            cout << Red << "Invalid election choice." << Reset << endl;
            delete[] elections;
            return;
        }
    
        string selectedElection = elections[choice - 1];
        delete[] elections;
    
        ifstream fin("candidates.txt");
        if (!fin.is_open()) 
        {
            cout << Red << "Could not open candidates file." << Reset << endl;
            return;
        }
    
        int candCount = 0;
        while (getline(fin, line)) 
        {
            for (int i = 0; i < 11; i++) getline(fin, line);
            getline(fin, line);
            if (line == area) candCount++;
        }
        fin.close();
    
        if (candCount == 0) 
        {
            cout << Red << "No candidates found in your area." << Reset << endl;
            return;
        }
    
        string* candID = new string[candCount];
        string* candName = new string[candCount];
        string* candParty = new string[candCount];
        string* candSymbol = new string[candCount];
    
        ifstream fin2("candidates.txt");
        int idx = 0;
        while (getline(fin2, line)) 
        {
            string name = line, age, cnic, city, role, pw, cid, party, symbol, cArea, votes, elig, sep;
            getline(fin2, age); getline(fin2, cnic); getline(fin2, city);
            getline(fin2, role); getline(fin2, pw); getline(fin2, cid);
            getline(fin2, party); getline(fin2, symbol); getline(fin2, cArea);
            getline(fin2, votes); getline(fin2, elig); getline(fin2, sep);
    
            if (cArea == area && idx < candCount) 
            {
                candID[idx] = cid;
                candName[idx] = name;
                candParty[idx] = party;
                candSymbol[idx] = symbol;
                idx++;
            }
        }
        fin2.close();
    
        cout << Bold << "\nCandidates in your area (" << area << "):\n" << Reset;
        for (int i = 0; i < candCount; i++) 
        {
            cout << i + 1 << ". " << candName[i] << " (" << candParty[i] << ", " << candSymbol[i] << ")\n";
        }
    
        cout << "Enter the number of the candidate you want to vote for: ";
        int candChoice;
        cin >> candChoice;
        cin.ignore();
    
        if (candChoice < 1 || candChoice > candCount) 
        {
            cout << Red << "Invalid candidate choice." << Reset << endl;
            delete[] candID; delete[] candName; delete[] candParty; delete[] candSymbol;
            return;
        }
    
        string chosenID = candID[candChoice - 1];
        delete[] candID; delete[] candName; delete[] candParty; delete[] candSymbol;
    
        ifstream fin3("candidates.txt");
        ofstream fout("temp.txt");
    
        while (getline(fin3, line)) 
        {
            fout << line << endl;
            for (int i = 0; i < 10; i++) 
            {
                getline(fin3, line);
                fout << line << endl;
            }
            string voteStr;
            getline(fin3, voteStr);
            int v = stoi(voteStr);
            string cid; getline(fin3, cid);
            if (cid == chosenID) v++;
            fout << v << endl;
            fout << cid << endl;
        }
    
        fin3.close(); fout.close();
        remove("candidates.txt");
        rename("temp.txt", "candidates.txt");
    
        ifstream vin("voters.txt");
        ofstream vout("temp_v.txt");
    
        while (getline(vin, line)) 
        {
            fout << line << endl;
            for (int i = 0; i < 7; i++) 
            {
                getline(vin, line); fout << line << endl;
            }
            getline(vin, line); // hasvoted
            fout << (line == voterID_loggedIn ? "1" : line) << endl;
            getline(vin, line); fout << line << endl; // sep
        }
    
        vin.close(); vout.close();
        remove("voters.txt");
        rename("temp_v.txt", "voters.txt");
    
        sethasvoted(true);
        cout << Green << "Your vote has been cast successfully. Thank you!\n" << Reset;
    }
    
    // Display full info
    void displayDetails() {
        user::displayuserinfo();
        cout << "Voter ID: " << voterID << "\n";
        cout << "Area: " << area << "\n";
        cout << "Voted: " << (hasvoted ? "Yes" : "No") << "\n";
    }

    // Display short info
    void displayShort() {
        cout << getname() << " - ID: " << voterID << " - Area: " << area << " - Voted: "
            << (hasvoted ? "Yes" : "No") << endl;
    }

    // Save voter to file
    void saveToFile() {
        ofstream file("voters.txt", ios::app);
        if (file.is_open()) {
            file << getname() << endl;
            file << getage() << endl;
            file << getcnic() << endl;
            file << getcity() << endl;
            file << getrole() << endl;
            file << getpassword() << endl;
            file << voterID << endl;
            file << area << endl;
            file << hasvoted << endl;
            file << "----------" << endl;
            file.close();
            cout << "Voter saved successfully!\n";
        }
        else {
            cout << "Error saving voter to file.\n";
        }
    }

    void deleteVoter()
    {
        string targetVoterID;
        cout << "Enter the Voter ID to remove: ";
        cin.ignore();
        getline(cin, targetVoterID);

        ifstream fin("voters.txt");
        ofstream fout("temp.txt");

        if (!fin || !fout)
        {
            cout << Red << "Error opening file." << Reset << endl;
            return;
        }

        string name, age, cnic, city, role, password, voterID, area, hasvoted, sep;
        bool found = false;

        while (getline(fin, name))
        {
            getline(fin, age);
            getline(fin, cnic);
            getline(fin, city);
            getline(fin, role);
            getline(fin, password);
            getline(fin, voterID);
            getline(fin, area);
            getline(fin, hasvoted);
            getline(fin, sep);  // ----------

            if (voterID == targetVoterID)
            {
                found = true;
                cout << Yellow << "Voter with ID " << voterID << " removed successfully." << Reset << endl;
                continue;
            }

            fout << name << endl;
            fout << age << endl;
            fout << cnic << endl;
            fout << city << endl;
            fout << role << endl;
            fout << password << endl;
            fout << voterID << endl;
            fout << area << endl;
            fout << hasvoted << endl;
            fout << "----------" << endl;
        }

        fin.close();
        fout.close();
        remove("voters.txt");
        rename("temp.txt", "voters.txt");
        if (!found)
        {
            cout << Red << "No voter found with ID: " << targetVoterID << Reset << endl;
        }
    }

    void deleteAllVoters()
    {
        ofstream file("voters.txt", ios::trunc);
        if (file.is_open())
        {
            file.close();
            cout << Yellow << "All voter records have been deleted successfully." << Reset << endl;
        }
        else
        {
            cout << Red << "Error: Unable to open voters.txt for deletion." << Reset << endl;
        }
    }

    // Area match check
    bool matchArea(const string& voterArea) {
        return area == voterArea;
    }

    // Overridden role display
    void showrole() override {
        cout << "Role: Voter\n";
    }
};

class Graph
{
public:
    static void drawPartyGraph()
    {
        ifstream file("result.txt");
        if (!file.is_open())
        {
            cout << Red << "Error opening result.txt!" << Reset << endl;
            return;
        }
        const int MAX = 100;
        string parties[MAX];
        int wins[MAX] = { 0 };
        int partyCount = 0;

        string line, currentParty, currentStatus;

        while (getline(file, line))
        {
            if (line.find("Party:") == 0)
            {
                currentParty = line.substr(7);
            }
            if (line.find("Result Status:") == 0)
            {
                currentStatus = line.substr(15);
                if (currentStatus == "Won")
                {
                    bool found = false;
                    for (int i = 0; i < partyCount; i++)
                    {
                        if (parties[i] == currentParty)
                        {
                            wins[i]++;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        parties[partyCount] = currentParty;
                        wins[partyCount] = 1;
                        partyCount++;
                    }
                }
            }
        }
        file.close();

        cout << Bold << "\nParty-wise Winning Candidates Graph\n" << Reset;
        for (int i = 0; i < partyCount; i++)
        {
            cout << parties[i] << " | ";
            for (int j = 0; j < wins[i]; j++)
                cout << "█";
            cout << " (" << wins[i] << ")" << endl;
        }
    }

    static void drawCandidateGraph(const string& areaName)
    {
        ifstream file("result.txt");
        if (!file.is_open())
        {
            cout << Red << "Error opening result.txt!" << Reset << endl;
            return;
        }
        const int MAX = 100;
        string names[MAX];
        int votes[MAX] = { 0 };
        string areas[MAX];
        int count = 0;

        string line, currentName, currentArea, currentVotes;

        while (getline(file, line))
        {
            if (line.find("Candidate Name:") == 0)
            {
                currentName = line.substr(17);
            }
            else if (line.find("Area:") == 0)
            {
                currentArea = line.substr(6);
            }
            else if (line.find("Total Votes:") == 0)
            {
                currentVotes = line.substr(13);
            }
            else if (line.find("Result Status:") == 0)
            {
                if (currentArea == areaName && count < MAX)
                {
                    names[count] = currentName;
                    votes[count] = stoi(currentVotes);
                    count++;
                }
            }
        }
        file.close();

        if (count == 0)
        {
            cout << Red << "No candidates found for area: " << areaName << Reset << endl;
            return;
        }
        cout << Bold << "\nCandidate-wise Vote Graph for Area: " << areaName << "\n" << Reset;
        for (int i = 0; i < count; i++)
        {
            cout << names[i] << " | ";
            for (int j = 0; j < votes[i]; j += 10)  // scale down
                cout << "*";
            cout << " (" << votes[i] << " votes)" << endl;
        }
    }
};

class Result :virtual public candidate, virtual public Graph
{
private:
    string status;  // "Won" or "Lost"

public:
    Result() {}

    Result(const candidate& c, string winStatus)
    {
        setname(c.getname());
        setage(c.getage());
        setcity(c.getcity());
        setcnic(c.getcnic());
        setrole(c.getrole());
        setpassword(c.getpassword());

        party = c.getparty();
        symbol = c.getsymbol();
        area = c.getarea();
        votecount = c.getvotecount();

        status = winStatus;
    }

    void setStatus(string s) {
        status = s;
    }

    string getStatus() const {
        return status;
    }

    void saveResultToFile() const
    {
        ofstream file("result.txt", ios::app);
        if (file.is_open())
        {
            file << "Candidate Name: " << getname() << endl;
            file << "Party: " << party << endl;
            file << "Symbol: " << symbol << endl;
            file << "Area: " << area << endl;
            file << "Total Votes: " << votecount << endl;
            file << "Result Status: " << status << endl;
            file << "--------------------------" << endl;
            file.close();
            cout << Green << "Result saved for " << getname() << "." << Reset << endl;
        }
        else
        {
            cout << Red << "Error writing to result.txt!" << Reset << endl;
        }
    }

    static void resetResults()
    {
        ofstream file("result.txt", ios::trunc);
        if (file.is_open())
        {
            file.close();
            cout << Yellow << "All results have been reset." << Reset << endl;
        }
        else
        {
            cout << Red << "Error resetting result.txt!" << Reset << endl;
        }
    }

    static void showAreaResults(const string& areaName)
    {
        ifstream file("candidates.txt");
        if (!file.is_open())
        {
            cout << Red << "Error opening candidates.txt!" << Reset << endl;
            return;
        }

        const int MAX_CANDIDATES = 100;
        Result results[MAX_CANDIDATES];
        int count = 0;
        int highestVotes = -1;

        string name, age, cnic, city, role, password, party, symbol, area, votes, eligibility, line;

        while (getline(file, name))
        {
            getline(file, age);
            getline(file, cnic);
            getline(file, city);
            getline(file, role);
            getline(file, password);
            getline(file, party);
            getline(file, symbol);
            getline(file, area);
            getline(file, votes);
            getline(file, eligibility);
            getline(file, line); // Separator ----------

            if (area == areaName && count < MAX_CANDIDATES)
            {
                results[count].setname(name);
                results[count].setage(stoi(age));
                results[count].setcity(city);
                results[count].setcnic(cnic);
                results[count].setrole(role);
                results[count].setpassword(password);
                results[count].setparty(party);
                results[count].setsymbol(symbol);
                results[count].setarea(area);
                results[count].setvotecount(stoi(votes));

                if (stoi(votes) > highestVotes)
                    highestVotes = stoi(votes);

                count++;
            }
        }
        file.close();

        if (count == 0)
        {
            cout << Red << "No candidates found for area: " << areaName << Reset << endl;
            return;
        }

        cout << Bold << "\nResults for area: " << areaName << "\n" << Reset;

        for (int i = 0; i < count; i++)
        {
            if (results[i].getvotecount() == highestVotes)
                results[i].setStatus("Won");
            else
                results[i].setStatus("Lost");

            results[i].saveResultToFile();
            cout << "----------------------------------" << endl;
            cout << "Candidate: " << results[i].getname() << endl;
            cout << "Party: " << results[i].getparty() << endl;
            cout << "Symbol: " << results[i].getsymbol() << endl;
            cout << "Votes: " << results[i].getvotecount() << endl;
            cout << "Status: " << results[i].getStatus() << endl;
        }
    }

    void showLeadingParty()
    {
        ifstream file("result.txt");
        if (!file.is_open())
        {
            cout << Red << "Error opening result.txt!" << Reset << endl;
            return;
        }
        const int MAX_RECORDS = 1000;
        string parties[MAX_RECORDS];
        int wins[MAX_RECORDS] = { 0 };
        int partyCount = 0;

        string line, currentParty, currentStatus;

        while (getline(file, line))
        {
            if (line.find("Party:") == 0)
            {
                currentParty = line.substr(7);
            }
            if (line.find("Result Status:") == 0)
            {
                currentStatus = line.substr(15);
                if (currentStatus == "Won")
                {
                    bool found = false;
                    for (int i = 0; i < partyCount; i++)
                    {
                        if (parties[i] == currentParty)
                        {
                            wins[i]++;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        parties[partyCount] = currentParty;
                        wins[partyCount] = 1;
                        partyCount++;
                    }
                }
            }
        }
        file.close();
        if (partyCount == 0)
        {
            cout << Red << "No winning candidates found in result.txt!" << Reset << endl;
            return;
        }
        int maxIndex = 0;
        for (int i = 1; i < partyCount; i++)
        {
            if (wins[i] > wins[maxIndex])
            {
                maxIndex = i;
            }
        }
        cout << Bold << "\nParty Wins Summary:\n" << Reset;
        for (int i = 0; i < partyCount; i++)
        {
            cout << parties[i] << ": " << wins[i] << " winning candidate(s)" << endl;
        }
        cout << Green << "\nLeading Party: " << Bold << parties[maxIndex]
            << Reset << Green << " with " << wins[maxIndex] << " winning candidates!" << Reset << endl;
    }

};

class admin : public voter, public Result 
{
    int electionCount;

public:
    admin(string name = "", int age = 0, string city = "", string cnic = "", string role = "Admin", string password = "")
        : user(name, age, city, cnic, role, password), electionCount(0) {}

    void adminMenu() 
    {
        int choice;
        do 
        {
            //system("cls");
            cout << "========================================="<<endl;
            cout << "              ADMIN MENU                 "<<endl;
            cout << "========================================="<<endl;
            cout << "1. Create Election"<<endl;
            cout << "2. Add Candidate"<<endl;;
            cout << "3. Update Candidate Info"<<endl;;
            cout << "4. Add New Voter"<<endl;;
            cout << "5. Update Voter Info"<<endl;;
            cout << "6. Remove Candidate"<<endl;;
            cout << "7. Remove Voter "<<endl;;
            cout << "8. Show Results "<<endl;;
            cout << "9. Reset Results "<<endl;;
            cout << "10. Delete All Voters "<<endl;;
            cout << "0. Logout"<<endl;;
            cout << "==========================================="<<endl;;
            cout << "Enter your choice: "<<endl;
            cin >> choice;

            switch (choice) 
            {
                case 1: 
                    createElection(); 
                    break;
                case 2: 
                    addCandidate(); 
                    break;
                case 3: 
                    updateCandidate(); 
                    break;
                case 4:     
                    addNewVoter(); 
                    break;
                case 5:
                    updateVoter(); 
                    break;
                case 6: 
                    removeCandidate(); 
                    break;
                case 7: 
                    removeVoter(); 
                    break;
                case 8: 
                    showResults(); 
                    break;
                case 9: 
                    resetResults(); 
                    break;
                case 10: 
                    deleteAllVotersData(); 
                    break;
                case 0: 
                    cout << Green << "Logging out...\n"; 
                    return;
                default: 
                    cout << Red << "Invalid choice, try again.\n" << Reset;
            }
            //system("pause");
        } while (choice!=0);
    }

    void createElection() 
    {
        cout << Bold << "\nNew election created.\n" << Reset;
        electionCount++;
    }

    void addCandidate() 
    {
        candidate c;
        c.setDetails();
        c.saveToFile();
        cout << Green << "Candidate added successfully.\n" << Reset;
    }

    void updateCandidate() 
    {
        candidate c;
        c.update();
    }

    void removeCandidate() 
    {
        candidate c;
        c.removeCandidate();
    }

    void addNewVoter() 
    {
        voter v;
        v.setDetails();
        v.saveToFile();
        cout << Green << "New voter added successfully.\n" << Reset;
    }

    void updateVoter() 
    {
        voter v;
        v.update();
    }

    void removeVoter() 
    {
        voter v;
        v.deleteVoter();
    }

    void deleteAllVotersData() 
    {
        voter v;
        v.deleteAllVoters();
    }

    void resetResults() 
    {
        Result::resetResults();
        cout << Green << "All election results have been reset.\n" << Reset;
    }

    void showResults() 
    {
        string area;
        int choice;
        cout << "\nChoose result type:\n1. National Election\n2. Provincial Election\n3. Area-wise Result\nEnter: ";
        cin >> choice;
        cin.ignore();

        switch (choice) 
        {
            case 1:
                Result::showLeadingParty();
                Graph::drawPartyGraph();
                break;
            case 2:
                cout << "Provincial results feature under development.\n";
                break;
            case 3:
                cout << "Enter area name: ";
                getline(cin, area);
                Result::showAreaResults(area);
                Graph::drawCandidateGraph(area);
                break;
            default:
                cout << Red << "Invalid input!\n" << Reset;
        }
    }

    void showrole() override 
    {
        cout << "Role: Admin\n";
    }
};


class provincial
{
private:
    string provincename;
    int provinceid;
    string* cities;
    int citycount;
    int cityCapacity;
    candidate** candidates;
    int candidatecount;
    int candidateCapacity;
    bool electionStarted;
public:
    provincial(string name = "", int id = 0) : provincename(name), provinceid(id), citycount(0), cityCapacity(5), candidatecount(0), candidateCapacity(5), electionStarted(false)
    {
        cities = new string[cityCapacity];
        candidates = new candidate * [candidateCapacity];
    }

    ~provincial()
    {
        delete[] cities;
        delete[] candidates;
    }

    void resizeCities()
    {
        cityCapacity *= 2;
        string* newCities = new string[cityCapacity];
        for (int i = 0; i < citycount; i++)
        {
            newCities[i] = cities[i];
        }
        delete[] cities;
        cities = newCities;
    }

    void resizeCandidates()
    {
        candidateCapacity *= 2;
        candidate** newCandidates = new candidate * [candidateCapacity];
        for (int i = 0; i < candidatecount; i++)
        {
            newCandidates[i] = candidates[i];
        }
        delete[] candidates;
        candidates = newCandidates;
    }

    void addCity(const string& city)
    {
        if (citycount == cityCapacity)
        {
            resizeCities();
        }
        cities[citycount++] = city;
    }

    void loadCandidatesFromFile()
    {
        ifstream file("candidates.txt");
        string name, age, cnic, city, role, password, party, symbol, area, votes, eligibility, sep;

        while (getline(file, name))
        {
            getline(file, age);
            getline(file, cnic);
            getline(file, city);
            getline(file, role);
            getline(file, password);
            getline(file, party);
            getline(file, symbol);
            getline(file, area);
            getline(file, votes);
            getline(file, eligibility);
            getline(file, sep);

            for (int i = 0; i < citycount; i++)
            {
                if (cities[i] == area)
                {
                    if (candidatecount == candidateCapacity)
                    {
                        resizeCandidates();
                    }
                    candidate* c = new candidate();
                    c->setname(name);
                    c->setage(stoi(age));
                    c->setcnic(cnic);
                    c->setcity(city);
                    c->setrole(role);
                    c->setpassword(password);
                    c->setparty(party);
                    c->setsymbol(symbol);
                    c->setarea(area);
                    c->setvotecount(stoi(votes));
                    candidates[candidatecount++] = c;
                    break;
                }
            }
        }
        file.close();
    }

    void createElection()
    {
        electionStarted = true;
        cout << Green << "Provincial Election started in " << provincename << Reset << endl;
    }

    void showCandidates()
    {
        if (!electionStarted)
        {
            cout << Yellow << "Election not started in " << provincename << Reset << endl;
            return;
        }
        for (int i = 0; i < candidatecount; i++)
        {
            candidates[i]->displaydetails();
        }
    }

    string getWinningParty()
    {
        string* parties = new string[candidatecount];
        int* seats = new int[candidatecount];
        int partycount = 0;

        for (int i = 0; i < candidatecount; i++)
        {
            string pname = candidates[i]->getparty();
            bool found = false;
            for (int j = 0; j < partycount; j++)
            {
                if (parties[j] == pname)
                {
                    seats[j]++;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                parties[partycount] = pname;
                seats[partycount++] = 1;
            }
        }

        int maxSeats = 0;
        string winner = "None";
        for (int i = 0; i < partycount; i++)
        {
            if (seats[i] > maxSeats)
            {
                maxSeats = seats[i];
                winner = parties[i];
            }
        }

        delete[] parties;
        delete[] seats;
        return winner;
    }

    int getCandidateCount() const
    {
        return candidatecount;
    }

    candidate* getCandidateAt(int index)
    {
        return (index >= 0 && index < candidatecount) ? candidates[index] : nullptr;
    }

    string getProvinceName() const
    {
        return provincename;
    }

    bool hasStarted() const
    {
        return electionStarted;
    }
};

class national_election
{
private:
    provincial** provinces;
    int provinceCount;
    int provinceCapacity;

public:
    national_election()
    {
        provinceCount = 0;
        provinceCapacity = 3;
        provinces = new provincial * [provinceCapacity];
    }

    ~national_election()
    {
        delete[] provinces;
    }

    void resizeProvinces()
    {
        provinceCapacity *= 2;
        provincial** newArray = new provincial * [provinceCapacity];
        for (int i = 0; i < provinceCount; i++)
        {
            newArray[i] = provinces[i];
        }
        delete[] provinces;
        provinces = newArray;
    }

    void addProvince(provincial* p)
    {
        if (provinceCount == provinceCapacity)
        {
            resizeProvinces();
        }
        provinces[provinceCount++] = p;
    }

    void createElection()
    {
        cout << Green << "National Election Started!\n" << Reset;
        for (int i = 0; i < provinceCount; i++)
        {
            provinces[i]->createElection();
        }
    }

    void showAllCandidates()
    {
        for (int i = 0; i < provinceCount; i++)
        {
            cout << Cyan << "Province: " << provinces[i]->getProvinceName() << Reset << endl;
            provinces[i]->showCandidates();
        }
    }

    string getNationalWinner()
    {
        string* parties = new string[provinceCount];
        int* wins = new int[provinceCount];
        int partyCount = 0;

        for (int i = 0; i < provinceCount; i++)
        {
            string winner = provinces[i]->getWinningParty();
            if (winner == "None") continue;
            bool found = false;
            for (int j = 0; j < partyCount; j++)
            {
                if (parties[j] == winner)
                {
                    wins[j]++;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                parties[partyCount] = winner;
                wins[partyCount++] = 1;
            }
        }

        string nationalWinner = "No party";
        int max = 0;
        for (int i = 0; i < partyCount; i++)
        {
            if (wins[i] > max)
            {
                max = wins[i];
                nationalWinner = parties[i];
            }
        }

        delete[] parties;
        delete[] wins;
        return nationalWinner;
    }
};

void login_page()
{
    int n;
    string entered_id, entered_pw;

    while (true) {
        interface_logo();

        cout << "Enter Your ID (VoterID / CandidateID / AdminID): ";
        getline(cin, entered_id);

        cout<<"Select your Role:"<<endl; 
        cout<<"1. Voter"<<endl;
        cout<<"2. Candidate"<<endl; 
        cout<<"3. Admin"<<endl;
        cout<<"0. Exit"<<endl;
        cin >> n;
        cin.ignore();

        cout << "Enter Password: ";
        getline(cin, entered_pw);

        if (n == 0) {
            cout << Yellow << "Exiting the system. Goodbye!\n" << Reset;
            break;
        }

        string filename;
        if (n == 1) filename = "voters.txt";
        else if (n == 2) filename = "candidates.txt";
        else if (n == 3) filename = "admin.txt";
        else {
            cout << Red << "Invalid role choice.\n" << Reset;
            continue;
        }

        ifstream file(filename);
        if (!file.is_open()) {
            cout << Red << "Error opening " << filename << Reset << endl;
            continue;
        }

        string line, name, age, cnic, city, role, password, ID;
        bool found = false;

        while (getline(file, name)) {
            getline(file, age);
            getline(file, cnic);
            getline(file, city);
            getline(file, role);
            getline(file, password);

            if (role == "Voter") {
                string voterID, area, hasvoted, sep;
                getline(file, voterID);
                getline(file, area);
                getline(file, hasvoted);
                getline(file, sep);

                if (entered_id == voterID && entered_pw == password) {
                    found = true;
                    cout << Green << "Welcome " << name << "! (Voter)\n" << Reset;
                    voter v(name, stoi(age), city, cnic, role, password, voterID, area);
                    v.sethasvoted(hasvoted == "1");
                    v.cast_vote(voterID);  // Cast vote immediately
                    break;
                }
            }
            else if (role == "Candidate") {
                string candidateID, party, symbol, area, votes, eligible, sep;
                getline(file, candidateID);
                getline(file, party);
                getline(file, symbol);
                getline(file, area);
                getline(file, votes);
                getline(file, eligible);
                getline(file, sep);

                if (entered_id == candidateID && entered_pw == password) {
                    found = true;
                    cout << Green << "Welcome " << name << "! (Candidate)\n" << Reset;
                    // Optionally show candidate dashboard here
                    break;
                }
            }
            else if (role == "Admin") {
                string adminID, sep;
                getline(file, adminID);
                getline(file, sep);

                if (entered_id == adminID && entered_pw == password) {
                    found = true;
                    cout << Green << "Welcome Admin " << name << "!\n" << Reset;
                    admin a(name, stoi(age), city, cnic, role, password);
                    a.adminMenu();
                    break;
                }
            }
        }

        file.close();

        if (!found) {
            cout << Red << "Incorrect ID or Password. Try again!\n\n" << Reset;
        }
    }
}

int main()
{
    login_page();
    return 0;
}
