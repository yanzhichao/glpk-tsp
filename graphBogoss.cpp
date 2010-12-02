
#include <string>
#include "graphBogoss.hpp"
using namespace std;



    Graph::Graph()
    {
        nodes = new map<int,Node*>();
        edges = new map<int,Edge*>();
    }
    bool Graph::hasSubcycles()
    {
        int compt=1;
        Node node1 = *(*nodes)[0];
        Node nodeTemp0 = *(*nodes)[0];
        Node nodeTemp1=*((*nodes)[(*((*edges)[nodeTemp0.getEdge(0)])).getOpposite(nodeTemp0.getEdge(0))]);

        while(node1.getId()!=nodeTemp1.getId())
        {
            Node nodeTemp2;
            if(*(*edges[nodeTemp1.getEdge(0)]).getOpposite(nodeTemp1.getId())!=nodeTemp0.getId())
                nodeTemp2=*nodes[*edges[nodeTemp1.getEdge(0)].getOpposite(nodeTemp1.getId())];
            else
                nodeTemp2=*nodes[*edges[nodeTemp1.getEdge(1)].getOpposite(nodeTemp1.getId())];
            nodeTemp1=nodeTemp0;
            nodeTemp0=nodeTemp2;
            compt++;
        }
        if(compt==*nodes.size())
            return false;
        return true;
    }
   /* vector<map<int,Node*>> getSubcycles()
    {
        vector<map<int,Node*>* subCycles = new vector<map<int,Node*>();
        vector<int> nodesTemp = new vector<int>();
        int i,j;
        for(int i=0;i<&nodes.size();i++)
        {
            nodesTemp.push_back(&(&nodes[i]).getId());
        }
        int compt=1;

        for(i=0;i<&nodes.size();i++)
        {
            int wasMade = 0;
            for(j=0;j<nodesTemp.size();j++)
            {
                if(&(&nodes[i]).getId()==nodesTemp.at(j))
                    wasMade=1;
            }
            if(wasMade==0)
            {
                Node node1 = &nodes[0];
                Node nodeTemp0 = &nodes[0];
                Node nodeTemp1 = &nodes[nodeTemp0.getEdge(0).getOpposite(nodeTemp0.getId())];

                while(node1.getId()!=nodeTemp1.getId())
                {
                    Node nodeTemp2;
                    if(nodeTemp1.getEdge(0).getOpposite(nodeTemp1.getId())!=nodeTemp0.getId())
                        nodeTemp2=&nodes[nodeTemp1.getEdge(0).getOpposite(nodeTemp1.getId())];
                    else
                        nodeTemp2=&nodes[nodeTemp1.getEdge(1).getOpposite(nodeTemp1.getId())];
                    nodeTemp1=nodeTemp0;
                    nodeTemp0=nodeTemp2;
                    compt++;
                }
            }
        }
        return NULL;
    }*/





    
   
        Node::Node(int i)
        {
            id=i;
            card=0;
            e1=e2=NULL;
        }
        int Node::getId()
        {
            return id;
        }
        void Node::setEdge(int e)
        {
            if(e1==NULL)
                e1=e;
            else
                e2=e;
        }
        int Node::getEdge(int i)
        {
            if(i==1)
            {
                return e1;
            }
            else
            {
                return e2;
            }
        }


        Edge::Edge(string i,int id1,int id2, int l)
        {
            id=i;
            idNode1=id1;
            idNode2=id2;
            length=l;
        }
        int Edge::getId()
        {
            return id;
        }
        int Edge::getLength()
        {
            return length;
        }
        void Edge::setLength(int l)
        {
            length=l;
        }
        int Edge::getNode(int i)
        {
            if(i==1)
                return idNode1;
            return idNode2;
        }
        int Edge::getOpposite(int i)
        {
            if(i==idNode1)
                return idNode2;
            return idNode1;
        }
