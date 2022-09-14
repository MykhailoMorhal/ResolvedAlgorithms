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
#include <type_traits>
#include<bits/stdc++.h>

using namespace std;

/*
	Utils
	Own Implementation of Queue and Stack
*/

class MyQueue
{
private:
    struct Node
    {
        Node() = default;
        Node(const int data_, Node* next_) 
            : data(data_), next(next_){}
        int data{};
        Node* next{nullptr};
    };
public:
    
    ~MyQueue()
    {
        clean();
    }
    
    void push(const int data)
    {
        if(latest)
        {
            Node* temp = new Node{data,nullptr};
            latest->next = temp;
            latest = latest->next;
            
        }
        else
        {
            Node* temp = new Node{data,nullptr};
            first = temp;
            latest = first;
        }
    }
    
    int pop()
    {
        int res{};
        if(first)
        {
            res = first->data;
            Node* deleteNode = first;
            first = first->next;
            delete deleteNode;
            deleteNode = nullptr;
        }
        else
        {
            cout << "Empty Queue" << endl;
        }
        return res;
    }
    
    int get()
    {
        int res{};
        if(first)
        {
            res = first->data;
        }
        else
        {
            cout << "Empty Queue" << endl;
        }
        return res;
    }
    
    bool isEmpty()
    {
        return first ? true : false; 
    }
    
    void clean()
    {
        Node* currentNode = first;
        if(currentNode)
        {
            Node* deleteNode = first;
            first = first->next;
            delete deleteNode;
            deleteNode = nullptr;
        }
        else
        {
            cout << "Empty Queue" << endl;
        }
    }
    
    void print()
    {
        Node* currentNode = first;
        if(currentNode)
        {
            while(currentNode)
            {
                cout << "Data=" << currentNode->data << endl;
                currentNode = currentNode->next;
            }
        }
        else
        {
            cout << "Empty Queue" << endl;
        }
    }
    
private:
    Node* first{nullptr};
    Node* latest{nullptr};
};

class MySteck
{
private:
    struct Node
    {
        Node() = default;
        Node(int data_, Node* node_)
        : data(data_), next(node_){}
        
        int data{};
        Node* next{nullptr};
    };
    
public:
    
    MySteck() = default;
    
    MySteck& operator=(MySteck&& data)
    {
        if(this != &data)
        {
            if(not isEmpty())
            {
                clean();
            }
            
            if(data.top)
            {
                copyStack(data.top);
                data.clean();
            }
            
        }
    }
    
    MySteck(const MySteck& data)
    {
        if(not isEmpty())
        {
            clean();
        }
        
        if(data.top)
        {
            copyStack(data.top);
        }
    }
    
    MySteck& operator=(const MySteck& data)
    {
        if(not isEmpty())
        {
            clean();
        }
        
        if(data.top)
        {
            copyStack(data.top);
        }
        
        return *this;
    }
    
    ~MySteck()
    {
        clean();
    }
    
    int pop()
    {
        int res{};
        if(top)
        {
            res = top->data;
            Node* delateNode = top;
            top = top->next;
            delete delateNode;
            delateNode = nullptr;
            
            if(topMinElems and (res == topMinElems->data))
            {
                Node* deleteNodeMin = topMinElems;
                topMinElems = topMinElems->next;
                delete deleteNodeMin;
                deleteNodeMin = nullptr;
            }
        }
        else
        {
            cout << "Stack is empty" << endl;
        }
        return res;
    }
    
    void push(const int data)
    {
        if(top)
        {
            Node* temp = top;
            top = new Node(data, temp);
            
            if(data < topMinElems->data)
            {
                Node* tempMin = topMinElems;
                topMinElems = new Node{data, tempMin};
            }
        }
        else
        {
            top = new Node(data, nullptr);
            topMinElems = new Node{data, nullptr};
        }
        
    }
    
    int get()
    {
        int res{};
        if(top)
        {
            res = top->data;  
        }
        else
        {
            cout << "Empty Stack" << endl;
        }
        return res;
    }
    
