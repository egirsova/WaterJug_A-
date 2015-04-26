//
//  Domain.cpp
//  WaterJug_A*
//
//  Created by Liza Girsova on 10/23/14.
//  Copyright (c) 2014 CMSC470. All rights reserved.
//

#include "Domain.h"
#include <string>
#include <list>
#include <vector>

using namespace std;

// Templated constructor for Node
template<typename T, typename S> Node::Node(T state, S function, int cost, Node* parent){
    Node::state = state;
    Node::function = function;
    Node::cost = cost;
    Node::parent = parent;
}

// Successor function generates the potential nodes
list<Node> Domain::successorFn(Node* currentNode, Node* parentNode, list<Node> nodeStore){
    list<Node> possibleStates;  // Temporary list that stores the states
    list<Node>::iterator itr;
    
    vector<int> tempVector(3);
    
    // Creates states where jugs are filled from a faucet
    for(int i = 0; i < 3; i++){
        tempVector = currentNode->state;
        if(!isFull(tempVector, i)){
            tempVector = addFaucetWater(tempVector, i);
            Node tempNode(tempVector, getFunction(tempVector, 1), 1, currentNode);
            if(!checkDuplicates(tempVector, nodeStore)){
                cout<<"Filling jug "<<i<<"...";
                print(tempVector);
                possibleStates.push_back(tempNode);
            }
        }
    }
    
    // Creates states where jugs are emptied
    for(int i = 0; i < 3; i++){
        tempVector = currentNode->state;
        if(!isEmpty(tempVector, i)){
            tempVector = emptyJug(tempVector, i);
            Node tempNode(tempVector, getFunction(tempVector, 1), 1, currentNode);
            if(!checkDuplicates(tempVector, nodeStore)){
                cout<<"Emptying jug "<<i<<"...";
                print(tempVector);
                possibleStates.push_back(tempNode);
            }
        }
    }
    
    // Pours from jug 0 into jug 1
    tempVector = currentNode->state;
    if (!isEmpty(tempVector, 0) && !isFull(tempVector, 1)){
        tempVector = pourJug(tempVector, 0, 1);
        Node tempNode(tempVector, getFunction(tempVector, 1), 1, currentNode);
        if(!checkDuplicates(tempVector, nodeStore)){
            cout<<"Pouring jug 0 into jug 1...";
            print(tempVector);
            possibleStates.push_back(tempNode);
        }
    }
    
    // Pours from jug 0 into jug 2
    tempVector = currentNode->state;
    if (!isEmpty(tempVector, 0) && !isFull(tempVector, 2)){
        tempVector = pourJug(tempVector, 0, 2);
        Node tempNode2(tempVector, getFunction(tempVector, 1), 1, currentNode);
        if(!checkDuplicates(tempVector, nodeStore)){
            cout<<"Pouring jug 0 into jug 2...";
            print(tempVector);
            possibleStates.push_back(tempNode2);
        }
    }
    
    // Pours from jug 1 into jug 0
    if (!isEmpty(tempVector, 1) && !isFull(tempVector, 0)){
        tempVector = currentNode->state;
        tempVector = pourJug(tempVector, 1, 0);
        Node tempNode3(tempVector, getFunction(tempVector, 1), 1, currentNode);
        if(!checkDuplicates(tempVector, nodeStore)){
            cout<<"Pouring jug 1 into jug 0...";
            print(tempVector);
            possibleStates.push_back(tempNode3);
        }
    }
    
    // Pours from jug 1 into jug 2
    tempVector = currentNode->state;
    if (!isEmpty(tempVector, 1) && !isFull(tempVector, 2)){
        tempVector = pourJug(tempVector, 1, 2);
        Node tempNode4(tempVector, getFunction(tempVector, 1), 1, currentNode);
        if(!checkDuplicates(tempVector, nodeStore)){
            cout<<"Pouring jug 1 into jug 2...";
            print(tempVector);
            possibleStates.push_back(tempNode4);
        }
    }
    
    // Pours from jug 2 into jug 0
    if (!isEmpty(tempVector, 2) && !isFull(tempVector, 0)){
        tempVector = currentNode->state;
        tempVector = pourJug(tempVector, 2, 0);
        Node tempNode5(tempVector, getFunction(tempVector, 1), 1, currentNode);
        if(!checkDuplicates(tempVector, nodeStore)){
            cout<<"Pouring jug 2 into jug 0...";
            print(tempVector);
            possibleStates.push_back(tempNode5);
        }
    }
    
    // Pours from jug 2 into jug 1
    tempVector = currentNode->state;
    if (!isEmpty(tempVector, 2) && !isFull(tempVector, 1)){
        tempVector = pourJug(tempVector, 2, 1);
        Node tempNode6(tempVector, getFunction(tempVector, 1), 1, currentNode);
        if(!checkDuplicates(tempVector, nodeStore)){
            cout<<"Pouring jug 2 into jug 1...";
            print(tempVector);
            possibleStates.push_back(tempNode6);
        }
    }
    return possibleStates;
}

// Prints the state in the way that it is represented
void Domain::print(vector<int> state){
    for (int i = 0; i<3; ++i){
        printf("%d ",state[i]);
    }
    cout<<endl;
}

// Determines path cost
int Domain::getPathCost(Node* currentNode, Node* rootNode){
    int pathCost = 0;
    while(currentNode != rootNode->parent){
        pathCost = pathCost + currentNode->cost;
        currentNode = currentNode->parent;
    }
    return pathCost;
}

// Determines depth
int Domain::getDepth(Node* currentNode, Node* rootNode){
    int pathCount = 0;
    while(currentNode != rootNode->parent){
        currentNode = currentNode->parent;
        pathCount++;
    }
    return pathCount;
}