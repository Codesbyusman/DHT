#pragma once
#include <iostream>
#include "LinkedList.h"

using namespace std;

//the data to hold key and value --- key value pair
struct Data
{
   
   int id; //to hold the id -- orginal
   string  value;
};

template <class T>
struct avlNode
{
    int key; //hash generated
    Linklist<Data> nodeDataList; //the list of data to contain collided data also
    avlNode<T>* leftChild;
    avlNode<T>* rightChild;

    //at starting making the childs null
    avlNode()
    {
        key = -1;
        leftChild = rightChild = NULL;
    }
};

template <class T>
class avlTree
{
private:
    //the root of the tree --- starting point
    avlNode<T>* root;

    //for displaying the preorder
    void dispalyPreOrder(avlNode<T>* node)
    {
        //if not null then print
        if (node != NULL)
        {
            //the temp node
            Data tempNode;

            //creating a copy of avl node ist
            Linklist<Data> tempList = node->nodeDataList;
            cout << "\n\n\t\t :::::::::::: Avl Node " << node->key << " :::::::::::: " << endl;//after displaying key will display the whole data in the node
            
            if (!tempList.isEmpty())
            {
                //starting from head
                while (!tempList.isEmpty())
                {
                    tempNode = tempList.returnLast();
                    tempList.deleteNode(); //deleting last 

                    //displaying the data
                    cout << "\n\t\t ::::::::: " << tempNode.id << "  " << tempNode.value << " ::::::::::::::" << endl;
                }
            }
            else
            {
                cout << " Empty " << endl;
            }
            
            dispalyPreOrder(node->leftChild);
            dispalyPreOrder(node->rightChild);
        }
    }

    //the finding of deleting node and deleting that
    void deleteNode(int key, avlNode<T>*& temp)
    {
        //for storing balnace factor
        int balanceFactor = 0;

        //node does not exist in the tree
        if (temp == NULL)
        {
            cout << key << " key not found\n" << endl;
        }
        else if (key < temp->key)
        {
            // find in left subtree
            deleteNode(key, temp->leftChild);
        }

        else if (key > temp->key)
        {
            // find in right subtree
            deleteNode(key, temp->rightChild);
        }
        else
        {
            //actually deletes node from BST
            deleteMe(temp);

        }

        //if no node all tree deleted no need to do furthur
        if (root == NULL)
        {
            return;
        }

        //after deleting node now checking balnace of each node and applying the rotation accordingly
        balanceFactor = findHeight(temp->leftChild) - findHeight(temp->rightChild);

    }

    //delete the entered node
    void deleteMe(avlNode<T>*& toDelete)
    {
        avlNode<T>* temp; // Temperary pointer

        //if right not exist than only left child exist
        if (toDelete->rightChild == NULL)
        {
            temp = toDelete; //assigning one to delete
            toDelete = toDelete->leftChild;  //assiging to left child === left child
            delete temp; //deleting leaf
        }
        else if (toDelete->leftChild == NULL) //if was on right 
        {

            temp = toDelete; //assigning one to delete
            toDelete = toDelete->rightChild; //assign to right
            delete temp;
        }
        else
        {
            //if the both are there
            temp = toDelete->rightChild;

            //finding the place in the left most side of right tree
            while (temp->leftChild)
            {
                temp = temp->leftChild;
            }

            //now assiging the child to left
            temp->leftChild = toDelete->leftChild; //if any of left child of deleting was there was added to rights childs left most side

            //now assigning the one to delete
            temp = toDelete;
            toDelete = toDelete->rightChild; //will be change when recursion will be done and will be assign to the previous one
            delete temp; //delete the temp that contains the deleteing node
        }
    }

public:
    //initallay no tree
    avlTree()
    {
        root = NULL;
    }

