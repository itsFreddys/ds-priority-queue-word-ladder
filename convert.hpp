#ifndef ___CONVERT_HPP
#define ___CONVERT_HPP

#include <string>
#include <unordered_set>
#include <vector>

void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in);


std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words);

int get_heur(const std::string & s1, const std::string & current, const std::string & s2, const int depth);
int letter_delta(const std::string & current, const std::string & s2);

#endif