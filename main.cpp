#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Node {
    vector<Node*> listNodes;
    Node* prevNode;
    int nameNode;
    bool mainHead;
    Node() {
        mainHead = true;
        nameNode = 0;
        prevNode = nullptr;
    }
    Node(int name) : nameNode(name) {
        mainHead = false;
        prevNode = nullptr;
        if (name == 0) {
            mainHead = true;
        }
    }
    Node(int name, Node* prev) : Node(name) {
        prevNode = prev;
    }
    ~Node() {

    }
};

ostream& operator<<(ostream& os, const Node* node) {
    os << node->nameNode << " { ";
    for (int i = 0; i < node->listNodes.size(); i++) {
        os << node->listNodes.at(i)->nameNode;
        if (i < node->listNodes.size()-1) {
            os << ",";
        }
    }
    os << " }" << endl;
    return os;
}

class Graph {
private :
    Node* MH;

/*
 *  return node index....
 */
    int checkPresentNode(const Node* node, int name) {
        int i = 0;
        int realNode = i;
        bool findRealNode = false;

        if (!node->listNodes.size()) {
            return 0;
        }
        while(i < node->listNodes.size()) {
            if (node->listNodes.at(i)->nameNode == -1) {
                return i;
            }
            if (node->listNodes.at(i)->nameNode != name) {
                if  (node->nameNode != name) {
                    realNode = i;
                    findRealNode = true;
                }
                else {
                    findRealNode = false;
                }
            }
            else {
                findRealNode = false;
            }
            i++;
        }
        if (findRealNode == false) {
            return -1;
        }

        return 1;  //
    }

        //перебрать узлы в tempListIndexPresentNodes
        //getRealIndex
    int getRealIndex(const vector<int>& tempListIndex, const vector<int>& listNodes) {
        if (tempListIndex.empty()) {
            return -1;
        }
        for (int i = 0; i < listNodes.size(); i++) {
            bool present = false;
            for (int j = 0; j < tempListIndex.size(); j++) {
                if (tempListIndex.at(j) == i) {
                    present = true;
                    break;
                }
            }
            if (present == false) {
                return i;
            }
        }
        return -1;
    }

    std::pair<int, bool> compareNameNode(int nameNode, const vector<int>& listNode) {
        int i = 0;
        bool presentName = false;
        while(listNode.at(i) != -1) {
            if (nameNode == listNode.at(i)) {
                presentName = true;
                return {i, presentName};
            }
            i++;
        }
        return {i, presentName};
    }

    int checkPresentNode(const Node* currNode, const vector<int>& listNode) {
        if (listNode.at(0) == -1) {
            return 0;   //no available nodes to check
        }
        if (currNode->listNodes.empty()) {
            return 0;
        }
        int i = 0;

        while(listNode.at(i++) != -1);
        int indexPrevNode = i-1;

//        if (compareNameNode(currNode->nameNode, listNode).second == true) {
//            return indexPrevNode;   //return index of element which equal -1
//        }

        i = 0;

        vector<int> tempListIndexPresentNodes;
        pair<int, bool> ind;
        while ((listNode.at(i) != -1)) {
            if (i >= currNode->listNodes.size()) {
                int realIndex = getRealIndex(tempListIndexPresentNodes, listNode);
                if (realIndex == -1)
                    return i;
                return realIndex;
            }
            ind = compareNameNode(currNode->listNodes.at(i)->nameNode, listNode);
            if (ind.second == true) {
                tempListIndexPresentNodes.push_back(ind.first);
                ++i;
                continue;
            }
            return ind.first;
        }

        if (ind.second == true) {

            return indexPrevNode;   //return index of element = -1
        }
// else get from tempListPresetnNodes

        return i;
    }
    void putFromBeginToEnd(vector<int> &listNode) const {
        listNode.push_back(listNode.at(0));
        listNode.erase(listNode.begin());
    }

    void putFromIndToEnd(vector<int>& listNode, int numNode) const {
        listNode.push_back(listNode.at(numNode));
        listNode.erase(listNode.begin() + numNode);
    }
    void putFromEndToBegin(vector<int>& listNode) {
        listNode.insert(listNode.begin(), listNode.back());
        listNode.pop_back();
    }
public:
    Graph() {
        MH = new Node();
    }
    ~Graph() {}


    void /* Node* */ buildGraph(vector<int> listNodeName, Node* currNode) {
        static int dbgCount = 0;
        Node* tNode;
        if (currNode == nullptr) {
            currNode = MH;
        }

        if (listNodeName.at(0) == -1 && currNode->prevNode == nullptr) {
            return; //put all elements to graph, and get MainHead node...... stop all
        }

        int ind = 0;
        ind = checkPresentNode(currNode, listNodeName); //must return index of element in listNodeNam

        if (listNodeName.at(ind) != -1) {
            tNode = new Node(listNodeName.at(ind), currNode);
            putFromIndToEnd(listNodeName, ind);
            currNode->listNodes.push_back(tNode);
        }
        else {
            tNode = currNode->prevNode;
            putFromEndToBegin(listNodeName);
        }

        dbgCount++;
        cout << dbgCount << " ";
        buildGraph(listNodeName, tNode);
    }

    void printGraph() {
        Node* tempMH = MH;
        cout << "\n";
        cout << MH;
        for (int i = 0; i < MH->listNodes.size(); i++) {
            cout << MH->listNodes.at(i);
        }
    }

    void DFS() {

    }

    void BFS() {

    }

    void testBuild() {
        buildGraph({1,2,3,4,5,-1}, nullptr);



        printGraph();
        int a = 10;
    }
};

int main() {

    Graph *testGr = new Graph();
    testGr->testBuild();

    return 0;
}



