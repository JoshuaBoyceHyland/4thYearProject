#ifndef FILEREADING_H
#define FILEREADING_H


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <filesystem>

namespace FileReading {

	/// <summary>
	/// Tels us whether the file is a png
	/// </summary>
	bool isPNG(std::string t_fileName);

	/// <summary>
	/// Readds the file and returns the line in the a vector
	/// </summary>
	/// <param name="t_path"></param>
	/// <returns></returns>
	std::vector < std::vector<int>> readFile(std::string t_path);

	/// <summary>
	/// gets all the the file paths within a file
	/// </summary>
	std::vector<std::string> getAllInFile(std::string t_pathToFile);
}

#endif
