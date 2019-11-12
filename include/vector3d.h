//vector3d.h

#ifndef VECTOR3D
#define VECTOR3D

#include <iostream>

#include "defines.h"

#define X (Vector3D(1, 0, 0))
#define Y (Vector3D(0, 1, 0))
#define Z (Vector3D(0, 0, 1))

class Vector3D
{
 public:
  Vector3D(void);
  Vector3D(double nx, double ny, double nz);
  Vector3D(bool v);
  
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
  double x,y,z;
 protected:
 private:
};

//Vector3D normalize(Vector3D v);
//double magnitude(Vector3D v);
Vector3D rotate(Vector3D v, Vector3D axis, double angle);
Vector3D cross(Vector3D v, Vector3D w);
double dot(Vector3D v, Vector3D w);

Vector3D operator+(Vector3D v, Vector3D w);
Vector3D operator-(Vector3D v, Vector3D w);
Vector3D operator*(Vector3D v, Vector3D w);
 Vector3D operator*(Vector3D v, double w);
 Vector3D operator*(double w, Vector3D v);
Vector3D operator/(Vector3D v, Vector3D w);
 Vector3D operator/(Vector3D v, double w);
 Vector3D operator/(double w, Vector3D v);

//****************
//* Constructors *
//****************

inline Vector3D::Vector3D(void)
{
 z=y=x=0;
 valid=true;
}

inline Vector3D::Vector3D(double nx, double ny, double nz)
{
 x=nx;
 y=ny;
 z=nz;
 valid=true;
}

inline Vector3D::Vector3D(bool v)
{
 x=y=z=0;
 valid=v; 
}

//******************************
//* More complicated functions *
//******************************

//Basic arithmetic (+, -, *, /)

inline Vector3D operator+(Vector3D v, Vector3D w)
{
 return Vector3D(
  v.x + w.x,
  v.y + w.y,
  v.z + w.z
 );
}

inline Vector3D operator-(Vector3D v, Vector3D w)
{
 return Vector3D(
  v.x - w.x,
  v.y - w.y,
  v.z - w.z
 );
}

inline Vector3D operator*(Vector3D v, Vector3D w)
{
 return Vector3D(
  v.x * w.x,
  v.y * w.y,
  v.z * w.z
 );
}

 inline Vector3D operator*(Vector3D v, double w)
 {
  return Vector3D(
   v.x * w,
   v.y * w,
   v.z * w
  );
 }
 
 inline Vector3D operator*(double w, Vector3D v)
 {
  return v*w;
 }

inline Vector3D operator/(Vector3D v, Vector3D w)
{
 return Vector3D (
  v.x / w.x,
  v.y / w.y,
  v.z / w.z
 );
}

 inline Vector3D operator/(Vector3D v, double w)
 {
  return Vector3D (
   v.x / w,
   v.y / w,
   v.z / w
  );
 }
 
 inline Vector3D operator/(double w, Vector3D v)
 {
  return Vector3D (
   w / v.x,
   w / v.y,
   w / v.z
  );
 }

//Normalization

inline void Vector3D::normalize(void)
{
 double mag=magnitude();
 x/=mag;
 y/=mag;
 z/=mag;
}

//Finding the magnitude

inline double Vector3D::magnitude(void)
{
 return sqrt(x*x+y*y+z*z);
}

//Cross product

inline Vector3D cross(Vector3D v, Vector3D w)
{
 return Vector3D(
  v.y*w.z - v.z*w.y,
  v.z*w.x - v.x*w.z,
  v.x*w.y - v.y*w.x
 );
}

//Dot product

inline double dot(Vector3D v, Vector3D w)
{
 Vector3D x=w*v;
 return x.x + x.y + x.z;
}

//Rotation

inline Vector3D rotate(Vector3D v, Vector3D axis, double angle)
{
 //Working for this function by:
 // "John L. Richardson" <john@real3d.com>
  
 //axis must be normalized
 Vector3D n;
 axis.normalize();
 n=axis*dot(axis,v);
 return n + cos(angle)*(v-n) + sin(angle)*cross(axis, v);
}

inline void Vector3D::full_dump(void) const
{
 std::cout << ((valid==true)?"valid":"invalid") << ", " << x << ", " << y << ", " << z << "\n";
}

#endif
