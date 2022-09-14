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
#include <queue>
#include <algorithm>
#include <list>
#include <cmath>
#include <optional>

using namespace std;

/* 
	***** Task 1 *****
	
	Check if exist path between two node in graf 
 */
class GrafDirect
{
    enum STATE { VISITED, UNVISITED, VISITING };
    struct Node 
    { 
        int node{}; 
        STATE state{STATE::UNVISITED};
    };
    
public:
    GrafDirect(const vector<vector<int>> grafMatrix)
    : grafMatrix(grafMatrix)
    {}
    
    /* search in width */
    bool existPathSerchInWidth(const int node1, const int node2)
    {
        if(not isCorrectIndex(node1, node2))
        {
            return false;
        }

        constexpr uint8_t existPath{1u};
        queue<Node> myQueue;
        vector<Node> nodes;
        
        iniGraf(nodes);
        
        myQueue.push(nodes[node1]); /* add to queue firs node */
        
        while(not myQueue.empty())
        {
            Node currentNode = myQueue.front();
            myQueue.pop(); /* delete node from queue */
            nodes[currentNode.node].state = STATE::VISITING;

            for(uint64_t i = 0; i < grafMatrix.size(); ++i)
            {
                if((existPath == grafMatrix[currentNode.node][i]) and (nodes[i].state != STATE::VISITED))
                {
                    if(nodes[i].state != STATE::VISITING)
                    {
                        nodes[i].state = STATE::VISITING;
                        myQueue.push(nodes[i]);
                    }
                    /* Check if exist path */
                    if(i == node2)
                    {
                        return true;
                    }
                }
            }
            nodes[currentNode.node].state = STATE::VISITED;
        }
        return false;
    }
    
    bool existPathSerchInDeep(const int node1, const int node2)
    {
        bool res{false};
        if(not isCorrectIndex(node1, node2))
        {
            return false;
        }

        vector<Node> nodes;
        iniGraf(nodes);
        return visitNode(nodes[node1], nodes, node2);
    }
 
 private:
 
    bool visitNode(Node& currentNode, vector<Node>& nodes, const int serchNode)
    {
        bool res{false};
        constexpr uint8_t existPath{1u};
        currentNode.state = STATE::VISITED;
        
        for(int i = 0; i < grafMatrix.size(); ++i)
        {
            if((grafMatrix[currentNode.node][i] == existPath) and (nodes[i].state != STATE::VISITED))
            {
                if(i == serchNode)
                {
                    return true;
                }
                else
                {
                    res = visitNode(nodes[i], nodes, serchNode);
                }
            }
        }
        return res;
    }
 
    bool isCorrectIndex(const int node1, const int node2)
    {
        bool res{true};
        if(node1 == node2)
        {
            res = false;
        }
        else if((grafMatrix.size() <= node1) or (grafMatrix.size() <= node2)) 
        {
            cout << "Wrong indexes" << endl;
            res = false;
        }
        return res;
    }
    
    void iniGraf(vector<Node>& nodes)
    {
        for(int i = 0; i < grafMatrix.size(); ++i)
        {
            nodes.push_back(Node{i,STATE::UNVISITED});
        }
    }
 
    vector<vector<int>> grafMatrix;
};

/*
	***** Task 2 *****
	
	Create Binary Tree with minimal deep for sorted array
 */
class TreeForSortedArray
{
private:
    struct Node
    {
        int data{0u};
        Node* left{nullptr};
        Node* right{nullptr};
        Node* perent{nullptr};
    };
    
public:
    TreeForSortedArray() = default;
    ~TreeForSortedArray()
    {
        clerNode(head);
    }
    
    void prepareTree(const vector<int>& sortedArray)
    {
        if(not sortedArray.empty())
        {
            head = prepareTreeWithRange(sortedArray, 0, sortedArray.size() - 1);
        }
        else
        {
            cout << "Get empty array" << endl;
        }
    }
    
    void print()
    {
        if(head)
        {
            printNode(head);
        }
        else
        {
            cout << "Empty tree" << endl;
        }
    }
    
private:
    Node* prepareTreeWithRange(const vector<int>& sortedArray,const long long start, const long long end)
    {
        if(end < start)
        {
            return nullptr;
        }
        
        auto itStart{ sortedArray.begin() + start };
        auto itEnd{ sortedArray.begin() + end };
        
        long long average { (end - start) / 2u };
        Node* tmp = new Node{*(itStart + average),nullptr, nullptr};
        
        tmp->left = prepareTreeWithRange(sortedArray, start, start + (average - 1));
        tmp->right = prepareTreeWithRange(sortedArray, start + (average + 1), end);
        
        return tmp;
    }
    
