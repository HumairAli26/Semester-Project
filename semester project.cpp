class candidate:public user

{
private:
    string party;
    string symbol;
    string area;
    int votecount;
    bool eligibility;
public:
    candidate() : user(), party(""), symbol(""), area(""), votecount(0), eligibility(true) {}//agr kush enter nai karta to default values store hon gi


    void setDetails() {
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
    void update() {
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
    }//ek masla ho gaya yahan pa user sa name age city or cnic inharit nai ho raha get wala functions like user::getname(); ye  error kar raha ha 
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
    bool matcharea(const string& voterarea) {//copy constructor 
        if (area == voterarea) {
            return true;
        }
        else
            return false;
    }
    bool iseligble() {
        return eligibility && getage() >= 25;//agr age 25 ye 25 sa bhari ha tabhi vote cast kar saka ga 
    }
    void showrole() override {
        cout << "Role: Candidate (" << party << ")\n";
    }
    void saveToFile() {
        ofstream file("candidates.txt", ios::app);
        if (file.is_open()) {
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
            file.close();
        }
        else {
            cout << "Error opening candidates file.\n";
        }
    }
};
        


