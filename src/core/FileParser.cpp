#include <optional>

#include "FileParser.h"

namespace PathTracer::FileParser
{
enum AppendMode {AppendToName, AppendToValue};

static FileNode *addChild(FileNode *root)
{
    if(!root || root->childrenCount == root->children.size()) throw FileParserException();

    return (root->children[root->childrenCount++] = new FileNode(root));
}

static bool getNonEmptyLine(std::ifstream &stream, std::string &line)
{
    while(std::getline(stream, line))
    {
        if(line.empty()) continue;
        return true;
    }

    return false;
}

static int countIndentationSpaces(std::string &line)
{
    int i = 0;

    for (; line[i] == ' '; i++);

    return i;
}

static int indentationCount(std::string &line)
{
    int indentation = countIndentationSpaces(line);
    if(indentation % INDENTATION_SPACES != 0) {
        throw FileParserException();
    }

    return countIndentationSpaces(line) / INDENTATION_SPACES;
}

static FileNode *getParentAtDepth(FileNode *fileNode, int depth)
{
    while(fileNode)
    {
        if(fileNode->depth == depth) return fileNode;
        fileNode = fileNode->parent;
    }

    throw FileParserException();
}

static void parseLine(std::string &line, FileNode *root)
{
    AppendMode appendMode = AppendToName;

    for(char c : line)
        {
            if(c == ' ')
            {
                continue;
            }
            else if(c == ':')
            {
                if(appendMode != AppendToValue) appendMode = AppendToValue;
                else throw FileParserException();
            }
            else if(appendMode == AppendToName)
            {
                root->appendToName(c);
            }
            else
            {
                root->appendToValue(c);
            }
        }
}

FileNode *parseFile(const std::string &fileName)
{
    std::ifstream fileInputStream(fileName);

    std::string line;

    FileNode* root = new FileNode;

    while (getNonEmptyLine(fileInputStream, line))
    {
        int depth = indentationCount(line);

        root = getParentAtDepth(root, depth-1);

        root = addChild(root);

        parseLine(line, root);
    }

    return getParentAtDepth(root, -1);
}

};
