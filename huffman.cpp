#include <iostream> 
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""

// A Tree node
struct Node
{
 char ch;
 int freq;
 Node *left, *right;
};
// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
 Node* node = new Node();

 node->ch = ch;
 node->freq = freq;
 node->left = left;
 node->right = right;

 return node;
}
// Comparison object to be used to order the heap 
struct comp
{
 bool operator()(const Node* l, const Node* r) const
 {
 // the highest priority item has the lowest frequency
 return l->freq > r->freq;
 }
};
// Utility function to check if Huffman Tree contains only a single node
bool isLeaf(Node* root) {
 return root->left == nullptr && root->right == nullptr;
}
// Traverse the Huffman Tree and store Huffman Codes in a map.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
 if (root == nullptr) {
 return;
 }
 // found a leaf node
 if (isLeaf(root)) {
 huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
 }
 encode(root->left, str + "0", huffmanCode);
 encode(root->right, str + "1", huffmanCode);
}
// Traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int &index, string str)
{ 
 if (root == nullptr) {
 return;
 }

 // found a leaf node
 if (isLeaf(root))
 {
 cout << root->ch;
 return;
 }

 index++;

 if (str[index] == '0') {
 decode(root->left, index, str);
 }
 else {
 decode(root->right, index, str);
 }
}

// Builds Huffman Tree and decodes the given input text
void buildHuffmanTree(string text)
{
 // base case: empty string
 if (text == EMPTY_STRING) {
 return;
 } 

 // count the frequency of appearance of each character
 // and store it in a map
 unordered_map<char, int> freq;
 for (char ch: text) {
 freq[ch]++;
 }

 // Create a priority queue to store live nodes of the Huffman tree
 priority_queue<Node*, vector<Node*>, comp> pq;

 // Create a leaf node for each character and add it
 // to the priority queue.
 for (auto pair: freq) {
 pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
 }

 // do till there is more than one node in the queue
 while (pq.size() != 1)
 {
 // Remove the two nodes of the highest priority
 // (the lowest frequency) from the queue

 Node* left = pq.top(); pq.pop();
 Node* right = pq.top(); pq.pop();

 // create a new internal node with these two nodes as children and
 // with a frequency equal to the sum of the two nodes' frequencies. 
 // Add the new node to the priority queue.

 int sum = left->freq + right->freq;
 pq.push(getNode('\0', sum, left, right));
 }

 // `root` stores pointer to the root of Huffman Tree
 Node* root = pq.top();

 // Traverse the Huffman Tree and store Huffman Codes
 // in a map. Also, print them
 unordered_map<char, string> huffmanCode;
 encode(root, EMPTY_STRING, huffmanCode);

 cout << "\n\tHuffman Codes are: \n\n";
 for (auto pair: huffmanCode) {
 cout <<"\t\t"<< pair.first << "\t" << pair.second << endl;
 }

 cout << "\n\tOriginal Text:\n\n\t\t" << text << endl;


 // Print encoded string
 string str;
 for (char ch: text) {
 str += huffmanCode[ch];
 }
 
 cout << "\n\tHuffman Encoded Text\n\n\t\t" << str << endl;
 cout << "\n\tHuffman Decoded Text\n\n\t\t";

 if (isLeaf(root))
 {
 // Special case: For input like a, aa, aaa, etc.
 while (root->freq--) {
 cout << root->ch;
 }
 }
 else {
 // Traverse the Huffman Tree again and this time,
 // decode the encoded string
 int index = -1;
 while (index < (int)str.size() - 1) {
 decode(root, index, str);
 }
 }
 cout<<"\n\n\tCompression Ratio ";
 double ASCII=text.size()*8;
 double huff=str.size();
 double compress=huff/ASCII;
 cout<<"\n\n\tText Size in ASCII : "<<ASCII;
 cout<<"\n\tText Size in Huffman Encoding : "<<huff;

 cout<<"\n\n\tCompression Ration : "<<compress*100;
}
 
// Huffman coding algorithm implementation in C++
int main()
{
 char text[1000];
 cout << "\n\tEnter Text: ";
 cin.get(text, 1000);
 buildHuffmanTree(text);

 return 0;
} 
