// Name         : Validator.h
// Author       : Kevin Tran
// Description  : Class of Contact file that include method declarations and
// class variable declarations. Edited to add an == override for pointer contact
// comparisons. This has been revised to remove printInformation and add in more
// operator overloads in order to effectively sort and utilize Contacts.


#ifndef ASSIGNMENT4_CONTACT_H
#define ASSIGNMENT4_CONTACT_H

#include <string>
using namespace std;
class Contact {
    //private fields of contact are the name and phone number
    string name;
    string phoneNumber;
    //public methods include, constructor, destructor, getters, setters,
    //required functions including friend function from instructions, and
    //over-rided operator+ function.
public:
    //this constructor will have default empty string parameters.
    Contact(string="", string="");
    //default destructor
    ~Contact(){};

    //all methods below will be defined in Contact.cpp
    string getName();
    string getPhoneNumber();
    Contact operator+(Contact);
    friend string operator<<(string&, Contact&);
    friend string operator+=(string&, Contact&);
    friend ostream& operator<<(ostream&, Contact);
    friend bool operator<(const Contact&, Contact&);
    friend bool operator>(const Contact&, Contact&);
    friend bool operator!=(const Contact&, Contact&);
    friend bool operator==(const Contact&, Contact&);
    friend bool operator==(const Contact*, Contact&);
};

#endif //ASSIGNMENT4_CONTACT_H
