/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstddef>
#include <vector>
#include <utility>
#include <cstdint>

using namespace std;

class MyLinkList
{
    struct Node
    {
        int data;
        Node* next;
    };
    
public:
    
    MyLinkList() = default;
    
    ~MyLinkList()
    {
        clear(head);
    }
    
    void push(int arg)
    {
        if(head)
        {
            Node* tail = head;
            while(true)
            {
                if(nullptr == tail->next)
                {
                    tail->next = new Node {arg, nullptr};
                    this->tail = tail->next;
                    break;
                }
                tail = tail->next;
            }
        }
        else
        {
            head = new Node{arg, nullptr};
        }
    }
    
/*
	***** Task 1 *****
	
	Delete all duplicates node. You can't use temporary buffer.
*/
    void deleteDuplicateHash()
    {
        if(head)
        {
            std::map<size_t,size_t> mMap;
            
            Node* currentNode = head;
            mMap[currentNode->data]++;
            
            while(currentNode->next)
            {
                mMap[currentNode->next->data]++;
                /* If node already exist when delete */
                if( mMap[currentNode->next->data] > 1 )
                {
                    Node* deletedNode = currentNode->next;
                    currentNode->next = currentNode->next->next;
                    delete deletedNode;
                    deletedNode = nullptr;
                    
                }
                else /* If dosent exist go to next */
                {
                    currentNode = currentNode->next;
                }
            }
        }
        
    }
    
    void deleteDuplicate()
    {
        if(head)
        {
            Node* firstIterator = head;
            Node* secondIterator = head;
            
            while(firstIterator->next)
            {
                while(secondIterator->next)
                {
                    if(secondIterator->next->data == firstIterator->data)
                    {
                        Node* deleteNode = secondIterator->next;
                        secondIterator->next = secondIterator->next->next;
                        delete deleteNode;
                        deleteNode = nullptr;
                    }
                    else
                    {
                        secondIterator = secondIterator->next;
                    }
                }
                firstIterator = firstIterator->next;
                secondIterator = firstIterator;
                if(not firstIterator)
                {
                    break;
                }
            }
        }
    }
	
/*
	***** Task 2 *****
	
	Write algorithm for find k-element from the end list.
	Example: 1->2->3->4->5: k=2; Algorithm must return 4
*/
    void getElemFromBack(const int k)
    {
        if(head)
        {
            int res{0};
            if(0 == k)
            {
                res = head->data;
            }
            else
            {
                int index{0};
                Node* node = getIndex(head, index, k);
                if(node)
                {
                    res = node->data;
                }
            }
            cout << "This elem has data=" << res << endl;
        }
        else
        {
            cout << "Empty List" << endl;
        }
    }
    
/*
	***** Task 3 *****
	
	Implement an algorithm that removes a node from the middle of a singly linked list 
	(that is, a node that is neither the start nor the end - not necessarily exactly 
	in the middle). Access is granted only to this node.

	Example: 
	Input: node "с" from list a->b->c->d->e ->f 
	Output: nothing is returned, but the new list looks: a->b->d- >e->f 
*/
    void deleteNodeByIndex(const int index)
    {
        Node* node = getElemByIndex(index);
        if(node)
        {
            Node* deletedNode = node->next;
            node->data = deletedNode->data;
            node->next = deletedNode->next;
            delete deletedNode;
            deletedNode = nullptr;
        }
    }
    
/*
	***** Task 4 *****

	Write code to split a linked list around the value "x" so that all nodes less than "x" 
	precede nodes greater than or equal to "x". If x is contained in a list, then the values 
	of x must come exactly after elements less than "x"

	Example: 
	Input: 3->5->8->5- >10->2->1 [value "x" = 5] 
	Output: 3 ->1->2->10->5->5->8
*/
    void sortListWithMiddleValue(const int value)
    {
        Node* headForListWithLessElem = nullptr;
        Node* headForListWithHigheElem = nullptr;
        Node* currentNodeForListWithLessElem = nullptr;
        Node* currentNodeForListWithHigheElem = nullptr;
        Node* currentNode = head;
        
        if(currentNode)
        {
            /* Fill List with less & high elements */
            while(currentNode)
            {
                if(currentNode->data < value)
                {
                    if(not headForListWithLessElem)
                    {
                        headForListWithLessElem = currentNode;
                        currentNodeForListWithLessElem = headForListWithLessElem;
                    }
                    else
                    {
                        currentNodeForListWithLessElem->next = currentNode;
                        currentNodeForListWithLessElem = currentNodeForListWithLessElem->next;
                    }
                }
                else
                {
                    if(not headForListWithHigheElem)
                    {
                        headForListWithHigheElem = currentNode;
                        currentNodeForListWithHigheElem = headForListWithHigheElem;
                    }
                    else
                    {
                        currentNodeForListWithHigheElem->next = currentNode;
                        currentNodeForListWithHigheElem = currentNodeForListWithHigheElem->next;
                    }
                }
                
                currentNode = currentNode->next;
            }
            
            // set "next" in latest elem to nullptr
            currentNodeForListWithLessElem->next = nullptr;
            currentNodeForListWithHigheElem->next = nullptr;
            Node* latestElemInListWithLessElem = currentNodeForListWithLessElem; /* save latest elem */

            if(latestElemInListWithLessElem)
            {
                 /* combine 2 list's */
                head = headForListWithLessElem;
                latestElemInListWithLessElem->next = headForListWithHigheElem;
            }
            else
            {
                cout << "List has not less elem from main value" << endl;
            }
        }
        else
        {
            cout << "Empty List" << endl;
        }
    }
    
