#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cmath> //for mathematics
#include <string>

using namespace std;

//contains different classes including routing tables and ringDHT and aslo alv tree header file
#include "IdentifierSpace.h"


/*
		-------------------------------------------------------------------------------
		--------------------------- Functions prototypes ------------------------------
		-------------------------------------------------------------------------------
*/

//for displaying the logo
void displayLogo();

//the global function foR hashing
int generateKey_Hashing(const int , const int);

//for handling machine generation
template<class T>
void machineControl(int * , int&, const int, RingDHT<T>&);

//will find the required machine that where to go in the ring DHT with the help of routing tables
template<class T>
machineNode<T>* findtheCorrectMachine(RingDHT<T> , machineNode<T>* , const int , const int, Linklist<int> &);

//the driver function for data manipulation related tasks
template<class T>
void dataRelatedFunctionality(RingDHT<T>&, const int, const int, const int);

//the driver function for machine manipulation related tasks
template <class T>
void machineRelatedFunctionality(RingDHT<T>& , const int , const int , const int );

/*
		-------------------------------------------------------------------------------
		------------------------------ Main Function ----------------------------------
		-------------------------------------------------------------------------------
*/

int main()
{
	//for generatin random numbers each time different
	srand(time(NULL));

	int machineNum = 0, space = 0; //for taking inputs
	int bitNum = 0;
	int a = 0;
	char option;

	//the ring that contains all machines
	//containg the mchines as nodes in a circular machine and data accordingly
	RingDHT<int> identifierSpace;
	int* machineIds = NULL; //to hold the dynamic array

	displayLogo(); //for displaying DHT message

	cout << "\n\n Enter the bits of space identifier : ";
	cin >> bitNum;

	//calculating the space 
	space = pow(2, bitNum); //the 2 powers enter as number of bits entered for 4 it will be 16 for 5 it will be 32

	//will take machine numbers and will come back after populating the DHT ring 
	machineControl(machineIds, machineNum, space, identifierSpace);

	
	//will assign the end ranges accordingly
	identifierSpace.assignEndranges(space);
	
	//making the routing tables
	identifierSpace.makeroutingTables(machineNum, space, bitNum);


	//label to come back
mainMenu:

	system("cls"); //clearing the screen)

	displayLogo(); //for displaying DHT message

	/* making menu for asking from the user about the things he want to do */
	cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


	cout << "\n\t    Enter 1 for machine related Tasks " << endl;
	cout <<   "\t    Enter 2 for data related Tasks " << endl;
	cout <<   "\t    Enter any other character to quit " << endl;


	cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


	cout << "\n\t Enter the desired option : ";
	cin >> option;

	//the menu functionality
	switch (option)
	{
		/*
			-------------------------------------------------------------------------------
			------------------------ machine Related program ------------------------------
			-------------------------------------------------------------------------------
		*/

		case '1':
		{
			//calling the menu program --- the driver function to handle data
			machineRelatedFunctionality(identifierSpace, machineNum, space, bitNum);

			break;
		}

		/*
			-------------------------------------------------------------------------------
			--------------------------- Data Related program ------------------------------
			-------------------------------------------------------------------------------
		*/
		case '2' :
		{

			//calling the menu program --- the driver function to handle data
			dataRelatedFunctionality(identifierSpace, machineNum, space, bitNum);

			break;
		}
		
		/*
			-------------------------------------------------------------------------------
			--------------------------- Quitting the program ------------------------------
			-------------------------------------------------------------------------------
		*/
		default:
		{
			//do nothing
			return 0;
		}
	}

	//go back to main menu untill not exited
	goto mainMenu;

	
	
	return 0;
}


/*
		-------------------------------------------------------------------------------
		--------------------------- Function Definitions ------------------------------
		-------------------------------------------------------------------------------
*/

//displaying the logo DHTT
void displayLogo()
{

	cout << "\n\t :::::::::::::::::::::::::::::::::::::::::::::::" << endl;


	cout << "\n\t :::::::::::::::::::::::::::::::::::::::::::::::" << endl;
	cout << "\t ::::::::::::: Distributed Hash Tables :::::::::" << endl;
	cout << "\t :::::::::::::::::::::::::::::::::::::::::::::::" << endl;

	cout << "\n\t :::::::::::::::::::::::::::::::::::::::::::::::" << endl;



}

