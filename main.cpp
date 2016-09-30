#include <iostream>
#include <string>
#include <map>
#include <deque>

using namespace std;

class solution {
  public:
    string longestSubsKDistinct(const string & s, int k) {
        size_t start, end, minmax;
        size_t idx = 0;
        map<char, deque<size_t>> found;
        while (idx < s.size() && found.size() <= (size_t)k) {
            if (found.find(s[idx]) == found.end())
                found[s[idx]] = deque<size_t>();
            found[s[idx]].push_back(idx);
            ++idx;
        }

        if (idx < s.size()) {
            auto it = found.begin();
            start = it->second.front();
            end = it->second.back();
            minmax = it->second.back();
            while (it != found.end()) {
                if (it->second.front() < start)
                    start = it->second.front();
                if (it->second.back() > end)
                    end = it->second.back();
                if (it->second.back() < minmax)
                    minmax = it->second.back();
                ++it;
            }

            it = found.begin();
            while (it != found.end()) {
                if (it->second.back() <= minmax)
                    found.erase(it);
                else {
                    while (!it->second.empty() && it->second.front() < minmax)
                        it->second.pop_front();
                }
                ++it;
            }
        }

        while (idx < s.size()) {
            while (idx < s.size() && found.size() <= (size_t)k) {
                if (found.find(s[idx]) == found.end())
                    found[s[idx]] = deque<size_t>();
                found[s[idx]].push_back(idx);
                ++idx;
            }

            if (idx < s.size() && found.size() > (size_t)k) {
                size_t start_new, end_new;
                auto it = found.begin();
                start_new = it->second.front();
                end_new = it->second.back();
                minmax = it->second.back();
                while (it != found.end()) {
                    if (it->second.front() < start_new)
                        start_new = it->second.front();
                    if (it->second.back() > end_new)
                        end_new = it->second.back();
                    if (it->second.back() < minmax)
                        minmax = it->second.back();
                    ++it;
                }

                if (end_new-start_new > end-start) {
                    start = start_new;
                    end = end_new;
                }

                it = found.begin();
                while (it != found.end()) {
                    if (it->second.back() <= minmax)
                        found.erase(it);
                    else {
                        while (!it->second.empty() && it->second.front() < minmax)
                            it->second.pop_front();
                    }
                    ++it;
                }
            }
            else if (idx == s.size() && found.size() <= (size_t)k) {
                size_t start_new, end_new;
                auto it = found.begin();
                start_new = it->second.front();
                while (it != found.end()) {
                    if (it->second.front() < start_new)
                        start_new = it->second.front();
                    ++it;
                }
                end_new = idx;

                if (end_new-start_new > end-start) {
                    start = start_new;
                    end = end_new;
                }                
            }
        }

        return s.substr(start, end-start);
    }
};

int main() {
    // string s{"eceba"};
    // string s{"abcbbbbcccbdddadacb"};
    // int k = 2;

    string s{"abcadcacacaca"};
    int k = 3;

    solution soln;
    string longestSubs = soln.longestSubsKDistinct(s, k);
    std::cout << "The longest substring with at most K distinct chars is:\n";
    std::cout << longestSubs << std::endl;
}
