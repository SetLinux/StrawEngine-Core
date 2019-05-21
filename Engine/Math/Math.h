#pragma once
#include <cmath>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <type_traits>
struct X_Vector {

  float x, y, z , w;
  X_Vector() : x(0), y(0), z(0), w(0) {}

  X_Vector(float x, float y) {
    this->x = x;
    this->y = y;
    this->z = 0;
    this->w = 0;
  }
  X_Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 0;
  }

  X_Vector(float x, float y, float z,float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
  X_Vector Normalize() {
    float length = std::sqrt(std::pow(this->x,2) + std::pow(this->y,2));
    if(length == 0) return *this;
    return *this / length; 
  }
  // Vector On Vector Operators
  X_Vector operator+(const X_Vector &other) const {
    return X_Vector(x + other.x, y + other.y, z + other.z);
  }
  X_Vector operator-(const X_Vector &other) const {
    return X_Vector(x - other.x, y - other.y, z - other.z);
  }

  X_Vector operator*(const X_Vector &other) const {
    return X_Vector(x * other.x, y * other.y, z * other.z);
  }

  X_Vector operator/(const X_Vector &other) const {
    return X_Vector(x / other.x, y / other.y, z / other.z);
  }

  // Float Operators OverLoading
  X_Vector operator+(const float &other) const {
    return X_Vector(x + other, y + other, z + other);
  }
  X_Vector operator-(const float &other) const {
    return X_Vector(x - other, y - other, z - other);
  }

  X_Vector operator*(const float &other) const {
    return X_Vector(x * other, y * other, z * other);
  }

  X_Vector operator/(const float &other) const {
    return X_Vector(x / other, y / other, z / other);
  }
   // Logical Operators
  bool operator==(const X_Vector &other) const {
    return (x == other.x && y == other.y && z == other.z);
  }
  bool operator!=(const X_Vector &other) const {
    return (x != other.x || y != other.y || z != other.z);
  }
  X_Vector operator+=(const X_Vector &other) const{
    return X_Vector(this->x + other.x , this->y + other.y);
  }

  X_Vector operator*(const glm::mat4 &other) {

  glm::vec4 temp = glm::vec4(x, y, z, 1.0f);
  glm::vec4 endtemp = temp * other;
  return X_Vector(endtemp.x, endtemp.y);
}
  template <typename T> static X_Vector fromVec(const T& other, bool zExist);
  template <class T> static X_Vector fromVec(const T& other);
  template <typename T> static T ToVec(const X_Vector& other, bool zExist);
  template <typename T> static T ToVec(const X_Vector& other);

  static X_Vector Interpolate(const X_Vector& previous, const X_Vector& current,
                              float alpha) {
    // state = currentState * alpha + previousState * (1-alpha)
    X_Vector res(0, 0, 0);
    float oneMinusRatio = 1 - alpha;
    res = (current * alpha) + (previous * (oneMinusRatio));
    return res;
  }
  static float Distance(const X_Vector& pointa, const X_Vector& pointb) {
    float undersqrt =
      std::pow(pointb.x - pointa.x, 2) + std::pow(pointb.y - pointa.y, 2);
    float result = std::sqrt(undersqrt);
    return result;
  }
  static float Dot(const X_Vector& pointa,const X_Vector& pointb){
    return (pointa.x * pointb.x ) + (pointa.y * pointb.y);
  }
};
// Just Some Template Work
template <class T> T X_Vector::ToVec(const X_Vector& other, bool zExist) {
  T x;
  x.x = other.x;
  x.y = other.y;
  if (zExist)
    x.z = other.z;
  return x;
}
static float Radians(float degrees){
  float multiplier= M_PI / 180.f;
  return degrees * multiplier;
}

inline std::ostream &operator<<(std::ostream &os, const X_Vector &vec) {
  os << "X : " << vec.x << " Y : " << vec.y << " Z : " << vec.z;
  return os;
}

template <typename T> inline X_Vector X_Vector::fromVec(const T& other, bool zExist) {
  return X_Vector(other.x, other.y, zExist ? other.z : 0);
}
// Just Some Template Work
template <class T> T X_Vector::ToVec(const X_Vector& other) {
  T x;
  x.x = other.x;
  x.y = other.y;
  return x;
}

template <typename T> inline X_Vector X_Vector::fromVec(const T& other) {
  return X_Vector(other.x, other.y, 0);
}

struct Vertex {
  X_Vector position;
  X_Vector TexCoord;
};
