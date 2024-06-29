#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <bits/stdc++.h>
#include "huffman.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->outputLabel1->setReadOnly(true);
    ui->outputLabel2->setReadOnly(true);
    ui->outputLabel3->setReadOnly(true);
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

}

void MainWindow :: onButtonClicked(){

    QString inputText = ui->inputText->toPlainText();
    QString output1 = "";
    QString output2 = "";
    QString output3 = "";

    std :: string text = "";
    text = inputText.toStdString();

    if(!text.empty()){

        Huffman instance;
        HuffmanNode *root = instance.buildHuffmanTree(text);
        std::unordered_map<char, std::string> huffmanCode;
        instance.generateCodes(root, "", huffmanCode);

        std :: string huffmanTable = "";
        for (auto &pair : huffmanCode)
        {
            std::ostringstream oss;
            oss << pair.first << ": " << pair.second << "\n";
            huffmanTable += oss.str();
        }

        output2 = QString :: fromStdString(huffmanTable);
        std :: cout << huffmanTable << std :: endl;

        std::string compressedText = instance.compressText(text, huffmanCode);

        output1 = QString :: fromStdString(compressedText);
        std :: cout << compressedText << std :: endl;

        std::string decompressedText = instance.decompressText(compressedText, root);
        output3 = QString :: fromStdString(decompressedText);
        std :: cout << decompressedText << std :: endl;

        instance.deleteTree(root);
    }
    /*
    else{
        return;
    }
*/

    ui->outputLabel1->setPlainText(output1);
    ui->outputLabel2->setPlainText(output2);
    ui->outputLabel3->setPlainText(output3);
}

MainWindow::~MainWindow()
{
    delete ui;
}
