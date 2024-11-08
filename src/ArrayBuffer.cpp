#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ArrayBuffer.h"

ArrayBuffer::ArrayBuffer(std::string filename, GLenum usage) : BufferObj(GL_ARRAY_BUFFER, usage) {
    std::vector<float> vector;

    fileToVector(vector, filename);
    for (int x = 0; x < vector.size(); ++x) {
        std::cout << vector[x] << ' ';
    }

    glBindBuffer(target, id);
    glBufferData(target, vector.size() * sizeof(float), vector.data(), usage);
}

void ArrayBuffer::fileToVector(std::vector<float>& vector, std::string filename) {
    std::ifstream file(filename);
    std::string line;

    while(std::getline(file, line)) {
        split(line, ' ', vector);
    }
}

void ArrayBuffer::split(std::string s, char del, std::vector<float>& vector) {
    std::stringstream ss(s);
    std::string word;

    while (!ss.eof()) {
        getline(ss, word, del);
        vector.push_back(std::stof(word));
    }
}