// Copyright [2024] Ashish Kosana
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>

struct BootRecord {
    int startLine;
    int endLine;
    std::string startTime;
    std::string endTime;
    bool completed;
    int durationMs;
};

std::regex startRegex(R"(\(log\.c\.166\) server started)");
std::regex endRegex(R"(oejs\.AbstractConnector:Started .+)");

int calculateDurationMs(const std::string& start, const std::string& end) {
    std::tm tmStart = {}, tmEnd = {};
    std::istringstream ssStart(start);
    std::istringstream ssEnd(end);
    ssStart >> std::get_time(&tmStart, "%Y-%m-%d %H:%M:%S");
    ssEnd >> std::get_time(&tmEnd, "%Y-%m-%d %H:%M:%S");

    auto startTime = std::chrono::
    system_clock::from_time_t(std::mktime(&tmStart));
    auto endTime = std::chrono::
    system_clock::from_time_t(std::mktime(&tmEnd));
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        endTime - startTime).count();
}

std::vector<BootRecord> parseLogFile(const std::string& filename) {
    std::vector<BootRecord> bootRecords;
    std::ifstream file(filename);
    std::string line;
    int lineNumber = 0;
    BootRecord currentBoot;
    bool inBoot = false;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return bootRecords;
    }

    while (std::getline(file, line)) {
        lineNumber++;
        std::smatch match;

        if (std::regex_search(line, match, startRegex)) {
            if (inBoot) {
                currentBoot.completed = false;
                bootRecords.push_back(currentBoot);
            }
            inBoot = true;
            currentBoot = BootRecord{lineNumber, 0,
            line.substr(0, 19), "", false, 0};
        } else if (inBoot && std::regex_search(line, match, endRegex)) {
            currentBoot.endLine = lineNumber;
            currentBoot.endTime = line.substr(0, 19);
            currentBoot.completed = true;
            currentBoot.durationMs = calculateDurationMs(
            currentBoot.startTime, currentBoot.endTime);
            bootRecords.push_back(currentBoot);
            inBoot = false;
        }
    }

    if (inBoot) {
        currentBoot.completed = false;
        bootRecords.push_back(currentBoot);
    }

    file.close();
    return bootRecords;
}

void generateReport(const std::string&
inputFile, const std::string& outputFile,
                    const std::vector<BootRecord>& bootRecords) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Error: Unable to create output file "
        << outputFile << std::endl;
        return;
    }

    out << "Device Boot Report" << std::endl;
    out << "InTouch log file: " << inputFile << std::endl;
    out << "Summary:" << std::endl << std::endl;

    for (const auto& record : bootRecords) {
        out << "Device Boot - " << std::endl;
        out << record.startLine << "(" << inputFile << "): " << record.startTime
            << " Boot Start" << std::endl;
        if (record.completed) {
            out << record.endLine << "(" << inputFile << "): " << record.endTime
                << " Boot Completed\t   Time: " << record.durationMs << "ms"
                << std::endl;
        } else {
            out << "Boot Incomplete" << std::endl;
        }
        out << std::endl;
    }

    out.close();
    std::cout << "Report generated successfully in: "
    << outputFile << std::endl;
}

std::vector<std::string> getEndTimes(
    const std::vector<BootRecord>& records) {
    std::vector<std::string> endTimes;
    for (const auto& record : records) {
        if (!record.completed) {
            endTimes.push_back(record.startTime);
        }
    }
    return endTimes;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <logfile>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = inputFile + ".rpt";

    auto bootRecords = parseLogFile(inputFile);
    generateReport(inputFile, outputFile, bootRecords);

    auto failedBoots = getEndTimes(bootRecords);
    std::cout << "Failed Boots: " << failedBoots.size() << std::endl;
    for (const auto& time : failedBoots) {
        std::cout << time << std::endl;
    }

    return 0;
}
