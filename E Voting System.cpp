#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <sstream>
#include <cstring>

using namespace std;

const string White = "\033[37m";
const string Red = "\033[31m";
const string Green = "\033[32m";
const string Blue = "\033[34m";
const string Yellow = "\033[33m";
const string Cyan = "\033[36m";
const string Magenta = "\033[35m";
const string Bold = "\033[1m";
const string Reset = "\033[0m";

tm parseCTimeString(const string &timeStr)
{
    tm result = {};
    istringstream ss(timeStr);
    string weekday, month;
    int day, hour, min, sec, year;
    char colon;
    ss >> weekday >> month >> day >> hour >> colon >> min >> colon >> sec >> year;

    string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; i++)
    {
        if (months[i] == month)
        {
            result.tm_mon = i;
            break;
        }
    }
    result.tm_year = year - 1900;
    result.tm_mday = day;
    result.tm_hour = hour;
    result.tm_min = min;
    result.tm_sec = sec;

    return result;
}

bool isElectionActive(const string &fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Error opening " << fileName << endl;
        return false;
    }
    string line;
    string lastEndTime;

    while (getline(file, line))
    {
        if (line.find("End Time:") != string::npos)
        {
            lastEndTime = line.substr(10);
        }
    }
    file.close();
    if (lastEndTime.empty())
    {
        cout << "No end time found in file.\n";
        return false;
    }
    tm end_tm = parseCTimeString(lastEndTime);
    time_t endTime = mktime(&end_tm);
    time_t now = time(0);

    return now < endTime;
}

