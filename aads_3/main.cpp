#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

using namespace std;

struct Node
{
    std::vector<Node *> nodes;
    Node *father;
    string value;

    Node(string value)
    {
        this->value = value;
    }

    void AddNode(Node *node)
    {
        this->nodes.push_back(node);
        node->father = this;
    }
};

Node *InitTree()
{
    auto rootNode = new Node("A");
    auto nodeB = new Node("B");
    auto nodeC = new Node("C");
    auto nodeD = new Node("D");
    auto nodeE = new Node("E");

    rootNode->AddNode(nodeB);
    nodeB->AddNode(nodeC);
    nodeB->AddNode(nodeD);

    return rootNode;
}

void PrintNode(Node *node)
{
    cout << node->value << ' ';
    for (auto child : node->nodes)
    {
        PrintNode(child);
    }
}

Node *FindNode(Node *node, string value)
{
    if (node->nodes.size() == 0)
    {
        // cout << "Im here" << node->nodes.size() << endl;
        return nullptr;
    }

    for (auto child : node->nodes)
    {
        if (child->value == value)
        {
            return child;
        }
        auto recursiveNode = FindNode(child, value);
        if (!recursiveNode)
        {
            continue;
        }
        if (recursiveNode->value == value)
        {
            return recursiveNode;
        }
    }

    return nullptr;
}

Node *FindCommonFather(Node *node, string value)
{
    auto currentNode = node;
    do
    {
        currentNode = currentNode->father;
        if (currentNode == nullptr)
        {
            return nullptr;
        }
        auto foundNode = FindNode(currentNode, value);

        if (foundNode)
        {
            return currentNode;
        }

    } while (true);

    return currentNode;
}

int main()
{
    ifstream fin("Test.txt");
    string str;
    getline(fin, str);
    auto rootNode = InitTree();

    auto nodeA = rootNode;
    auto nodeB = FindNode(rootNode, "B");
    auto nodeC = FindNode(rootNode, "C");
    auto nodeD = FindNode(rootNode, "D");

    auto firstNode = nodeB;
    auto secondNode = nodeD;

    if (FindNode(firstNode, secondNode->value))
    {
        cout << firstNode->value << " father of " << secondNode->value;
    }
    if (FindNode(secondNode, firstNode->value))
    {
        cout << secondNode->value << " father of " << firstNode->value;
    }

    cout << endl;

    auto commonFather = FindCommonFather(firstNode, "D");
    cout << commonFather->value << " is common father of " << firstNode->value << " and " << secondNode->value;

    // cout << endl;
    // PrintNode(nodeA);

    return 0;
}