//a key will be entered and a hashed key will be generated
int generateKey_Hashing(const int key, const int identifierspaceSize)
{
	//the generated number holder
	int toreturnKey = 0;

	toreturnKey = key % identifierspaceSize; //tking mode with the size given by user

	return toreturnKey; //the returning after taking mod
}

//for handling machine generation
template <class T>
void machineControl(int * machineIds, int& machineNum, const int space, RingDHT<T>& identifierSpace)
{
	int option = 0, a = 0; //helping

	//at this stage the dummy data 
	RoutingTable<int> Rtable; 
	avlTree<int> data;

	
	//asking for machine numbers
	do
	{
		//for error mesaaging
		if (a == 0)
		{
			cout << "\n Enter the number of machines : ";
			cin >> machineNum;

		}
		else
		{
			cout << "\n\t        ::::::::::: Error ::::::::::::::::" << endl;
			cout << "\t::::::: Machine Number can not exceed size ::::::::" << endl;
			cout << "\n Enter the number of machines again : ";
			cin >> machineNum;
		}

		a++;

	} while (!(machineNum <= space));


	//making an array to hold the id's of all machines created
	machineIds = new int[machineNum];

	a = 0;

	do
	{
		//for error mesaaging
		if (a == 0)
		{
			//asking from user whether he/she want to give id's to machine or not
			cout << "\n\n \t Enter 1 to assign Id's " << endl;
			cout << "\t Enter 0 to give random Id's to " << machineNum << " machines" << endl;

			cout << "\n\t Enter option : ";
			cin >> option;

		}
		else
		{
			cout << "\n\t        ::::::::::: Error ::::::::::::::::" << endl;
			//asking from user whether he/she want to give id's to machine or not
			cout << "\n\n \t Enter 1 to assign Id's " << endl;
			cout << "\t Enter 0 to give random Id's to " << machineNum << " machines" << endl;

			cout << "\n\t Enter option again : ";
			cin >> option;
		}

		a++;

	} while (!(option == 0 || option == 1));

	//the assigning of machines
	switch (option)
	{
		//the random assigning
		case 0:
		{
			//will iterate = to number of machines
			for (int i = 0; i < machineNum; i++)
			{	
				do
				{
					//generating random and assigning
					machineIds[i] = generateKey_Hashing(rand(), space); //generating random id's and passing through hash function'

				} while (identifierSpace.find(machineIds[i])); //checking if exist then make another random to make machines unique
				
				//inserting 
				identifierSpace.insert(Rtable, data, machineIds[i]);

			}
			break;
		}

		//assigning manuallay
		default:
		{
			//manually will ask id's from user 
			for (int i = 0; i < machineNum; i++)
			{
				a = 0;

				do
				{
					if (a == 0)
					{
						cout << "\n\t Enter the id for machine " << i + 1 << " : ";
						cin >> machineIds[i];
					}
					else
					{
						cout << "\n\t\t ::::: Error ::: Must ne Unique ::::" << endl;
						cout << "\n\t Enter the id for machine " << i + 1 << " again : ";
						cin >> machineIds[i];
					}
					
					a++;

				} while (identifierSpace.find(machineIds[i])); //checking if exist then make another random to make machines unique

				//making the dht by passing the ids to the hash funcion
				//inserting with hashed id's
				identifierSpace.insert(Rtable, data, generateKey_Hashing(machineIds[i], space));

			}


		}
	}
}


