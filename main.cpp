#include <iostream>
#include <string>
#include <regex>
#include "contactClass.h"

using namespace std;

/**
 * For project 4 you are asked to create and maintain contact information (name and phone number). Your program must include the following functionality:
 * 1) add a new contact
 * 2) delete a contact
 * 3) update contact info
 * 4) display contacts in ascending order by last name
 * 5) find the contact info for a particular person
 */

/**
 * Prints the menu
 * @author Min CHun Fu
 * @version 1.0
 */
int promptMenu() {
	int choice;

	cout << "1. Add a new contact" << endl;
	cout << "2. Delete a contact" << endl;
	cout << "3. Update contact info" << endl;
	cout << "4. Display contacts in ascending order by last name" << endl;
	cout << "5. Find the contact info for a particular person" << endl;
	cout << "6. Exit" << endl;
	cout << "===========================================================" << endl;
	cout << "Enter your choice" << endl;
	cout << " > ";

	cin >> choice;
	if (choice < 1 || choice > 6) {
		cout << "Invalid choice" << endl;
		return -1;
	}
	return choice;
}

/**
 * Main function
 * @author Min CHun Fu
 * @version 1.0
 */
int main() {
	contactList newList;
	string firstName, lastName, phoneNumber;
	int choice;
	char confirm;
	cout << "Welcome to the contact manager!" << endl;
	cout << "please choose which function you would like to execute by entering the corresponding number" << endl;
	cout << "===========================================================" << endl;
	string exit;
	do {

		//think about a way to prevent data from refreshing EDIT: done wooohoo
		//I tried using switch case but that doesn't work that great. Sorry for this ugly cout code.
		if (promptMenu() == 1) {
			cout << "You have chosen to add a new contact" << endl;
			cout << "Please enter the following information" << endl;
			cout << "What is the contact's first name? (i.g john)" << endl;
			cout << "> ";
			cin >> firstName;
			cout << "What is the contact's last name (i.g Doe)?" << endl;
			cout << "> ";
			cin >> lastName;
			cout << "What is the contact's phone number? (i.g 9999999999)" << endl;
			cout << "> ";
			cin >> phoneNumber;
			//validate it using regex
			contactNode newContact(firstName, lastName, phoneNumber);
			do {
				cout << "Please confirm the following information" << endl;
				cout << "First name: " << newContact.getFirstName() << endl;
				cout << "Last name: " << newContact.getLastName() << endl;
				cout << "Phone number: " << newContact.getPhoneNumber() << endl;
				// don't need to check if the input is empty
				// if it's empty you won't be able to continue

//				   if(newContact.getEmailAddress().empty()) {
//					   cout << "It seems like your email address is empty." << endl;
//				   } else if(newContact.getFirstName().empty()) {
//					   cout << "It seems like your first name is empty." << endl;
//				   } else if(newContact.getLastName().empty()) {
//					   cout << "It seems like your last name is empty." << endl;
//				   } else if(newContact.getPhoneNumber().empty()) {
//					   cout << "It seems like your phone number is empty." << endl;
//				   }
				cout << "Is this correct? (y/n)" << endl;
				cout << "> ";
				cin >> confirm;
				if (confirm == 'y') {
					newList.addContact(newContact);
					cout << "OK! Contact added successfully. There is " << newList.getListSize()
						 << " contact(s) in the list." << endl;
				} else if (confirm == 'n') {
					cout << "Sure! The info was not saved" << endl;
				} else {
					cout << "That's not a valid answer!" << endl;
				}
			} while (confirm != 'y' && confirm != 'n');
		} else if (promptMenu() == 2) {
			cout << "You have chosen to delete for a contact" << endl;
			cout << "Please enter the contact's phone number" << endl;
			cout << "> ";
			cin >> phoneNumber;
			if (newList.isContactInList(phoneNumber)) {
				cout << "Contact found!" << endl;
				newList.searchForContact(phoneNumber);
				do {
					cout << "Are you sure you want to delete this contact? (y/n)" << endl;
					cin >> confirm;
				} while (confirm != 'y' && confirm != 'n');
				newList.removeContact(phoneNumber);
				cout << "OK! Contact deleted successfully. There is " << newList.getListSize()
					 << " contact(s) in the list." << endl;
			} else {
				cout << "Sorry, we couldn't find the contact with the phone number " << phoneNumber << endl;
			}
		} else if (promptMenu() == 3) {
			cout << "You have chosen to update a contact" << endl;
			cout << "Please enter the contact's phone number" << endl;
			cout << "> ";
			cin >> phoneNumber;
			if (newList.isContactInList(phoneNumber)) {
				cout << "Contact found! Which of the following would you like to update?" << endl;
				cout << "===========================================================" << endl;
				cout << "1. First name" << endl;
				cout << "2. Last name" << endl;
				cout << "3. Phone number" << endl;
				do {
					cin >> choice;
					if (choice == 1) {
						do {
							string previousFirstName = newList.getFirstName(phoneNumber);
							cout << "What first name would you like to change to" << endl;
							cout << "> ";
							cin >> firstName;
							cout << "Please confirm the following information" << endl;
							cout << "Original first name: " << previousFirstName << endl;
							cout << "Updated first name " << firstName << endl;
							cout << "Is this the name you want to be updated? (y/n)" << endl;
							cout << "> ";
							cin >> confirm;
							if (confirm == 'y') {
								newList.updateContact(phoneNumber, choice, firstName);
								cout << "OK! Contact updated successfully. The contacts first name is now << "
									 << firstName << endl;
							} else if (confirm == 'n') {
								cout << "Sure! The info was not saved" << endl;
							} else {
								cout << "That's not a valid answer!" << endl;
							}
						} while (confirm != 'y' && confirm != 'n');
					} else if (choice == 2) {
						do {
							string previousLastName = newList.getLastName(phoneNumber);
							cout << "What last name would you like to change to?" << endl;
							cout << "> ";
							cin >> lastName;
							cout << "Please confirm the following information" << endl;
							cout << "Original last name: " << previousLastName << endl;
							cout << "Updated last name " << lastName << endl;
							cout << "Is this the name you want to be updated? (y/n)" << endl;
							cout << "> ";
							cin >> confirm;
							if (confirm == 'y') {
								newList.updateContact(phoneNumber, choice, lastName);
								cout << "OK! Contact updated successfully. The contacts last name is now << "
									 << lastName << endl;
							} else if (confirm == 'n') {
								cout << "Sure! The info was not saved" << endl;
							} else {
								cout << "That's not a valid answer!" << endl;
							}
						} while (confirm != 'y' && confirm != 'n');
					} else if (choice == 3) {
						do {
							string previousPhoneNumber = newList.getPhoneNumber(phoneNumber);
							cout << "What phone number would you like to change to?" << endl;
							cout << "> ";
							cin >> phoneNumber;
							cout << "Please confirm the following information" << endl;
							cout << "Original phone number: " << previousPhoneNumber << endl;
							cout << "Updated phone number " << phoneNumber << endl;
							cout << "Is this the number you want to be updated? (y/n)" << endl;
							cout << "> ";
							cin >> confirm;
							if (confirm == 'y') {
								newList.updateContact(phoneNumber, choice, phoneNumber);
								cout << "OK! Contact updated successfully. The contacts phone number is now << "
									 << phoneNumber << endl;
							} else if (confirm == 'n') {
								cout << "Sure! The info was not saved" << endl;
							} else {
								cout << "That's not a valid answer!" << endl;
							}
						} while (confirm != 'y' && confirm != 'n');
					} else {
						cout << "That's not a valid choice!" << endl;
					}
				} while (choice != 1 && choice != 2 && choice != 3);
			};
		} else if (promptMenu() == 4) {
			cout << "Here is the list of contacts saved!" << endl;
			newList.printList();
		} else if (promptMenu() == 5) {
			do {
				cout << "Sure! Do you have the phone number of the contact? (y/n)" << endl;
				cout << "> ";
				cin >> confirm;
				if(confirm == 'y'){
					cout << "Great! Whats the phone number of the contact you are looking for?" << endl;
					cout << "> ";
					cin >> phoneNumber;
					newList.searchForContact(phoneNumber);
				} else if (confirm == 'n'){
					cout << "No worries! Please enter the name of the contact (first name/ last name)" << endl;
					cout << "> ";
					string searchKeyword;
					cin >> searchKeyword;
					newList.searchForContactByName(searchKeyword);
				}
			} while(confirm != 'y' && confirm != 'n');
		} else if (promptMenu() == 6) {
			cout << "Thank you for using the contact manager!" << endl;
			//exit the program
		}
		cout << "If you wish to exit now, type 'exit', or enter any key to continue. " << endl;
		cout << "> ";
		cin >> exit;
	} while (exit != "exit" || exit != "Exit" || promptMenu() != 6);
	return 0;
}
