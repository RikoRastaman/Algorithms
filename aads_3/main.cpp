/*
11. Имеется   дерево,   корень    которого    соответствует
основателю  рода.  Сыновья  каждой  вершины  задают  сыновей и
дочерей  соответствующего  человека.  Указываются  имена  двух
человек  (например,  А  и  В).  Сообщить,  какая  из следующих
ситуаций имеет место:
   1) А предок В;
   2) В предок А;
   3) А и В имеют ближайшего общего предка С (10).
*/

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

	Node(const string &value)
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

std::string readTree(std::ifstream &file, Node *currentNode, std::string firstStr)
{
	int treeLevel = 0;
	while (firstStr[treeLevel] == ' ')
	{
		treeLevel++;
	}
	string name = firstStr.substr(treeLevel);
	currentNode->AddNode(new Node(name));
	while (!(file.eof()))
	{
		std::string str;
		std::getline(file, str);
		int currentSpace = 0;
		while (currentSpace < str.length() && str[currentSpace] == ' ')
		{
			currentSpace++;
		}
		if (currentSpace > treeLevel)
		{
			str = readTree(file, (currentNode->childs[currentNode->childs.size() - 1]), str);
			currentSpace = 0;
			while (currentSpace < str.length() && str[currentSpace] == ' ')
			{
				currentSpace++;
			}
		}
		if (currentSpace < treeLevel)
		{
			return str;
		}
		if (currentSpace == treeLevel)
		{
			currentNode->AddNode(new Node(str.substr(currentSpace)));
		}
	}
	return "";
}

Node *InitTree()
{
	string fileName = "";

	cout << "Enter file name: " << endl;
	cin >> fileName;

	ifstream fin(fileName);

	if (!fin.is_open())
	{
		cout << "File does not opened" << endl;
		return nullptr;
	}
	string str;
	getline(fin, str);

	auto rootNode = new Node(str);
	rootNode->father = nullptr;
	getline(fin, str);

	readTree(fin, rootNode, str);

	return rootNode;
}

Node *FindNode(Node *node, string value)
{
	if (node->childs.size() == 0)
	{
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

Node *GetNameFromInput(Node *root)
{

	string str;
	Node *result = nullptr;
	while (result == nullptr)
	{
		cout << "Enter name" << endl;
		cin >> str;

		if (root->value == str)
		{
			return root;
		}

		result = FindNode(root, str);
		if (result == nullptr)
		{
			cout << "There is no Node with name: " << str << endl;
			cout << "Please write correct name." << endl;
		}
	}

	return result;
}

int main()
{
	auto rootNode = InitTree();
	string command = "";

	while (command != "no")
	{
		Node *firstNode = nullptr;
		Node *secondNode = nullptr;
		string str = "";
		string str2 = "";
		do
		{
			firstNode = GetNameFromInput(rootNode);
			secondNode = GetNameFromInput(rootNode);
			if (firstNode->value == secondNode->value)
			{
				cout << "You`ve entered the same names. Please rewrite them." << endl;
			}
		} while (firstNode->value == secondNode->value);

		if (FindNode(firstNode, secondNode->value))
		{
			cout << firstNode->value << " father of " << secondNode->value << endl;
		}
		if (FindNode(secondNode, firstNode->value))
		{
			cout << secondNode->value << " father of " << firstNode->value << endl;
		}

		auto commonFather = FindCommonFather(firstNode, secondNode->value);
		if (commonFather != nullptr)
		{
			cout << commonFather->value << " is common father of " << secondNode->value << " and " << firstNode->value << endl;
		}

		cout << endl;

		cout << "Continue? (Write 'no' to stop running / 'yes' to continue)" << endl;
		cin >> command;
	}

	return 0;
}