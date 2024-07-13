#include <optional>

#include "FileParser.h"

namespace PathTracer::FileParser
{

static void printFileNode(FileNode *root)
{
    for (int i = 0; i < root->depth; i++) std::cout << "    ";
    std::cout << root->name << ": ";

    if (root->value.empty()) {
        std::cout << "\n";
        for (int i = 0; i < root->childrenCount; i++) {
            printFileNode(root->children[i]);
        }
    } else {
        std::cout << root->value << "\n";
    }
}

static void printFileStructure(const char *fileName)
{
    auto parsedFile = parseFile(fileName);


    if (!parsedFile.has_value()) return;

    FileNode *fileRoot = parsedFile.value();

    printFileNode(fileRoot);
}

static bool checkFileExtension(std::string &fileName, std::string &fileExtension)
{
    return fileName.ends_with(fileExtension);
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
        std::cerr << "Indentation error in file!";
        return -1;
    }

    return countIndentationSpaces(line) / INDENTATION_SPACES;
}

static std::optional<FileNode*> getParentAtDepth(FileNode *fileNode, int depth)
{
    while(fileNode)
    {
        if(fileNode->depth == depth) return fileNode;
        fileNode = fileNode->parent;
    }

    return {};
}

std::optional<FileNode*> parseFile(const std::string &fileName)
{

    std::array<std::string, 200> tokenStack;
    size_t stackTop = 0;

    std::ifstream fileInputStream(fileName);

    if(!fileInputStream.is_open())
    {
        std::cerr << "File cannot be opened!\n";
        return {};
    }

    std::string line;

    enum ActionMode {AppendToName, AppendToValue};

    ActionMode appendMode = AppendToName;
    FileNode* root = new FileNode;

    while (getNonEmptyLine(fileInputStream, line))
    {
        int depth = indentationCount(line);

        auto queryResult = getParentAtDepth(root, depth-1);

        if(!queryResult.has_value())
        {
            std::cerr << "Indentation error, cannot parse file!";
            return {};
        }

        root = queryResult.value();
        root->children[root->childrenCount++] = new FileNode(root);
        root = root->children[root->childrenCount - 1];

        for(char c : line)
        {
            if(c == ' ')
            {
                continue;
            }
            else if(c == ':')
            {
                appendMode = AppendToValue;
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

        appendMode = AppendToName;
    }

    return getParentAtDepth(root, -1);
}

};
