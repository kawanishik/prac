#include <string>
#include <vector>
#include <unordered_map>

namespace b3prac {

class StringSet {
public:
    uint8_t kLeafChar = 0;
    static constexpr uint8_t kEmptyCheck = 0xFF;
    static constexpr int kEmptyBase = 0xFFFFFFFF;
private:
    struct Unit {
        int base,check;
        Unit(int b=kEmptyBase, int c=kEmptyCheck) : base(b),check(c){}
    };
    std::vector<Unit> bc_;

public:
    StringSet() = default;
    StringSet(const std::vector<std::string>& str_list) {
        // Create table
        std::vector<std::unordered_map<uint8_t, int>> table(1);
        for (auto& key : str_list) {
            int node = 0;
            for (uint8_t c : key) {
                if (table[node].count(c) == 1) { // exists
                    node = table[node][c];
                } else {
                    auto new_node = table.size();
                    table.emplace_back();
                    table[node][c] = new_node;
                    node = new_node;
                }
            }
            if (table[node].count(kLeafChar) == 0) {
                table[node][kLeafChar] = 1;
            }
        }

        // Convert from table to Double-Array
        std::vector<int> row_to_index(table.size());
        bc_ = {0, kEmptyCheck}; // set root element
        row_to_index[0] = 0;
        for (int i = 0; i < table.size(); i++) {
            auto& row = table[i];
            if (row.empty())
                continue;
            int parent_index = row_to_index[i];
            int base = find_base(row);
            bc_[parent_index].base = base;
            for (auto p : row) {
                uint8_t c = p.first;
                int next_row = p.second;
                int next_index = base ^ c;
                expand(next_index);
                bc_[next_index].check = parent_index;
                row_to_index[next_row] = next_index;
            }
        }
    }

    bool contains(const std::string& key) const {
        int node = 0; // root
        for (uint8_t c : key) {
            int next_node = bc_[node].base ^ c;
            if (bc_[next_node].check != node) {
                std::cout << key << std::endl;
                return false;
            }
            node = next_node;
        }
        // '\0'
        int next_node = bc_[node].base + kLeafChar;
        return bc_[next_node].check == node;
    }

private:
    int find_base(const std::unordered_map<uint8_t, int>& row) const {
        for (int base = 0; true; ++base) {
            bool found = true;
            for (auto p : row) {
                uint8_t c = p.first;
                int next_row = p.second;
                int index = base ^ c;
                if (index < bc_.size() and bc_[index].check != kEmptyCheck) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return base;
            }
        }
        return bc_.size();
    }

    void expand(int index) {
        if (index < bc_.size())
            return;
        bc_.resize(index+1);
    }


};

}