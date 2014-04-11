#ifndef INTVECTOR_H
#define INTVECTOR_H

#include <ostream>
namespace PushMe{

struct IntVector{

    int x, y;

    explicit IntVector(int x, int y):x{x}, y{y}{}
    explicit IntVector(int size):IntVector(size, size){}
    explicit IntVector():IntVector(0){}

    IntVector& operator+=(IntVector vec){x+=vec.x; y+=vec.y; return *this;}
    IntVector& operator-=(IntVector vec){x-=vec.x; y-=vec.y; return *this;}
};

inline IntVector operator+(IntVector v1, IntVector v2){return v1+=v2;}
inline IntVector operator-(IntVector v1, IntVector v2){return v1-=v2;}
inline bool operator==(IntVector v1, IntVector v2){return v1.x==v2.x && v1.y==v2.y;}
inline bool operator!=(IntVector v1, IntVector v2){return !(v1==v2);}

inline std::ostream& operator<<(std::ostream& str, const IntVector& vec){str<<"x:"<<vec.x<<", y:"<<vec.y; return str;}
}
#endif // INTVECTOR_H
