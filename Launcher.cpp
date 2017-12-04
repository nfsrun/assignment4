// Name         : Launcher.h
// Author       : Kevin Tran
// Derived      :
// Version      : 1.00 initial commit.
// Modified     : 1.00 initial commit.
// Description  : Sets up the program to launch the phone book. It has private
// fields itself and multiple methods to run different functions that would be
// apparent in phone book operations. This interacts with the Contact class in
// which Contacts is used to keep objects of each different contact.
// !!INPUTS ARE CASE SENSITIVE!!
// In the revision, I have added a boolean to start testing a certain range of
// contacts when a contact file is loaded. It will not print the contacts but
// will keep time as it traverses through.

#include "Contact.h"
#include <fstream>
#include <ctime>
#include "BinarySearchTree.h"

using namespace std;

//class is defined with two private variables.
class launcher {
    //constructor that defines the class with the Binary Search Tree
    //for the class.
    BinarySearchTree<Contact> *list;

    //boolean to switch search to testing mode
    bool testMode = true;
    string fileName;
public:
    //public constructor that initializes the size counter and the Binary
    //Search Tree.
    launcher() {
        list = new BinarySearchTree<Contact>();
    };

    string getName() {
        string name;
        cout << "Enter name: ";
        //cin.ignore is used to
        getline(cin, name);
        //name that was passed in will have a \r character that needs to be
        //removed to make string comparisons more accurate.
        return name;
    }

    void add() {
        string name = getName(), num;
        cout << "Enter Phone Number: ";
        cin >> num;
        Contact add = Contact(name, num);
        this->list->insert(add);
        //and display a success message
        cout << "Operation complete. " << endl << endl;
    }

    //search function
    //finds the contact information by searching the Binary Search Tree via name.
    //prints out the information. If testMode is true, then it will traverse
    //the recently loaded file of contacts in the Binary Search Tree database.
    void search() {
        //getName function is called to set the search_name variable.
        Contact retrieve, target;
        if(this->testMode==false) {
            string search_name = getName();
            cout << endl;
            target = Contact(search_name);
            retrieve = (this->list->search(target));
        }else{
            fstream fileIn;
            fileIn.open(this->fileName);
            ofstream file;
            string s;
            fileIn<<endl;
            string name;
            int elementNum = 1;
            while (1) {
                if (!(fileIn >> name)) {
                    break;
                }
                name.append(" ");
                string lastName;
                string skipPhone;
                fileIn >> lastName;
                name += lastName;
                fileIn >> skipPhone;
                target = Contact(name);


                for(int i=1; i<4; i++) {
                    s += "Binary Search Tree," + name + "," +
                            to_string(elementNum) + "," + to_string(i) + ",";
                    clock_t start = clock();
                    retrieve = (this->list->search(target));
                    clock_t end = clock();
                    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
                    s+=to_string(elapsed_secs)+"\n";
                }
                elementNum++;
            }
            file.open("DataAnalysis.csv");
            file << "Structure Type,Target Name,Element Number,"
                 << "Search Iteration,Time" << endl << s;
            file.close();
            fileIn.close();
        }
        Contact blank = Contact();
        if(this->testMode==true) {
            cout<<"Test completed."<<endl<<endl;
        }else if(retrieve!=blank){
            cout<<"Phone: " << retrieve.getPhoneNumber() << endl;
        }else{
            cout<<"Contact not found! "<<endl;
        }
    }

    void load() {
        fstream file;
        string name;
        string phoneNumber;
        bool first=true;
        file.clear(file.failbit);
        while(1) {
            if(!file.fail()) {
                break;
            }else if(first==false){
                cout << "No file exists, please check the file again. ";
            }
            first=false;
            cout << "Enter file name: ";
            cin >> this->fileName;
            cout << endl;
            file.open(this->fileName);
        }
        file.clear();
        file.seekg(0, ios::beg);
        while (1) {
            if (!(file >> name)) {
                break;
            }
            name.append(" ");
            string lastName;
            file >> lastName;
            name += lastName;
            file >> phoneNumber;
            Contact c = Contact(name, phoneNumber);
            this->list->insert(c);
        }
        file.close();
    }

    void print(){
        //Contact empty = Contact();
        string s = this->list->inOrder();
        if(s!=""){
            cout<<s;
        }else{
            cout<<"The Binary Tree List of contacts is empty! ";
        }
    }

    void filter(){
        //Contact empty = Contact();
        string name = getName();
        Contact add = Contact(name, "");
        string s = this->list->inOrder("", add);
        if(s!=""){
            cout<<s;
        }else{
            cout<<"The Binary Tree List of contacts is empty! ";
        }
    }

    //run method
    //checks user char input to choose what will happen next.
    int run() {
        cout<< "A(Add) | L (Load) | S(Search) | P(Print) |F(Filter) |Q(Quit): ";
        char check;
        cin >> check;
        cout << endl;
        cin.ignore();
        //respective letter entered in will start a respective operation.
        if ((check == 'a' || check == 'A') == 1) {
            add();
            run();
        } else if ((check == 'l' || check == 'L') == 1) {
            load();
            run();
        } else if ((check == 's' || check == 'S') == 1) {
            search();
            run();
        } else if ((check == 'p' || check == 'P') == 1) {
            print();
            run();
        } else if ((check == 'f' || check == 'F') == 1) {
            filter();
            run();
        } else if ((check == 'q' || check == 'Q') == 1) {
            cout<<"Bye";
            return 0;
            //else if input does not match, please re-run and return an error.
        } else {
            cout << endl << "Invalid Command" << endl << endl;
            run();
        }
        return 0;
    }
};


//main function
//starts the program
int main(){
    cout<<"***MY	PHONEBOOK	APPLICATION***"<<endl;
    //creates the launcher object.
    launcher * inst = new launcher();
    cout<<"Please	choose	an	operation:"<<endl;
    //start running the program
    while(inst->run()==1)
        return 0;
};