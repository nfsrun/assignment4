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

//Default constructor that takes in two strings of a full name and phone number
//and populates the contact fields
Contact::Contact(string _name, string _phoneNumber) {
	name = _name;
	phoneNumber = _phoneNumber;
}

//setPhoneNumber method sets the phone number of the contact
void Contact::setPhoneNumber(string _number){
	phoneNumber=_number;
}

//setName method sets the name of the contact
void Contact::setName(string _name){
	name=_name;
}

//getName method retrieves the name of the contact
string Contact::getName(){
	return name;
}

//getPhoneNumber method retrieves the phone number of the contact
string Contact::getPhoneNumber(){
	return phoneNumber;
}

//printInformation method retrives the name and phone number of the contact and
//prints the information to the console
void printInformation(Contact c){
	cout<<"Name: "<<c.getName()<<endl<<"Phone Number: "<<c.getPhoneNumber()<<endl<<endl;
}

//Operator+ overload. This operator takes in another contact and appends
//the name and number between two Contacts. Any additional differences (shared
//name, shared phone number will be added to the target contact.
Contact Contact::operator +(Contact c){
	string nameNew = name, numNew = phoneNumber;
	Contact temp;

	//checks a contact and another contact if they have the same name. If not,
	//do nothing. If so, combine.
	if(c.getName() != nameNew){
		nameNew+=" & " + c.getName();
	}

	//checks a contact and another contact if they have the same phone number.
	//If not, do nothing. If so, combine.
	if(numNew != c.getPhoneNumber()){
		numNew+=" / " + c.getPhoneNumber();
	}
	temp.name=nameNew;
	temp.phoneNumber=numNew;
	return temp;
}
