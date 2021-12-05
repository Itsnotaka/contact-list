#include <iostream>
#include <string>
#include "contactClass.h"


//TODO find a way to fix memory leak
contactList myList;

int main() {
	char choice ;
	contactNode contact("John", "Doe", "999999");
	contactNode contact1("John", "Doe", "1241414");
	myList.addContact(contact);
	myList.addContact(contact1);
	myList.printList();
	cout << "Waiting..." << endl;
	cin >> choice;
	if (choice == 6){
		myList.addContact(contact1);
		myList.printList();

	}
	return 0;
}