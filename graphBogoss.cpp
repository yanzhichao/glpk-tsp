
#include <string>


using namespace std;


class Graph{

};


class Node{
    private:
        int id;
        int card;
        Edge* e1,e2;
    public:
        Node(int i)
        {
            id=i;
            card=0;
            e1=e2=void;
        }

        void setEdge(Edge* e)
        {

        }
        Edge* getEdge(int i)
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

};

class Edge{
private:
    string id;
    int idNode1,idNode2;
    int length
public:
    Edge(string i,int id1,int id2, int l)
    {
        id=i;
        idNode1=id1;
        idNode2=id2;
        length=l;
    }


};