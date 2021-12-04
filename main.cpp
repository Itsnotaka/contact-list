#include <iostream>
#include <string>
#include "contactClass.h"

using namespace std;

/**
 * Developer function
 * Used to test in a preset environment with a couple of preset values to ensure every single function is working
 * @author Min Chun Fu
 * @version 1.0
 */
void devTest() {
	contactList devList;
	string devFirstName, devLastName, devPhoneNumber;
	//precreate 4 unique contactNode
	cout << "Pre-creating 4 unique contactNode" << endl;
	contactNode devContact1("Gwen", "Elliott", "520-549-6686");
	contactNode devContact2("Ann", "Willis", "908-645-2304");
	contactNode devContact3("Barry", "Chavez", "310-743-8391");
	contactNode devContact4("Yvette", "Francis", "410-248-9506");
	//Test basic functions
	devList.addContact(devContact1);
	devList.addContact(devContact2);
	devList.addContact(devContact3);
	devList.addContact(devContact4);
	cout << "Test addContact() successful" << endl;
	devList.printList();
	cout << "Test printList() successful" << endl;
	exit(0);
}

/**
 * Menu function
 * Prints the menu
 * @author Min Chun Fu
 * @version 1.0
 */
int promptMenu() {
	contactList mainList;
	string firstName, lastName, phoneNumber;
	int menuChoice, choice;
	char confirm;
	cout << "1. Add a new contact" << endl;
	cout << "2. Delete a contact" << endl;
	cout << "3. Update contact info" << endl;
	cout << "4. Display contacts in ascending order by last name" << endl;
	cout << "5. Find the contact info for a particular person" << endl;
	cout << "6. Exit" << endl;
	cout << "===========================================================" << endl;
	cout << "Enter your choice" << endl;
	cout << "> ";
	cin >> menuChoice;
	do {
		if (menuChoice == 1) {
			cout << "You have chosen to add a new contact" << endl;
			cout << "Please enter the following information" << endl;
			cout << "What is the contact's first name? (i.g john)" << endl;
			cout << "> ";
			cin >> firstName;
			cout << "What is the contact's last name (i.g Doe)?" << endl;
			cout << "> ";
			cin >> lastName;
			cout << "What is the contact's phone number? (i.g 012-345-6789)" << endl;
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
					mainList.addContact(newContact);
					cout << "OK! Contact added successfully. There is " << mainList.getListSize()
						 << " contact(s) in the list." << endl;
				} else if (confirm == 'n') {
					cout << "Sure! The info was not saved" << endl;
				} else {
					cout << "That's not a valid answer!" << endl;
				}
			} while (confirm != 'y' && confirm != 'n');
			promptMenu();
		} else if (menuChoice == 2) {
			cout << "You have chosen to delete for a contact" << endl;
			cout << "Please enter the contact's phone number" << endl;
			cout << "> ";
			cin >> phoneNumber;
			if (mainList.isContactInList(phoneNumber)) {
				cout << "Contact found!" << endl;
				mainList.searchForContact(phoneNumber);
				do {
					cout << "Are you sure you want to delete this contact? (y/n)" << endl;
					cin >> confirm;
				} while (confirm != 'y' && confirm != 'n');
				mainList.removeContact(phoneNumber);
				cout << "OK! Contact deleted successfully. There is " << mainList.getListSize()
					 << " contact(s) in the list." << endl;
			} else {
				cout << "Sorry, we couldn't find the contact with the phone number " << phoneNumber << endl;
			}
			promptMenu();
		} else if (menuChoice == 3) {
			cout << "You have chosen to update a contact" << endl;
			cout << "Please enter the contact's phone number" << endl;
			cout << "> ";
			cin >> phoneNumber;
			if (mainList.isContactInList(phoneNumber)) {
				cout << "Contact found! Which of the following would you like to update?" << endl;
				cout << "===========================================================" << endl;
				cout << "1. First name" << endl;
				cout << "2. Last name" << endl;
				cout << "3. Phone number" << endl;
				do {
					cin >> choice;
					if (choice == 1) {
						do {
							string previousFirstName = mainList.getFirstName(phoneNumber);
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
								mainList.updateContact(phoneNumber, choice, firstName);
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
							string previousLastName = mainList.getLastName(phoneNumber);
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
								mainList.updateContact(phoneNumber, choice, lastName);
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
							string previousPhoneNumber = mainList.getPhoneNumber(phoneNumber);
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
								mainList.updateContact(phoneNumber, choice, phoneNumber);
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
			}
		} else if (menuChoice == 4) {
			cout << "Loading contact list..." << endl;
			mainList.printList();
		} else if (menuChoice == 5) {
			do {
				cout << "Sure! Do you have the phone number of the contact? (y/n)" << endl;
				cout << "> ";
				cin >> confirm;
				if (confirm == 'y') {
					cout << "Great! Whats the phone number of the contact you are looking for?" << endl;
					cout << "> ";
					cin >> phoneNumber;
					mainList.searchForContact(phoneNumber);
				} else if (confirm == 'n') {
					cout << "No worries! Please enter the name of the contact (first name/ last name)" << endl;
					cout << "> ";
					string searchKeyword;
					cin >> searchKeyword;
					mainList.searchForContactByName(searchKeyword);
				}
			} while (confirm != 'y' && confirm != 'n');
		} else if (menuChoice == 6) {
			cout << "Thank you for using this program!" << endl;
			exit(0);
		} else if (menuChoice == 7) {
			devTest();
		} else {
			cout << "That's not a valid choice!" << endl;

			cout << "Would you like to use another function? (y/n)" << endl;
			cout << "> ";
			cin >> confirm;
			if (confirm == 'y') {
				promptMenu();
			} else if (confirm == 'n') {
				cout << "Hope to see you next time!";
				exit(0);
			}
		}
	} while (confirm != 'y' && confirm != 'n');


}

/**
 * Main function
 * @author Min CHun Fu
 * @version 1.0
 */
int main() {
	cout << "Welcome to the contact manager!" << endl;
	cout << "Please choose which function you would like to execute by entering the corresponding number" << endl;
	cout << "===========================================================" << endl;
	promptMenu();
	return 0;
}