//for searching machine
//returning the node that was searched
//this function will take hash id of the data and will return the node where that data is
//will be useful in inserting data or finding the data
//can be called from any machine
//using the routing table of given and finding the machine
//it will be a fecursive function to find
//will also save the path in the linked list the int type
template<class T>
machineNode<T>* findtheCorrectMachine(RingDHT<T> machines,  machineNode<T>* startFrom, const int hashId, const int bits, Linklist<int> & path) 
{
	//applying the conditions and finding the machine of storage
	const int mId = startFrom->machineId;

	//checking if the id is less than the current machine then data is hold by the machine
	//thus 
	if (hashId <= mId)
	{
		//returning as we found the desired
		return startFrom;
	}

	//for the first node data
	if (hashId > machines.getIdoflast())
	{
		
		//returning the head because data is of head
		return machines.getHead();
	}
	
	
	//now looking in the routing table
	if (mId < hashId && hashId <= startFrom->FTp.getidofShortcuts(1))
	{
		//thus the id will be in the first entry of routing table
		//thus goingbto routing table of first entry
		//recursive call
		machineNode<T>*  machinePointer = startFrom->FTp.returnPointer(1);
		
		//inserting the id of machine if visited
		path.insert(machinePointer->machineId);

		//finding the machine node now in the first entry of current machines routing table
		return findtheCorrectMachine(machines,  machinePointer, hashId, bits, path);
	}
	else
	{

		//now the third condition that looking in the whole routing table
		//iterating whole in list
		for (int i = 1; i < bits; i++) 
		{
			//the the i is the required
			if (startFrom->FTp.getidofShortcuts(i) < hashId && hashId <= startFrom->FTp.getidofShortcuts(i + 1))
			{
				//the required shortcut and will route in this machine routing table
				machineNode<T>* machinePointer = startFrom->FTp.returnPointer(i);

				//inserting the id of machine if visited
				path.insert(machinePointer->machineId);

				//finding the machine node now in the first entry of current machines routing table
				return findtheCorrectMachine(machines,  machinePointer, hashId, bits, path);

			}

		}

		//from above if not found then will check here for the heighest and will look in the highest machine
		//as in the routing table we didn't find any node that is greater than data thus
		//the data will be in some other as each nodes holds data less than or equal to its id thus
		//going to the maximum and going to that machine node
		//the required shortcut and will route in this machine routing table
		machineNode<T>* machinePointer = startFrom->FTp.returnHighest();

		//inserting the id of machine if visited
		path.insert(machinePointer->machineId);

		//finding the machine node now in the first entry of current machines routing table
		return findtheCorrectMachine(machines,  machinePointer, hashId, bits, path);


	}
	
	
}

