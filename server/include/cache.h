#ifndef __CACHE_H__
#define __CACHE_H__

#include <unordered_map>
#include <string>

using namespace std;

class Cache{
public:
    void readFromFile(string);
    void writeToFile(string);
    void addElement(string, string);
    void update(const Cache&);
    bool find(string);
    string& operator[](string key);

private:
    unordered_map<string, string> _hash_table;
};



#endif
