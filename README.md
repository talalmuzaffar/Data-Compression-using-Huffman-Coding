## Data-Compression-using-Huffman-Coding
This code implements the Huffman encoding algorithm to compress a string. It reads a string from a file and returns the compressed version of the string using Huffman encoding.

## Libraries used
- iostream
- string
- queue
- fstream

## Global Variables
- total : Stores the total length of the compressed string. It is updated in the Print() function.

## Classes
## node
This class is used to define a node in the Huffman tree. Each node has the following attributes:

- a : The character stored in the node.
- freq : The frequency of the character.
- left : Pointer to the left child.
- right : Pointer to the right child.
- next : Pointer to the next node in the priority queue.

This class also has the following constructors:

- node(char a = '-', int freq = 0) : Parameterized constructor that takes the character and frequency as input and initializes the node.
- node(node* x) : Copy constructor that takes a pointer to a node as input and initializes the current node as a copy of the input node.
- node(node* x, node* y) : Constructor that takes two pointers to nodes as input and creates a new node with '-' character and frequency equal to the sum of the -frequencies of the input nodes. It sets the left and right pointers of the new node to the input nodes.
It also has the following functions:

- Print(string code = "") : This function recursively traverses the Huffman tree and prints the character, frequency, and code for each leaf node. It also updates the global variable total with the total length of the compressed string.

## priority_q
This class is a priority queue that stores the nodes of the Huffman tree. It has the following attributes:

- head : Pointer to the first node in the queue.

It has the following functions:

- push(node* a) : Adds a node to the queue in ascending order of frequency.
- len() : Returns the length of the queue.
- pop() : Removes the first node from the queue.
- peek() : Returns the first node in the queue.

## Functions
- getTreei_node(node* root, vector<node*>& i_node)
This function recursively stores all the nodes of the Huffman tree in in-order traversal in the input vector i_node.

- MakeBalancedTree(vector<node*>& i_node, int start, int end)
This function takes the vector of nodes i_node, start index, and end index as input and returns a balanced Huffman tree with the nodes in i_node using a divide and conquer approach.

- MakeTree(string s)
This function takes a string as input and returns the Huffman tree.

- Main Function
The main function reads a string from a file named input.txt and calls the MakeTree() function to create the Huffman tree. It then calls the Print() function of the root of the Huffman tree to print the character, frequency, and code for each leaf node. Finally, it calculates the compression ratio and writes the compressed string and the compression ratio to a file named output.txt.
