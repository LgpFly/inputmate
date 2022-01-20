#ifndef __NOCOPYABLE_H__
#define __NOCOPYABLE_H__

class Nocopyable{

public:
    Nocopyable() = default;
    ~Nocopyable() = default;

private:

    // 把复制构造函数和赋值构造函数私有化
    Nocopyable(const Nocopyable &rhs);
    Nocopyable& operator=(const Nocopyable &rhs);
};



#endif
