#include <bits/stdc++.h>
#include "../include/huffman.hpp"


int main() {

    std::string text;
    std ::getline(std ::cin, text);
    std ::cout << "Original Text : " << text << std ::endl;

    Huffman instance;
    HuffmanNode *root = instance.buildHuffmanTree(text);
    
    std::unordered_map<char, std::string> huffmanCode;
    instance.generateCodes(root, "", huffmanCode);
    //std ::cout << huffmanCode.size() << std ::endl;


    std ::cout << "Code book : " << std ::endl;
    for (auto pair : huffmanCode)
    {
        std :: cout << pair.first << ": " << pair.second << std :: endl;
    }


    std::string compressedText = instance.compressText(text, huffmanCode);
    std ::cout << "Compressed text : " ;
    std :: cout << compressedText << std :: endl;

    // Decompress the text and output to a file
    std::string decompressedText = instance.decompressText(compressedText, root);
    std ::cout << "Decompressed text : ";
    std ::cout << decompressedText << std ::endl;

    instance.deleteTree(root);
    return 0;
}
