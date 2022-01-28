#pragma once
#include "AVLtree.h"

/*
      will contain the functionality of singular circular linked list and its component
                      is the space identifier
*/

//forward declaration to avoid dependencies
template <class T>
struct machineNode;

template <class T>
struct RTnode
{
    int index; //will be identicat to each obect --- as above is static only a counter
    machineNode<T>* machinePointer; //the shorcut pointer

    //as doubly thus pointers to make it doubly
    RTnode<T>* next; //to point upcoming
    RTnode<T>* previous;  //to point the previous

    //a constructor
    RTnode()
    {
        index = 0;
        machinePointer = NULL;
        next = previous = NULL;

    }
};

template <class T>
class RoutingTable
{
    //doubly linked list class
private:
    RTnode<T>* head;

public:

    //constructor
    RoutingTable()
    {
        head = NULL; //no list initallay 

    }

    //inserting the data
    void insert(machineNode<T>* toinsert, int index)
    {
        //the memory block to be inserted
        RTnode<T>* newNode = new RTnode<T>;
        newNode->machinePointer = toinsert; //the shortcut pointer as a data

        //assiging the index count to the unique index of obj
        newNode->index = index;//whenever insertion is done increment index

        //if the inserting is first node --- the head
        if (isEmpty())
        {
            //the next and previous will be null
            head = newNode; //the head --- the entered
        }
        else
        {
            //the nodes exist thus traverse and see for end and insert
            RTnode<T>* iterator = head;

            while (iterator->next != NULL)
            {
                iterator = iterator->next; //going to next till null encountered
            }

            //the next null encountered add it here to next
            iterator->next = newNode; //pointing next to newly
            newNode->previous = iterator; //pointing to its back
        }
    }

    //check the list empty or not
    bool isEmpty()
    {
        if (head == NULL)
        {
            return true; //empty
        }

        return false; //not empty
    }

    //for returning the index elemnt id --- the shortcut id
    int getidofShortcuts(int index)
    {
        RTnode<T>* temp = head; // for iteration

        //iterating in linked list
        while (temp)
        {
            if (temp->index == index)
            {
                //the required
                return temp->machinePointer->machineId; //this id required
            }

            temp = temp->next; //going next in list
        }

        return -1; //returning the id garbage
    }

    //return the pointer of said indes
    machineNode<T>* returnPointer(const int index)
    {
        //for iteration
        RTnode<T>* temp = head;

        while (temp)
        {
            if (temp->index == index)
            {
                //the required
                return temp->machinePointer; //this pointer required
            }

            temp = temp->next; //going next in list
        }

        //for returning null if not found
        machineNode<T>* returning = NULL;
        return returning;
    }

    //return highest shortcut pointer in table
    machineNode<T>* returnHighest()
    {

        int id = 0;
        RTnode<T>* iterator = head; //for iterating in the table 
        machineNode<T>* toreturn = NULL; //the machine shortcut to return 

        //the id of head at starting
        id = iterator->machinePointer->machineId;

        while (iterator) //null not encountered
        {
            //if highest encountered
            if (iterator->machinePointer->machineId > id)
            {
                //then returning info should be updated
                id = iterator->machinePointer->machineId;
                toreturn = iterator->machinePointer;
            }
            //going to next
            iterator = iterator->next;
        }

        //returning the pointer
        return toreturn;

    }

    //for displaying
    void display()
    {
        //the nodes exist thus traverse and see for end and insert
        RTnode<T>* iterator = head;


        cout << "\n\t\t :::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;

        if (iterator == NULL)
        {
            cout << "empty" << endl;
            return;
        }

        cout << "\n\t\t\t index \t : \t Shortcut machine pointer " << endl;
        while (iterator)
        {
            
            cout << "\n\t\t\t " << iterator->index << " \t : \t " << iterator->machinePointer->machineId << endl;
            iterator = iterator->next; //going to next till null encountered
        }


        cout << "\n\t\t :::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    
    }

    //will delete from the last node 
    void deleteRt()
    {

        //iterating to the end of list and will find the last one
        RTnode<T>* iterator = head;

        while (iterator->next)
        {
            iterator = iterator->next; //going to next till null encountered
        }

        //iterator contains deleting node
        if (iterator != head) //if deleting node is not head
        {
            //iterator conatons the last element
            iterator->previous->next = NULL;

            delete iterator;
        }
        else //if it is head also set head
        {
            delete head;
            head = NULL;
        }



    }

    void deleteRtables()
    {
        //delete all nodes till the list is not empty
        while (!isEmpty())
        {
            deleteRt();
        }

    }
    //destructor
    ~RoutingTable()
    {

        //delete all nodes till the list is not empty
        while (!isEmpty())
        {
            deleteRt();
        }

    }
};

//the mchine node --- the circular identifier space nodes
template <class T>
struct machineNode
{
    int machineId; //the machine id
    RoutingTable<T> FTp; //the routing table of each machine
    avlTree<T> machineData; //for holding the data an avl tree
    int endRange; //the previous machine number  as range will start from machine number to the previous machine excluding previousone

