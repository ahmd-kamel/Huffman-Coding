#ifndef _HUFFMAN_HPP
#define _HUFFMAN_HPP


class HuffmanNode
{
    public:
        char character;
        int freq;
        HuffmanNode *left, *right;

        HuffmanNode(char character, int freq) {
            this->character = character;
            this->freq = freq;
            left = right = nullptr;
        }
};

class Huffman{
public:
    HuffmanNode *buildHuffmanTree(const std::string &text);
    void generateCodes(HuffmanNode *root, std::string str, std::unordered_map<char, std::string> &huffmanCode);
    std::string compressText(const std::string &text, std::unordered_map<char, std::string> &huffmanCode);
    std::string decompressText(const std::string &str, HuffmanNode *root);
    void deleteTree(HuffmanNode *node);

};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};


#endif