#include "pch.h"
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
// class parents{
//     std::vector<Node *> parents;
//     int deep;
// }
std::vector<Node *> parents;

void PrintNode(Node *node)
{
	cout << node->value << ' ';
	;
	for (auto child : node->childs)
	{
		PrintNode(child);
	}
}

void createNode(Node *node, std::ifstream &fin, std::string &str, std::vector<Node *> parents)
{

	// parents.push_back(node);

	// cout << "FIRST STR IN FUNCTION:" << str << endl;
	int treeLevel = 0;
	while (str[treeLevel] == ' ')
	{
		treeLevel++;
	}
	parents.reserve(10);
	parents.emplace(parents.begin(), node);

	// cout << treeLevel << endl;
	// getline(fin, str);
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
		string secondstr;
		getline(fin, secondstr);
		// cout << "SECOND STR IN FUNCTION:" << secondstr << endl;
		string name;
		int spaces = 0;
		while (spaces < secondstr.length() && secondstr[spaces] == ' ')
		{
			spaces++;
		}
		// cout << " spaces: " << spaces << endl;
		name = secondstr.substr(spaces);
		auto nodeSon = new Node(name);
		// cout << "name: " << name << endl;

		if (spacesMain < spaces)
		{

			createNode(nodeMainSon, fin, secondstr, parents);
			// cout << "GET BACK:";
			// PrintNode(node);
			// cout << endl;
			// cout << "SPACES MAIN BACK:" << spacesMain << endl;

			spaces = 0;
			while (spaces < secondstr.length() && secondstr[spaces] == ' ')
			{
				spaces++;
			}

			// continue;
			// createNode(nodeSon, fin, str);
		}

		// cout << "Node son: ";
		// PrintNode(nodeSon);
		// cout << spacesMain << " :SPACES MAIN" << endl;
		// cout << "TRUE??" << (spacesMain > spaces) << endl;
		if (spacesMain > spaces)
		{
			node = (parents[0]->father);
			node->AddNode(nodeSon);
			//(parents[0]->father)->AddNode(nodeSon);
			//spacesMain = spaces;// DOUB!!!!!!!!!!!!!!!!!!!
		}

		if (spacesMain == spaces)
		{
			node->AddNode(nodeSon);
		}

		// node->AddNode(nodeSon);

		// if (spaces < treeLevel)
		// {
		//     return;
		// }
		// if (spaces == treeLevel)
		// {
		//     node->AddNode(nodeSon);
		// }

		// if (spaces > treeLevel)
		// {
		//     node->nodes.push_back(nodeSon);
		//     nodeSon->father = node;
		// }

		// if (spaces == treeLevel)
		// {

		//     continue;
		// }

		// if (spaces >= treeLevel)
		// {
		//     node->AddNode(nodeSon);
		//     if (spaces == treeLevel)
		//     {
		//         continue;
		//     }
		//     createNode(nodeSon, fin, str);
		// }

		// node->AddNode(nodeSon);
		// cout << (spaces > treeLevel) << endl;
		// if (spaces > treeLevel)
		// {
		//     cout << " im here:" << name << endl;
		//
		//     spaces = 0;
		// }
	}
}

std::string readTree(std::ifstream & file, Node & currentNode, const std::string & firstStr) {
	int treeLevel = 0;
	while (firstStr[treeLevel] == ' ') {
		treeLevel++;
	}
	currentNode.childs.push_front(TreeElement());
	currentNode.childs.begin()->name = firstStr.substr(treeLevel);
	currentNode.childs.begin()->parent = &currentNode;
	std::cout << firstStr << std::endl;
	while (!(file.eof())) {
		std::string str;
		std::getline(file, str);
		int currentSpace = 0;
		while (currentSpace < str.length() && str[currentSpace] == ' ') {
			currentSpace++;
		}
		if (currentSpace > treeLevel) {
			str = readTree(file, *(currentNode.childs.begin()), str);
			currentSpace = 0;
			while (currentSpace < str.length() && str[currentSpace] == ' ') {
				currentSpace++;
			}
		}
		if (currentSpace < treeLevel) {
			return str;
		}
		if (currentSpace == treeLevel) {
			currentNode.childs.push_front(TreeElement());
			currentNode.childs.begin()->name = str.substr(currentSpace);
			currentNode.childs.begin()->parent = &currentNode;
			std::cout << str << std::endl;
		}
	}
	return "";
}


Node *InitTree()
{
	ifstream fin("Test.txt");
	string str;
	getline(fin, str);
	// cout << str << endl;

	auto rootNode = new Node(str);
	getline(fin, str);

	readTree(fin, rootNode, str);

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
	auto nodeR = FindNode(rootNode, "Rikardo");
	auto nodeQ = FindNode(rootNode, "Qwery");
	auto nodeM = FindNode(rootNode, "Milosh");
	auto nodeDob = FindNode(rootNode, "Danie");

	PrintNode(rootNode);
	cout << endl;
	//if first = root ryturn root
	auto firstNode = nodeM;
	auto secondNode = nodeDob;

	string forCommon = "Danie";

	if (FindNode(firstNode, secondNode->value))
	{
		cout << firstNode->value << " father of " << secondNode->value << endl;
	}
	if (FindNode(secondNode, firstNode->value))
	{
		cout << secondNode->value << " father of " << firstNode->value << endl;
	}

	auto commonFather = FindCommonFather(firstNode, forCommon);
	cout << commonFather->value << " is common father of " << firstNode->value << " and " << secondNode->value << endl;

	cout << endl;

	return 0;
}