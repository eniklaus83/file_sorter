#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <map>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: ./file_sorter <source file> <target file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
	std::string targetfile = argv[2];

    std::ifstream inputFile(filename);
		
    if (!inputFile) {
        std::cout << "File '" << filename << "' not found." << std::endl;
        return 1;
    }

    std::map<std::string, std::unordered_set<std::string>> headerDataMap;
    std::string currentHeader;
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            // Empty line, skip
            continue;
        } else if (line[0] == 'H') {
            // Line starts with 'H', treat it as a header
            currentHeader = line;
        } else if (line[0] == 'P') {
            // Line starts with 'P', treat it as data line
            headerDataMap[currentHeader].insert(line);
        }
    }

    inputFile.close();

    std::ofstream outputFile(targetfile);
    if (!outputFile) {
        std::cout << "Error creating output file." << std::endl;
        return 1;
    }

    // Output the headers and sorted unique data lines
    for (const auto& headerData : headerDataMap) {
        outputFile << headerData.first << std::endl;
        std::vector<std::string> sortedDataLines(headerData.second.begin(), headerData.second.end());
        std::sort(sortedDataLines.begin(), sortedDataLines.end());
        for (const auto& dataLine : sortedDataLines) {
            outputFile << dataLine << std::endl;
        }
    }

    outputFile.close();

    std::cout << "File '" << filename << "' has been sorted, duplicate lines removed, and original structure maintained." << std::endl;
    std::cout << "Sorted output saved to: " << targetfile << std::endl;

    return 0;
}
