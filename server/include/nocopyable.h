#ifndef __NOCOPYABLE_H__
#define __NOCOPYABLE_H__

class Nocopyable{
public:
    Nocopyable() = default;
    ~Nocopyable() = default;

private:
    Nocopyable(const Nocopyable& rhs);
    Nocopyable& operator=(const Nocopyable& rhs);

};



#endif
