#include <iostream>
#include <string>
#include "contactClass.h"

int main(){
	//create a contact list
	contactList myList;
	//create a contact object
	contactNode contact("abc","fwf","12421515");
	contactNode contact1("dword","ffmpeg","12421514");
	contactNode contact2("added","aah","51151");
	//add the contacts to the contact list
	myList.addContact(contact);
	cout << "added";
	myList.addContact(contact1);
//	myList.addContact(contact2);
	//print contact list
	//myList.printList();
	//print sorted contact list

	return 0;
}