    //as circular --- the linked list
    machineNode<T>* next; //singly linked list

    //constructor
    machineNode()
    {
        //no next
        next = NULL;
        machineId = 0;
        endRange = 0;
    }
};

//the identifier space --- circular linked list 
template <class T>
class RingDHT
{

public:

    machineNode<T>* head; //the starting of circular list

public:

    //constructor 
    RingDHT()
    {
        //initallay the head is null no list
        head = NULL;
    }

    //for inserting ascendingly
    void insert(RoutingTable<T> RT, avlTree<T> data, int id)
    {

        //the memory block to insert
        machineNode<T>* newMachine = new machineNode<T>;

        newMachine->FTp = RT; //the routing table
        newMachine->machineData = data; //the data
        newMachine->machineId = id; //the id of machine

        //now seting the pointers
        if (isEmpty())
        {
            //if the head inserted
            head = newMachine;
            head->next = head; //points again to head
        }
        else if (id <= head->machineId)
        {
            //for second iteration
            machineNode<T>* temp = NULL;

            //iterating to end
            temp = head;

            while (temp->next != head)
            {
                temp = temp->next;
            }

            newMachine->next = head;//pointing to head
            head = newMachine;//updating head
            temp->next = head; //updating to point new head

        }
        else
        {
            //finding the last node of list 
            machineNode<T>* iterator = head;
            bool byBreak = 0;

            //for second iteration
            machineNode<T>* temp = NULL;

           do
            {
                if (id <= iterator->machineId)
                {
                    //mean insert before the iterator
                    byBreak = 1;
                    break;
                }
                iterator = iterator->next;

           } while (iterator != head); //while head encountered again


            if (iterator->next == head && !byBreak) //the last entry
            {
                //now iterator is pointing to the last 
                iterator->next = newMachine;
                //also pointing new entered to head
                newMachine->next = head;
            }
            else
            {
                //in between 
                //traversing till previous of iterator
                temp = head;

                //will the iterate previous not found
                while (temp->next != iterator)
                {
                    temp = temp->next; //going onward
                }

                //setting ponters
                temp->next = newMachine;
                newMachine->next = iterator;
            }



        }
    }

    //for geting id of last machine
    int getIdoflast()
    {
        //iterating to last 
        machineNode<T>* iterate = head;

        do
        {
            
            //going to next
            iterate = iterate->next;

        } while (iterate->next != head); //again going to head

        return iterate->machineId; //returning
    }

    //for deleting the data
    void deleteMachine(int id)
    {
        if (id != head->machineId)
        {
            //finding the id in the list to delete
            //the iterator to iterate in the list
            machineNode<T>* iterator = head; //will contain the current
            machineNode<T>* prev = head; //will contain previous of others
            machineNode<T>* temp = NULL; //the temporaray

            do
            {
                prev = iterator; //the previous 

                //if the next data is same
                if (iterator->next->machineId == id)
                {
                    temp = iterator->next; //to delte
                    prev->next = temp->next; //setting pointers

                    //deleting temp
                    delete temp;

                    return; //as deleted
                }

                //going to next
                iterator = iterator->next;


            } while (iterator != head); //till head not encountered

            cout << "\n\t\t No data found to delete " << endl;

        }
        else
        {
            //the head deletion 
            if (head->next == head) //mean only one the head
            {
                delete head; //deleting head
                head = NULL; //assiging null
            }
            else
            {
                //list exist but to cancel the head
                //traversing in the list and finding last one 
                machineNode<T>* iterator = head;
                machineNode<T>* temp = NULL;

                //moving to last one
                while (iterator->next != head)
                {
                    iterator = iterator->next; //going to next
                }

                //iterator contains last one now deleting head and pointing to new head
                temp = head;

                head = head->next; //updating head
                iterator->next = head; //pointing back to new head

                delete temp; //deleting 
            }
        }

    }

    //for displaying
    void display()
    {
        //iterating in the list
        machineNode<T>* iterator = head;
        int i = 1;

        cout << "\n\t\t ::::::::::::::::::::::::::::::::" << endl << endl;
        
        if (isEmpty())
        {
            cout << "\n\t\t Empty " << endl;
        }
        else
        {
            do
            {

                cout << "\t\t     Machine Number  " << i << " : " << iterator->machineId << endl;

                //going to next
                iterator = iterator->next;
                i++; //count

            } while (iterator != head); //till head encountered again

        }

        cout << "\n\t\t ::::::::::::::::::::::::::::::::" << endl << endl;

    }

    //for finding 
    bool find(int id)
    {
        machineNode<T>* iterator = head; //for iteration

        if (head != NULL) //if tree exists
        {
            do
            {
                if (id == iterator->machineId)
                {
                    return true; //the id exist
                }
                iterator = iterator->next; //going to next
            } while (iterator != head); //again head not encountered

        }
       
        return false; //no id
    }