    //for checking the height
    //height from a specified node --- specific child
    //will find recursively
    int findHeight(avlNode<T>* strt)
    {
        //for storing the depth of left and right and will return accordingly so that may contribute next
        int deepl = 0, deepr = 0;

        //go till leaf
        if (strt == NULL)
        {
            //no length --- the null
            return -1;
        }

        //call again --- and find length in deepl(left) and deepr(right)
        deepl = findHeight(strt->leftChild);  //left depth
        deepr = findHeight(strt->rightChild); //right depth

        //now checking which will contribute
        if (deepl >= deepr)
        {
            //if the left height is greater or equal to the right depth
            //adding 1 to left depth returned as connected to the current iteration node and returning
            return (deepl + 1);
        }
        else
        {
            //if the right height is greater  to the left depth
            //adding 1 to left depth returned as connected to the current iteration node
            return (deepr + 1);
        }
    }

    //the insert function
    void insert(Data data, int HashId)
    {
        root = insert(root, data, HashId);
    }

    void insert(avlNode<T>* data)
    {
        int i = data->key;
        Data d = data->nodeDataList.returnLast();

        root = insert(root, d, i);

    }

    //recursive insertion
    avlNode<T>* insert(avlNode<T>* start, Data data, int hashId)
    {
      
        int balanceFactor = 0; //balance factor

        //base case --- if null the palace to insert
        if (start == NULL)
        {
           
           
            //insert the data
            avlNode<T>* newData = new avlNode<T>;
            newData->nodeDataList.insert(data);
            newData->key = hashId;

            
            start = newData;

            return start;
        }

        //now seeing insertion place and rotating if needed
        if (hashId < start->key)
        {

            //go to left subtree
            start->leftChild = insert(start->leftChild, data, hashId);

            //in the recusrion checking whether on the same level after insertion
            //the node is unbalnce or not ... if unbalance than the rotation will be done accordingly
            //checking the balnce factor and storing
            balanceFactor = findHeight(start->leftChild) - findHeight(start->rightChild);

            //if the balance factor is 2 as left - right mean 2 the left sub tree heavy -- right rotation
            if (balanceFactor == 2)
            {
                //if the data inserted is less than the parent node
                //i.e the leaf data < parent than left most then only right rotation else double
                if (hashId < start->leftChild->key)
                {
                    return rightRotation(start); //the single right rotation
                }
                else
                {
                    //RL rotation first rotated right the left sub child of unbalanced node then right to node
                    start->leftChild = leftRotation(start->leftChild);
                    return rightRotation(start);
                }
            }
        }
        else if (hashId > start->key)
        {
            //go to right subtree
            start->rightChild = insert(start->rightChild, data, hashId);

            //in the recusrion checking whether on the same level after insertion
            //the node is unbalnce or not ... if unbalance than the rotation will be done accordingly
            //checking the balnce factor and storing
            balanceFactor = findHeight(start->rightChild) - findHeight(start->leftChild);

            //the unbalanced is caused as right - left results 2 mean left - right = -2 --- means right subtree heavy
            //the left rotation will be done
            if (balanceFactor == 2)
            {
                //if the data is on the right most side only single rotation
                //if leaf node > then the parent mean on right most then only single
                if (hashId > start->rightChild->key)
                {
                    //LL single left rotation
                    return leftRotation(start);
                }
                else
                {
                    //LR the first right rotation to right child of unbalanced and then left to unbalanced
                    start->rightChild = rightRotation(start->rightChild);
                    return leftRotation(start);
                }
            }
        }
        else
        {
            //nothing to insert case as the duplicate found
            //and duplicate not allowed in standard bst or avl trees
            //but this can be collision if it is collision then will add in the node as a linked list
            //the current node has that 
            start->nodeDataList.insert(data); // will insert data next to the already entered head
            return start;
        }

        //returning the start that has been inserted abd corrected after rotation
        return start;
    }

    //left rotation to rotate left
    avlNode<T>* leftRotation(avlNode<T>* unbalanced)
    {

        //now rotating left
        avlNode<T>* childRight = unbalanced->rightChild; //the one which will be returned
        avlNode<T>* already = childRight->leftChild;     //if any left exist
        childRight->leftChild = unbalanced;
        unbalanced->rightChild = already;

        return childRight;
    }

    //right rotation to rotate right
    avlNode<T>* rightRotation(avlNode<T>* unbalanced)
    {

        //now rotating right
        avlNode<T>* childLeft = unbalanced->leftChild; //the one which will be returned
        avlNode<T>* already = childLeft->rightChild;   //if any right exist
        childLeft->rightChild = unbalanced;
        unbalanced->leftChild = already;

        return childLeft;
    }