    void print()
    {
        Node* currentNode = top;
        if(currentNode)
        {
            while(currentNode)
            {
                cout << "Node=" << currentNode->data << endl;
                currentNode = currentNode->next;
            }
        }
        else
        {
            cout << "Empty Steck" << endl;
        }
    }
    
/*
	***** Task 1 *****
	
	Write implementation for get minimal element 
	from Stack O(1) time.
*/
    int getMinElem()
    {
        int res{};
        
        if(topMinElems)
        {
            res = topMinElems->data;
        }
        else
        {
            cout << "Empty Steck" << endl;
        }
        return res;
    }
    
    bool isEmpty(){ return nullptr == top; }

private:

    void copyStack(Node* dataTop)
    {
        top = new Node{dataTop->data, nullptr};
        topMinElems = new Node{dataTop->data, nullptr};
        Node* currentNodefromData = dataTop->next;
        Node* currentNode = top;
        while(currentNodefromData)
        {
            Node* temp = new Node{currentNodefromData->data, nullptr};
            // Fill min elems
            if(topMinElems->data > currentNodefromData->data)
            {
                Node* tempMin = topMinElems;
                topMinElems = new Node{currentNodefromData->data, tempMin};
            }
            //
            currentNode->next = temp;
            currentNode = currentNode->next;
            currentNodefromData = currentNodefromData->next;
        }
    }

    void clean()
    {
        Node* currentNode = top;
        if(currentNode)
        {
            while(currentNode)
            {
                Node* deleteNode = currentNode;
                currentNode = currentNode->next;
                delete deleteNode;
                deleteNode = nullptr;
            }
            cleanMinElems();
            top = nullptr;
        }
    }
    
    void cleanMinElems()
    {
        Node* currentNode = topMinElems;
        
        if(currentNode)
        {
            while(currentNode)
            {
                Node* deleteNode = currentNode;
                currentNode = currentNode->next;
                delete deleteNode;
                deleteNode = nullptr;
            }
        }
        else
        {
            cout << "Empty Steck with min elements" << endl;
        }
    }

    Node* top{nullptr};
    Node* topMinElems{nullptr};
};

/* 
	***** Task 2 *****
	
	Sort Stack. 
    Remark: You can use us temporary container only another one Stack 
*/
void sortStack(MySteck& mySteck)
{
    MySteck stackRes;
    int currentData;
    int temp;
    bool firstIni{true};

    if(not mySteck.isEmpty())
    {
        stackRes.push(mySteck.pop());
        
        while(not mySteck.isEmpty())
        {
            currentData = mySteck.pop();
            
            while(currentData > stackRes.get())
            {
                temp = stackRes.pop();
                mySteck.push(temp);
                if(stackRes.isEmpty())
                {
                    break;
                }
            }
            stackRes.push(currentData);
        }
        
        mySteck = stackRes;
    }
    else
    {
        cout << "Try to sort empty Stack" << endl;
    }
}

/*
	***** Task 3 *****
	
	Write special Stack. When elements in Stack
	more 5 create new simply Stack. Write special
	method popAt() which get and delete element from
	certain Stack
*/
class StackOfStack
{
public:
    void push(const int data)
    {
        if(vectorWithMyStacks.empty())
        {
            setFirstStack(data);
        }
        else
        {
            setDataToStack(data);
        }
    }
    
    int pop()
    {
        int res{};
        
        if(vectorWithMyStacks.empty())
        {
            cout << "Empty Stack" << endl;
        }
        else
        {
            res = vectorWithMyStacks.back().pop();
            stacksSizes[currentStack]--;
            if(0u == stacksSizes[currentStack])
            {
                stacksSizes.pop_back();
                --currentStack;
                vectorWithMyStacks.pop_back();
            }
            
        }
        return res;
    }
    
    int popAt(const uint64_t stackNumber)
    {
        int res{};
        if(vectorWithMyStacks.size() > stackNumber)
        {
            res = vectorWithMyStacks[stackNumber].pop();
            stacksSizes[stackNumber]--;
            stacksWithEmptyPlaces.push_back(stackNumber);
            if(0u == stacksSizes[stackNumber])
            {
                stacksSizes.erase(stacksSizes.begin()+stackNumber);
                --currentStack;
                vectorWithMyStacks.erase(vectorWithMyStacks.begin()+stackNumber);
                removeStackWithEmptyPlaces(stackNumber);
            }
        }
        else
        {
            cout << "Set wrong Stack index" << endl;
        }
    }
    