    /*
		***** Task 5 *****
    
	The two numbers are stored as linked lists, with each node representing one digit. 
	All digits are stored in reverse order, with the least significant digit (ones) 
	stored at the beginning of the list. Write a function that sums two numbers and 
	returns the result as a linked list
	
    Example: 
    Input: (7->1->6) + (5->9->2),  617 + 295. 
    Output: 2->1->9,  912.
	
    Extra task 
    Solve the problem assuming the numbers are written in direct order.
	
	Example:
    Input: (6->1 ->7) + (2->9->5), то есть 617 + 295. 
    Output: 9->1->2, то есть 912. 
    */
    
    uint64_t sumTwoLists(const MyLinkList& list1, const MyLinkList& list2, const bool isSmallValueInHead)
    {
        uint64_t res { convertListToValue_smallValueInHead(list1) + convertListToValue_smallValueInHead(list2) };
        if(not isSmallValueInHead)
        {
            string tempStr { to_string(res) };
            string valInStr;
            std::copy(tempStr.rbegin(), tempStr.rend(), valInStr.begin());
            res = std::stoi(valInStr);
        }
        return res;
    }
    
	
/*
	***** Task 5 *****

	Check if current list is polindrom 
*/
    
    bool isPolindrom()
    {
        bool res {true};
        Node* reverseList = nullptr;
        if(head)
        {
            /* allocate memory for List */
            reverseList = prepareReverseList(head);
            Node* currentNode = head;

            while(currentNode)
            {
                if(currentNode->data != reverseList->data)
                {
                    res = false;
                    break;
                }
                currentNode = currentNode->next;
                reverseList = reverseList->next;
            }
        }
        else
        {
            res = false;
            cout << "Empty List" << endl;
        }
        
        clear(reverseList);
        return res;
    }
    
/*
	***** Task 6 *****

	There are 2 list. Return pointer to Node where this lists intersect.
	Otherway return nullptr
*/
    Node* isListsIntersect()
    {
        MyLinkList list1;
        MyLinkList list2;
        MyLinkList list3;
        prepareIntersectLists(list1, list2);
        
        Node* res = nullptr;
        Node* currentNodeInList1 = list1.head;
        Node* currentNodeInList2 = list2.head;
        
        while(currentNodeInList1)
        {
            if(currentNodeInList1 == currentNodeInList2)
            {
                res = currentNodeInList1;
                break;
            }
            currentNodeInList1 = currentNodeInList1->next;
            
            if(currentNodeInList2)
            {
                currentNodeInList2 = currentNodeInList2->next;
            }
            else
            {
                cout << "Empty list2" << endl;
                break;
            }
        }
        
        clear(list1.head);
        clear(list2.head);
        return res;
    }
    
/*
	***** Task 7 *****
	
	There is list.This list tail point to some Node in this list (circular list).
	Find Node from which begin circular movement
*/
    Node* getFirstCircularNodeInCircularList()
    {
        bool listIsCircular{false};
        MyLinkList list;
        prepareCircularList(list);
        Node* fastIterator = list.head;
        Node* slowIterator = list.head;
        
        while(fastIterator->next and fastIterator->next->next)
        {
            fastIterator = fastIterator->next->next;
            slowIterator = slowIterator->next;
            
            if(fastIterator == slowIterator)
            {
                listIsCircular = true;
                break;
            }
        }
        
        if(not listIsCircular)
        {
            cout << "List is not circular" << endl;
            return nullptr;
        }
        
        slowIterator = list.head;
        int i = 10;
        while(i)
        {
            if(fastIterator == slowIterator)
            {
                return fastIterator;
            }
            slowIterator = slowIterator->next;
            fastIterator = fastIterator->next;
        }
        
        return nullptr;
    }

private:

