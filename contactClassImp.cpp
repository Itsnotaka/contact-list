#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "contactClass.h"

using namespace std;

/**
 * Implementation of the contact class
 * @author Min Chun Fu
 * @version 1.0
 */


/** Create an instance of the contact class
*
* @version 1.0
 *
* We are assuming that the email address is unique, so we used it as a key
*
* @param firstName The name of the contact
* @param lastName The last name of the contact
* @param phoneNumber The phone number of the contact
* @object contact_id an unique identifier for the contact generated base on the phone number
 * can be used to reference in other classes
* @object first_name the first name of the contact, default is ```John```.
* @object last_name the last name of the contact, default is ```Doe```.
* @object phone_number the phone number of the contact, default is ```999-999-9999```.
* @object createdAt shows the local date and time when the contact was created.
* @object the pointer to the next contact in the list.
*/
contactNode::contactNode(string firstName, string lastName, const string &phoneNumber) {

	contact_id = setId(phoneNumber);
	first_name = firstName;
	last_name = lastName;
	phone_number = phoneNumber;
	// convert time to string form
	// current date/time based on current system
	time_t created = time(nullptr);
	createdAt = ctime(&created);

	next = nullptr;
}

/**
 * Preset contact class with default values
 */
contactNode::contactNode() {
	time_t created = time(nullptr);
	contact_id = setId("example@gmail.com");
	first_name = "example";
	last_name = "example";
	phone_number = "999-999-9999";
	createdAt = ctime(&created);
	next = nullptr;
}

/**
 * Gets the contact id
 * @return the contact_id of the contact
 */
int contactNode::get_id() const {
	return contact_id;
}

/**
 * Gets the first name of the contact
 * @return the first name of the contact
 */
string contactNode::getFirstName() {
	return first_name;
}

/**
 * Gets the last name of the contact
 * @return the last name of the contact
 */
string contactNode::getLastName() {
	return last_name;
}

/**
 * Gets the phone number of the contact
 * @return the phone number of the contact
 */
string contactNode::getPhoneNumber() {
	return phone_number;
}

/**
 * Generates a random id for the contact
 *
 *  @version 1.0 -
 *  I made it that it randomly generates from  1 to 10000;
 *  @version 1.1 -
 *  I am going to change it to be more random by hashing the first name and last name
 *  @version 1.2 -
 *  I am going to change it to be more random by hashing the email address
 *  @version 1.3 -
 *  I am going to change it to be more random by hashing the phone number since phone number is unique
 *
 *  @param first_name the first name of the contact
 *  @param last_name the last name of the contact
 *  @return
 */
int contactNode::setId(const string &phoneNumber) {
	//contact_id = rand() % 10000;
	contact_id = hash<string>{}(phoneNumber);

	return contact_id;
}

/**
 * Sets the first name of the contact
 * @param firstName
 * @return updated firstName
 */
void contactNode::setFirstName(string firstName) {
	first_name = firstName;
}

/**
 * Sets the last name of the contact
 * @param lastName
 * @return updated lastName
 */
void contactNode::setLastName(string lastName) {
	last_name = lastName;
}

/**
 * Sets the phone number of the contact
 * @param phoneNumber
 * @return updated phoneNumber
 */
void contactNode::setPhoneNumber(string phoneNumber) {
	phone_number = phoneNumber;
}

/**
 * Delete the contact
 */
contactNode::~contactNode() {
	delete next;
}

/**
 * @return the next contact
 */
contactNode *contactNode::getNext() {
	return next;
}

/**
 * @param nextContact
 * @return the updated nextContact
 */
contactNode *contactNode::setNext(contactNode *nextNode) {
	next = nextNode;
	return next;
}

/**
 * Creates a new empty contact list
 */
contactList::contactList() {
	head = nullptr;
	tail = nullptr;
	listSize = 0;
}


/**
 * Deletes the contact list
 */
contactList::~contactList() {
	//delete all nodes
	contactNode *temp = head;
	while (temp != nullptr) {
		head = head->getNext();
		delete temp;
		temp = head;
	}
}


