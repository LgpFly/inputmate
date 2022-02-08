#ifndef __MYTASK_H__
#define __MYTASK_H__

#include <string>
#include <queue>
#include <jsoncpp/json/json.h>
#include "./tcpconnection.h"
#include "./mydict.h"
#include "./configuration.h"
#include "./cache.h"
#include "./cachemanage.h"
#include "./message.pb.h"
using namespace std;

class MyCompare{
public:
    bool operator()(const MyResult &lhs, const MyResult &rhs){
        if(lhs.dist != rhs.dist){
            return lhs.dist < rhs.dist;
        }else{
            return lhs.freq > rhs.freq;
        }
    }
};


class MyTask{

public:

    MyTask(const string& querry, TcpConnectionPtr p_conn)
        :_querry(querry), _p_conn(p_conn)
    {}

    void execute();
private:
    void querryIndex();
    void statistic(set<int>&);
    int distance(const string &rhs);
    bool response(Cache &cache);
    vector<string> getOne(const string &word);

private:
    string _querry;
    TcpConnectionPtr _p_conn;
    priority_queue<MyResult, vector<MyResult>, MyCompare> _result;
};

#endif