    void prepareCircularList(MyLinkList& list)
    {
        Node* pointAtCircularNode = nullptr;
        list.push(1);
        list.push(2);
        list.push(3);
        pointAtCircularNode = list.tail;
        list.push(4);
        list.push(5);
        list.push(6);
        list.push(7);
        list.tail->next = pointAtCircularNode;
    }

/*
	Utils
*/

    void prepareIntersectLists(MyLinkList& list1, MyLinkList& list2)
    {
        Node* pointListsCrossRoad{nullptr};
        /* fill list1 */
        list1.push(1);
        list1.push(2);
        list1.push(3);
        list1.push(4);
        pointListsCrossRoad = list1.tail;
        list1.push(5);
        list1.push(6);
        list1.push(7);
        /* fill list2 */
        list2.push(8);
        list2.push(9);
        list2.push(10);
        list2.tail->next = pointListsCrossRoad;
        list2.print();
        cout << "intersect adress: " << pointListsCrossRoad << endl;
    }

    Node* prepareReverseList(Node* currentNode)
    {
        static Node* reverseHead = nullptr;
        static uint64_t listSize {0u};
        
        if(nullptr == currentNode)
        {
            return nullptr;
        }
        ++listSize;
        Node* temp = prepareReverseList(currentNode->next);
        
        if(nullptr == temp)
        {
            reverseHead = new Node;
            reverseHead->data = currentNode->data;
            --listSize;
            return reverseHead;
        }
        else
        {
            Node* nodeClone = new Node{ currentNode->data, nullptr };
            temp->next = nodeClone;
            --listSize;
            return (0u == listSize) ? reverseHead : nodeClone;
        }
        
    }

    uint64_t convertListToValue_smallValueInHead(const MyLinkList& list)
    {
        uint8_t incrementForIndex{10u};
        uint64_t res {0u};
        uint64_t index{1u};
        Node* currentNode = list.head;
        
        while(currentNode)
        {
            res += currentNode->data * index;
            currentNode = currentNode->next;
            index *= incrementForIndex;
        }
        return res;
    }

    Node* getElemByIndex(const int index)
    {
        if(head)
        {
            int currentIndex{0};
            Node* currentNode = head;
            while(currentNode)
            {
                if(currentIndex == index)
                {
                    return currentNode;
                }
                ++currentIndex;
                currentNode = currentNode->next;
            }
            cout << "Given wrong index" << endl;
            return nullptr;
        }
        else
        {
            cout << "Empty List" << endl;
        }
    }
    
    Node* getIndex(Node* currentNode, int& counter, const int k)
    {
        static int sizeList{0};
        static int counterForSizeList{0};
        
        if(not currentNode)
        {
            sizeList = counterForSizeList;
            cout << "sizeList=" << sizeList << endl;
            return nullptr;
        }
        
        counterForSizeList++;
        Node* node = getIndex(currentNode->next, counter, k);
        ++counter;
        
        if(counter == k)
        {
            cout << "Find index" << endl;
            return currentNode;
        }
        
        if(sizeList <= counter + 1)
        {
            cout << "Geven wrong index" << endl;
            counter = 0;
            return nullptr;
        }
        
        return node;
    }
    
public:    
    void print()
    {
        if(head)
        {
            Node* currentNode = head;
            while(currentNode->next)
            {
                std::cout << "data=" << currentNode->data << std::endl;
                currentNode = currentNode->next;
            }
            std::cout << "data=" << currentNode->data << std::endl;
        }
        else
        {
            cout << "Cleat List" << endl;
        }
    }
    
    void clear(Node* head)
    {
        if(head)
        {
            Node* currentNode = head;
            
            if(currentNode->next)
            {
                Node* deleteNode;
                
                while(currentNode->next)
                {
                    deleteNode = currentNode;
                    currentNode = currentNode->next;
                    delete deleteNode;
                    deleteNode = nullptr;
                    if(tail == currentNode)
                    {
                        break;
                    }
                }
            }
            else
            {
                delete currentNode;
            }
            head = nullptr;
        }
    }
private:
    Node* head{nullptr};
    /* tail define only for prepare intersect lists. In other methods you can't use this value */
    Node* tail{nullptr};
};

int main()
{
    
    return 0;
}