/**
 * Adds a new contact to the list
 * @param newContact
 * contact should always have value
 *
 * the function itself checks if the email address hash is the same with the ones in the database,
 * simply have to check if the list is empty,
 * if it is empty , add the contact to the head,
 * if it is	not empty, add the contact to the tail,
 * it then will add 1 to the size of the list.
 */
void contactList::addContact(contactNode newContact) {
	//create a temporary node
	//Could change to auto temp = new contactNode(...);
	contactNode *temp = new contactNode(newContact.getFirstName(), newContact.getLastName(),
										newContact.getPhoneNumber());
	//reduce time by checking if the contact is already in the list
	if (isContactInList(temp->getPhoneNumber())) {
		cout << "Contact already exists" << endl;
		return;
	}
	//check if the list is empty
	if (head == nullptr) {
		head = temp;
		tail = temp;
	} else {
		tail->setNext(temp);
		tail = temp;
	}
	listSize++;
}

/**
 * Removes a contact from the list
 * @param phoneNumber
 */
void contactList::removeContact(const string &phoneNumber) {
	//create a temporary node
	contactNode *temp = head;
	contactNode *prev = nullptr;
	//reduce time by checking if the contact is already in the list
	// If yes, then proceed to remove the contact
	if (!isContactInList(temp->getPhoneNumber())) {
		cout << "Contact does not exists" << endl;
		return;
	}
	//check if the list is empty
	while (temp != nullptr) {
		//if it's not empty, check if the contact id matches
		if (temp->getPhoneNumber() == phoneNumber) {
			//if it does, check if it's the head
			if (temp == head) {
				// if it is, set the head to the next node
				head = head->getNext();
				//check if it is the tail
			} else if (temp == tail) {
				//if it is, set the tail to the previous node
				prev->setNext(nullptr);
				tail = prev;
			} else {
				//if it's not the head or tail, set the previous node to the next node
				prev->setNext(temp->getNext());
			}
			//delete the node and minus 1 from the size
			delete temp;
			listSize--;
			return;
		}
		//if contact_id doesn't match, set the previous node to the current node
		//and set the current node to the next node
		//keep looking
		prev = temp;
		temp = temp->getNext();
	}
}

/**
 * A crucial function that checks if the contact is in the list.
 * Used in addContact function and removeContact function
 * @param phoneNumber
 * @return true if the contact is in the list, false otherwise
 */
bool contactList::isContactInList(const string &phoneNumber) {
	contactNode *temp = head;
	while (temp != nullptr) {
		if (temp->getPhoneNumber() == phoneNumber) {
			return true;
		}
		temp = temp->getNext();
	}
	return false;
}

/**
 * Similar function to isContactInList that checks if the contact is in the list.
 * @param phoneNumber
 */
void contactList::searchForContact(const string &phoneNumber) {
	//create a temporary node
	contactNode *temp = head;
	//check if the list is empty
	while (temp != nullptr) {
		//if it's not empty, check if the contact id matches
		if (temp->getPhoneNumber() == phoneNumber) {
			//if it does, print the contact
			printContact(temp);
			return;
		}
		//if contact_id doesn't match, go to the next node
		temp = temp->getNext();
	}
	cout << "Contact not found" << endl;
}

/**
 * Similar function to searchForContact that checks if the contact is in the list by using entered name.
 * This will only return the first contact that matches the name.
 * @param searchName
 */
void contactList::searchForContactByName(const string &searchName) {
	//create a temporary node
	contactNode *temp = head;
	//check if the list is empty
	while (temp != nullptr) {
		//if it's not empty, check if the contact name matches
		if (temp->getFirstName() == searchName) {
			//if it does, print the contact
			printContact(temp);
			return;
		} else if (temp->getLastName() == searchName) {
			//if it does, print the contact
			printContact(temp);
			return;
		}
		//if contact_id doesn't match, go to the next node
		temp = temp->getNext();
	}
	cout << "Contact not found" << endl;
}

/**
 * Use the phone number to find the contact and replace the value in the contactField with updated value
 * @param phoneNumber phone number of the contact
 * @param contactField the field that needs to be updated
 * @param updatedValue the new value of the field
 */
