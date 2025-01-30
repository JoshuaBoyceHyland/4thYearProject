#include "FileReader.h"



bool FileReading::isPNG(std::string t_fileName)
{
    std::vector<char> fileType;
    std::string possiblePng;
    int length = t_fileName.length();

    for (int i = 2; i > -1; i--)
    {
        fileType.push_back(t_fileName[length - (i + 1)]);
    }
    for (int i = 0; i < fileType.size(); i++)
    {
        possiblePng.push_back(fileType[i]);
    }

    if (possiblePng == "png")
    {
        return true;
    }

    return false;
}

std::vector<std::vector<int>> FileReading::readFile(std::string t_path)
{
    std::ifstream file;
    file.open(t_path);

    int lineNum = 0;
    std::string currentLine;
    std::vector<std::vector<int>> lines;


    while (std::getline(file, currentLine))
    {
        std::istringstream stringStream(currentLine);
        
        int val;

        lines.push_back(std::vector<int>());
        while (stringStream >> val)
        {
            lines[lineNum].push_back(val);
        }

        lineNum++;

    }
    file.close();
    return lines;
}

std::vector<std::string> FileReading::getAllInFile(std::string t_pathToFile)
{
    std::vector<std::string> fileNames;

    if (std::filesystem::exists(t_pathToFile))
    {
        for (auto file : std::filesystem::directory_iterator(t_pathToFile))
        {
            fileNames.push_back(file.path().string());
        }
    }

    return fileNames;
}

