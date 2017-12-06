/*
 * Contact.cpp
 *
 *  Created on: Oct 2, 2017
 *  Revised on Dec 4, 2017
 *      Author: Kevin Tran
 *      Contact.cpp class
 *      Includes all the public methods defined in the Contact header class.
 *      Destructor is predefined in header already as it is an empty destructor.
 *      Revision includes more implemented operator overloads and a deletion of
 *      a method as indicated in the respective header file.
 */

#include "Contact.h"
#include <iostream>

//Default constructor that takes in two strings of a full name and phone number
//and populates the contact fields
Contact::Contact(string _name, string _phoneNumber) {
	name = _name;
	phoneNumber = _phoneNumber;
}

string Contact::getName(){
	return name;
}

string Contact::getPhoneNumber(){
	return phoneNumber;
}

//Operator+ overload. This operator takes in another contact and appends
//the name and number between two Contacts. Any additional differences (shared
//name, shared number will be added to the target contact.
Contact Contact::operator +(Contact c){
	string nameNew = name, numNew = phoneNumber;
	Contact temp;
	if(c.getName() != nameNew){
		nameNew+=" & " + c.getName();
	}
	if(numNew != c.getPhoneNumber()){
		numNew+=" / " + c.getPhoneNumber();
	}
	temp.name=nameNew;
	temp.phoneNumber=numNew;
	return temp;
}

string operator<< (string& s, Contact& c){
    return s+c.name;
}

//Operator+ overload. This operator takes in another contact and appends
//the name and number between two Contacts. Any additional differences (shared
//name, shared number will be added to the target contact.
string operator +=(string& s, Contact& c){
    return s.append(c.name+" :" + c.phoneNumber + "\n");
}

//overloaded << to output contact correctly as "firstName lastName address
//phoneNumber".
ostream& operator<<(ostream& os, Contact &p1){
	return os<<(p1.getName() + " :" + p1.getPhoneNumber());
}

//overloaded == operator to compare two contact if A is contact B
bool operator==(const Contact& p1, Contact& p2){
	return p1.name == p2.name;
}

//overloaded == operator to compare two contact if A is contact B
bool operator==(const Contact* p1, Contact& p2){
	return p1->name == p2.name;
}

//overloaded != operator to compare two contact if A is not contact B
bool operator!=(const Contact& p1, Contact& p2){
	return p1.name != p2.name;
}

//overloaded > operator to compare two contact if A is more (further in the
//alphabet) than contact B
bool operator>(const Contact& p1, Contact& p2){
	return p1.name > p2.name;
}

//overloaded < operator to compare two contact if A is less (lesser in the
//alphabet) than contact B
bool operator<(const Contact& p1, Contact& p2) {
	return p1.name < p2.name;
}