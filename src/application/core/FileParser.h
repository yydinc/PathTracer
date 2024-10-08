#ifndef FILE_PARSER_H
#define FILE_PARSER_H


#include <fstream>
#include <iostream>
#include <array>

namespace PathTracer::FileParser
{

constexpr static int INDENTATION_SPACES = 4;


 class FileParserException : public std::exception
 {
  public:
     const char *what() const noexcept override
     {
         return "FileParserException!";
     }
 };


class FileNode
{
 public:
    FileNode() = default;
    explicit FileNode(FileNode *parent) : parent(parent), depth(parent->depth+1){}
    ~FileNode()
    {
        for(int i = 0; i < childrenCount; i++)
        {
            delete children[i];
        }
    }

    inline void appendToName(char c) {name += c; }
    inline void appendToValue(char c) {value += c; }

    inline FileNode *operator[](const std::string &childName)
    {
        for(int i = 0; i < childrenCount; i++)
        {
            if(children[i]->name == childName) return children[i];
        }

        throw FileParserException();
    }
    inline double getDouble(const std::string &childName) { return std::stod((*this)[childName]->value); }
    inline int getInt(const std::string &childName) { return std::stoi((*this)[childName]->value); }

 public:
    std::string name;
    std::string value;
    int depth = -1;

    std::array<FileNode*, 10> children{};
    int childrenCount = 0;

    FileNode *parent = nullptr;
};

FileNode *parseFile(const path &fileName);

};

#endif  //  FILE_PARSER_H
