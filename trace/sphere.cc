//sphere.cc

#include <iostream>

#include "sphere.h"

Sphere::Sphere(void)
{
 set_center(Vector(0,0,0));
 set_radius(1);
 norm=new Vector;
 (*norm)=Vector(0,0,0);
 ins=new bool;
 (*ins)=false;
}

Sphere::Sphere(Vector c, double r)
{
 set_center(c);
 set_radius(r);
 norm=new Vector;
 (*norm)=Vector(0,0,0);
 ins=new bool;
 (*ins)=false;
}

Sphere::~Sphere(void)
{
 delete norm;
 delete ins;
}

void Sphere::set_center(Vector c)
{
 center=c;
}

Vector Sphere::get_center(void)
{
 return center;
}

void Sphere::set_radius(double r)
{
 radius=r;
}

double Sphere::get_radius(void)
{
 return radius;
}

Vector Sphere::normal(void) const
{
 return (*norm);
}

bool Sphere::inside(void) const
{
 return (*ins);
}

//Version 1 by Kai
Vector Sphere::_intersection(Line line) const
{
  double a, b, c;     // as in ax + bx + c;
  double p2, q;       // as in x + px + q; p2 is just p/2
  double xs, ys, zs;  // line.start (x, y, z) triple
  double xd, yd, zd;  // line.direction (x, y, z) triple
  double p2p2;        // p/2 * p/2
  double t1, t2;      // parameter of the line
  double root, root2; // the "root" in the quadratic "formula" and root

  // the lines start is translated to match that coordinate system
  // in which the sphere has it's center at (0, 0, 0)
  Vector start=line.get_start()-center;
  Vector direction=line.get_direction();
  Vector retval;

  if (start.magnitude()<radius)
  {
   (*ins)=true;
  } else
  {
   (*ins)=false;
  }
  
  // direction must not be the null vector !
  xs=start.x, ys=start.y, zs=start.z;
  xd=direction.x, yd=direction.y, zd=direction.z;
  
  // from solving the sphere equation sqrt(x + y + z) = r:
  a=xd*xd + yd*yd + zd*zd;
  b=2*(xs*xd + ys*yd + zs*zd);
  c=xs*xs + ys*ys + zs*zs - radius*radius;

  //for solving the quadratic equation w/ the "easy to remember" formula
  p2=.5*(b/a);
  p2p2=p2*p2;
  q=c/a;

  // "no solution", so there is no intersection:
  if (p2p2 - q < .0) {
    retval.valid=false;
    return retval;
  }
  
  root2=p2p2-q;
  root=sqrt(root2);
  t1=-p2+root;
  t2=-p2-root;

  // I'm not sure this is quite correct; we should probably
  // ignore a negative parameter :)
  //retval = line.get_start() + direction*(fabs(t1)<fabs(t2)?t1:t2);
  //return retval;
 
  if (t1<.0)
  {
   if (t2<.0)
   {
    retval.valid=false;
    return retval; // no intersection in front of us (break)
   }
   t1= t2;
  }
  else
   if (t2>=.0) // t2 is not behind us (ok)
    if (t2<t1) // t2 is closer than t1
     t1=t2;

 retval=line.get_start() + direction*t1;
 retval.valid=true;

 //Normal for sphere is simple so work it out now
 (*norm)=retval-center;
 //If the ray started from inside the sphere then invert the normal
 if ((*ins))
 {
  (*norm)=(*norm)*(-1.0);
 }

 return retval;
}


/*
//Version 2 by Nigel
//Needs fixed
Vector Sphere::intersection(Line line) const
{
 Vector retval;
 retval.set_valid(true);
 Vector tran_line=line.get_start()-center;
 Vector direction=line.get_direction();
 
 double
  D=dot(tran_line, tran_line),
  C=-radius*radius+D,
  B=2*dot(tran_line, direction),
  A=dot(direction, direction),
  s=B*B-4*A*C;
 
 //cout << "A: " << A << "\nB: " << B << "\nC: " << C << "\nD: " << D << "\n";
 
 double t1, t2;
 
 //cout << "s before sqrt(): " << s << "\n";
 
 if (s>0)
 {
  s=sqrt(s);
  
  double a2=2*A;
  t1=(-B-s)/a2;
  t2=(-B+s)/a2;
  double t;
  
  if (t1>0)
  {
   t=t1;
  }
  else
  {
   if (t2>0)
   {
    t=t2;
   }
   else
   {
    retval.set_valid(false);
    t=0;
   }
  }
  
  retval=line.get_start()+t*direction;
 } else
  retval.set_valid(false);
 
 return retval;
}
*/