template <class T>
void dataRelatedFunctionality(RingDHT<T> & machines , const int machineNum, const int space , const int bitNum)
{
	//the inputs
	int id = 0;
	int hashid = 0;
	string name, age, gender;
	string data; //a final string to store
	Data theRequired; //the requested data

	char opt, opt1; //for the option taking

	//finding the desired machine
	machineNode<T>* reqMachine = NULL;

	//for holding path of isertion
	Linklist<int> pathFollowed;

Mainmenu:

	system("cls"); //clearing the screen)

	displayLogo(); //for displaying DHT message

	//removing path array -- because to add new
	pathFollowed.deleteList();

	/* making menu for asking from the user about the things he want to do */
	cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


	cout << "\n\t    Enter 1 for inserting Data " << endl;
	cout << "\t    Enter 2 for Deleting Data " << endl;
	cout << "\t    Enter 3 for searching Data" << endl;
	cout << "\t    Enter any other character to go back " << endl;


	cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


	cout << "\n\t Enter the desired option : ";
	cin >> opt;

	/* 
		for insertion and deletion we are not asking from the user from which machine to start oly for searching will ask
		other wise using head as starting point
	*/
	//now doing data related things
	switch (opt)
	{
		/*
			-------------------------------------------------------------------------------
			----------------------------- Data Insertion ----------------------------------
			-------------------------------------------------------------------------------
		*/

		case '1':
		{
			//removing path array -- because to add new
			pathFollowed.deleteList();

			//taking key
			cout << "\n\t Enter the id : ";
			cin >> id;

			//ignoring the input
			cin.ignore();

			//askig for the value
			cout << "\t Enter Your name : ";
			getline(cin, name);

			//askig for the value
			cout << "\t Enter Your age : ";
			getline(cin, age);

			//askig for the value
			cout << "\t Enter Your gender : ";
			getline(cin, gender);

			//mapping in the identifier space
			hashid = generateKey_Hashing(id, space);

			//making the data that to enter
			data = name + " " + age + " " + gender;

			//now will add this to a data --- structure and will insert in the machine
			Data Value;
			Value.id = id;
			Value.value = data;

			//the starting value in path
			reqMachine = machines.getHead();
			pathFollowed.insert(reqMachine->machineId); //inserting the starting id

			//updaing the insert in
			//first finding the machine node were to inser
			reqMachine = findtheCorrectMachine(machines, machines.getHead(), hashid, bitNum, pathFollowed);

			//now insertig the dat to the machine --- finding the node in machines and also updating that
			reqMachine->machineData.insert(Value, hashid);
			
			

			cout << "\n\t :::::::: Seccussfully added The data to machine " << reqMachine->machineId << " ::::::::::::" << endl;

			cout << endl;

			system("pause");

			cout << endl;

			//giving option for path and for checking the whole AVL tree
		Menu:

			
			/* making menu for asking from the user about the things he want to do */
			cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


			cout << "\n\t    Enter 1 for checking Path of insertion " << endl;
			cout << "\t    Enter 2 for seeing the AVL tree " << endl;
			cout << "\t    Enter any other character to go back " << endl;


			cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


			cout << "\n\t Enter the desired option : ";
			cin >> opt1;

			switch (opt1)
			{
				//for path 
				case '1':
				{
					
					pathFollowed.displayPath();

					cout << endl;
					system("pause");
					cout << endl;

					goto Menu; //displaying the menu again
					break;
				}
				//for seeing the hole avl tree
				case '2':
				{
					cout << "\n\t Pre-order is : ";
					reqMachine->machineData.displayPreOder();
					cout << endl;

					system("pause");

					cout << endl;

					goto Menu; //displaying menu again
					break;

				}
				default:
				{
					break; // go back
				}
			}

			break;
		}

		/*
			-------------------------------------------------------------------------------
			--------------------------- Data Deletion ------------------------------------
			-------------------------------------------------------------------------------
		*/
		case '2':
		{
			//removing path array -- because to add new
			pathFollowed.deleteList();

			//taking id of data to remove
			cout << "\n\t Enter the data id to remove : ";
			cin >> id;

			//maping in the identifier space
			hashid = generateKey_Hashing(id, space);
			
			//the starting value in path
			reqMachine = machines.getHead();
			pathFollowed.insert(reqMachine->machineId); //inserting the starting id

			//updaing the reqMachine
			//first finding the machine node were to delete
			reqMachine = findtheCorrectMachine(machines, machines.getHead(), hashid, bitNum, pathFollowed);

			//now deleting the dat to the machine --- finding the node in machines and also updating that
			reqMachine->machineData.deleteNode(hashid);



			cout << "\n\t :::::::: Seccussfully Deleted The data from machine " << reqMachine->machineId << " ::::::::::::" << endl;

			cout << endl;

			system("pause");

			cout << endl;

			//giving option for path and for checking the whole AVL tree
		Menu0:


			/* making menu for asking from the user about the things he want to do */
			cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


			cout << "\n\t    Enter 1 for checking Path of deletion " << endl;
			cout << "\t    Enter 2 for seeing the AVL tree " << endl;
			cout << "\t    Enter any other character to go back " << endl;


			cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


			cout << "\n\t Enter the desired option : ";
			cin >> opt1;

			switch (opt1)
			{
				//for path 
				case '1':
				{

					pathFollowed.displayPath();

					cout << endl;
					system("pause");
					cout << endl;

					goto Menu0; //displaying the menu again
					break;
				}
				//for seeing the hole avl tree
				case '2':
				{
					cout << "\n\t Pre-order is : ";
					reqMachine->machineData.displayPreOder();
					cout << endl;

					system("pause");

					cout << endl;

					goto Menu0; //displaying menu again
					break;

				}
				default:
				{
					break; // go back
				}
			}
			



			break;
		}

		/*
			-------------------------------------------------------------------------------
			------------------------------ Data Searching ----------------------------------
			-------------------------------------------------------------------------------
		*/
		case '3':
		{
			//clearing the path followed 
			pathFollowed.deleteList();

			cout << "\n\t Enter Id : ";
			cin >> id; //the original id

			//mapping to the space
			hashid = generateKey_Hashing(id, space);

			int machineId = 0;

			cout << "\n\t Enter the machine from where you want to start search : ";
			cin >> machineId;

			if (machines.find(machineId))
			{

				//the starting value in path
				reqMachine = machines.returnMachine(machineId); //will start from user defined machine
				pathFollowed.insert(reqMachine->machineId); //inserting the starting id

				//updaing the reqMachine
				//first finding the machine node were to delete
				reqMachine = findtheCorrectMachine(machines, reqMachine, hashid, bitNum, pathFollowed);

				//foe storing the avl node if found
				avlNode<T>* dataFound = NULL;
				//now searching in the required machine
				if (reqMachine->machineData.findMe(hashid, dataFound))
				{
					
					//now checking in the node list s to confrom that asked data is found not the dirty data due to collision
					if (reqMachine->machineData.findinList(id, dataFound->nodeDataList, theRequired))
					{
						cout << "\n\t ::::::::::: Data Found ::::::::::::::" << endl;
					}
					else
					{
						cout << "\n\t\t :::::::: Data Doesn't exist :::::::::::::" << endl;

						cout << endl;
						system("pause");
						cout << endl;

						goto Mainmenu;
					}
				}
				else
				{
					cout << "\n\t\t :::::::: Data Doesn't exist :::::::::::::" << endl;

					cout << endl;
					system("pause");
					cout << endl;

					goto Mainmenu;
				}
			}
			else
			{
				cout << "\n\t :::::::: Sorry no machine Exist with entered ID ::::::::::::" << endl;

				cout << endl;
				system("pause");
				cout << endl;

				goto Mainmenu;
			}

			cout << endl;
			system("pause");
			cout << endl;

			//giving option for path and for checking the whole AVL tree
		Menu1:


			/* making menu for asking from the user about the things he want to do */
			cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


			cout << "\n\t    Enter 1 for checking Path of searching " << endl;
			cout << "\t    Enter 2 for seeing the data " << endl;
			cout << "\t    Enter any other character to go back " << endl;


			cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


			cout << "\n\t Enter the desired option : ";
			cin >> opt1;

			switch (opt1)
			{
				//for path 
				case '1':
				{

					pathFollowed.displayPath();

					cout << endl;
					system("pause");
					cout << endl;

					goto Menu1; //displaying the menu again
					break;
				}
				//for seeing the data
				case '2':
				{
					cout << "\n\t\t Data is as follow : " << endl;
					cout <<"\n\t\t :::: " << theRequired.id << " " << theRequired.value << " ::::" << endl;

					goto Menu1;

					break;
				}
				default:
				{
					break; // go back
				}
			}

			
			break;
		}

		/*
			-------------------------------------------------------------------------------
			--------------------------- Quitting the driver -------------------------------
			-------------------------------------------------------------------------------
		*/
		default:
		{
			//do nothing
			return;
		}

	}

	//back to menu
	goto Mainmenu;

}

