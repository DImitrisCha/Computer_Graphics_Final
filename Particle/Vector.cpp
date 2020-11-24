//
//  Vector.cpp
//  Assignment4
//
//  Created by Miguel Donado on 11/6/20.
//

#include "Vector.hpp"

Vector::Vector(float x, float y, float z){
    m_x = x;
    m_y = y;
    m_z = z;
    m_length = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

Vector::~Vector(){
    
}

Vector Vector::operator+(const Vector& v){
    return Vector(this->m_x + v.m_x, this->m_y + v.m_y, this->m_z + v.m_z);
}


Vector Vector::operator-(const Vector& v){
    return Vector(this->m_x - v.m_x, this->m_y - v.m_y, this->m_z - v.m_z);
}

Vector Vector::operator*(float c){
    return Vector(c * this->m_x, c * this->m_y, c * this->m_z);
}

Vector Vector::operator/(float c){
    return Vector(this->m_x / c, this->m_y / c, this->m_z / c);
}

float Vector::dot(Vector v){
    return (this->m_x*v.m_x + this->m_y*v.m_y + this->m_z*v.m_z);
}

void Vector::recalculateLength(){
    m_length = sqrt(pow(m_x, 2.0) + pow(m_y, 2.0) + pow(m_z, 2.0));
}

void Vector::normal(){
    recalculateLength();
    
    m_x = m_x / m_length;
    m_y = m_y / m_length;
    m_z = m_z / m_length;
}

float Vector::x(){
    return m_x;
}

float Vector::y(){
    return m_y;
}

float Vector::z(){
    return m_z;
}