    void print()
    {
        if(not vectorWithMyStacks.empty())
        {
            uint64_t index{1u};
            for(auto& stack : vectorWithMyStacks)
            {
                cout << "Print stack:"<< index << endl;
                cout << "-----------" << endl;
                stack.print();
                ++index;
            }
        }
        else
        {
            cout << "Empty Steck" << endl;
        }
    }
private:

    void removeStackWithEmptyPlaces(const uint64_t stackNumber)
    {
        uint8_t needDeleteElem{0u};
        const auto it { std::remove_if(stacksWithEmptyPlaces.begin(), stacksWithEmptyPlaces.end(), 
                                                        [&](const auto& elem)
                                                        { 
                                                            ++needDeleteElem; 
                                                            return elem == stackNumber; 
                                                        }) };
        while(needDeleteElem--)
        {
            stacksWithEmptyPlaces.pop_back();
        }
    }
    
    void setDataToStack(const int data)
    {
        const bool hasEmptyPlaceInStacks { not stacksWithEmptyPlaces.empty() };
        
        if(hasEmptyPlaceInStacks)
        {
            const uint64_t indexLatestStackWithEmptyPlace { stacksWithEmptyPlaces.back() };
            stacksWithEmptyPlaces.pop_back();
            vectorWithMyStacks[indexLatestStackWithEmptyPlace].push(data);
            stacksSizes[indexLatestStackWithEmptyPlace]++;
        }
        else
        {
            // if steck full create new stack
            if(stacksSizes[currentStack] >= maxSizeInStack)
            {
                setFirstStack(data);
                ++currentStack;
            }
            else
            {
                vectorWithMyStacks.back().push(data);
                stacksSizes[currentStack]++;
            }
        }
        
    }

    void setFirstStack(const int data)
    {
        MySteck mySteck;
        mySteck.push(data);
        stacksSizes.push_back(1u);
        vectorWithMyStacks.push_back(mySteck);
    }
    
    
    vector<MySteck> vectorWithMyStacks;
    vector<uint64_t> stacksSizes;
    vector<uint64_t> stacksWithEmptyPlaces;
    uint64_t currentStack{0u};
    uint8_t maxSizeInStack{3u};
};

/*
	***** Task 4 *****
	
	Implement Queue at base on 2 stacks 
*/
class MyQueueStacks
{
public:
    MyQueueStacks() = default;
    
    void push(const int data)
    {
        steckWithNewElems.push(data);
    }
    
    int pop()
    {
        int res{};
        
        if(isEmpty())
        {
            cout << "Try to get elem from empty Queue" << endl;
            return res;
        }
        
        if(steckWithOldElems.isEmpty())
        {
            /* Move elems from steckWithNewElems */
            while(not steckWithNewElems.isEmpty())
            {
                steckWithOldElems.push(steckWithNewElems.pop());
            }
        }
        
        res = steckWithOldElems.pop();
    }
    
    bool isEmpty()
    {
        return steckWithOldElems.isEmpty() and steckWithNewElems.isEmpty();
    }
    
    void print()
    {
        if(not steckWithNewElems.isEmpty())
        {
            cout << "======= Print StackNew =======" << endl;
            steckWithNewElems.print();
        }
        
        if(not steckWithOldElems.isEmpty())
        {
            cout << "======= Print StackOld =======" << endl;
            steckWithOldElems.print();
        }
    }
    
private:
    MySteck steckWithNewElems;
    MySteck steckWithOldElems;
};

int main()
{
    MySteck mySteck;
    mySteck.push(3);
    mySteck.push(1);
    mySteck.push(8);
    mySteck.push(5);
    mySteck.push(2);
    mySteck.push(2);
    sortStack(mySteck);
    
    return 0;
}