template <class T>
void machineRelatedFunctionality(RingDHT<T>& machines, const int machineNum, const int space, const int bitNum)
{
	//the inputs
	int id = 0;
	int hashid = 0;
	Data theRequired; //the requested data

	char option, opt1; //for the option taking

	//finding the desired machine
	machineNode<T>* reqMachine = NULL;

	//for holding path of isertion
	Linklist<int> pathFollowed;

	//making a menu for the code
mainMenu:

	system("cls"); //clearing the screen)

	displayLogo(); //for displaying DHT message

	//removing path array -- because to add new
	pathFollowed.deleteList();

	/* making menu for asking from the user about the things he want to do */
	cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


	cout << "\n\t\t Enter 1 to Add Machine " << endl;
	cout << "\t\t Enter 2 to Remove Machine" << endl;
	cout << "\t\t Enter 3 to see list of machines" << endl;
	cout << "\t\t Enter 4 to see routing tables" << endl;
	cout << "\t\t Enter any other character to exit " << endl;

	cout << "\n\t   :::::::::::::::::::::::::::::::::::::::" << endl;


	cout << "\n\t\t Enter the desired option : ";
	cin >> option;

	//checking for options
	switch (option)
	{
		/*
			-------------------------------------------------------------------------------
			----------------------------- Add Machine -- ----------------------------------
			-------------------------------------------------------------------------------
		*/

		case '1':
		{

			//adding the machine
			cout << "\n\t Enter the id : ";
			cin >> id;

			//mapping id to identifier space
			hashid = generateKey_Hashing(id, space);

			//checking already not exist
			if (!machines.find(hashid))
			{ 
				avlTree<int> inserting;
				RoutingTable<int> rt;
				Linklist<avlNode<T>*> storeData; //will store the data 
				
				/*
				machineNode<T>* temp;

				Linklist<Data> d;

				int i;
				avlNode<T>* td;

				//updating the avl trees
				//first stoeing data in linked list of the next to inserted
				//for insertion the previous machine data will be affected
				machines.updateAVL_addition(hashid, storeData);

				//now deleting avl of the previous node
				temp = machines.givePrevious(hashid);
				temp->machineData.nullHead();

				//if unique then inserting the machine 
				machines.insert(rt, inserting, hashid);

				machineNode<T>* reqMachine = machines.returnMachine(hashid);

				//now inerting whole linked list
				while (!storeData.isEmpty())
				{
					td = storeData.returnLast();

					reqMachine->machineData.insert(td);

					storeData.deleteNode();
				}
				*/

				machines.insert(rt, inserting, id);

				//updating the end ranges
				machines.assignEndranges(space);

				//updating the routing tables also
				machines.makeroutingTables(machineNum, space, bitNum);


				
				cout << "\n\t ::::: Machine " << hashid << "  Successfully added ::::::" << endl;
			}
			else
			{
				cout << "\n\t :::: Machine ID must be unique ::::::" << endl;

			}

			cout << endl;
			system("pause");
			cout << endl;

			break;
		}

		/*
			-------------------------------------------------------------------------------
			----------------------------- Machine Deletion ----------------------------------
			-------------------------------------------------------------------------------
		*/

		case '2':
		{

			//adding the machine
			cout << "\n\t Enter the id : ";
			cin >> id;

			//mapping id to identifier space
			hashid = generateKey_Hashing(id, space);

			//checking already not exist
			if (machines.find(hashid))
			{
				avlTree<int> inserting;
				RoutingTable<int> rt;
				Linklist<avlNode<T>*> storeData; //will store the data 

				/*
				machineNode<T>* temp;

				Linklist<Data> d;

				int i;
				avlNode<T>* td;

				//updating the avl trees
				//first stoeing data in linked list of the next to inserted
				//for insertion the previous machine data will be affected
				machines.updateAVL_addition(hashid, storeData);

				//now deleting avl of the previous node
				temp = machines.givePrevious(hashid);
				temp->machineData.nullHead();

				//if unique then inserting the machine
				machines.insert(rt, inserting, hashid);

				machineNode<T>* reqMachine = machines.returnMachine(hashid);

				//now inerting whole linked list
				while (!storeData.isEmpty())
				{
					td = storeData.returnLast();

					reqMachine->machineData.insert(td);

					storeData.deleteNode();
				}
				*/

				machines.deleteMachine(hashid);

				//updating the end ranges
				machines.assignEndranges(space);

				//updating the routing tables also
				machines.makeroutingTables(machineNum, space, bitNum);



				cout << "\n\t ::::: Machine " << hashid << "  Successfully Deleted ::::::" << endl;
			}
			else
			{
				cout << "\n\t :::: Machine does not exist ::::::" << endl;

			}

			cout << endl;
			system("pause");
			cout << endl;

			break;
		}

		/*
			-------------------------------------------------------------------------------
			----------------------------- List of machines---------------------------------
			-------------------------------------------------------------------------------
		*/

		case '3' :
		{
			//displaying the machines
			machines.display();

			cout << endl;
			system("pause");
			cout << endl;

			break;
		}

		/*
			-------------------------------------------------------------------------------
			----------------------------- routing tables ----------------------------------
			-------------------------------------------------------------------------------
		*/

		case '4':
		{

			cout << "\n\t Enter the id of machine : ";
			cin >> id;

			//mapping in the space
			hashid = generateKey_Hashing(id, space);

			if (machines.find(hashid))
			{
				//finding the machine
				machineNode<T>* toDisplay = machines.returnMachine(hashid);
				toDisplay->FTp.display();

			}
			else
			{

				cout << "\n\t ::::::::: Machine doesn't exist ::::::::::" << endl;
			}
			

			cout << endl;
			system("pause");
			cout << endl;

			break;
		}

		/*
			-------------------------------------------------------------------------------
			----------------------------- Quiting------------------------------------------
			-------------------------------------------------------------------------------
		*/

		default:
		{

			return; //returning

		}

		
	}

	//going to menu
	goto mainMenu;

}