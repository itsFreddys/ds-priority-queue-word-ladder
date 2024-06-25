#include "convert.hpp"
#include <string>
#include <sstream>
#include <unordered_set>
#include <string>
#include "MyPriorityQueue.hpp"
#include <unordered_map>
#include <algorithm>

// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
{
    std::string line, word;
    std::stringstream ss;

    while(	getline(in, line) )
    {
        ss.clear();
        ss << line;
        while( ss >> word )
        {
            words.insert( word );
        }
    }

}

int letter_delta(const std::string & current, const std::string & s2){
    int diff = 0;
    for (size_t i = 0; i < current.size(); ++i){
        if (current[i] != s2[i]){
            diff++;
        }
    }
    return diff;
}

int get_heur(const std::string & s1, const std::string & current, const std::string & s2, const int depth)
{
    // H(s1, current, s2) = LCD(s1, current) + LetterDelta(current, s2)
    //lcd depth, i think
    // letterDelta is the characters different between current and s2
    return depth + letter_delta(current, s2);

}


// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
    std::vector< std::string > ret;
    // base cases
    if (s1 == s2){ return ret;} // s1 and s2 are the same
    if (s1.size() != s2.size()) { return ret;}      // s1 and s2 are different sizes, so path not possible
    if (words.count(s2) == 0) { return ret; } // s2 are not part of the words

    MyPriorityQueue<std::string> q;
    std::unordered_map<std::string, int> depth_map;
    std::unordered_map<std::string, std::string> set;
    std::string temp_s;
    std::string alt_s;
    int depth = 0;
    int h = get_heur(s1, s1, s2, depth);
    q.insert(s1, h);
    depth_map[s1] = 0;

    while (!q.isEmpty()){
        temp_s = q.min();
		// std::cout << "size = " << q.size();
        q.extractMin();
		// std::cout << temp_s << "\n";

        for (size_t i=0; i < temp_s.size(); ++i){
            alt_s = temp_s; // cat -> *at -> c*t -> ca*
            for (char c = 'a'; c <= 'z'; ++c){
                alt_s[i] = c;
                // if alt word is end word, break
                if (alt_s == s2) {
                    set[alt_s] = temp_s;
                    break;
                }
                // check if alt_string is part of words, check that it doesnt exist in map set
                if (words.count(alt_s) == 1 && depth_map.count(alt_s) == 0){
                    depth_map[alt_s] = depth_map[temp_s] + 1;
                    set[alt_s] = temp_s;
                    h = get_heur(s1, alt_s, s2, depth_map[alt_s]);
                    q.insert(alt_s, h);
					
                }
            } if (alt_s == s2) { break;}
        } if(alt_s == s2){ break;}
    }

    if (set.empty())
        {return ret;}  // No path found
	
    std::string current = s2;
    while (current != s1){
        ret.push_back(current);
        current = set[current];
    }
    ret.push_back(s1);

    std::reverse(ret.begin(), ret.end());

    return ret;  // stub obviously
}