    //will display pre oroder  ---- a container for recursive function
    void displayPreOder()
    {
        if (root != NULL)
        {
            dispalyPreOrder(root);
        }
        else
        {
            cout << " Empty " << endl;
        }
    }

    //doing the bst deletion 
    //and after deleting one node than rotating accordingly to balnace if unbalanced occur
    void deleteNode(int key)
    {
        //the recursive function call that will delee the node
        //and the node will be passed by reference so deletion make in any level should be changed
        deleteNode(key, root);
    }

    //the recursive function if data found will be returning the node where data can be
    bool findMe(const int hashId, avlNode<T>* start, avlNode<T> *& required)
    {
        
        if ( start != NULL && start->key == hashId )
        {
            //the data stored in has found --- this node willcontain data 
            //before returning also taking the the data block
            required = start;

            return true;
        }

        //if not than will traverse in sunb trees accordingly
        if (start != NULL && hashId < start->key)
        {
            //finding in left subtree
            if (start->leftChild != NULL)
            {
               return  findMe(hashId, start->leftChild, required);

            }
            else
            {
                return false;
            }
        }
        else  if (start != NULL)
        {
            //finding in right subtree
            if (start->leftChild != NULL)
            {
                return findMe(hashId, start->rightChild, required);

            }
            else
            {
                return false;
            }
        }

        return false; //data not found

    }

    //for finding the data in avl tree
    bool findMe(const int hashId , avlNode<T> *& required)
    {
        if (root == NULL)
        {
            return false;
        }

        if (!(root->leftChild == NULL && root->rightChild == NULL))
        {
            //callling recursive function
            return findMe(hashId, root, required);
        }
        else
        {
            if (hashId == root->key)
            {
                
                required = root; //if finding was the node
                return true;
            }
        }
        
    }

    //finding in the list of node
    bool findinList(const int orgId, Linklist<Data> findIn , Data & displayData)
    {
        if (!findIn.isEmpty())
        {
            //the temporary 
            Data tempData;

            while (!findIn.isEmpty())
            {
                tempData = findIn.returnLast();

                //checking the data 
                if (orgId == tempData.id)
                {
                    //also updating the data structure passed
                    displayData = tempData;
                    return true; //the data also found
                }
                
                //deleting the last and traversing again last as will be updated
                findIn.deleteNode();
            }
            

            return false; //not in the list
        }
        else
        {
            return false; //the list was empty thus no data
        }
    }

    //for displaying specific node data
    void displayNode(avlNode<T> node)
    {

        //if not null then print
        if (node != NULL)
        {
            //the temp node
            Data tempNode;

            //creating a copy of avl node ist
            Linklist<Data> tempList = node->nodeDataList;
            cout << "\n\n\t\t  :::::::::::: Avl Node " << node->key << " :::::::::::: " << endl;//after displaying key will display the whole data in the node

            if (!tempList.isEmpty())
            {
                //starting from head
                while (!tempList.isEmpty())
                {
                    tempNode = tempList.returnLast();
                    tempList.deleteNode(); //deleting last 

                    //displaying the data
                    cout << "\n\t\t ::::::::: " << tempNode.id << "  " << tempNode.value << " ::::::::::::::" << endl;
                }
            }
            else
            {
                cout << " Empty " << endl;
            }
        }
        

    }

    //populating list
    void populate(avlNode<T>* start, Linklist<avlNode<T>*>& tempList)
    {
        if (start != NULL)
        {
            //storing the nodes in linked list
            tempList.insert(start);
            populate(start->leftChild, tempList);
            populate(start->rightChild, tempList);

        }
    }

    //for populating the linked list
    bool updateList(Linklist<avlNode<T>*>& listPopulating)
    {
        //seeing if tree is empty mean nothing
        if (root == NULL)
        {
            return false; //no tree
        }

        //will iterate recursively and will populate 
        populate(root, listPopulating);

        return true;
    }

    void nullHead()
    {
        root = NULL;
    }

};
