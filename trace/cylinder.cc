//cylinder.cc

#include <math.h>

#include "cylinder.h"

Cylinder::Cylinder(void)
{
 ins=new bool;
 hit_side=new bool;
 a=i=j=1;
}

Cylinder::~Cylinder(void)
{
 delete ins;
 delete hit_side;
}

void Cylinder::set_length(double l)
{
 a=l;
}

void Cylinder::set_radius_a(double r1)
{
 i=r1;
}

void Cylinder::set_radius_b(double r2)
{
 j=r2;
}

Vector Cylinder::_intersection(Line line) const
{
 //cout << "START:  Cylinder::_intersection()\n";

 Vector start=line.get_start(), direction=line.get_direction();
#define k start.x
#define l direction.x
#define m start.y
#define n direction.y
#define o start.z
#define p direction.z

 Vector retval(false); (*ins)=(*hit_side)=false;

 double
  a2=a*a, i2=i*i, j2=j*j, k2=k*k, l2=l*l, m2=m*m, n2=n*n, o2=o*o, p2=p*p,
  t1=a2*(i2*(n2+p2)-m2*p2+n*o*(2*m*p-n*o))+2*a*i*(i-j)*(l*(m*n+o*p)-k*(n2+p2))+pow((i-j),2)*(k2*(n2+p2)-2*k*l*(m*n+o*p)+l2*(m2+o2));

 if ( ((m2+o2)<pow((k*(j-i))/a+i,2))&&(start.x>0)&&(start.x<a) )
  (*ins)=true;
 
 if (!(t1<0))
 {
  //retval.valid=true;
  
  double
   t2=a*sqrt(t1),
   c1=(t2+a2*(m*n+o*p)+a*i*l*(i-j)-k*l*pow((i-j),2))/(l2*(i*i-2*i*j+j2)-a2*(n2+p2)),
   c2=(t2-a2*(m*n+o*p)+l*(j-i)*(a*i-k*(i-j)))/(a2*(n2+p2)-l2*(i2-2*i*j+j2));

#undef k
#undef l
#undef m
#undef n
#undef o
#undef p

  double 
   c3=(-start.x/direction.x),
   c4=((a-start.x)/direction.x);

  Vector
   p1=start+c1*direction,
   p2=start+c2*direction,
   p3=start+c3*direction,
   p4=start+c4*direction;
  
  double
   m=(j-i)/a;
  
  if ( (c1<0)||(p1.x<0)||(p1.x>a)||((i+p1.x*m)<0) ) p1.valid=false;
  if ( (c2<0)||(p2.x<0)||(p2.x>a)||((i+p2.x*m)<0) ) p2.valid=false;
  if ( (c3<0)||((p3.y*p3.y + p3.z*p3.z)>(i2)) ) p3.valid=false;
  if ( (c4<0)||((p4.y*p4.y + p4.z*p4.z)>(j2)) ) p4.valid=false;
  
  double c=-1;
  
  if ( p1.valid&&((c1<c)||(c<0)) )
  {
   retval=p1;
   c=c1;
  }
  if ( p2.valid&&((c2<c)||(c<0)) )
  {
   retval=p2;
   c=c2;
  }
  if ( p3.valid&&((c3<c)||(c<0)) )
  {
   (*hit_side)=true;
   retval=p3;
   c=c3;
  }
  if ( p4.valid&&((c4<c)||(c<0)) )
  {
   (*hit_side)=true;
   retval=p4;
   c=c4;
  }

 }
 
 //cout << "FINISH\n";
 return retval;
}

Vector Cylinder::normal(void) const
{
 //cout << "START:  Cylinder::normal\n";
 Vector lp=*(lip);

 if ( !(*hit_side) )
 {
  lp.x=0;
  lp.normalize();
  lp.x=lp.x-(j-i)/a; 
 } else
 {
  lp=Vector((lp.x/a)-0.5, 0, 0);
  //lp=Vector(0,0,-1);
 }

 if ( (*ins) ) { lp=Vector(0,0,0)-lp; }
 
 //cout << "FINISH\n";
 return lp;
}

bool Cylinder::inside(void) const
{
 return false;
}