    void printNode(Node* node)
    {
        if(node)
        {
            printf("Node=%d\n", node->data);
            printNode(node->left);
            printNode(node->right);
        }
    }
    
    void clerNode(Node* node)
    {
        if(node)
        {
            clerNode(node->left);
            clerNode(node->right);
            delete node;
            node = nullptr;
        }
    }
    
    Node* head{nullptr};
};

/* 
	***** Task 4 *****
	
	For each level in binary tree create link list.
	For example if binary tree has 3 levels must be 3 link lists.
 */
 
class BinaryTreeWithListLevel
{
private:
    struct Node
    {
        int data{0u};
        Node* left{nullptr};
        Node* right{nullptr};
        Node* perent{nullptr};
    };
public:
    BinaryTreeWithListLevel() = default;
    
    ~BinaryTreeWithListLevel()
    {
        clearTree(head);
    }
    
    void add(const int data)
    {
        if(head)
        {
            addNodeToTree(head, data);
        }
        else
        {
            head = new Node{data, nullptr, nullptr, nullptr};
        }
    }
    
    void prepareLevelLinkLists(std::vector<std::list<int>>& data)
    {
        uint64_t level{1};
        prepareListInOneLevel(data, head, level);
    }
    
    /* To do: Check if binary tree is balancet */
    bool isBalancetTree()
    {
        bool res{true};
        if(head)
        {
            int64_t level{1u};
            getDeepOfNode(head, level, res);    
        }
        
        return res;
    }
    
    void print()
    {
        if(head)
        {
            printTree(head);
        }
        else
        {
            printf("\nEmpty tree");
        }
    }
    
	***** Task 4 *****
	
/*
	***** Task 5 *****

				return next node after given node.
                      Given Node (we here)
                     |                    \
                 left Node              Right node (get the most left node)     
      Flow: left -> given node -> right. Must be return 
      the most left node in right sub tree. If right sub tree
      don't exist return parent node (only if current node is from right sub tree)
*/
    optional<int> getNextNode(const int data)
    {
        Node* node{findNode(data, head)};
        if(node)
        {
            return {findNextNode(node)};
        }
        else
        {
            printf("\nNode don't exist");
            return {nullopt};
        }
    }
	
/* 
	***** Task 6 *****

	We have list of projects. Some projects depended from anothe project.
	Project can be add to list only after project from which it depend.
	Exaple: 
	Projects: a, b, c, d, e, f
	Dependency: (d,a), (b,f), (d,b), (a,f), (c,d)
	Result list: f, e, a, b, d, c
 */
    void prepareProjectDependency(
    const vector<string>& projects, 
    const vector<pair<string, string>>& dependency,
    vector<string>& res)
    {
        vector<pair<string, string>> dependencyProject(dependency);
        findEndependedProjects(res, projects, dependencyProject);
        while(projects.size() != res.size())
        {
            deleteDependency(res, dependencyProject);
        }
    }
    
    // Give two nodes. We must find joint parent for this nodes
    optional<int> findJointParent(const int firstNode,const int secondNode)
    {
        if(findNode(firstNode,head) and findNode(secondNode,head))
        {
            return{findJointParent(head, firstNode, secondNode)->data};
        }
        return {nullopt};
    }
    
    void getAllPossibleParentArray(vector<vector<int>>& res)
    {
        if(head)
        {
            prepareAllPossibleParentArray(head, res);
        }
        else
        {
            printf("\nEmpty tree");
        }
    }
    
private:

void prepareAllPossibleParentArray(const Node* node, vector<vector<int>>& res)
{
	vector<int> v1{50};
	vector<int> v2{45,55};
	vector<int> v3{35, 47, 52, 60};
	vector<int> v4{37, 56, 65};
#if NEW_ALG     
	std::queue<Node> treeQueue;
	treeQueue.push(*node);
	
	while(not treeQueue.empty())
	{
		Node currentNode{treeQueue.front()};
		treeQueue.pop();
		printf("\nDebug currentNode=%d", currentNode.data);
		if(currentNode.left)
		{
			treeQueue.push(*currentNode.left);
		}
		if(currentNode.right)
		{
			treeQueue.push(*currentNode.right);
		}
	}
#endif
}

    const Node* findJointParent(const Node* node,const int firstNode,const int secondNode)
    {
        if(node)
        {
            if(node->data == firstNode and node->data == secondNode)
            {
                return node;
            }
            
            const Node* x{findJointParent(node->left, firstNode, secondNode)};
            const Node* y{findJointParent(node->right, firstNode, secondNode)};
            
            if(x and x->data != firstNode and x->data != secondNode)
            {
                return x; /* Find res */
            }
            
            if(y and y->data != firstNode and y->data != secondNode)
            {
                return y; /* Find res */
            }
            
            if(node->data == firstNode or node->data == secondNode)
            {
                return node;
            }
            
            return (x and y) ? node : x ? x : y ? y : nullptr;
        }
        return nullptr;
    }
    
