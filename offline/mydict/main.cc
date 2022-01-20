#include <iostream>
#include <memory>

#include "configuration.h"
#include "splittool.h"
#include "dictproducer.h"
#include "getindex.h"
#include "../cppjieba/include/cppjieba/Jieba.hpp"

using namespace std;

const char* const DICT_PATH = "../cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "../cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../cppjieba/dict/stop_words.utf8";

const string AID_DICT_PATH = "../server/data/dict.txt";
const string AID_INDEX_PATH = "../server/data/index.txt";

int main(){
    Configuration *p_config = Singleton<Configuration>::getInstance("configure.txt");
    SplitToolJieba *p_tool = new SplitToolJieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);
    DictProducer my_dict_producer(p_config->getEnglishDir(), p_config->getChineseDir(), AID_DICT_PATH, p_tool);
    my_dict_producer.buildEnglishDict();
    my_dict_producer.buildChineseDict();
    my_dict_producer.storeDict();
    GetIndex my_index(AID_DICT_PATH, AID_INDEX_PATH, "stop_words_zh.txt");
    my_index.constructIndex();
    my_index.storeIndex();
    Singleton<Configuration>::destroy();
    return 0;
}