void contactList::updateContact(const string &phoneNumber, int contactField, const string &updatedValue) {
	//create a temporary node
	contactNode *temp = head;
	//check if the list is empty
	while (temp != nullptr) {
		//if it's not empty, check if the phone number matches
		if (temp->getPhoneNumber() == phoneNumber) {
			//if it does, update the contact
			switch (contactField) {
				case 1:
					temp->setFirstName(updatedValue);
					break;
				case 2:
					temp->setLastName(updatedValue);
					break;
				case 3:
					temp->setPhoneNumber(updatedValue);
					break;
				default:
					cout << "Invalid field" << endl;
					break;
			}
			return;
		}
		//if contact_id doesn't match, go to the next node
		temp = temp->getNext();
	}
	cout << "Contact not found" << endl;
}

/**
 * Sorts the contact list in ascending order by last name
 */
void contactList::printSortedList() {
	//initialize a vecotr for the last name of the contact
	vector<string> lastNameVector;
	//create a temporary node
	contactNode *temp = head;
	//check if the list is empty
	while (temp != nullptr) {
		//if it's not empty, add the last name to the vector
		lastNameVector.push_back(temp->getLastName());
		//go to the next node
		temp = temp->getNext();
	}
	//sort the vector
	sort(lastNameVector.begin(), lastNameVector.end());
//create a temporary node
}

/**
 * Prints out the whole list containing every contact info
 */
void contactList::printList() {
	//create a temporary node
	contactNode *temp = head;
	//int i means the person's position in the list, so we start from 1
	int i = 1;
	//check if the list is empty
	while (temp != nullptr) {
		//if it's not empty, print out the contact info
		cout << "==============================" << endl;
		cout << "Person " << i << endl;
		cout << "First Name: " << temp->getFirstName() << endl;
		cout << "Last Name: " << temp->getLastName() << endl;
		cout << "Phone Number: " << temp->getPhoneNumber() << endl;
		i++;
		//after printing one info, set the temporary node to the next node
		temp = temp->getNext();
	}
	//if the list is empty, print out the message
	if (head == nullptr) {
		cout << "The list is empty" << endl;
	}
}

/**
 * Prints out a specific contact info based on the contact id
 * @param phoneNumber
 */
void contactList::printContact(contactNode *contact) {
	//if it's not empty and has matched the contact id, print out the contact info
	cout << "First Name: " << contact->getFirstName() << endl;
	cout << "Last Name: " << contact->getLastName() << endl;
	cout << "Phone Number: " << contact->getPhoneNumber() << endl;
}

/**
 * Gets the number of contacts of the list
 * @return int listSize
 */
int contactList::getListSize() const {
	return listSize;
}

/**
 * Get the first name of the contact from the list by the phone number
 * @param phoneNumber
 * @return
 */
string contactList::getFirstName(const string &phoneNumber) {
	//back up safety in case the contact isn't in the list, and I forgot to check before calling this function
	if (isContactInList(phoneNumber)) {
		contactNode *temp = head;
		while (temp != nullptr) {
			if (temp->getPhoneNumber() == phoneNumber) {
				return temp->getFirstName();
			}
			temp = temp->getNext();
		}
		return "";
	} else {
		return "Error: Contact not found";
	}
}

/**
 * Get the last name of the contact from the list by the phone number
 * @param phoneNumber
 * @return
 */
string contactList::getLastName(const string &phoneNumber) {
	//back up safety in case the contact isn't in the list, and I forgot to check before calling this function
	if (isContactInList(phoneNumber)) {
		contactNode *temp = head;
		while (temp != nullptr) {
			if (temp->getPhoneNumber() == phoneNumber) {
				return temp->getLastName();
			}
			temp = temp->getNext();
		}
		return "";
	} else {
		return "Error: Contact not found";
	}
}

/**
 * Return the phone number for the contact
 * @param phoneNumber
 * @return
 */
string contactList::getPhoneNumber(const string &phoneNumber) {
	//back up safety in case the contact isn't in the list, and I forgot to check before calling this function
	if (isContactInList(phoneNumber)) {
		contactNode *temp = head;
		while (temp != nullptr) {
			if (temp->getPhoneNumber() == phoneNumber) {
				return temp->getPhoneNumber();
			}
			temp = temp->getNext();
		}
		return "";
	} else {
		return "Error: Contact not found";
	}
}