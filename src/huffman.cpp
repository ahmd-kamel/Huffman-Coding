#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include "../include/huffman.hpp"


HuffmanNode* Huffman ::  buildHuffmanTree(const std::string& text) {
    
    std::unordered_map<char, int> freqMap;
    for (char c : text) {
        if(c != '\0')
            freqMap[c]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;

    for (auto pair : freqMap) {
        std ::cout << pair.first << " " << pair.second << std::endl;
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    if (pq.size() == 1) {
        HuffmanNode* onlyNode = pq.top();
        HuffmanNode* dummyNode = new HuffmanNode('$', onlyNode->freq);
        dummyNode->left = onlyNode;
        return dummyNode;
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* sum = new HuffmanNode('$', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }


    return pq.top();
}


void Huffman :: generateCodes(HuffmanNode* root, std::string str, std::unordered_map<char, std::string>& huffmanCode) {

    if (!root) return;



    if (root->character != '$') {
        huffmanCode[root->character] = str;
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}


std::string Huffman :: compressText(const std::string& text, std::unordered_map<char, std::string>& huffmanCode) {

    std::string str = "";
    for (char c : text) {
        str += huffmanCode[c];
    }
    return str;
}


std :: string Huffman ::  decompressText(const std::string& str, HuffmanNode* root) {

    std :: string result = "";
    HuffmanNode* currentNode = root;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {
            result += currentNode->character;
            currentNode = root;
        }
    }
    return result;
}

void Huffman :: deleteTree(HuffmanNode *node){

    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;

}
