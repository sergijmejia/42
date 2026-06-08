#include "FileReplacer.hpp"
#include <fstream>

FileReplacer::FileReplacer(void) {
}

FileReplacer::FileReplacer(const std::string& fileName, const std::string& replaceFrom, const std::string& replaceTo) {
    _inFile = fileName;
    _outFile = fileName + ".replace";
    _s1 = replaceFrom;
    _s2 = replaceTo;
}

FileReplacer::~FileReplacer(void) {
}

void FileReplacer::setInFile (const std::string& fileName) {
    _inFile = fileName;
}

void FileReplacer::setOutFile (const std::string& fileName) {
    _outFile = fileName + ".replace";
}

void FileReplacer::setS1 (const std::string& str1) {
    _s1 = str1;
}

void FileReplacer::setS2 (const std::string str2) {
    _s2 = str2;
}

const std::string& FileReplacer::getInFile(void) const {
    return _inFile;
}

const std::string& FileReplacer::getOutFile(void) const {
    return _outFile;
}

const std::string& FileReplacer::getS1(void) const {
    return _s1;
}

const std::string& FileReplacer::getS2(void) const {
    return _s2;
}

bool FileReplacer::process(void) {
    std::ifstream   inputFile(_inFile.c_str());
    std::string     lineToReplace;
    size_t          pos;
    size_t          lenS1 = _s1.length();
    size_t          lenS2 = _s2.length();
    size_t          lenLine;
    size_t          i = 0;

    if(!inputFile.is_open()) {
        std::cerr << "Error. " << _inFile << " could not be opened" << std::endl;
        return false;
    }

    std::ofstream outputFile(_outFile.c_str());

    if(!outputFile.is_open()) {
        std::cerr << "Error. " << _outFile << " could not be created" << std::endl;
        inputFile.close();
        return false;
    }
 
    while (std::getline(inputFile, lineToReplace)) {
        lenLine = lineToReplace.length();
        while (i < lenLine) {
            pos = lineToReplace.find(_s1, i);
            if (pos == std::string::npos) {
                i = lenLine;
                break;
            }
            lineToReplace.erase(pos, lenS1);
            lineToReplace.insert(pos, _s2);
            i = pos + lenS2;
            lenLine = lineToReplace.length();
        }
        outputFile << lineToReplace;
        if (!inputFile.eof()) {
            outputFile << std::endl;
        }
        i = 0;
    }
    inputFile.close();
    outputFile.close();
    return true;
}