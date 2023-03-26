#include<iostream>
#include<string>
#include<queue>
#include<fstream>
using namespace std;
float total; // Using a global funciton because values keep changing due to the recursive call of the funciton
class node
{
public:
	char a = '-';
	int freq = 0;
	node* left;   //left child
	node* right;  // right child
	node* next;   // next pointer, will be helpful in push and pop

	node(char a = '-', int freq = 0) // Parameterised Constructor to get values in single format
	{
		this->a = a;
		this->freq = freq;
		left = NULL;
		right = NULL;
		next = NULL;
	}

	node(node* x) // Constructor to be used when to push entire node i.e in Push Function after adding the two noes that we pop
	{
		a = x->a;
		freq = x->freq;
		left = x->left;
		right = x->right;
		next = x->next;
	}
	node(node* x, node* y) //This constructor helps in adding the frequencies of two i_node and then stores the result !!!!SUPER HELPFUL
	{
		a = '-';
		int freq = x->freq + y->freq; //adding frequencies of the two i_node that I poped from the queue
		left = x;
		right = y;
	}

	void Print(string code = "") // Function to traverse the whole tree of i_node
	{
		static float length = 0; //Using a static float to retain the value which might be affected due to the recursion
		if (left != NULL)
		{
			left->Print(code + '0'); //String Library funciton that appens the character to a string
			right->Print(code + '1');
		}
		else
		{
			cout << "Character: " << a << "  Frequency: " << freq << "  Code: " << code << endl;
			length = length + (freq * code.size()); // Calculating length of the code and frequncy to calculate the compresison ratio
		}
		total = length; // storing sum of F1L1+F2L2.....FnLn in the total
	}
};

void getTreei_node(node* root, vector<node*>& i_node) // Function to store each node into the vector in in-order
{
	if (root != NULL)
	{
		getTreei_node(root->left, i_node);
		i_node.push_back(root);
		getTreei_node(root->right, i_node);
	}
}

node* MakeBalancedTree(vector<node*>& i_node, int start, int end) //Balancing the tree to reduce the height of the tree which will reduce the height of the charcter code
{
	if (start > end)
	{
		return  NULL;
	}
	int temp = (start + end) / 2; // Finding the Middle index
	node* root = i_node[temp];
	root->left = MakeBalancedTree(i_node, start, temp - 1);
	root->right = MakeBalancedTree(i_node, temp + 1, end);
	return root;
}

class priority_q  // Priority Queue Class
{
public:
	node* head = NULL;
	void push(node* a)
	{
		node* temp = head;
		node* prev = NULL;
		node* nnode = a;
		if (head == NULL)
		{
			head = a;
		}
		else
		{
			while (temp != NULL && temp->freq < a->freq) //Condition for setting priority asendingly
			{
				prev = temp;
				temp = temp->next;
			}

			if (temp == NULL)
			{
				prev->next = nnode;
			}
			else
			{
				if (prev == NULL)
				{
					nnode->next = head;
					head = nnode;
				}
				else
				{
					nnode->next = temp;
					prev->next = nnode;
				}
			}
		}

	}

	int len() // Helper Function to calculate the length on the queue. It helps to know when there is only one element left in the queue. It helps in breaking the loop
	{
		node* temp = head;
		int i = 0;
		while (temp != NULL)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}

	void pop() //Function to remove a node from the head
	{
		if (head != NULL)
		{
			head = head->next;
		}
	}
	node* peek() // Return the head and I also called the pop function here to remove the element after getting the node
	{
		node* temp = head;
		return temp;
	}
};

node* MakeTree(string s) // Function to make Huffman Tree
{
	priority_q p; // Priority Queue Object
	int count = 0;
	for (int i = 0; i <= 128; i++) // Traversing the whole ascii table to save all characters
	{
		char c = i;
		for (int j = 0; s[j] != '\0'; j++) // Inner loop traverses the whole string to get the frequency of individual string
		{
			if (c == s[j])
			{
				count++;
			}
		}
		if (count != 0)
		{
			node* temp = new node(c, count); //Making new node using the character and frequency and then pushing it into the queue
			p.push(temp);
		}
		count = 0; //resetting the queue to zero
	}

	while (p.len() > 1)// Breaking the loop when there is only root node left in the queue
	{
		node* a = new node(p.peek()); // Left Node
		p.pop();
		node* b = new node(p.peek()); // Right Node
		p.pop();
		node* temp = new node(a, b); // Parent/Root Node
		p.push(temp); // Pushing the Root Node
	}
	p.peek()->Print(); // Printing the codes
	node* a = p.peek();
	return a;
}

string getting_input_from_file() //Reading the Text form the file
{
	string name;
	cout << "Enter the File Name: ";
	cin >> name;
	string s; //string to store the text of the file
	ifstream myfile(name);
	if (myfile.is_open()) //Condition if file is open
	{
		while (getline(myfile, s))
		{
			cout << s << endl;
		}
		myfile.close();
	}
	return s;
}


void Compression_Ratio(string s) //Function to calculate the compression ratio
{
	int t = 0;
	for (int i = 0; s[i] != NULL; i++) //calculating the total number of characters in the file/string
	{
		t++;
	}
	float c = total / t;
	float a = 8;
	float d = a / c;
	cout << "This is the compression ratio: " << c << endl;
}

node* SimpleHuffmanTree(string s)
{
	node* root = MakeTree(s); // We are saving this root node so that we use it to traverse the tree and then store it into the AVL
	Compression_Ratio(s);
	return root;
}

void ImprovedHuffmanTree(node* root, string s)
{
	vector<node*> i_node;
	getTreei_node(root, i_node);
	root = MakeBalancedTree(i_node, 0, i_node.size() - 1);
	root->Print();
	Compression_Ratio(s);
}

int main()
{
	string s = getting_input_from_file();
	node* root = SimpleHuffmanTree(s);
	ImprovedHuffmanTree(root, s);
}