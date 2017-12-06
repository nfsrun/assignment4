// Name         : Launcher.h
// Author       : Kevin Tran
// Derived      : Phone Book Console Project
// Version      : 1.00 initial commit.
// Modified     : 1.01 initial commit.
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
#include <chrono>
#include "BinarySearchTree.h"

using namespace std;
using namespace std::chrono;

//class is defined with two private variables.
class launcher {
    //constructor that defines the class with the Binary Search Tree
    //for the class.
    BinarySearchTree<Contact> *list;
    string fileName;
public:
    //public constructor that initializes the size counter and the Binary
    //Search Tree.
    launcher() {
        list = new BinarySearchTree<Contact>();
    };

    //getName method is a recycling method that would be used multiple times to
    //get the name of some individuals for different action purposes.
    string getName() {
        string name;
        cout << "Enter name: ";

        //cin.ignore is used to
        getline(cin, name);

        //name that was passed in will have a \r character that needs to be
        //removed to make string comparisons more accurate.
        return name;
    }

    //Add method to manually add a person in as a contact via the console.
    //It will ask the user to input the name and phone number via a method
    //called in validator.
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
    //finds the contact information by searching the Binary Search Tree via
    //name. Prints out the information. If testMode is true, then it will
    //traverse the recently loaded file of contacts in the Binary Search Tree
    //database.
    void search() {
        //getName function is called to set the search_name variable.
        Contact retrieve, target;
        string search_name = getName();
        cout << endl;
        target = Contact(search_name);
        retrieve = (this->list->search(target));
        Contact blank = Contact();
        if(this->list->isEmpty()) {
            cout<<"Contact list is currently empty. " << endl << endl;
        }else if(retrieve!=blank){
            cout<<"Phone: " << retrieve.getPhoneNumber() << endl;
        }else{
            cout<<"Contact not found! "<<endl;
        }
    }

    //searchAutoTest function
    //Utilizes the last loaded file as the basis of time testing the tree of
    //contacts.
    void searchAutoTest(){
        cout<<"Loading Automated testing on last loaded file: " <<
                                                                this->fileName;
        fstream fileIn;

        //if the file is loaded, filename should not be empty, then
        if(this->fileName!="") {
            fileIn.open(this->fileName);
            ofstream file;
            string s;
            fileIn << endl;
            cout << endl << "File Loaded. Starting test. " << endl;
            string name;
            int elementNum = 1;

            //iterate through each contact and parse the strings to yield
            //interests of testing
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
                Contact target = Contact(name);

                //the testing for each contact is done three times
                for (int i = 1; i < 4; i++) {
                    s += "Binary Search Tree," + name + "," +
                         to_string(elementNum) + "," + to_string(i) + ",";

                    //start using an accurate time clock
                    auto start = high_resolution_clock::now();

                    //perform the search
                    this->list->search(target);

                    //record end time
                    auto end = high_resolution_clock::now();
                    int elapsed_secs =
                            duration_cast<nanoseconds>(end-start).count();
                    s += to_string(elapsed_secs) + "\n";
                }
                elementNum++;
            }
            fileIn.close();
            file.open("DataAnalysis.csv");
            file << "Structure Type,Target Name,Element Number,"
                 << "Search Iteration,Time (nanoseconds)" << endl << s;
            file.close();
            cout << "Test completed." << endl << endl;

        //else if the command to test was ran with no prevviously loaded csv
        //files, then cancel action and request user to try again
        }else{
            cout<<"No valid file has been loaded. Try loading again. "
                << endl << endl;
        }
    }

    //load function
    //loads a txt file of contacts to put into the contact database.
    void load() {
        fstream file;
        string name;
        string phoneNumber;

        //boolean for first run on FileName request so the wrong message doesn't
        //appear. Also clears failbit in case a non-existent file name has been
        //called before.
        bool first=true;
        file.clear(file.failbit);

        //while loop will continue to run until a valid file has been inputted.
        while(1) {

            //the if statement will be true when a real file has been found.
            if(!file.fail()) {
                break;

            //else keep asking
            }else if(first==false){
                cout << "No file exists, please check the file again. " << endl
                        << endl;
            }

            //after the first iteration of the loop has been past, this is set
            //to off in order to control output messages from displaying
            //wrongfully the first time.
            first=false;
            cout << "Enter file name: ";
            cin >> this->fileName;
            cout << endl;
            file.open(this->fileName);
        }

        //once a valid file will start at the beginning. Also clears failbit in
        //case a non-existent file name has been called before.
        file.clear();
        file.seekg(0, ios::beg);

        //Then the whole lists of contacts will be parsed through and added to
        //the contact book.
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

    //print function
    //prints the list of contacts in order by traversing through the tree in an
    //in order fashion.
    void print(){
        //Contact empty = Contact();
        string s = this->list->inOrder();
        if(s!=""){
            cout<<s;
        }else{
            cout<<"The Binary Tree List of contacts is empty! ";
        }
        cout << endl <<endl;
    }

    //filter method
    //this method is similar to print except it will stop printing before it
    //traerses and hits the target person (that person will not be printed).
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
        cout<< "A(Add) | L (Load) | S(Search) | P(Print) | F(Filter) | Q(Quit)"
                <<" | U(Automated Search Testing): ";
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
        } else if ((check == 'u' || check == 'U') == 1) {
            searchAutoTest();
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