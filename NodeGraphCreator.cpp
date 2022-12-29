/**************************
 *
 * Name: Devam Shah
 * Project Name: Node Graph Creator
 * Date: 12/02/2022
 *
 * ************************/
//Uses linked lists 
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node* link;
    Node(){};
    Node(int Id){
        this->data=Id;
        link=NULL;
    }
};

class Graph {
public:
    bool isRepeat(int nodeId, int neighborId) {
        if(vertices[nodeId] != NULL){
            Node *currNode = vertices[nodeId];
            while (currNode->link != NULL) {
                if (currNode->data == neighborId) {
                    return true;
                } else {
                    currNode = currNode->link;
                    return false;
                }
            }
        }
        else{
            return false;
        }

    };
    void moveNext(){
        Node *curr = new Node();
        if(curr->link==NULL){
            return;
        }
        else{
            while (curr!=NULL){
                curr= curr->link;
            }
        }
    }
    //add the node with neighborId as the neighbor of nodeId
    void addNeighbor(int nodeId, int neighborId){
        if (vertices.size()<nodeId + 1) {
            vertices.resize(nodeId + 1);
        }
        if (vertices.size()<neighborId + 1) {
            vertices.resize(neighborId + 1);
        }
        Node* insertNode=new Node(neighborId);
        if (vertices[nodeId]==NULL){
            vertices[nodeId]=insertNode;
        }
        else{
            Node* currNode=vertices[nodeId];
            while (currNode!= NULL){
                if (currNode->data==neighborId) {
                    return;
                }
                else{
                    currNode=currNode->link;
                }
            }
            if (vertices[nodeId]->data>neighborId){
                Node* temp=vertices[nodeId];
                insertNode->link=temp;
                vertices[nodeId]=insertNode;
                return;
            }
            else{
                Node* temp=vertices[nodeId];
                if (temp)
                    while (temp->link!=NULL){
                        if (temp->data==neighborId){
                            return;
                        }
                        if (temp->link->data>neighborId){
                            break;
                        }
                        temp=temp->link;
                    }
                insertNode->link=temp->link;
                temp->link=insertNode;
            }
        }
    }
    void gameOut(int nodeId, int neighborId) {
        int count = 0;
        while (count != 5) {
            if (!isRepeat(nodeId, neighborId)) {
                moveNext();
                gameOut(nodeId, neighborId);
            }
        }
    }

    //reads the edge list from file and creates the adjacency list data structure
    void loadGraph(string edgeListFileName){
        string line;
        ifstream file(edgeListFileName);
        if (file.is_open()){
            while (!file.eof()){
                int nodeID;
                int neighborID;
                file >> nodeID;
                file >> neighborID;
                addNeighbor(nodeID, neighborID);
                addNeighbor(neighborID, nodeID);
            }
        }
        file.close();
    }

    //writes the adjacency list into the file
    void dumpGraph(string adjListFileName){
        ofstream file(adjListFileName);
        if(file.is_open()){
            for (int i=0; i<vertices.size(); i++){
                Node *tmpVar=vertices[i];
                if (tmpVar!=NULL){
                    file << i << ":";
                    file << " " << tmpVar->data;
                    while (tmpVar->link!=NULL){
                        tmpVar=tmpVar->link;
                        file << tmpVar->data << " ";
                    }
                    file<<endl;
                }
            }
        }
    };

    //Prints number of nodes, number of edges, and maximum degree on terminal
    void printGraphInfo(){
        int count=0;
        int check =0;
        int maximum=0;
        for (int i=0; i<vertices.size(); i++){
            int huLuLuLu=0;
            Node* temp=vertices[i];
            if (temp!=NULL){
                count++;
                huLuLuLu++;
                while (temp->link!=NULL){
                    huLuLuLu++;
                    temp=temp->link;

                }
                if (huLuLuLu>maximum){
                    maximum=huLuLuLu;
                }
                check += huLuLuLu;
            }
        }
        cout << "Number of nodes: " << count<<endl;
        cout << "Number of edges: " << check/2 <<endl;
        cout << "Maximum degree: " << maximum << endl;
    }

    //returns the number of neighbor (degree) of a node
    int getNumNeighbors(int nodeId){
        int numNeighbors=0;
        Node *curr=vertices[nodeId];
        while(curr->link!=NULL){
            curr=curr->link;
            numNeighbors++;
        }
        return numNeighbors;
    }

    //returns the number of nodes in the graph
    int getNumVertices(){
        return vertices.size();
    }

    void print(){
        if(true){
            for (int i=0; i<vertices.size(); i++){
                Node* temp=vertices[i];
                if (temp!=NULL){
                    cout << i << ":";
                    cout << " " << temp->data;
                    while (temp->link!=NULL){
                        temp=temp->link;
                        cout << " " << temp->data;
                    }
                    cout << endl;
                }
            }
        }
    }

private:
    vector<Node*> vertices;
};

void run(string edgeListFileName, string adjListFileName) {
    Graph newGraph;
    newGraph.loadGraph(edgeListFileName);
    newGraph.dumpGraph(adjListFileName);
    newGraph.print();
    newGraph.printGraphInfo();
}

//*****************************************************************************


// The main will be removed for testing, do not add any code in the main function
int main() {
    //Change the filenames according to your local path.
    string edgeListFileName("karate.txt");
    string adjListFileName("karate_adj.txt");
    run(edgeListFileName, adjListFileName);
    return 0;
}
