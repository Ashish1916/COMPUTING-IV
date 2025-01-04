// Copyright [2024] Ashish Kosana

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <random>

class RandWriter {
 public:
    RandWriter(const std::string& input_text, size_t order);
    size_t orderK() const;

    int freq(const std::string& kgram) const;
    int freq(const std::string& kgram, char c) const;
    char kRand(const std::string& kgram);
    std::string generate(const std::string& kgram, size_t L);

    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    void populateKgramMap();
    char weightedRandomChar(const std::unordered_map<char, int>& charFreq) const;

    size_t k;
    std::string text;
    std::unordered_map<std::string, std::unordered_map<char, int>> kgram_map;
};
