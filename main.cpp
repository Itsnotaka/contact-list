#include <iostream>
#include <string>
#include "contactClass.h"


//TODO find a way to fix memory leak

using namespace std;

//initialize the contact list class globally
contactList newList;

//input a character will mostly crash the program
//TODO find a way to fix this
void promptMenu() {
	char confirm;

	string firstName, lastName, phoneNumber, error;
	int menuChoice, choice;
	bool loop;
	cout
			<< "1) Add a new contact\n2) Delete a contact\n3) Update contact info\n4) Display contacts in ascending order by last name\n5) Find the contact info for a particular person\n6) Exit\n=================================================="
			<< endl;
	cout << "> ";
	cin >> menuChoice;
	// a while condition here will cause a crash loop if you entered a string
	if (menuChoice < 1 || menuChoice > 6) {
		cout << "Fatal crash - Invalid input" << endl;
	} else {
		while (menuChoice != 6) {
			if (menuChoice == 1) {
				cout << "You have chosen to add a new contact\nPlease enter the first name of the contact" << endl;
				cout << "> ";
				cin >> firstName;
				cout << "Please enter the last name of the contact" << endl;
				cout << "> ";
				cin >> lastName;
				cout << "Please enter the phone number of the contact" << endl;
				cout << "> ";
				cin >> phoneNumber;
				contactNode newContact(firstName, lastName, phoneNumber);
				try {
					newList.addContact(newContact);
					cout << "Contact added successfully" << endl;
				} catch (string error) {
					cout << error << endl;
				}
			} else if (menuChoice == 2) {
				cout << "You have chosen to remove a contact" << endl;
				cout << "Please enter the phone number of the contact that you want to remove" << endl;
				cout << "> ";
				cin >> phoneNumber;
				try {
					newList.removeContact(phoneNumber);
				} catch (string error) {
					cout << "Internal error removing contact" << error << endl;
				}
			} else if (menuChoice == 3) {
				cout << "You have chosen to update a contact\nPlease enter the phone number of the contact you would like to update."
						<< endl;
				cout << "> ";
				cin >> phoneNumber;
				if (!newList.isContactInList(phoneNumber)) {
					cout << "Contact not found" << endl;
				} else {
					//if found, print the contact
					newList.searchForContact(phoneNumber);
					cout << "Which of the following would you like to update contact for?" << endl;
					cout << "1) First name\n2) Last name\n3) Phone number" << endl;
					cout << "==================================================" << endl;
					cout << "> ";
				};
				cin >> choice;
				while (choice < 1 || choice > 3) {
					cout << "Invalid choice, try again" << endl;
					cout << "> ";
					cin >> choice;
				}
				try {
					if (choice == 1) {
						string oldValue = newList.getFirstName(phoneNumber);
						cout << "What would you like to change the first name to?" << endl;
						cout << "> ";
						cin >> firstName;
						cout << "Are you sure you want to change the first name from " << oldValue << " to "
							 << firstName << "? (y/n)" << endl;
						cout << "> ";
						cin >> confirm;
						if (confirm == 'y') {
							newList.updateContact(phoneNumber, choice, firstName);
						} else {
							cout << "First name not changed" << endl;
						}
					} else if (choice == 2) {
						string oldValue = newList.getLastName(phoneNumber);
						cout << "What would you like to change the last name to?" << endl;
						cout << "> ";
						cin >> lastName;
						cout << "Are you sure you want to change the last name from " << oldValue << " to "
							 << lastName << "? (y/n)" << endl;
						cout << "> ";
						cin >> confirm;
						if (confirm == 'y') {
							newList.updateContact(phoneNumber, choice, lastName);
						} else {
							cout << "Last name not changed" << endl;
						}
					} else if (choice == 3) {
						string oldValue = newList.getPhoneNumber(phoneNumber);
						cout << "What would you like to change the phone number to?" << endl;
						cout << "> ";
						cin >> phoneNumber;
						cout << "Are you sure you want to change the phone number from " << oldValue << " to "
							 << phoneNumber << "? (y/n)" << endl;
						cout << "> ";
						cin >> confirm;
						if (confirm == 'y') {
							firstName = newList.getFirstName(phoneNumber);
							lastName = newList.getLastName(phoneNumber);
							//Update contact might not work for this
							//newList.updateContact(phoneNumber, choice, phoneNumber);
							//remove the contact and add it again
							newList.removeContact(phoneNumber);
							contactNode newContact(firstName, lastName, phoneNumber);
							newList.addContact(newContact);
						} else {
							cout << "Phone number not changed" << endl;
						}
					}
				} catch (string error) {
					cout << "Internal error updating contact" << error << endl;
				}
			} else if (menuChoice == 4) {
				try {
					newList.sortList();
					newList.printList();
				} catch (string error) {
					cout << "Internal error displaying contacts" << error << endl;
				}
			} else if (menuChoice == 5) {
				cout << "Please enter the phone number of the contact" << endl;
				cout << "> ";
				cin >> phoneNumber;
				try {
					newList.searchForContact(phoneNumber);
				} catch (string error) {
					cout << "Internal error finding contact" << error << endl;
				}
			} else if (menuChoice == 6) {
				exit(0);
			}
			cout << "Would you like to continue? (y/n)" << endl;
			cout << "> ";
			cin >> confirm;
			while (confirm != 'y' && confirm != 'n') {
				cout << "Invalid input, please try again" << endl;
				cout << "> ";
				cin >> confirm;
			}
			if (confirm == 'n') {
				exit(0);
			} else if (confirm == 'y') {
				promptMenu();
			}
		}
	}
}


/**
 * Main function
 * @author Min CHun Fu
 * @version 1.0
 * @github
 */
int main() {

	cout
			<< "Welcome to the contact manager!\nPlease choose which function you would like to execute by entering the corresponding number\n==========================================================="
			<< endl;

	//think about a way to prevent data from refreshing EDIT: done wooohoo
	//I tried using switch case but that doesn't work that great. Sorry for this ugly cout code.
	promptMenu();
	return 0;
}

//DOCS
/*
 * A discussion of the most common operation performed on the contacts,
 * the efficiency of your solution, and the biggest challenge you overcame in completing this assignment.
 *
 * The most common operation performed on the contacts is to search for a contact by phone number.
 * Every time you search for a contact, you must search through every contact in the list.
 * This is inefficient because you must search through every contact in the list.
 * The time complexity of Linear Search in the best case is O(1). In the worst case, the time complexity is O(n).
 * However, we could possibly improve the efficiency of the program by using a binary search tree.
 * But I am more used to using a linked list, so I will not implement a binary search tree.
 *
 * The hardest part is to keep on thinking and adding the structure of this program.
 * Should we make a while loop or do while or If statement?
 * Will silly user input cause the program to crash?
 * Will the program crash if the user enters a number that is not in the menu?
 * The process of editing and adding functions is a bit tedious.
 */