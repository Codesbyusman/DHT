#pragma once
/*
	Muhammad Usman Shahid
	   Assignment 03
		  20i-1797
			 T
*/


template<class T>
struct linkData
{
	T data;
	linkData<T>* next;
};

template<class T>
class Linklist
{

private:

	linkData<T>* head; //the starting
	linkData<T>* tail; // the end

public:

	Linklist()
	{
		//at starting no link lst
		head = NULL;
		tail = NULL;
	}

	//insertion of data
	void insert(T data)
	{
		//making the memory block to be added
		linkData<T>* newData = new linkData<T>;

		//assigning the data
		newData->data = data;

		//now setting the start and end ---- setting pointers
		if (head == NULL)
		{
			//the first element
			newData->next = NULL;
			head = tail = newData; //head tail pointing to same
		}
		else
		{
			//the other nodes

			//all other
			tail->next = newData;
			tail = newData; //tail pointing to added one
			tail->next = NULL;

		}
	}

	//displaying the list
	void displayList()
	{
		linkData<T>* iterator = head; //iterator

		//the empty list
		if (head == NULL)
		{
			cout << " --- Empty List ---";
		}

		//while end is encountered
		while (iterator)
		{

			cout << iterator->data << " ";

			//move to next
			iterator = iterator->next;
		}

	}

	//geting the last node
	T returnLast()
	{
		
		linkData<T>* toReturn = tail;

		return toReturn->data;

	}

	//delete node --- will delte node from end
	void deleteNode()
	{

		//if deleteing is the 1st element
		if (head == tail)
		{
			delete head; //deleting single
			head = tail = NULL; //no list
		}
		else
		{
			//not the single element
			linkData<T>* iterator = head; //for iteration

			//will move till the second last element
			while (iterator->next != tail)
			{
				iterator = iterator->next; //moving to next
			}	

			delete tail;

			//updating tail
			tail = iterator;
			iterator->next = NULL;

		}
	}

	bool isEmpty()
	{
		if (head == NULL)
		{
			return true; //empty
		}

		return false; //not empty
	}

	
	//for displaying path
	void displayPath()
	{
		//for iteration
		linkData<T>* iterate = head;

		cout << "\n\t Path followed was : ";

		//starting from head and traversing
		while (iterate)
		{
			
			cout << iterate->data << " --> ";

			iterate = iterate->next; //going onward
		}

		cout << "\b\b\b\b     " << endl;

		cout << "\n\t\t :::::: Number are visited machine id's ::::::::" << endl;

	}
	
	//delete whole list
	void deleteList()
	{
		//deleting noodes till list is empty thus
		while (head)
		{
			deleteNode(); //while head !- null delete the nodes
		}
	}

	~Linklist()
	{
		deleteList();
	}
};
