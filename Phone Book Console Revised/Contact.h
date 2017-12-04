//
// Created by super on 03-Dec-17.
//

#ifndef PHONE_BOOK_CONSOLE_REVISED_CONTACT_H
#define PHONE_BOOK_CONSOLE_REVISED_CONTACT_H
using namespace std;

#include <string>


class Contact {
    //private fields of contact are the name and phone number
    string name;
    string phoneNumber;
    //public methods include, constructor, destructor, getters, setters, required functions
    //including friend function from instructions, and over-rided operator+ function.
public:
    //this constructor will have default empty string parameters.
    Contact(string="", string="");
    ~Contact(){};
    void setPhoneNumber(string);
    void setName(string);
    string getName();
    string getPhoneNumber();
    friend void printInformation(Contact);
    Contact operator+(Contact);
};
#endif //PHONE_BOOK_CONSOLE_REVISED_CONTACT_H
