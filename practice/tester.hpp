#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

#include "practice.hpp"

namespace b3prac {

class Tester {
private:
    int num;
    std::unordered_map<std::string, bool> samples;
    b3prac::StringSet strset;
public:
    Tester(int num) : num(num) {
        std::string input_name = std::string("s")+char(num+'0')+".txt";
        std::ifstream ifs(input_name);
        if (!ifs) {
            std::cerr<<"File not found input file: "<<input_name<<std::endl;
            exit(0);
        }
        std::vector<std::string> str_list;
        for (std::string s; std::getline(ifs, s); ) {
            str_list.push_back(s);
        }
        for (auto s:str_list)
        strset = b3prac::StringSet(str_list);

        std::string test_name = std::string("t")+char(num+'0')+".txt";
        ifs = std::ifstream(test_name);
        if (!ifs) {
            std::cerr<<"File not found test file: "<<test_name<<std::endl;
            exit(0);
        }
        for (std::string s; std::getline(ifs, s); ) {
            auto key = s.substr(0, s.size()-2);
            char exists = s[s.size()-1];
            samples[key] = exists == '1';
            // std::cout << key << ", " << exists << std::endl;
        }
    }

    bool test() const {
        bool success = true;
        for (auto p : samples) {
            auto key = p.first;
            auto exists = p.second;
            //std::cout << key << ", " << exists << std::endl;
            if (exists != strset.contains(key)) {
                success = false;
                std::cout << "Failed: The \""<<key<<"\" should "<<(!exists?"NOT ":"")<<"be contained!"<<std::endl;
            }
        }
        return success;
    }
};
    
}