    //to check that empty or not
    bool isEmpty()
    {
        if (head == NULL)
        {
            return true; //no list
        }

        return false; //not empty
    }

    //for assiging the ranges to each machine
    void assignEndranges(const int space)
    {
        //for iteration
        machineNode<T>* iterator = head->next;
        machineNode<T>* previous = head;

        //for holding previous ids
        int temp = previous->machineId;
        temp++;

        while (iterator != head)
        {
            iterator->FTp.deleteRtables();
            iterator->endRange = temp;
            previous = previous->next;
            iterator = iterator->next;
            temp = previous->machineId;
            temp++;
        }

         //now for the head 
        temp = previous->machineId;
        temp++;
        if (temp >= space)
        {
            iterator->endRange = temp % 16;
        }
        else
        {
            iterator->endRange = temp;
        }

    }

    //for getting head
    machineNode<T>* getHead()
    {
        return head; //returning head
    }

    //for populating the routing tables
    void makeroutingTables(const int numMachine, const int space, const int bits)
    {
        machineNode<T>* shortcutToadd = NULL; //for routing table
        machineNode<T>* temp = head; //the iterator

        do
        {
            //the calling ftp routing table will be made
             //making alinked list equal to the number of machines
            for (int i = 1; i <= bits; i++)
            {
                shortcutToadd = NULL;
                //finding the point to insert
                findpointertoInsert(i, shortcutToadd, temp->machineId , space, bits);
                temp->FTp.insert(shortcutToadd, i); //inserting to the routing table
            }

            cout << endl;

            //going to next
            temp = temp->next;

        } while (temp != head); //head encountered again
        

    }

    //return routing table
    RoutingTable<T> returnRoutingtable(int id)
    {

        machineNode<T>* iterator = head; // for iteration

        do
        {

            if(id == iterator->machineId)
            {
                //the required
                return iterator->FTp; //returning the routing table
            }

            iterator = iterator->next; //going onward

        } while (iterator != head); //again head not encountered

        //routing table
        RoutingTable<T> returnThis;

        return returnThis; //if not found garbage

    }

    //will find the node where to go  ---- the shortcut
    void findpointertoInsert(int index, machineNode<T>*& shortcut, int id, const int space, const int bits)
    {
        //the formula implementation
        int p = pow(2, index - 1);
        p += id;

        //mapping in range if exceeded
        if (p >= space)
        {
            p = p % space;

        }

        machineNode<T>* iterator = head; //to iterate
        int endingRange = 0;
        int idM = 0;

        //finding the last node it's id so to have starting range of machine 1

        do
        {
            endingRange = iterator->endRange; //the ending range of machine
            idM = iterator->machineId; //to hold the id of the mahine
            
            
            //checking each node that p is in which range
            if (p >= endingRange && p <= idM)
            {

                //now assingng the pointer of machine and returning
                shortcut = iterator;
               
                return; //work has done

            }

            iterator = iterator->next; //moving to next

        } while (iterator != head); //head not found again
       
        //after this only the first node range will be left because of the circular property thus
        shortcut = head;
     
        return;
        
        
        
    }

    //updating avl after addition
    void updateAVL_addition(const int id, Linklist<avlNode<T>*> & storeAvl)
    {

        //finding the previous node 
        machineNode<T>* temp = givePrevious(id);

        //now populating whole linked list with the avl data
        temp->machineData.updateList(storeAvl);

   
    }

    //will find the next node inserted

    //for geting the machine pointer of given id
    machineNode<T>* returnMachine(const int id)
    {
        //for the iteration
        machineNode<T>* iterate = head;

        do
        {
            //if id matches
            if (id == iterate->machineId)
            {
                return iterate; //required return this
            }

            iterate = iterate->next; //going to next

        } while (iterate != head); //again head not found

        iterate = NULL;
        return iterate;
    }
    /*
    //for updating the data 
    void update(machineNode<T>* newUpdate)
    {

        //for iteration 
        machineNode<T>* iterate = head;

        do
        {
            if (newUpdate->machineId == iterate->machineId)
            {
                //updating the data in machines node
                iterate = newUpdate;
                return;//work done
            }
            iterate = iterate->next; //going in the list
        } while (iterate != head); //again head not encounteed

    }
    */

    machineNode<T>* givePrevious(int id)
    {
        //for the iteration
        machineNode<T>* iterate = head;

        do
        {
            //if id matches
            if (id == iterate->next->machineId)
            {
                return iterate; //required return this
            }

            iterate = iterate->next; //going to next

        } while (iterate != head); //again head not found

        iterate = NULL;
        return iterate;
    }

    //the next 
    machineNode<T>* giveNext(int id)
    {
        //for the iteration
        machineNode<T>* iterate = head;

        do
        {
            //if id matches
            if (id == iterate->machineId)
            {
                return iterate->next; //required return this
            }

            iterate = iterate->next; //going to next

        } while (iterate != head); //again head not found

        iterate = NULL;
        return iterate;
    }



};
