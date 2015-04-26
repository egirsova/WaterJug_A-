//
//  Domain.h
//  WaterJug_A*
//
//  Created by Liza Girsova on 10/22/14.
//  Copyright (c) 2014 CMSC470. All rights reserved.
//

#ifndef WaterJug_A__Domain_h
#define WaterJug_A__Domain_h

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Node
{
public:
    vector<int> state;
    int function;
    int cost;
    Node* parent;
    template<typename T, typename S> Node(T state, S function, int cost, Node *parent);
};

// Used to compare the nodes to enter into priority queue
class compareNode
{
public:
    // Overides the operator ()
    bool operator() (const Node* node1, const Node* node2) const
    {
        return node1->function > node2->function;
    }
};

class Domain
{
public:
    // Creates initial state
    template<typename T>
    Node createInitialState(T state){
        vector<int> jugVector(3);
        for(int i = 0; i < 3; i++){
            jugVector[i] = 0;
        }
        Node rootNode = *new Node(jugVector, getFunction(jugVector, 1), 1, &rootNode);
        return rootNode;
    }
    
    // Calculates the heuristic
    template<typename T>
    int getHeuristic(T state){
        int min = 500;
        for(int i = 0; i < 3; i++){
            int temp = state[i]-1;
            if(temp < min)
                min = temp;
            if(state[i] == 0)
                min = 1;
        }
        return min;
    }
    
    // Calculates the function f(n) = g(n)+h(n)
    template<typename T>
    int getFunction(T state, int cost){
        int function = getHeuristic(state)+cost;
        return function;
    }
    
    // Fills specified jug entirely from the faucet
    template<typename T>
    vector<int> addFaucetWater(T currentState, int jug){
        switch(jug){
            case 0:
                currentState[jug]=12;
                break;
            case 1:
                currentState[jug]=8;
                break;
            case 2:
                currentState[jug]=3;
                break;
        }
        return currentState;
    }
    
    // Empties specified jug
    template<typename T>
    vector<int> emptyJug(T currentState, int jug){
        currentState[jug]=0;
        return currentState;
    }
    
    // Pours water from specified jug "emptyJug" into specified jug "addJug"
    template<typename T>
    vector<int> pourJug(T currentState, int emptyJug, int addJug){
        while (!isEmpty(currentState, emptyJug) && !isFull(currentState, addJug)){
            currentState[addJug] = currentState[addJug]+1;
            currentState[emptyJug] = currentState[emptyJug]-1;
        }
        return currentState;
    }
    
    // Checks if specified jug is empty
    template<typename T>
    bool isEmpty(T currentState, int jug){
        if(currentState[jug]==0)
            return true;
        else
            return false;
    }
    
    // Checks if specified jug is full
    template<typename T>
    bool isFull(T currentState, int jug){
        switch(jug){
            case 0:
                if(currentState[jug]==12)
                    return true;
                else
                    return false;
                break;
            case 1:
                if(currentState[jug]==8)
                    return true;
                else
                    return false;
                break;
            case 2:
                if(currentState[jug]==3)
                    return true;
                else
                    return false;
                break;
        }
    }
    
    // Checks potential nodes for duplicates
    template<typename T, typename S>
    bool checkDuplicates(T currentState, S nodeList){
        list<Node>::iterator itr;
        itr = nodeList.begin();
        while(itr!=nodeList.end()){
        if(itr->state == currentState)
            return true;
            itr++;
        }
        return false;
    }
    
    // Checks for goalState
    template<typename T, typename S>
    bool goalState(T currentState, S goalState){
        for(int i = 0; i < 3; i++){
            if(currentState[i] == 1)
                return true;
        }
        return false;
    }
    
    // Prints the final solution/goal in a user-friendly way
    template <typename T, typename S>
    void printFinal(T currentNode, S rootNode){
        cout<<"Moves: "<<endl;
        list<vector<int>> moves;
        list<vector<int>>::iterator itr;
        while(currentNode != rootNode->parent){
            moves.push_front(currentNode->state);
            currentNode = currentNode->parent;
        }
        for(itr = moves.begin(); itr != moves.end(); ++itr){
            print(*itr);
        }
    }
    
    // Methods that are not templated
    list<Node> successorFn(Node* currentNode, Node* parentNode, list<Node> nodeStore);
    void print(vector<int> state);
    int getDepth(Node* currentNode, Node* rootNode);
    int getPathCost(Node* currentNode, Node* rootNode);
};


#endif