bool isCNICDuplicate(const string &cnic)
{
    string line;
    ifstream files[] = 
    {
        ifstream("voter.txt"),
        ifstream("candidate.txt"),
        ifstream("admin.txt"),
        ifstream("Approval.txt")
    };

    for (auto &file : files)
    {
        while (getline(file, line))
        {
            if (line == cnic)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

bool isValidCNIC(const string &input)
{
    if (input.length() != 15)
    {
        cout << Red << "Invalid Length! CNIC must be 15 characters (xxxxx-xxxxxxx-x).\n" << Reset;
        return false;
    }

    for (char ch : input)
    {
        if (!isdigit(ch) && ch != '-')
        {
            cout << Red << "Invalid input! Only digits and '-' are allowed.\n" << Reset;
            return false;
        }
    }
    return true;
}

bool isOnlyAlphabet(const string &input)
{
    if (input.empty())
    {
        cout << Red << "Input cannot be empty.\n" << Reset;
        return false;
    }

    for (char ch : input)
    {
        if (isdigit(ch))
        {
            cout << Red << "Invalid input! Digits are not allowed.\n" << Reset;
            return false;
        }
    }
    return true;
}

void interface_logo()
{
    cout << White << "=====================================================================" << endl;
    cout << White << "#                   E - V O T I N G   S Y S T E M                   #" << endl;
    cout << White << "=====================================================================" << endl;
}

class user
{
private:
    string name;
    int age;
    string city;
    string cnic;
    string role;
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
        isOnlyAlphabet(n);
        name = n;
    }
    void setage(int a)
    {
        age = a;
    }
    void setcity(string c)
    {
        isOnlyAlphabet(c);
        city = c;
    }
    void setcnic(string cn)
    {
        isValidCNIC(cn);
        cnic = cn;
    }
    void setrole(string r)
    {
        isOnlyAlphabet(r);
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
    }
};

class candidate : virtual public user
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
        string n, p, s, c, a,r;
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
        getline(cin, party);
        cout << "Symbol: ";
        getline(cin, symbol);
        cout<<"Role: ";
        getline(cin,r);
        setrole(r);
        cout << "Candidate ID: ";
        getline(cin, CandidateID);
        cout << "City: ";
        getline(cin, c);
        setcity(c);
        cout << "Area: ";
        getline(cin, area);
        cout << "CNIC: ";
        getline(cin, cn);
        setcnic(cn);
        cout << "Password: ";
        getline(cin, pw);
        setpassword(pw);
    }

    void update()
    {
        string targetCandidateID;
        cout << "Enter the Candidate ID of the person you want to update: ";
        cin.ignore();
        getline(cin, targetCandidateID);

        ifstream fin("candidates.txt");
        ofstream fout("temp.txt");

        if (!fin || !fout)
        {
            cout << Red << "Error opening file." << Reset << endl;
            return;
        }

        string name, age, cnic, city, role, password, candidateID, party, symbol, area, votes, eligibility, sep;
        bool found = false;

        while (getline(fin, name))
        {
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
                switch (choice)
                {
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
                cout << Green << "Information updated successfully.\n"
                     << Reset;
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
        ifstream fin("candidates.txt");
        if (!fin.is_open())
        {
            cout << Red << "Error opening candidates file!" << Reset << endl;
            return;
        }

        string line, name, age, cnic, city, role, password, candidateID, party, symbol, area, votes, eligible, sep;

        while (getline(fin, name))
        {
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
            getline(fin, eligible);
            getline(fin, sep);

            if (cnic == this->getcnic())  // 🟢 Match by CNIC instead of CandidateID
            {
                cout << Bold << "\nCandidate Full Details:\n" << Reset;
                cout << "Name: " << name << endl;
                cout << "Age: " << age << endl;
                cout << "CNIC: " << cnic << endl;
                cout << "City: " << city << endl;
                cout << "Role: " << role << endl;
                cout << "Candidate ID: " << candidateID << endl;
                cout << "Party: " << party << endl;
                cout << "Symbol: " << symbol << endl;
                cout << "Area: " << area << endl;
                cout << "Votes: " << votes << endl;
                cout << "Eligible: " << (eligible == "1" ? "Yes" : "No") << endl;
                fin.close();
                return;
            }
        }

        fin.close();
        cout << Red << "Candidate record not found in file." << Reset << endl;
    }

    void removeCandidate()
    {
        string targetCandidateID;
        cout << "Enter the Candidate ID to remove: ";
        cin.ignore();
        getline(cin, targetCandidateID);

        ifstream fin("candidates.txt");
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
            getline(fin, CandidateID);
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
        remove("candidates.txt");
        rename("temp.txt", "candidates.txt");
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
    
    void candidateMenu(candidate &c)
    {
        int choice;
        do
        {
            cout << "\n" << Bold << "Candidate Menu:\n" << Reset;
            cout << "1. View Information\n";
            cout << "2. View Vote Count in Election\n";
            cout << "3. See Area Standing\n";
            cout << "0. Log Out\n";
            cout << "Enter your choice: ";
            cin >> choice;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice)
            {
            case 1:
                c.displaydetails();  // pulls from file
                break;

            case 2:
            {
                // Re-fetch the latest vote count from file
                ifstream fin("candidates.txt");
                string line, name, age, cnic, city, role, password, candidateID, party, symbol, area, votesStr, eligible, sep;
                bool found = false;

                while (getline(fin, name))
                {
                    getline(fin, age);
                    getline(fin, cnic);
                    getline(fin, city);
                    getline(fin, role);
                    getline(fin, password);
                    getline(fin, candidateID);
                    getline(fin, party);
                    getline(fin, symbol);
                    getline(fin, area);
                    getline(fin, votesStr);
                    getline(fin, eligible);
                    getline(fin, sep);

                    if (candidateID == this->CandidateID)
                    {
                        cout << "Current Vote Count: " << votesStr << endl;
                        found = true;
                        break;
                    }
                }
                fin.close();
                if (!found)
                    cout << Red << "Candidate record not found." << Reset << endl;
                break;
            }

            case 3:
            {
                string targetArea;
                cout << "Enter area to check standings: ";
                getline(cin, targetArea);

                ifstream fin("candidates.txt");
                if (!fin)
                {
                    cout << Red << "Error opening candidates file." << Reset << endl;
                    break;
                }

                const int MAX = 100;
                string names[MAX], parties[MAX], symbols[MAX];
                int votes[MAX];
                int count = 0;

                string name, age, cnic, city, role, password, candidateID, party, symbol, area, votesStr, eligible, sep;

                while (getline(fin, name))
                {
                    getline(fin, age);
                    getline(fin, cnic);
                    getline(fin, city);
                    getline(fin, role);
                    getline(fin, password);
                    getline(fin, candidateID);
                    getline(fin, party);
                    getline(fin, symbol);
                    getline(fin, area);
                    getline(fin, votesStr);
                    getline(fin, eligible);
                    getline(fin, sep);

                    if (area == targetArea && count < MAX)
                    {
                        names[count] = name;
                        parties[count] = party;
                        symbols[count] = symbol;
                        votes[count] = stoi(votesStr);
                        count++;
                    }
                }
                fin.close();

                if (count == 0)
                {
                    cout << Red << "No candidates found in this area." << Reset << endl;
                    break;
                }

                // Manual selection sort
                for (int i = 0; i < count - 1; i++)
                {
                    int maxIdx = i;
                    for (int j = i + 1; j < count; j++)
                    {
                        if (votes[j] > votes[maxIdx])
                            maxIdx = j;
                    }
                    swap(names[i], names[maxIdx]);
                    swap(parties[i], parties[maxIdx]);
                    swap(symbols[i], symbols[maxIdx]);
                    swap(votes[i], votes[maxIdx]);
                }

                cout << "\n" << Yellow << "Candidates in Area: " << targetArea << Reset << endl;
                for (int i = 0; i < count; i++)
                {
                    cout << names[i] << " (" << parties[i] << ") - Symbol: "
                        << symbols[i] << " - Votes: " << votes[i] << endl;
                }
                break;
            }

            case 0:
                cout << Green << "Logging out..." << Reset << endl;
                break;

            default:
                cout << Red << "Invalid choice. Try again." << Reset << endl;
            }

        } while (choice != 4);
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
        : user(n, a, c, cn, r, p), voterID(vid), hasvoted(false), area(assigned_area)
    {
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
    void update()
    {
        string targetVoterID;
        cout << "Enter the Voter ID of the person you want to update: ";
        cin.ignore();
        getline(cin, targetVoterID);

        ifstream fin("voter.txt");
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
            getline(fin, sep);

            if (voterID == targetVoterID)
            {
                found = true;
                int choice;
                cout << "\nMatch Found!\nUpdate Options:\n1. Area\n2. Password\n3. City\n4. CNIC\nEnter choice: ";
                cin >> choice;
                cin.ignore();

                string newval;
                switch (choice)
                {
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
                cout << Green << "Information updated successfully.\n"
                     << Reset;
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

        if (!found)
        {
            cout << Red << "No voter found with ID: " << targetVoterID << Reset << endl;
        }
    }

    void cast_vote(const string& voterID_loggedIn)
    {
        if (hasvoted)
        {
            cout << Red << "You have already cast your vote. Multiple votes are not allowed.\n" << Reset;
            return;
        }

        int electionType;
        cout << Bold << "\nWhich election do you want to vote in?\n" << Reset;
        cout << Cyan << "1. National Election\n" << Reset;
        cout << Cyan << "2. Local Election\n" << Reset;
        cout << "Enter your choice: ";
        cin >> electionType;
        cin.ignore();

        char filename[30];
        if (electionType == 1)
        {
            strcpy(filename, "national_election.txt");
        }
        else if (electionType == 2)
        {
            strcpy(filename, "local_election.txt");
        }
        else
        {
            cout << Red << "Invalid election type selected.\n" << Reset;
            return;
        }

        // Load elections
        ifstream fin(filename);
        if (!fin)
        {
            cout << Red << "Could not open " << filename << Reset << endl;
            return;
        }

        const int MAX_ELECTIONS = 20;
        string elections[MAX_ELECTIONS];
        int count = 0;
        string line, block = "";

        while (getline(fin, line))
        {
            if (line == "----------------------")
            {
                if (block != "" && count < MAX_ELECTIONS)
                {
                    elections[count++] = block + line + "\n";
                    block = "";
                }
            }
            else
            {
                block += line + "\n";
            }
        }
        fin.close();

        if (electionType == 2)
        {
            string temp[MAX_ELECTIONS];
            int tempCount = 0;
            for (int i = 0; i < count; i++)
            {
                if (elections[i].find("Area: " + area) != string::npos)
                {
                    temp[tempCount++] = elections[i];
                }
            }
            for (int i = 0; i < tempCount; i++)
            {
                elections[i] = temp[i];
            }
            count = tempCount;

            if (count == 0)
            {
                cout << Red << "No Local elections found for your area: " << area << "\n" << Reset;
                return;
            }
        }

        if (count == 0)
        {
            cout << Red << "No elections found.\n" << Reset;
            return;
        }

        cout << Bold << "\nAvailable Elections:\n" << Reset;
        for (int i = 0; i < count; i++)
        {
            cout << "Election " << i + 1 << ":\n" << elections[i] << endl;
        }

        int choice;
        cout << "Enter the number of the election you want to vote in: ";
        cin >> choice;
        cin.ignore();
        if (choice < 1 || choice > count)
        {
            cout << Red << "Invalid election choice.\n" << Reset;
            return;
        }

        // Load candidates
        ifstream cf("candidates.txt");
        if (!cf)
        {
            cout << Red << "Cannot open candidates.txt\n" << Reset;
            return;
        }

        string candName[50], candID[50], candParty[50], candSymbol[50], candArea[50];
        int candVotes[50];
        int totalCandidates = 0;

        while (getline(cf, line))
        {
            string name = line;
            string age, cnic, city, role, pass, id, party, symbol, areaLine, voteLine, eligible, sep;
            getline(cf, age);
            getline(cf, cnic);
            getline(cf, city);
            getline(cf, role);
            getline(cf, pass);
            getline(cf, id);
            getline(cf, party);
            getline(cf, symbol);
            getline(cf, areaLine);
            getline(cf, voteLine);
            getline(cf, eligible);
            getline(cf, sep);

            if (areaLine == area && totalCandidates < 50)
            {
                candName[totalCandidates] = name;
                candID[totalCandidates] = id;
                candParty[totalCandidates] = party;
                candSymbol[totalCandidates] = symbol;
                candArea[totalCandidates] = areaLine;
                candVotes[totalCandidates] = stoi(voteLine);
                totalCandidates++;
            }
        }
        cf.close();

        if (totalCandidates == 0)
        {
            cout << Red << "No candidates found in your area.\n" << Reset;
            return;
        }

        cout << Bold << "\nCandidates in your area (" << area << "):\n" << Reset;
        for (int i = 0; i < totalCandidates; i++)
        {
            cout << i + 1 << ". " << candName[i] << " (" << candParty[i] << ", " << candSymbol[i] << ")\n";
        }

        cout << "Enter the number of the candidate you want to vote for: ";
        int voteIndex;
        cin >> voteIndex;
        cin.ignore();

        if (voteIndex < 1 || voteIndex > totalCandidates)
        {
            cout << Red << "Invalid candidate selected.\n" << Reset;
            return;
        }

        string selectedID = candID[voteIndex - 1];

        //Update candidate vote
        ifstream cfin("candidates.txt");
        ofstream cfout("temp.txt");
        string sep;

        while (getline(cfin, line))
        {
            string fields[12];
            fields[0] = line;
            for (int i = 1; i < 12; i++) getline(cfin, fields[i]);
            getline(cfin, sep);

            if (fields[6] == selectedID) // CandidateID match
            {
                int newVotes = stoi(fields[10]) + 1;
                fields[10] = to_string(newVotes);
            }

            for (int i = 0; i < 12; i++) cfout << fields[i] << endl;
            cfout << "----------" << endl;
        }
        cfin.close();
        cfout.close();
        remove("candidates.txt");
        rename("temp.txt", "candidates.txt");

        //Update voter record
        ifstream vin("voter.txt");
        ofstream vout("temp_v.txt");

        while (getline(vin, line))
        {
            string vfields[9];
            vfields[0] = line;
            for (int i = 1; i < 9; i++) getline(vin, vfields[i]);
            getline(vin, sep);

            if (vfields[6] == voterID_loggedIn)  // VoterID match
            {
                vfields[8] = "1"; // Set hasvoted = 1
                hasvoted = true;
            }

            for (int i = 0; i < 9; i++) vout << vfields[i] << endl;
            vout << "----------" << endl;
        }

        vin.close();
        vout.close();
        remove("Voter.txt");
        rename("temp_v.txt", "Voter.txt");

        cout << Green << "Your vote has been cast successfully.\n" << Reset;
    }


    // Display full info
    void displayDetails()
    {
        user::displayuserinfo();
        cout << "Voter ID: " << voterID << "\n";
        cout << "Area: " << area << "\n";
        cout << "Voted: " << (hasvoted ? "Yes" : "No") << "\n";
    }

    void saveToFile()
    {
        ofstream file("voter.txt", ios::app);
        if (file.is_open())
        {
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
        else
        {
            cout << "Error saving voter to file.\n";
        }
    }

    void deleteVoter()
    {
        string targetVoterID;
        cout << "Enter the Voter ID to remove: ";
        cin.ignore();
        getline(cin, targetVoterID);

        ifstream fin("voter.txt");
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
            getline(fin, sep); // ----------

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
        remove("voter.txt");
        rename("temp.txt", "voter.txt");
        if (!found)
        {
            cout << Red << "No voter found with ID: " << targetVoterID << Reset << endl;
        }
    }

    void deleteAllVoters()
    {
        ofstream file("voter.txt", ios::trunc);
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
    bool matchArea(const string &voterArea)
    {
        return area == voterArea;
    }

    // Overridden role display
    void showrole() override
    {
        cout << "Role: Voter\n";
    }

    void displayMenu(voter &v) {
        int choice;
        do {
            cout <<"\t\t\t\t" <<  "=========================================" << endl;
            cout <<Yellow<<"\t\t\t\t" << "              VOTER MENU                 " <<Reset<< endl;
            cout <<"\t\t\t\t" <<  "=========================================" << endl;
            cout<< "\t\t\t\t" << Blue << "1." <<"  View My Details" << endl;
            cout <<"\t\t\t\t" << Blue << "2." <<" Cast Vote" << endl;
             cout <<"\t\t\t\t" << Blue << "0." <<"  Logout" <<Reset<< endl;
            cout <<"\t\t\t\t"<< "=========================================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    v.displayDetails();  
                    break;
                case 2:
                    v.cast_vote(v.getVoterID());  
                    break;
               
                case 0:
                    cout << Green << "Logging out...\n" << Reset;
                    break;
                default:
                    cout << Red << "Invalid choice, please try again.\n" << Reset;
            }
        } while (choice != 0);
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
        int wins[MAX] = {0};
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

        cout << Bold << "\nParty-wise Winning Candidates Graph\n"
             << Reset;
        for (int i = 0; i < partyCount; i++)
        {
            cout << parties[i] << " | ";
            for (int j = 0; j < wins[i]; j++)
                cout << "█";
            cout << " (" << wins[i] << ")" << endl;
        }
    }

    static void drawCandidateGraph(const string &areaName)
    {
        ifstream file("result.txt");
        if (!file.is_open())
        {
            cout << Red << "Error opening result.txt!" << Reset << endl;
            return;
        }
        const int MAX = 100;
        string names[MAX];
        int votes[MAX] = {0};
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

        /*if (count == 0)
        {
            cout << Red << "No candidates found for area: " << areaName << Reset << endl;
            return;
        }*/
        cout << Bold << "\nCandidate-wise Vote Graph for Area: " << areaName << "\n"
             << Reset;
        for (int i = 0; i < count; i++)
        {
            cout << names[i] << " | ";
            for (int j = 0; j < votes[i]; j += 50) // scale down
                cout << "█";
            cout << " (" << votes[i] << " votes)" << endl;
        }
    }
};

class Result : virtual public candidate, virtual public Graph
{
private:
    string status; // "Won" or "Lost"

public:
    Result() {}

    Result(const candidate &c, string winStatus)
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

    void setStatus(string s)
    {
        status = s;
    }

    string getStatus() const
    {
        return status;
    }

    void saveResultToFile() const
    {
        if (status != "Won") return;

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

    static void showAreaResults(const string &areaName)
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

    cout << Bold << "\nResults for area: " << areaName << "\n"
         << Reset;

    for (int i = 0; i < count; i++)
    {
        if (results[i].getvotecount() == highestVotes)
        {
            results[i].setStatus("Won");
            results[i].saveResultToFile();
        }
        else
        {
            results[i].setStatus("Lost");
        }

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
        int wins[MAX_RECORDS] = {0};
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
        cout << Bold << "\nParty Wins Summary:\n"
             << Reset;
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
            // system("cls");
            cout << "=====================================================================" << endl;
    cout << White <<"                              ADMIN MENU                             " << endl;
            cout << "=====================================================================" << endl;
            cout<< "\t\t\t\t" << Blue << "1." << Reset << " Create Election" << endl;
            cout <<"\t\t\t\t" << Blue << "2." << Reset << " Add Users" << endl;
            cout <<"\t\t\t\t" << Blue << "3." << Reset << " Update Users" << endl;
            cout <<"\t\t\t\t" << Blue << "4." << Reset << " Remove Users" << endl;
            cout <<"\t\t\t\t" << Blue << "5." << Reset << " Show Results " << endl;
            cout <<"\t\t\t\t" << Blue << "6." << Reset << " Reset Results " << endl;
            cout <<"\t\t\t\t" << Blue << "7." << Reset << " Delete All Voters " << endl;
            cout <<"\t\t\t\t" << Blue << "8." << Reset << " Approve Pending Users" << endl;
            cout <<"\t\t\t\t" << Blue << "0." << Reset << " Logout" << endl;
            cout << "=====================================================================" << endl;
            
            cout << "\t\t\tEnter your choice: " << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                createElection();
                break;
            case 2:
                addUsers();
                break;
            case 3:
                updateUsers();
                break;
            case 4:
                removeUsers();
                break;
         
            case 5:
                showResults();
                break;
            case 6:
                resetResults();
                break;
            case 7:
                deleteAllVotersData();
                break;
            case 8:
                approvedPendingUsers();
                break;
            case 0:
                cout << Green << "Logging out...\n"
                     << Reset;
                return;
            default:
                cout << Red << "Invalid choice, try again.\n"
                     << Reset;
            }
            // system("pause");
        } while (choice != 0);
    }
    void updateUsers(){
      while(true)
        {
            cout << White <<"                              UPDATE  USERS                             " << endl;
                cout << Blue << "\t\t\t\t1." << Reset << "Voter\n";
                cout << Blue << "\t\t\t\t2." << Reset << "Candidate\n";
                 cout << Blue << "\t\t\t\t0." << Reset << "Back\n";
        
                int n;
                cout << "\t\t\tEnter choice : ";
                cin >> n;
         if(n==1){ 
               updateVoter();
                continue;
         }
        if(n==2){ 
             updateCandidate();
             continue;
         }
         
         if(n==0){ 
            break;
         }
       
        }

 } 

 void removeUsers(){
      while(true)
        {
            cout << White <<"                              REMOVE  USERS                             " << endl;
                cout << Blue << "\t\t\t\t1." << Reset << "Voter\n";
                cout << Blue << "\t\t\t\t2." << Reset << "Candidate\n";
                 cout << Blue << "\t\t\t\t0." << Reset << "Back\n";
        
                int n;
                cout << "\t\t\tEnter choice : ";
                cin >> n;
         if(n==1){ 
               removeVoter();
                continue;
         }
        if(n==2){ 
             removeCandidate();
             continue;
         }
         
         if(n==0){ 
            break;
         }
       
        }

 }   
void  addUsers(){
  
        while(true)
        {
            cout << White <<"                              ADD  USERS                             " << endl;
                cout << Blue << "\t\t\t\t1." << Reset << "Voter\n";
                cout << Blue << "\t\t\t\t2." << Reset << "Candidate\n";
                 cout << Blue << "\t\t\t\t0." << Reset << "Back\n";
        
                int n;
                cout << "\t\t\tEnter choice : ";
                cin >> n;
         if(n==1){ 
                addNewVoter();
                continue;
         }
        if(n==2){ 
             addCandidate();
             continue;
         }
         
         if(n==0){ 
            break;
         }
       
        }

}
    void approvedPendingUsers()
    {

        
        while(true)
        {
            cout << White <<"                              PENDING USERS                             " << endl;
                cout << Blue << "\t\t\t\t1." << Reset << "Voters\n";
                cout << Blue << "\t\t\t\t2." << Reset << "Candidates\n";
                cout << Blue << "\t\t\t\t3." << Reset << "Admin\n";
                cout << Blue << "\t\t\t\t0." << Reset << "Back\n";
        
                int n;
                cout << "\t\t\tEnter choice : ";
                cin >> n;
         if(n==1){ 
            approveVoters();
            continue;
         }
        if(n==2){ 
           approveCandidates();
           continue;
         }
         if(n==3){ 
           approveAdmins();
           continue;
         }
         if(n==0){ 
            break;
         }
       
        }
    }

    void createElection()
    {
        cout << Bold << "\t\t\t\t=== Create New Election ===" << Reset << endl;
        int electionType;
        string AreaName;
        ofstream file;

        cout << "\t\t\t\tWhich type of election do you want to start?" << endl;
        cout << Cyan << "\t\t\t\t1. National Election" << Reset << endl;
        cout << Cyan << "\t\t\t\t2. Local Election" << Reset << endl;
        cout << "\t\t\tEnter your choice: ";
        cin >> electionType;

        int year, month, day, hour, minute;
        cout << "Enter election end date and time (YYYY MM DD HH MM): ";
        cin >> year >> month >> day >> hour >> minute;

        tm end_tm = {};
        end_tm.tm_year = year - 1900;
        end_tm.tm_mon = month - 1;
        end_tm.tm_mday = day;
        end_tm.tm_hour = hour;
        end_tm.tm_min = minute;
        end_tm.tm_sec = 0;

        time_t endTime = mktime(&end_tm);
        if (endTime == -1)
        {
            cout << Red << "Invalid time entered." << Reset << endl;
            return;
        }

        char *endTimeStr = ctime(&endTime);

        switch (electionType)
        {
        case 1:
            file.open("national_election.txt", ios::app);
            if (!file.is_open())
            {
                cout << Red << "Error: Could not open national_election.txt." << Reset << endl;
                return;
            }
            cout << Green << "National Election started successfully." << endl;
            file << "----------------------" << endl;
            file << "ElectionType: National" << endl;
            file << "Election Number: " << ++electionCount << endl;
            file << "End Time: " << endTimeStr;
            file << "----------------------" << endl;
            break;
        case 2:
            cin.ignore();
            cout << "Enter the name of the Area ";
            getline(cin, AreaName);
            file.open("local_election.txt", ios::app);
            if (!file.is_open())
            {
                cout << Red << "Error: Could not open provincial_election.txt." << Reset << endl;
                return;
            }
            cout << Green << AreaName << " Provincial Election started successfully." << Reset << endl;
            file << "----------------------" << endl;
            file << "ElectionType: Provincial" << endl;
            file << "Area " << AreaName << endl;
            file << "Election Number: " << ++electionCount << endl;
            file << "End Time: " << endTimeStr;
            file << "----------------------" << endl;
            break;

        default:
            cout << Red << "Invalid election type selected." << Reset << endl;
            return;
        }
        file.close();
    }

    void addCandidate()
    {
        candidate c;
        c.setDetails();
        c.saveToFile();
        cout << Green << "Candidate added successfully.\n"
             << Reset;
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
        cout << Green << "New voter added successfully.\n"
             << Reset;
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
        cout << Green << "All election results have been reset.\n"
             << Reset;
    }

    void showResults()
    {
        string area;
        int choice;
        cout << "\nChoose result type:\n1. National Election\n2. Local/Area-wise Result\n3. Exit\nEnter: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            Result::showLeadingParty();
            Graph::drawPartyGraph();
            break;
        case 2:
            cout << "Enter area name: ";
            getline(cin, area);
            Result::showAreaResults(area);
            Graph::drawCandidateGraph(area);
            break;
        case 3:
            break;
        default:
            cout << Red << "Invalid input!\n"
                 << Reset;
        }
    }

    void approveRole(const string &targetRole, const string &outputFile)
    {
        ifstream inFile("Approval.txt");
        ofstream tempFile("temp.txt");
        ofstream outFile(outputFile, ios::app);

        if (!inFile || !tempFile || !outFile)
        {
            cout << "File open error.\n";
            return;
        }

        string line;
        string record[1000];
        int index = 0;

        while (getline(inFile, line))
        {
            if (line == "----------")
            {
                if (index >= 5 && record[4] == targetRole)
                {
                    cout << "\nPending " << targetRole << ":\n";
                    for (int i = 0; i < index; i++)
                        cout << record[i] << endl;

                    cout << "\nApprove this " << targetRole << "? (y/n): ";
                    char choice;
                    cin >> choice;
                    cin.ignore();

                    if (choice == 'y' || choice == 'Y')
                    {
                        for (int i = 0; i < index; i++)
                            outFile << record[i] << endl;
                        outFile << "----------" << endl;
                        cout << targetRole << " approved.\n";
                    }
                    else
                    {
                        for (int i = 0; i < index; i++)
                            tempFile << record[i] << endl;
                        tempFile << "----------" << endl; // remaining pending es file mei hongye
                        cout << targetRole << " skipped.\n";
                    }
                }
                else
                {
                    for (int i = 0; i < index; i++)
                        tempFile << record[i] << endl;
                    tempFile << "----------" << endl;
                }
                index = 0;
            }
            else
            {
                if (index < 1000)
                    record[index++] = line;
            }
        }

        inFile.close();
        tempFile.close();
        outFile.close();

        remove("Approval.txt");
        rename("temp.txt", "Approval.txt");
    }

    void approveVoters()
    {
        approveRole("Voter", "voter.txt");
    }

    void approveCandidates()
    {
        approveRole("Candidate", "candidate.txt");
    }

    void approveAdmins()
    {
        approveRole("Admin", "admin.txt");
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
    string *cities;
    int citycount;
    int cityCapacity;
    candidate **candidates;
    int candidatecount;
    int candidateCapacity;
    bool electionStarted;

public:
    provincial(string name = "", int id = 0) : provincename(name), provinceid(id), citycount(0), cityCapacity(5), candidatecount(0), candidateCapacity(5), electionStarted(false)
    {
        cities = new string[cityCapacity];
        candidates = new candidate *[candidateCapacity];
    }

    ~provincial()
    {
        delete[] cities;
        delete[] candidates;
    }

    void resizeCities()
    {
        cityCapacity *= 2;
        string *newCities = new string[cityCapacity];
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
        candidate **newCandidates = new candidate *[candidateCapacity];
        for (int i = 0; i < candidatecount; i++)
        {
            newCandidates[i] = candidates[i];
        }
        delete[] candidates;
        candidates = newCandidates;
    }

    void addCity(const string &city)
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
                    candidate *c = new candidate();
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
        string *parties = new string[candidatecount];
        int *seats = new int[candidatecount];
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

    candidate *getCandidateAt(int index)
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
    provincial **provinces;
    int provinceCount;
    int provinceCapacity;

public:
    national_election()
    {
        provinceCount = 0;
        provinceCapacity = 3;
        provinces = new provincial *[provinceCapacity];
    }

    ~national_election()
    {
        delete[] provinces;
    }

    void resizeProvinces()
    {
        provinceCapacity *= 2;
        provincial **newArray = new provincial *[provinceCapacity];
        for (int i = 0; i < provinceCount; i++)
        {
            newArray[i] = provinces[i];
        }
        delete[] provinces;
        provinces = newArray;
    }

    void addProvince(provincial *p)
    {
        if (provinceCount == provinceCapacity)
        {
            resizeProvinces();
        }
        provinces[provinceCount++] = p;
    }

    void createElection()
    {
        cout << Green << "National Election Started!\n"<< Reset;
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
};

void login_page()
{
    int n;
    string entered_id, entered_pw;

    while (true)
    {
        cout << "\n\t\t\t       Select your Role:" << endl;
        cout << "\t\t\t\t" << Blue << "1." << Reset << " Voter" << endl;
        cout << "\t\t\t\t" << Blue << "2." << Reset << " Candidate" << endl;
        cout << "\t\t\t\t" << Blue << "3." << Reset << " Admin" << endl;
        cout << "\t\t\t\t" << Blue << "0." << Reset << " Exit" << endl;
        cin >> n;

        if (n == 0)
        {
            cout << Yellow << "Exiting the system. Goodbye!\n" << Reset;
            break;
        }

        cin.ignore();
        cout << "Enter Your ID (VoterID / CandidateID / AdminID): ";
        getline(cin, entered_id);

        string filename;
        if (n == 1)
            filename = "voter.txt";
        else if (n == 2)
            filename = "candidates.txt";
        else if (n == 3)
            filename = "admin.txt";
        else
        {
            cout << Red << "Invalid role choice.\n" << Reset;
            continue;
        }

        ifstream file(filename);
        if (!file.is_open())
        {
            cout << Red << "Error opening " << filename << Reset << endl;
            continue;
        }

        string line, name, age, cnic, city, role, password;
        bool found = false, correctPassword = false;

        while (getline(file, name))
        {
            string userBlock = name + "\n";
            getline(file, age); userBlock += age + "\n";
            getline(file, cnic); userBlock += cnic + "\n";
            getline(file, city); userBlock += city + "\n";
            getline(file, role); userBlock += role + "\n";
            getline(file, password); userBlock += password + "\n";

            string userID;

            if (role == "Voter")
            {
                string area, hasvoted, sep;
                getline(file, userID); userBlock += userID + "\n";
                getline(file, area); userBlock += area + "\n";
                getline(file, hasvoted); userBlock += hasvoted + "\n";
                getline(file, sep); userBlock += sep + "\n";

                if (entered_id == userID)
                {
                    for (int attempts = 1; attempts <= 3; attempts++)
                    {
                        cout << "Enter Password: ";
                        getline(cin, entered_pw);
                        if (entered_pw == password)
                        {
                            correctPassword = true;
                            break;
                        }
                        else
                        {
                            cout << Red << "Wrong password! Attempt " << attempts << "/3\n" << Reset;
                        }
                    }

                    if (!correctPassword)
                    {
                        cout << Red << "Too many wrong attempts. User blocked.\n\n" << Reset;

                        ofstream blockFile("block.txt", ios::app);
                        blockFile << userBlock;
                        blockFile << "----------------\n";
                        blockFile.close();

                        ifstream inFile(filename);
                        ofstream tempFile("temp.txt");
                        string tempLine, currentBlock = "";
                        bool skip = false;

                        while (getline(inFile, tempLine))
                        {
                            currentBlock += tempLine + "\n";
                            if (tempLine == userID)
                                skip = true;

                            if (tempLine == "----------------")
                            {
                                if (!skip)
                                    tempFile << currentBlock;
                                currentBlock = "";
                                skip = false;
                            }
                        }
                        inFile.close();
                        tempFile.close();
                        remove(filename.c_str());
                        rename("temp.txt", filename.c_str());
                        break;
                    }
                    found = true;
                    cout << Green << "Welcome " << name << "! (Voter)\n" << Reset;
                    voter v(name, stoi(age), city, cnic, role, password, userID, area);
                    v.sethasvoted(hasvoted == "1");
                    v.displayMenu(v);
                    break;
                }
            }
            else if (role == "Candidate")
            {
                string candidateID, party, symbol, area, votes, eligible, sep;
                getline(file, candidateID);
                getline(file, party);
                getline(file, symbol);
                getline(file, area);
                getline(file, votes);
                getline(file, eligible);
                getline(file, sep);

                userBlock += candidateID + "\n" + party + "\n" + symbol + "\n" + area + "\n" +
                             votes + "\n" + eligible + "\n" + sep + "\n";

                if (entered_id == candidateID)
                {
                    for (int attempts = 1; attempts <= 3; attempts++)
                    {
                        cout << "Enter Password: ";
                        getline(cin, entered_pw);

                        if (entered_pw == password)
                        {
                            correctPassword = true;
                            break;
                        }
                        else
                        {
                            cout << Red << "Wrong password! Attempt " << attempts << "/3\n" << Reset;
                        }
                    }

                    if (!correctPassword)
                    {
                        cout << Red << "Too many wrong attempts. Candidate blocked.\n\n" << Reset;

                        ofstream blockFile("block.txt", ios::app);
                        blockFile << userBlock;
                        blockFile << "----------------\n";
                        blockFile.close();

                        ifstream inFile(filename);
                        ofstream tempFile("temp.txt");
                        string tempLine, currentBlock = "";
                        bool skip = false;

                        while (getline(inFile, tempLine))
                        {
                            currentBlock += tempLine + "\n";
                            if (tempLine == candidateID)
                                skip = true;

                            if (tempLine == "----------------")
                            {
                                if (!skip)
                                    tempFile << currentBlock;
                                currentBlock = "";
                                skip = false;
                            }
                        }

                        inFile.close();
                        tempFile.close();
                        remove(filename.c_str());
                        rename("temp.txt", filename.c_str());
                        break;
                    }

                    found = true;
                    cout << Green << "Welcome " << name << "! (Candidate)\n" << Reset;
                    candidate c(name, stoi(age), city, cnic, role, password, symbol, candidateID);
                    c.setparty(party);
                    c.setarea(area);
                    c.setvotecount(stoi(votes));
                    c.candidateMenu(c);
                    break;
                }
            }
            else if (role == "Admin")
            {
                string sep;
                getline(file, userID); userBlock += userID + "\n";
                getline(file, sep); userBlock += sep + "\n";

                if (entered_id == userID)
                {
                    for (int attempts = 1; attempts <= 3; attempts++)
                    {
                        cout << "Enter Password: ";
                        getline(cin, entered_pw);
                        if (entered_pw == password)
                        {
                            correctPassword = true;
                            break;
                        }
                        else
                        {
                            cout << Red << "Wrong password! Attempt " << attempts << "/3\n" << Reset;
                        }
                    }

                    if (!correctPassword)
                    {
                        cout << Red << "Too many wrong attempts. Admin blocked.\n\n" << Reset;

                        ofstream blockFile("block.txt", ios::app);
                        blockFile << userBlock;
                        blockFile << "----------------\n";
                        blockFile.close();

                        ifstream inFile(filename);
                        ofstream tempFile("temp.txt");
                        string tempLine, currentBlock = "";
                        bool skip = false;

                        while (getline(inFile, tempLine))
                        {
                            currentBlock += tempLine + "\n";
                            if (tempLine == userID)
                                skip = true;

                            if (tempLine == "----------------")
                            {
                                if (!skip)
                                    tempFile << currentBlock;
                                currentBlock = "";
                                skip = false;
                            }
                        }
                        inFile.close();
                        tempFile.close();
                        remove(filename.c_str());
                        rename("temp.txt", filename.c_str());
                        break;
                    }
                    found = true;
                    cout << Green << "Welcome Admin " << name << "!\n" << Reset;
                    admin a(name, stoi(age), city, cnic, role, password);
                    a.adminMenu();
                    break;
                }
            }
        }

        file.close();
        if (!found && !correctPassword)
        {
            cout << Red << "Incorrect ID or user not found.\n\n" << Reset;
        }
    }
}

void signup()
{
    string name, city, cnic, password, id, area, party, symbol, role;
    int age;

    cin.ignore();
    cout << "Enter Role (Voter/Candidate/Admin): ";
    getline(cin, role);

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    while (!(cin >> age) || age < 18 || age > 120)
    {
        cout << Red << "Invalid age. Enter a number between 18 and 120: " << Reset;
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    cout << "Enter City: ";
    getline(cin, city);

    cout << "Enter CNIC: ";
    getline(cin, cnic);
    if (isCNICDuplicate(cnic))
    {
        cout << "Error: CNIC already exists!\n";
        return;
    }

    cout << "Enter Password: ";
    getline(cin, password);

    if (role == "Voter")
    {
        cout << "Enter Voter ID: ";
        getline(cin, id);
        cout << "Enter Area: ";
        getline(cin, area);
    }
    else if (role == "Candidate")
    {
        cout << "Enter Candidate ID: ";
        getline(cin, id);
        cout << "Enter Party: ";
        getline(cin, party);
        cout << "Enter Symbol: ";
        getline(cin, symbol);
        cout << "Enter Area: ";
        getline(cin, area);
    }
    else if (role == "Admin")
    {
        cout << "Enter Admin ID: ";
        getline(cin, id);
    }
    else
    {
        cout << "Invalid role.\n";
        return;
    }

    ofstream file("Approval.txt", ios::app);
    if (!file)
    {
        cout << "Error opening approval file.\n";
        return;
    }

    file << name << endl;
    file << age << endl;
    file << cnic << endl;
    file << city << endl;
    file << role << endl;
    file << password << endl;
    file << id << endl;
    if (role == "Voter")
    {
        file << area << endl;
        file << "0\n";
    }
    else if (role == "Candidate")
    {
        file << party << endl;
        file << symbol << endl;
        file << area << endl;
        file << "0\n1\n";
    }
    file << "----------\n";
    file.close();
    cout << role << " account submitted for approval.\n";
}

int main()
{

    interface_logo();

    int choice;
    cout << "Enter Your Choice" << endl;
    cout << "\t\t\t\t" << Blue << "1." <<Reset<<"  Login" << endl;
    cout <<  "\t\t\t\t" << Blue << "2." <<Reset<<"  Sign Up" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        login_page();
        break;
    case 2:
        signup();
        break;
    default:
        break;
    }
    return 0;
}