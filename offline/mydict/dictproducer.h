#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>

#include "nocopyable.h"
#include "splittool.h"

using namespace std;

class DictProducer
:public Nocopyable
{
public:
    DictProducer(const string, const string, const string &, SplitToolJieba *);
    ~DictProducer();
    void buildEnglishDict();
    void buildChineseDict();
    void storeDict();
    vector<pair<string, int>>& getIndict(){
        return _indict;
    }

private:
    void processEnglishWord(string &word);
    void processChineseWord(string &word);
    void construct_indict();

    string _english_dir;
    string _chinese_dir;
    string _aid_file_path;
    vector<string> _english_files;
    vector<string> _chinese_files;
    map<string, int> _dict;
    vector<pair<string, int>> _indict;
    shared_ptr<SplitToolJieba> _split_tool;

};

#endif
