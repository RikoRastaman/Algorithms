#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>

using namespace std;

struct Node
{
    std::vector<Node *> childs;
    Node *father;
    string value;

    Node(string value)
    {
        this->value = value;
    }

    void AddNode(Node *node)
    {
        this->childs.push_back(node);
        node->father = this;
    }
};

void PrintNode(Node *node)
{
    cout << node->value << ' ';
    ;
    for (auto child : node->childs)
    {
        PrintNode(child);
    }
}

void createNode(Node *node, std::ifstream &fin, std::string &str)
{
    int treeLevel = 0;
    while (str[treeLevel] == ' ')
    {
        treeLevel++;
    }
    cout << treeLevel << endl;
    getline(fin, str);
    string name;
    int spacesMain = 0;
    while (spacesMain < str.length() && str[spacesMain] == ' ')
    {
        spacesMain++;
    }
    name = str.substr(spacesMain);
    auto nodeMainSon = new Node(name);
    // cout << name << endl;

    node->AddNode(nodeMainSon);

    while (!fin.eof())
    {
        getline(fin, str);
        string name;
        int spaces = 0;
        while (spaces < str.length() && str[spaces] == ' ')
        {
            spaces++;
        }
        cout << " spaces: " << spaces << endl;
        name = str.substr(spaces);
        auto nodeSon = new Node(name);
        cout << "name: " << name << endl;

        if (spaces < spacesMain)
        {
            return;
        }
        if (spaces > spacesMain)
        {
            // nodeMainSon->AddNode(nodeSon);
            createNode(nodeSon, fin, str);
        }

        if (spaces == spacesMain)
        {
            node->AddNode(nodeSon);
        }
        nodeMainSon->AddNode(nodeSon);

    }
}

Node *InitTree()
{
    ifstream fin("Test.txt");
    string str;
    getline(fin, str);
    // cout << str << endl;

    auto rootNode = new Node(str);

    createNode(rootNode, fin, str);

    // auto rootNode = new Node(str);
    // auto previousNode = rootNode;
    // while (str[treeLevel] == ' ')
    // {
    //     treeLevel++;
    // }

    // while (!fin.eof())
    // {
    // }

    // auto nodeD = new Node("D");
    // auto nodeE = new Node("E");

    // nodeB->AddNode(nodeC);
    // nodeB->AddNode(nodeD);

    // return rootNode;

    return rootNode;
}

Node *FindNode(Node *node, string value)
{
    if (node->childs.size() == 0)
    {
        // cout << "Im here" << node->childs.size() << endl;
        return nullptr;
    }

    for (auto child : node->childs)
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
    // ifstream fin("Test.txt");
    // string str;
    // getline(fin, str);
    auto rootNode = InitTree();
    //
    // cout << endl;
    // auto nodeA = rootNode;
    // auto root = FindNode(rootNode, "Artem");
    auto nodeC = FindNode(rootNode, "Christy");
    auto nodeD = FindNode(rootNode, "Diana");
    auto nodeB = FindNode(rootNode, "Bill");
    auto nodeR = FindNode(rootNode, "Riko");

    PrintNode(rootNode);
    cout << endl;

    auto firstNode = nodeD;
    auto secondNode = nodeC;

    if (FindNode(firstNode, secondNode->value))
    {
        cout << firstNode->value << " father of " << secondNode->value;
    }
    if (FindNode(secondNode, firstNode->value))
    {
        cout << secondNode->value << " father of " << firstNode->value;
    }

    auto commonFather = FindCommonFather(firstNode, "Diana");
    cout << commonFather->value << " is common father of " << firstNode->value << " and " << secondNode->value;

    cout << endl;

    return 0;
}