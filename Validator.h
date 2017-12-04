// Name         : Validator.h
// Author       : Kevin Tran
// Description  : Validator.h class contains methods that check for valid inputs
// for various situations that could occur within the Launcher.cpp program. It
// includes checking various inputs for valid strings and number entries from
// the user.


#ifndef ASSIGNMENT4_VALIDATOR_H
#define ASSIGNMENT4_VALIDATOR_H

#include <sstream>
#include <iostream>
using namespace std;

//checkLastName method checks user input so that the first name is purely a
//string.
string checkLastName() {
    string last_name;

    //a double value to take in integers or doubles IF THE INPUT CAN BE
    //CONVERTED TO A NUMERICAL VALUE
    double check;
    cout << "Enter last name: ";
    cin >> last_name;
    cout << endl;

    //stringstream is used to attempt to convert the input into a numerical
    //value, if so then clear cin, give an error message, and then recursively
    //ask for a last name again.
    stringstream s(last_name);
    if (s >> check) {
        cin.ignore(INTMAX_MAX, '\n');
        cout <<  "Invalid Last Name Input. Try again. " << endl << endl;
        return checkLastName();
    } else {
        return last_name;
    }
}

//checkFirstName method checks user input so that the first name is purely a
//string.
string checkFirstName() {
    string first_name;

    //a double value to take in integers or doubles IF THE INPUT CAN BE
    //CONVERTED TO A NUMERICAL VALUE
    double check;
    cout << "Enter first name: ";
    cin >> first_name;
    cout << endl;

    //stringstream is used to attempt to convert the input into a numerical
    //value, if so then clear cin, give an error message, and then recursively
    //ask for a first name again.
    stringstream s(first_name);
    if (s>>check) {
        cin.ignore(INTMAX_MAX, '\n');
        cout << "Invalid First Name Input. Try again. " << endl << endl;
        return checkFirstName();
    } else {
        return first_name;
    }
}

//checkFlightNumber method checks user input so that they do not enter a
//non-integer value, a negative integer, and/or an integer that is not 100, 200,
//300, or 400.
int checkFlightNumber(){
    int flight_number;
    cout<<"Enter flight number: ";
    cin>>flight_number;
    cout<<endl;

    //while loop will start if constraints are not met. It will clear the cin
    //and give a user error and recurses the process to make sure it is entered
    //correctly.
    while(cin.fail()==true || flight_number/100>4 || flight_number%100!=0 ||
          flight_number/100<0){
        cin.clear();
        cin.ignore(INTMAX_MAX, '\n');
        cin.sync();
        cout<<"Invalid flight number input. Try again. "<< endl << endl;
        return checkFlightNumber();
    }
    return flight_number/100;
}

#endif //ASSIGNMENT4_VALIDATOR_H
