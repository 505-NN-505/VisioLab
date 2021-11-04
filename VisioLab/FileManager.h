#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>

#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "SHELL32.LIB")

namespace VisioLab {
    template <typename T, typename S>
    inline std::ostream& operator<<(std::ostream& os, const std::pair<T, S>& pr) {
        os << "(" << pr.first << ", " << pr.second << ")";
        return os;
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
        os << "[";
        for (int i = 0; i < v.size(); ++i) {
            os << v[i];
            if (i != v.size() - 1) os << " ";
        }
        os << "]\n";
        return os;
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& os, const std::set<T>& v) {
        os << "[";
        for (auto it : v) {
            os << it << " ";
            if (it != *v.rbegin()) os << " ";
        }
        os << "]";
        return os;
    }

    template <typename T, typename S>
    inline std::ostream& operator<<(std::ostream& os, const std::map<T, S>& mp) {
        for (auto it : mp)
            os << it.first << " : " << it.second << "\n";
        return os;
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& os, const std::stack<T>& st) {
        auto temp = st;
        while (!temp.empty()) {
            os << temp.top() << "\n";
            temp.pop();
        }
        return os;
    }

    class FileManager {
    protected:
        std::ofstream os;
    public:
        FileManager() { }
        FileManager(const std::string& fileName) {
            os.open(fileName);
        }
        void writeToDisk(void) { }
    };
}