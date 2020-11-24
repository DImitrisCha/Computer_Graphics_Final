//
//  Vector.hpp
//  Assignment4
//
//  Created by Miguel Donado on 11/6/20.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include <math.h>

class Vector {
private:
    float m_x;
    float m_y;
    float m_z;
    float m_length;
    void recalculateLength();
    
public:
    Vector(float, float, float);
    ~Vector(void);
    Vector operator+(const Vector& v);
    Vector operator-(const Vector& v);
    Vector operator*(float c);
    Vector operator/(float c);
    float dot(Vector v);
    void normal();
    float x();
    float y();
    float z();
};

#endif /* Vector_hpp */
