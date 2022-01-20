#ifndef __GETINDEX_H__
#define __GETINDEX_H__

#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <utility>
#include <unordered_set>

using namespace std;

class GetIndex{

public:
    GetIndex(const string&, const string&, const string&);
    ~GetIndex();
    void constructIndex();
    void storeIndex();

private:
    bool isEnglish(const string & rhs) const;
    vector<string> getOneCharacter(const string & word);

    string _source_file_path;
    string _aid_file_path;
    string _stop_word_file_path;
    vector<pair<string, int>> _dict;
    unordered_set<string> _stop_words;
    unordered_map<string, set<int>> _index;
};


#endif
