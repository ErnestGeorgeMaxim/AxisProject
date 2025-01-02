#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct Node {
    char data;
    int freq;
    Node* left, * right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (const auto& pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root)
        return;

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

string encode(const string& str, const unordered_map<char, string>& huffmanCodes) {
    string encodedString = "";
    for (char c : str) {
        encodedString += huffmanCodes.at(c);
    }
    return encodedString;
}

string decode(const string& str, Node* root) {
    string decodedString = "";
    Node* current = root;
    for (char c : str) {
        if (c == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {
            decodedString += current->data;
            current = root;
        }
    }
    return decodedString;
}

int main() {
    string inputString = "Huffman coding is a data compression algorithm.";

    unordered_map<char, int> freqMap;
    for (char c : inputString) {
        freqMap[c]++;
    }

    Node* root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    string encodedString = encode(inputString, huffmanCodes);
    cout << "Encoded string: " << encodedString << endl;

    string decodedString = decode(encodedString, root);
    cout << "Decoded string: " << decodedString << endl;
    delete root;

    return 0;
}
