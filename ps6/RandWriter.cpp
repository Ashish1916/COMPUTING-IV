// Copyright [2024] Ashish Kosana
#include "RandWriter.hpp"
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>


thread_local std::mt19937 gen(std::random_device {}());

RandWriter::RandWriter(const std::string& input_text, size_t order)
    : k(order), text(input_text) {
    if (text.empty()) {
        throw std::invalid_argument("Input text cannot be empty");
    }
    if (k > text.size()) {
        throw std::invalid_argument("Order k cannot exceed input text length");
    }

    if (k > 0) {
        populateKgramMap();
    }
}

size_t RandWriter::orderK() const {
    return k;
}

void RandWriter::populateKgramMap() {
    size_t n = text.size();
    for (size_t i = 0; i < n; ++i) {
        std::string kgram = text.substr(i, k);

        // Wrap-around handling for k-grams
        if (kgram.size() < k) {
            kgram += text.substr(0, k - kgram.size());
        }

        char next_char = text[(i + k) % n];
        kgram_map[kgram][next_char]++;
    }
}

int RandWriter::freq(const std::string& kgram) const {
    if (k == 0) {
        if (kgram.empty()) {
            return text.size();
        }
        throw std::invalid_argument("kgram must be empty when k = 0");
    }
    if (kgram.size() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }
    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) {
        return 0;
    }
    int total = 0;
    for (const auto& pair : it->second) {
        total += pair.second;
    }
    return total;
}

int RandWriter::freq(const std::string& kgram, char c) const {
    if (k == 0) {
        return 0;  // No k-grams exist for k = 0
    }
    if (kgram.size() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }
    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) {
        return 0;
    }
    auto char_it = it->second.find(c);
    return (char_it != it->second.end()) ? char_it->second : 0;
}

char RandWriter::kRand(const std::string& kgram) {
    if (k == 0) {
        throw std::invalid_argument("kRand not valid for k = 0");
    }
    if (kgram.size() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }
    auto it = kgram_map.find(kgram);
    if (it == kgram_map.end()) {
        throw std::invalid_argument("kgram not found in text");
    }
    return weightedRandomChar(it->second);
}

char RandWriter::weightedRandomChar(const std::unordered_map<char, int>& charFreq) const {
    std::vector<char> chars;
    std::vector<int> weights;

    for (const auto& pair : charFreq) {
        chars.push_back(pair.first);
        weights.push_back(pair.second);
    }

    std::discrete_distribution<> dist(weights.begin(), weights.end());
    return chars[dist(gen)];
}

std::string RandWriter::generate(const std::string& kgram, size_t L) {
    if (k == 0) {
        throw std::invalid_argument("Cannot generate text with k = 0");
    }
    if (kgram.size() != k) {
        throw std::invalid_argument("kgram must be of length k");
    }
    if (L < k) {
        throw std::invalid_argument("L must be at least k");
    }

    std::string result = kgram;
    for (size_t i = k; i < L; ++i) {
        char next_char = kRand(result.substr(result.size() - k, k));
        result += next_char;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
    os << "Order: " << rw.k << "\nAlphabet: ";
    std::unordered_set<char> alphabet;
    for (char c : rw.text) {
        alphabet.insert(c);
    }
    for (char c : alphabet) {
        os << c << " ";
    }
    os << "\nFrequencies:\n";
    for (const auto& pair : rw.kgram_map) {
        os << pair.first << ": ";
        for (const auto& sub_pair : pair.second) {
            os << sub_pair.first << "(" << sub_pair.second << ") ";
        }
        os << "\n";
    }
    return os;
}