    void deleteDependency(vector<string>& res, vector<pair<string, string>>& dependency)
    {
        for(auto& project : res)
        {
            auto it {find_if(dependency.begin(), dependency.end(), [&](const pair<string, string>& arg){
                if(project == arg.second)
                {
                    if(res.back() != arg.first)
                    {
                        res.push_back(arg.first);
                    }
                    return true;
                }
                return false;
            })};
            
            if(it != dependency.end())
            {
                dependency.erase(it);
            }
        }
    }
    
    void findEndependedProjects(vector<string>& res,const vector<string>& projects,const vector<pair<string, string>>& dependency)
    {
        for(const auto& project : projects)
        {
            const auto it {find_if(dependency.begin(), dependency.end(), [&project](const pair<string, string>& arg)
            {
                return project == arg.first;
            })};
            
            if(it == dependency.end())
            {
                res.push_back(project);
            }
        }
    }

    optional<int> findNextNode(Node* node)
    {
        Node* nodeRes{nullptr};
        if(node->right)
        {
            return{getTheMostLeftNode(node->right)->data};
        }
        else
        {
            Node* currentNode{node};
            Node* parentNode{node->perent};
            printf("\ncurrentNode=%d perentNode=%d", currentNode->data, parentNode->data);
            while(parentNode and (parentNode->left != currentNode))
            {
                currentNode = parentNode;
                parentNode = parentNode->perent;
            }
            return{parentNode->data};
        }
        
        return{nullopt};
    }
    
    Node* getTheMostLeftNode(Node* node)
    {
        while(node->left)
        {
            node = node->left;
        }
        return node;
    }
    
    Node* findNode(const int data, Node* node)
    {
        if(node)
        {
            if(data == node->data)
            {
                return node;
            }
            Node* nodeLeft{findNode(data, node->left)};
            Node* nodeRight{findNode(data, node->right)};
            
            return nodeLeft ? nodeLeft : nodeRight ? nodeRight : nullptr;
        }
        return nullptr;
    }
    
    int64_t getDeepOfNode(const Node* node, int64_t level, bool& isBalanceTree)
    {
        if(node)
        {
            ++level;
            int64_t leftDeep{getDeepOfNode(node->left, level, isBalanceTree)};
            const bool isBalanceLeftNode{isBalanceTree};
            int64_t rightDeep{getDeepOfNode(node->right, level, isBalanceTree)};
            const bool isBalanceRightNode{isBalanceTree};
            const bool isCorrectDeep{ isBalanceLeftNode and isBalanceRightNode};
            
            if((std::abs(leftDeep - rightDeep) > 1) or (not isCorrectDeep))
            {
                isBalanceTree = false;
            }
            return std::max(leftDeep, rightDeep);
        }
        
        return level;
    }
    
    void printTree(Node* node)
    {
        if(node)
        {
            printf("Node=%d\t", node->data);
            printTree(node->left);
            printTree(node->right);
        }
    }

    void prepareListInOneLevel(std::vector<std::list<int>>& data, const Node* node, uint64_t level)
    {
        if(node)
        {
            if(data.size() < level)
            {
                std::list<int> mList;
                mList.push_back(node->data);
                data.push_back(std::move(mList));
            }
            else
            {
                data[level-1].push_back(node->data);
            }
            
            ++level;
            prepareListInOneLevel(data, node->left, level);
            prepareListInOneLevel(data, node->right, level);
        }
    }
    
    void addNodeToTree(Node* node, const int data)
    {
        if(node->data > data)
        {
            if(node->left)
            {
                addNodeToTree(node->left, data);
            }
            else
            {
                node->left = new Node{data, nullptr, nullptr, node};
            }
        }
        else
        {
            if(node->right)
            {
                addNodeToTree(node->right, data);
            }
            else
            {
                node->right = new Node{data, nullptr, nullptr, node};
            }
        }
    }
    
    void clearTree(Node* node)
    {
        if(node)
        {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
            node = nullptr;
        }
    }

    Node* head{nullptr};
};

int main()
{
    BinaryTreeWithListLevel tree;
    
    tree.add(50);
    tree.add(45);
    tree.add(35);
    tree.add(47);
    tree.add(37);
    tree.add(55);
    tree.add(52);
    tree.add(60);
    vector<vector<int>> allPossibleParentArray{};
    tree.getAllPossibleParentArray(allPossibleParentArray);
    
    return 0;
}
