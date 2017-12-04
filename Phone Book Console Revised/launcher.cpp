/*
 * launcher.cpp
 *
 *  Created on: Oct 2, 2017
 *  Revised on: Dec 4, 2017
 *      Author: Kevin Tran
 *      launcher.cpp class
 *      Sets up the program to launch the phone book. It has private fields
 *      itself and multiple methods to run different functions that would be
 *      apparent in phone book operations. This interacts with the Contact class
 *      in which Contacts is used to keep objects of each different contact.
 *      !!INPUTS ARE CASE SENSITIVE!!
 *      Revised on December 4th to encompass a testing mode where the
 *      applicaiton can write timing results to a csv file for comparison.
 */

#include <iostream>
#include <fstream>
#include "Contact.h"
using namespace std;

//class is defined with two private variables.
class launcher{
    //constructor that defines the class with the size counter and the array
    //for the class.
    int size;
    Contact *list;

    //boolean for testMode, change to adjust search behavior
    bool testMode =  true;
public:
    //public constructor that initializes the size counter and the array.
    launcher(){
        size=0;
        list = new Contact[0];
    };
    //getName method
    //asks the user for a name by using the getline method.
    string getName(){
        string name;
        cout<<"Enter name: ";
        getline(cin, name);
        return name;
    }
    //add function
    //adds a contact to an array.
    void add(){
        //getName function is called to set the name variable.
        string name = getName(), num;
        cout<<"Enter Phone Number: ";
        //cin used to set num for phone number.
        cin>>num;
        //increases the size
        size++;
        //initializes a new array to create.
        Contact *temp = new Contact[size];
        //for loop will transfer the contents of the original array into the new array
        for(int i=0; i<size-1; i++){
            temp[i]=list[i];
        }
        //the last array index will have the new content.
        temp[size-1] = Contact(name, num);
        //nullify the old list
        list = NULL;
        //change the array to look at the new array.
        list = temp;
        //and display a success message
        cout<<"Operation complete. "<<endl<<endl;
    }
    //append method. Adds in more information to contact if there are more
    //phone numbers and names associated to a contact object.
    void append(){
        //getName function is called to set the add name variable.
        string add_name = getName(), target_Name, num;
        cout<<endl;
        //Similar to getName function except message is more clear
        cout<<"Enter target contact name: ";
        getline(cin, target_Name);
        cout<<endl;
        target_Name.erase(target_Name.length()-1);
        //for loop goes through and finds the target name
        for(int i=0; i<size; i++){
            //if it finds it
            if(target_Name==list[i].getName()){
                //asks for the phone number to append it to.
                cout<<"Enter Phone Number: ";
                cin>>num;
                cout<<endl;
                //makes a temp second contact.
                Contact second(add_name, num);
                //uses the overloaded operator function to append information
                //(if changed) to the current Contact.
                list[i]=list[i]+second;
                break;
                //else display error message.
            }else if(i==size-1){
                cout<<"Could not find contact. "<<endl<<endl;
            }
        }
    }
    //search function
    //Finds the contact information by searching the array via name.
    //Prints out the information. If test mode is on, then it will not print
    //out anything but test each and every element three times and record the
    //time (in seconds) for which it took to find the element.
    void search(string search_name){
        if(this->testMode==false) {
            //getName function is called to set the search_name variable.
            search_name = getName();
            cout << endl;
        }
        for(int i=0; i<size; i++){
            //if it finds it, the output the information from the friend function
            //of contact called printInformation that prints the contact information.
            if(search_name.compare(list[i].getName())==0){
                if(this->testMode == false) {
                    printInformation(list[i]);
                }
                break;
                //if name is not found there will be an error.
            }else if(i==size-1){
                cout<<"Could not find contact. "<<endl<<endl;
            }
        }
    }
    //delete function
    //deletes contact by blanking out a contact information.
    void delete_Contact(){
        //getName function is called to set the search_name variable.
        string search_name = getName();
        cout<<endl;
        //goes through each element
        for(int i=0; i<size; i++){
            //if it finds the Contact
            if(list[i].getName()==search_name){
                //Blank it out
                list[i].setName("");
                list[i].setPhoneNumber("");
                //and display a success message
                cout<<"Operation complete. "<<endl<<endl;
                break;
                //else return an error mesage
            }else if(i==size-1){
                cout<<"Could not find contact. "<<endl<<endl;
            }
        }
    }
    //list_contact
    //lists out contacts from the populated phone book
    void list_Contact(int start){
        //if there are no contacts, print no contacts.
        if(size==0){
            cout<<"There are no contacts. "<<endl;
            //else
        }else{
            //if the size of the Contacts are less than four, print all of them
            if(size<4){
                for(int i=0; i<size; i++){
                    cout<<"Name: "<<list[i].getName()<<endl<<"Phone Number: "<<list[i].getPhoneNumber()<<endl;
                }
                cout<<"Reached end of list. "<<endl<<endl;
                //else
            }else{
                //print from the starting integer and print the four indices
                for(int i=start; i<(start+4); i++){
                    cout<<"Name: "<<list[i].getName()<<endl<<"Phone Number: "<<list[i].getPhoneNumber()<<endl;
                }
                //Asks user if he or she wants to continue printing
                cout<<"Do you want to continue listing? Enter Y for yes, press N for no. ";
                char choice;
                cin >> choice;
                cout << endl;
                //if so continue
                if((choice=='y' || choice=='Y')==1){
                    list_Contact(start+=4);
                    //if the user did not put in n or N, they made a mistake
                }else if((choice=='n' || choice=='N')==0){
                    //ask user again if they are choosing yes or no
                    while((choice=='y' || choice=='Y' || choice=='n' || choice=='N')==0){
                        cout<<"Sorry that was an invalid choice, if you would like to continue listing, enter Y for yes or N for no. ";
                        cin >> choice;
                        cout << endl;
                    }
                    //if yes continue again
                    if((choice=='y' || choice=='Y')==1){
                        list_Contact(start+=4);
                    }
                }
            }
        }
    }
//run method
    //checks user char input to choose what will happen next.
    int run(){
        cout<<"A(Add)	|	P	(Append)	|	S	(Search)	|	D(Delete)	|L(List)	|Q(Quit):	";
        char check;
        cin >> check;
        cout << endl;
        cin.ignore();
        //respective letter entered in will start a respective operation.
        if((check=='a' || check=='A')==1){
            add();
            run();
        }else if((check=='p' || check=='P')==1){
            append();
            run();
        //If test mode is on, then it will traverse through all elements and
        //record each and every element's (for three times) time (in seconds)
        //for which it took to find the element in a csv file.
        }else if((check=='s' || check=='S')==1){
            if(this->testMode==true){
                fstream fileIn;
                fileIn.open("phonebook.txt");
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
                    for (int i = 1; i < 4; i++) {
                        s += "ArraySearch," + name + "," +
                             to_string(elementNum) + "," + to_string(i) +
                             ",";
                        clock_t start = clock();
                        this->search(name);
                        clock_t end = clock();
                        double elapsed_secs =
                                double(end - start) / CLOCKS_PER_SEC;
                        s += to_string(elapsed_secs) + "\n";
                    }
                    elementNum++;
                }
                file.open("DataAnalysis.csv");
                file << "Structure Type,Target Name,Element Number,"
                     << "Search Iteration,Time" << endl << s;
                file.close();
                fileIn.close();
            }else{
                search("");
            }
            run();
        }else if((check=='d' || check=='D')==1){
            delete_Contact();
            run();
        }else if((check=='l' || check=='L')==1){
            list_Contact(0);
            run();
        }else if((check=='q' || check=='Q')==1){
            return 0;
            //else if input does not match, please re-run and return an error.
        }else{
            cout<<endl<<"Invalid Command"<<endl<<endl;
            run();
        }
        return 0;
    }
    void prepare(){
        ifstream file;
        file.open("phonebook.txt");
        string name;
        while(!file.eof()){
            getline(file, name);
            size++;
        }
        list = new Contact[size];
        file.clear();
        file.seekg(0);
        int pos = 0;
        string phoneNumber;
        while(1){
            if(!(file >> name)){
                break;
            }
            name.append(" ");
            string lastName;
            file >> lastName;
            name+=lastName;
            file >> phoneNumber;
            list[pos] = Contact(name, phoneNumber);
            pos++;
        }
    }
};

//main function
//starts the program
int main(){
    cout<<"***MY	PHONEBOOK	APPLICATION***"<<endl;
    //creates the launcher object.
    launcher * inst = new launcher();
    //prepare and populate the phone book.
    inst->prepare();
    cout<<"Please	choose	an	operation:"<<endl;
    //start running the program
    while(inst->run()==1)
        return 0;
}