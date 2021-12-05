#include <iostream>
#include <string>
#include "contactClass.h"

int main(){
	//create a contact list
	contactList myList;
	//create a contact object
	//add the contact to the list
	auto *newContact = new contactNode("abc","fwf","12421515");
	myList.addContact(newContact);
	cout << "Wanna add?" << endl;
	int answer;
	cin >> answer;
	if(answer == 1){
		string firstName, lastName, phoneNumber;
		cin >> firstName;
		cin >> lastName;
		cin >> phoneNumber;
		auto *newContact1 = new contactNode(firstName, lastName, phoneNumber);
		myList.addContact(newContact1);
	}

	return 0;
}