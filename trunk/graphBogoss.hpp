/* 
 * File:   graphBogoss.hpp
 * Author: badkrist
 *
 * Created on 2 décembre 2010, 16:46
 */

#ifndef GRAPHBOGOSS_HPP
#define	GRAPHBOGOSS_HPP


#include<vector>
#include<map>
using namespace std;
class Node{
    private:
        int id;
        int card;
        int e1,e2;
    public:
        Node(int);
        int getId();
        void setEdge(int);
        int getEdge(int);
};

class Edge{
    private:
        string id;
        int idNode1,idNode2;
        int length;
    public:
        Edge(string,int,int,int);
        int getId();
        int getLength();
        void setLength(int);
        int getNode(int);
        int getOpposite(int);
};
class Graph
{
private:
    map<int,Node*>* nodes;
    map<int,Edge*>* edges;
public:
    Graph();
    bool hasSubcycles();
    //vector<map<int,Node*>> getSubcycles();
};


#endif	/* GRAPHBOGOSS_HPP */

