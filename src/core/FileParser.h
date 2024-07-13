#ifndef FILE_PARSER_H
#define FILE_PARSER_H


#include <fstream>
#include <iostream>
#include <array>

namespace PathTracer::FileParser
{

constexpr static int INDENTATION_SPACES = 4;

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

    inline void appendToName(char c) {name += c;}
    inline void appendToValue(char c) {value += c;}
    inline std::optional<FileNode*> operator[](const std::string &childName)
    {
        for(int i = 0; i < childrenCount; i++)
        {
            if(children[i]->name == childName) return children[i];
        }

        return {};
    }

 public:
    std::string name;
    std::string value;
    int depth = -1;

    std::array<FileNode*, 10> children{};
    int childrenCount = 0;

    FileNode* parent = nullptr;
};

std::optional<FileNode*> parseFile(const std::string &fileName);

};

#endif  //  FILE_PARSER_H
