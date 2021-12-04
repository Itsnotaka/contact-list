#include <iostream>
#include <string>
#include "contactClass.h"

int main(){
	//create a contactlist
	contactList myList;
	//create a contact object
	contactNode contact("abc","fwf","12421515");
	contactNode contact1("dwqd","ffqwegwf","2525");
	contactNode contact2("aqdqdbc","aaaaaa","51151");
	//add the contacts to the contact list
	myList.addContact(contact);
	myList.addContact(contact1);
	myList.addContact(contact2);
	//print contact list
	//myList.printList();
	//print sorted contact list
	myList.printSortedList();

	return 0;
}