//vector2d.h

#ifndef VECTOR2D
#define VECTOR2D

#include <iostream>

#include <cmath>

#include "defines.h"

class Vector2D
{
 public:
  Vector2D(void);
  Vector2D(double nx, double ny);
  Vector2D(bool v);
  
  //double get_x(void);
  //double get_y(void);
  //double get_z(void);
  //bool get_valid(void);
  
  //void set_x(double nx);
  //void set_y(double ny);
  //void set_z(double nz);
  //void set_xyz(double nx, double ny, double nz);
  //void set_valid(bool v);  
  
  void normalize(void);
  double magnitude(void);
 
  void full_dump(void) const;

  bool valid;
  double x,y;
 protected:
 private:
};

//Vector2D normalize(Vector2D v);
//double magnitude(Vector2D v);
Vector2D rotate(Vector2D v, Vector2D axis, double angle);
Vector2D cross(Vector2D v, Vector2D w);
double dot(Vector2D v, Vector2D w);

Vector2D operator+(Vector2D v, Vector2D w);
Vector2D operator-(Vector2D v, Vector2D w);
Vector2D operator*(Vector2D v, Vector2D w);
 Vector2D operator*(Vector2D v, double w);
 Vector2D operator*(double w, Vector2D v);
Vector2D operator/(Vector2D v, Vector2D w);
 Vector2D operator/(Vector2D v, double w);
 Vector2D operator/(double w, Vector2D v);

//****************
//* Constructors *
//****************

inline Vector2D::Vector2D(void)
{
 x=y=0;
 valid=true;
}

inline Vector2D::Vector2D(double nx, double ny)
{
 x=nx;
 y=ny;
 valid=true;
}

inline Vector2D::Vector2D(bool v)
{
 x=y=0;
 valid=v; 
}

//******************************
//* More complicated functions *
//******************************

//Basic arithmetic (+, -, *, /)

inline Vector2D operator+(Vector2D v, Vector2D w)
{
 return Vector2D(
  v.x + w.x,
  v.y + w.y
 );
}

inline Vector2D operator-(Vector2D v, Vector2D w)
{
 return Vector2D(
  v.x - w.x,
  v.y - w.y
 );
}

inline Vector2D operator*(Vector2D v, Vector2D w)
{
 return Vector2D(
  v.x * w.x,
  v.y * w.y
 );
}

 inline Vector2D operator*(Vector2D v, double w)
 {
  return Vector2D(
   v.x * w,
   v.y * w
  );
 }
 
 inline Vector2D operator*(double w, Vector2D v)
 {
  return v*w;
 }

inline Vector2D operator/(Vector2D v, Vector2D w)
{
 return Vector2D (
  v.x / w.x,
  v.y / w.y
 );
}

 inline Vector2D operator/(Vector2D v, double w)
 {
  return Vector2D (
   v.x / w,
   v.y / w
  );
 }
 
 inline Vector2D operator/(double w, Vector2D v)
 {
  return Vector2D (
   w / v.x,
   w / v.y
  );
 }

//Normalization

inline void Vector2D::normalize(void)
{
 double mag=magnitude();
 x/=mag;
 y/=mag;
}

//Finding the magnitude

inline double Vector2D::magnitude(void)
{
 return sqrt(x*x+y*y);
}

//Cross product

inline Vector2D cross(const Vector2D& v, const Vector2D& w)
{
 (void)v;
 (void)w;
 NOT_WRITTEN_YET;
 return Vector2D(0,0);
}

//Dot product

inline double dot(const Vector2D& v, const Vector2D& w)
{
 Vector2D x=w*v;
 return x.x + x.y;
}

//Rotation

inline Vector2D rotate(const Vector2D& v, const Vector2D& axis, double angle)
{
 Vector2D n, o=v-axis;
 double ca=cos(angle), sa=sin(angle);
 n.x=o.x*ca + o.y*sa;
 n.y=o.x*-sa + o.y*ca;
 
 return (n+axis);
}

inline void Vector2D::full_dump(void) const
{
 std::cout << ((valid==true)?"valid":"invalid") << ", " << x << ", " << y << "\n";
}

#endif
