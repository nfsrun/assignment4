/*
 * Contact.cpp
 *
 *  Created on: Oct 2, 2017
 *      Author: Kevin Tran
 *      Contact.cpp class
 *      Includes all the public methods defined in the Contact header class.
 *      Destructor is predefined in header already as it is an empty destructor.
 *
 */

#include "Contact.h"
#include <iostream>

Contact::Contact(string _name, string _phoneNumber) {
	name = _name;
	phoneNumber = _phoneNumber;
}

void Contact::setPhoneNumber(string _number){
	phoneNumber=_number;
}
void Contact::setName(string _name){
	name=_name;
}
string Contact::getName(){
	return name;
}
string Contact::getPhoneNumber(){
	return phoneNumber;
}
void printInformation(Contact c){
	cout<<"Name: "<<c.getName()<<endl<<"Phone Number: "<<c.getPhoneNumber()<<endl<<endl;
}

//Operator+ overload. This operator takes in another contact and appends
//the name and number between two Contacts. Any additional differences (shared name,
//shared number will be added to the target contact.
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
