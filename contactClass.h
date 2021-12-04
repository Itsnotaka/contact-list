// my_class.h
#pragma once
#ifndef CONTACT_CLASS_H
#define CONTACT_CLASS_H

#include <iostream>
#include <string>
using namespace std;

/** Class of a contact
 * @author Min Chun Fu
 *
 * Implementation of a contact node class
 *
 * This class contains multiple functions that we could use to create or modify the contacts
 * it is paired with a linked list class to create a contact list
 */
class contactNode
{
private:
    int contact_id;
    string first_name;
    string last_name;
    string phone_number;
    char* createdAt{};

    contactNode *next;

public:
    contactNode();
    contactNode(string firstName, string lastName, const string& phoneNumber);
    ~contactNode();

    int get_id() const;
	int setId(const string& phoneNumber);

    string getFirstName();
    string getLastName();
    string getPhoneNumber();

    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setPhoneNumber(string phoneNumber);

    contactNode *getNext();
    contactNode *setNext(contactNode *next);
};

/** Class of a contact list
 * @author Min Chun Fu
 *
 * Implementation of a contact list class
 * contactList is a linked list of contactNode, used to store the contact information.
 * we could then use unique id's to identify the contact
*/
class contactList
{
private:
    contactNode *head;
    contactNode *tail;
    int listSize;

public:
    contactList();
    ~contactList();

	int getListSize() const;

	bool isContactInList(const string& phoneNumber);

	string getFirstName(const string &phoneNumber);
	string getPhoneNumber(const string &phoneNumber);
	string getLastName(const string &phoneNumber);

	void addContact(contactNode newContact);
    void removeContact(const string& phoneNumber);
	void sortContactList();
    void printList();
    void printContact(contactNode *contact);
	void searchForContact(const string& phoneNumber);
	void searchForContactByName(const string &searchName);
	void updateContact(const string& phoneNumber, int contactField, const string& updatedValue);


};
#endif /*CONTACT_CLASS_H*/