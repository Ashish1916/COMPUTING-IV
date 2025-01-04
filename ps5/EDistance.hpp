// Copyright Ashish Kosana [2024]
#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <string>
#include <vector>

class EDistance {
 public:
    EDistance(const std::string& x, const std::string& y);
    static int penalty(char a, char b);
    static int min3(int a, int b, int c);
    int optDistance();
    std::string alignment();

 private:
    std::string x, y;
    std::vector<std::vector<int>> opt;
    void calculateOptDistance();
};

#endif  // EDISTANCE_HPP
