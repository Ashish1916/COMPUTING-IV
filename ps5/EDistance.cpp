// Copyright Ashish Kosana [2024]
#include "EDistance.hpp"
#include <algorithm>
#include <stdexcept>

EDistance::EDistance(const std::string& x, const std::string& y) : x(x), y(y) {
    if (x.empty() || y.empty()) {
        throw std::invalid_argument("Input strings must not be empty.");
    }
    opt.resize(x.size() + 1, std::vector<int>(y.size() + 1, 0));
}

int EDistance::penalty(char a, char b) {
    return (a == b) ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
    return std::min({a, b, c});
}

void EDistance::calculateOptDistance() {
    for (size_t i = 0; i <= x.size(); ++i)
        opt[i][y.size()] = 2 * (x.size() - i);

    for (size_t j = 0; j <= y.size(); ++j)
        opt[x.size()][j] = 2 * (y.size() - j);

    for (int i = x.size() - 1; i >= 0; --i) {
        for (int j = y.size() - 1; j >= 0; --j) {
            int matchOrMismatch = opt[i + 1][j + 1] + penalty(x[i], y[j]);
            int gapInX = opt[i + 1][j] + 2;
            int gapInY = opt[i][j + 1] + 2;
            opt[i][j] = min3(matchOrMismatch, gapInX, gapInY);
        }
    }
}

int EDistance::optDistance() {
    calculateOptDistance();
    return opt[0][0];
}

std::string EDistance::alignment() {
    std::string result;
    std::string::size_type i = 0;
    std::string::size_type j = 0;

    while (i < x.size() || j < y.size()) {
        // Check bounds before accessing opt[i][j]
        if (i < x.size() && j < y.size() &&
            opt[i][j] == opt[i + 1][j + 1] + penalty(x[i], y[j])) {
            // Align characters from both strings
            result += x[i] + std::string(" ") + y[j] + " " +
                      std::to_string(penalty(x[i], y[j])) + "\n";
            i++;
            j++;
        } else if (i < x.size() && (j == y.size() ||
                   opt[i][j] == opt[i + 1][j] + 2)) {
            // Align character from x with a gap in y
            result += x[i] + std::string(" - 2\n");
            i++;
        } else if (j < y.size()) {
            // Align character from y with a gap in x
            result += "- " + std::string(1, y[j]) + " 2\n";
            j++;
        }
    }

    return result;
}
