
#include <utility>
#include <fstream>
#include <iostream>

#include "configuration.h"

using namespace std;

Configuration::Configuration(const string &file_path)
:_file_path(move(file_path))
{
    ifstream ifs(_file_path);
    if(!ifs){
        cout << "file open error" << endl;
    }
    ifs >> _english_dir;
    ifs >> _chinese_dir;
    ifs.close();
}


