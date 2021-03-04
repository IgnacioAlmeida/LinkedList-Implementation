#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include "LinkedListInterface.h"

using namespace std;

template<class T>
class LinkedList : public LinkedListInterface<T>{
private:
	struct Node {
		T data; //The data we are storing
		Node* next; //A pointer to the next node;
		Node(const T &the_data, Node* next_val = NULL) : data(the_data) {
				next = next_val;
			}
	};

	Node *head;
	Node *temp;
	Node *insert;
	int numItems = 0;

public:

	LinkedList(void) {
		head = NULL;  //Points to the front of the list
		numItems = 0;
	};
	virtual ~LinkedList(void) {
		clear();
	};

	//Inserts Head
	virtual void insertHead(T value){
		if (find(value) == true){
			cout << "The value already exists" << endl;
			return;
		}
		else{
			temp = new Node(value);
			temp->next = head;
			head = temp;
			numItems++;
			return;
		}
	};

	//Helper function that will go through the list and find the value
	bool find(T value){
		temp = head;
		while(temp != NULL){
			if(temp->data == value)
				return true;
			temp = temp->next;
		}
		return false;
	}; 

	//Inserts Tail
	virtual void insertTail(T value){
		//checks if the value already exists
		if (find(value) == true){
			cout << "The value already exists" << endl;
			return;
		}
		else{
			//Inserts Head if we don't have one
			if(head == NULL){
				insertHead(value);
				return;
			}
			//Inserts tail	
			else{
				temp = head;
				while(temp->next != NULL){
					temp = temp->next;
				}
				insert = new Node(value);
				temp->next = insert;
				numItems++;
				return;
			}
		}
	};
	
	//Inserts a node after the value(insertionNode) given 
	virtual void insertAfter(T value, T insertionNode){
		//check that node insertionNode exists - use Find function
		if (find(value) == true){
			cout << "The value already exists" << endl;
			return;
		}
		else if(find(insertionNode)==true){
			//make temp ptr and point to head
			temp = head;
			//Traverse through the list until we find insertionNode
			while(temp->data != insertionNode){
				temp = temp->next;
			}
			//Create new node with value
			insert = new Node(value);
			//set its next = to temp ptr's next value 
			insert->next = temp->next;
			//set tempr ptr next value = to new Node(Value)
			temp->next = insert;
			numItems++;
			return;
		}
	};

	//Removes a specific node
	virtual void remove(T value){		
		if(find(value) == true){
			//**If remove is head**
			if(head->data == value){
				//Make temp point head so that later we can delete head
				temp = head;
				//Set Head pointer to point the next node
				head = head->next;
				//After that delete the temp pointer
				numItems--;
				delete temp;
				return;
			}
			//**If remove isn't head
			else{
				temp = head;
				//while temp isn't the node before the value we want to delete
				while(temp->next->data != value){
					temp = temp->next;
				}
				//another tempo node pointing to the value we want to delete
				insert = temp->next;
				//make temp point to the node after the value that we want to delete;
				temp->next = insert->next;
				numItems--;
				delete insert;
				return;
			}
		}
		else{
			cout << "value is not in the list" << endl;
			return;
		}
	};

	//Remove all nodes from the list
	virtual void clear(){
		while(head != NULL){
			remove(head->data);
		}
		numItems = 0;
		return;
	};

	//Gets the value at a given index
	virtual T at(int index){
		int counter = 0;
		temp = head;
		if(index > numItems - 1 || index < 0 || numItems == 0)
			throw out_of_range("Out of range");
		while(temp != NULL){
			if(index > numItems - 1 || index < 0 || numItems == 0)
				throw out_of_range("Out of range");
			else if (counter == index)
				return (temp->data);
			counter++;
			temp = temp->next;
		}
	};

	//Returns the number of items
	virtual int size(){
		return numItems;
	};

	//Prints list
	virtual string toString(){
		stringstream ss;
		for(temp = head; temp != NULL; temp = temp->next){
			if(temp->next == NULL)
				ss << temp->data;
			else
				ss << temp->data << " ";
		}
		return ss.str();
	};
};
