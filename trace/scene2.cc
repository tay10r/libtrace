//scene2.cc

//Contains the bigger functions:
// Scene::point
// Scene::find_closest
// Scene::trace_ray

#include <math.h>
#include <iostream>

#include "scene.h"
#include "light.h"
#include "object.h"

#ifndef CLAMP
#define CLAMP(a, b, c) (a)<(b)?(b):(a)>(c)?(c):(a)
#endif

#ifndef DO_RANGE_INCLUDE
#define DO_RANGE_INCLUDE(a, b, c) {if ((c)<(a)) (a)=(c); else if ((c)>(b)) (b)=(c);}
#endif

rgb Scene::point(int x, int y, int depth)
{
 static rgb pixel[17][17];
 static int px=0, py=0;
 //Lookup tables
 static int size[]={16, 8, 4, 2, 1};
 static double limit[]={4.0/256.0, 16.0/256.0, 64.0/256.0, 1};
 
 rgb retval;
 if (anti_aliasing)
 {
  if (depth==0)
  {
   //Brand new pixel so blank the pixel[] array
   for (int tx=0; tx<17;tx++)
    for (int ty=0; ty<17;ty++)
     pixel[tx][ty].valid=false;
   //Co-ordinates for top left of pixel     
   px=x;
   py=y;
  }
#define x1 x
#define y1 y
  //Real co-ords of the section we are subsampling
  int x2=x+size[depth], y2=y+size[depth];
  //Pixel co-ords of the section we are subsampling
  int px1=x1-px, px2=x2-px, py1=y1-py, py2=y2-py;
  
  rgb *p1=&pixel[px1][py1];
  rgb *p2=&pixel[px1][py2];
  rgb *p3=&pixel[px2][py1];
  rgb *p4=&pixel[px2][py2];
  
  if (!((*p1).valid)) { (*p1)=pinpoint(x1, y1); (*p1).valid=true; } 
  if (!((*p2).valid)) { (*p2)=pinpoint(x1, y2); (*p2).valid=true; } 
  if (!((*p3).valid)) { (*p3)=pinpoint(x2, y1); (*p3).valid=true; } 
  if (!((*p4).valid)) { (*p4)=pinpoint(x2, y2); (*p4).valid=true; } 
  
  rgb min=(*p1), max=(*p1);
  
  DO_RANGE_INCLUDE(min.red, max.red, (*p2).red);
  DO_RANGE_INCLUDE(min.green, max.green, (*p2).green);
  DO_RANGE_INCLUDE(min.blue, max.blue, (*p2).blue);

  DO_RANGE_INCLUDE(min.red, max.red, (*p3).red);
  DO_RANGE_INCLUDE(min.green, max.green, (*p3).green);
  DO_RANGE_INCLUDE(min.blue, max.blue, (*p3).blue);

  DO_RANGE_INCLUDE(min.red, max.red, (*p4).red);
  DO_RANGE_INCLUDE(min.green, max.green, (*p4).green);
  DO_RANGE_INCLUDE(min.blue, max.blue, (*p4).blue);
  
  rgb range=max-min;
  double mr=range.red;
  if (range.green>mr) mr=range.green;
  if (range.blue>mr) mr=range.blue;
  
  if (mr>limit[depth])
  {
   //Colors differ enough to require another depth of subsampling
   depth++;
   x2=x1+size[depth];
   y2=y1+size[depth];
   retval=(
    point(x1, y1, depth)+
    point(x1, y2, depth)+
    point(x2, y1, depth)+
    point(x2, y2, depth)
   )/4.0;
  }
  else
  {
   //No more subsampling required
   retval=((*p1)+(*p2)+(*p3)+(*p4))/4.0;
  }
#undef p1
#undef p2
#undef p3
#undef p4
#undef x1
#undef y1
 }
 else
 {
  retval=pinpoint(x+8, y+8);
 }
 
 return retval;
}

void Scene::find_closest(Ray ray, double *closest, Vector *isect, Object **contact, rgb* filter)
{
 //This function goes through the scene looking for the closest hit for this ray
 //It returns the object that it hits and also modifies the "*closest" and "*isect" variables
 List *cur_list=objects;
 Object *cur_object=static_cast<Object *>(cur_list);
 double cutoff=(*closest), d_mag;
 bool ignore_cutoff=(cutoff<0);
 bool ignore_closest=((*closest)<0);

 //Go through all the objects and find the closest one that this ray hits
 while (cur_object!=0)
 {
  //cout << "\n.";
  //ray.get_start().full_dump();
  Vector t=(*cur_object).intersection(ray);
  //cout << ".\n";
  if (t.valid)
  {
   Vector d=(t-ray.get_start());
   d_mag=d.magnitude();
   if ( (d_mag<cutoff)||ignore_cutoff )
   {
    Surface surf=(*cur_object).get_surface();
    (*filter)=(*filter)*surf.transparency*surf.color;

    if ( (d_mag<(*closest))||ignore_closest )
    {
     //This new valid point is closer
     ignore_closest=false;
     (*closest)=d.magnitude();
     (*contact)=cur_object;
     (*isect)=t;
    }
   }
  }
  cur_list=(*cur_list).get_child();
  cur_object=static_cast<Object *>(cur_list);
 }
}

rgb Scene::trace_ray(Ray ray)
{
 ray_tally++;
 rgb retval=bg_color;
 retval.valid=false;
  
 Vector *isect=new Vector;
 (*isect).valid=false;
 double *closest=new double;
 (*closest)=-1;
 rgb *filter=new rgb;
 
 Object *contact=0;
 find_closest(ray, closest, isect, (&contact), filter); 
 
 delete closest;
 closest=0;
 delete filter;
 filter=0;
 
 if (contact!=0)
 {
  //Something was hit
  retval=rgb(0,0,0);
  retval.valid=true;
    
  if(ray.get_significance()>ray_threshold)
  {
   //The ray color still isn't down to the required accuracy so recurse further
   Surface surface=(*contact).get_surface();
   bool inside=(*contact).inside();
   
   surface.normal.normalize();
   Vector ns=0.000001*surface.normal;
   Vector start_of_test_ray=(*isect)+ns;
   Vector start_of_inside_test_ray=(*isect)-ns;

   Vector Vreflect=rotate(ray.get_direction(), surface.normal, M_PI)*-1;


//********************************
//* Diffusive and specular light *
//********************************
   
   if ( ((ray.get_significance()*surface.diffuse)>ray_threshold)||((ray.get_significance()*surface.specular)>ray_threshold) )
   {
    //Lights still make a big enough difference
    List *cur_list=lights;
    Light *cur_light=static_cast<Light *>(cur_list);
    rgb
     diffuse_color=surface.diffuse*surface.color;

    double *light_distance=new double;
    Vector *temp=new Vector;
    Object *tempo=0;
    rgb *light_color=new rgb;


    while (cur_light!=0)
    {
     Ray test;
     //This ray is only to test if the ray even get's to the destination
     //Significance is at -1 to ensure that it doesn't recurse
     test.set_significance(-1);
     
     //light_direction must point back to the light source
     //Vector light_direction=Vector(0,0,-1);
     
     Vector light_direction=(*cur_light).get_position()-(*isect);
     test.set_start_and_direction(start_of_test_ray, light_direction);      
     //test.set_start_and_direction((*isect), light_direction);      

     (*light_distance)=light_direction.magnitude();
     
     
     (*light_color)=(*cur_light).get_color();
     
     find_closest(test, light_distance, temp, &tempo, light_color);
     
     retval=retval +
       diffuse_color*(*light_color)*(dot(surface.normal, light_direction)/light_direction.magnitude());
     
     double dp=dot(Vreflect, light_direction)/(light_direction.magnitude()*Vreflect.magnitude());
     if ( dp<0 ) dp=0;
     retval=retval + 
      surface.specular*(*light_color)*pow(dp, surface.hardness);
       
     cur_list=(*cur_list).get_child();
     cur_light=static_cast<Light *>(cur_list);
    }

    delete temp;
    temp=0;
    delete light_distance;
    light_distance=0;
    delete light_color;
    light_color=0;
   }
   

//****************
//* Transparency *
//****************   

   if((ray.get_significance()*surface.transparency)>ray_threshold)
   {
    Ray test;
    test.set_significance(ray.get_significance()*surface.transparency);
    test.set_start(start_of_inside_test_ray);
    test.set_direction(ray.get_direction());
    
    retval=retval +
     surface.color*surface.transparency*trace_ray(test);
   }

   double reflect=surface.reflect;

//**************
//* Refraction *
//**************

   if((ray.get_significance()*surface.refract)>ray_threshold)
   {
    Ray test;
    
    Vector i=ray.get_direction(), n=surface.normal;
    //I thought I'd normalize the vectors just in case
    //May take them out later on
    i.normalize();
    //n is already normalized
    
    //i=Vector(sqrt(3.0)/3.0, sqrt(3.0)/3.0, sqrt(3.0)/3.0);
    //n=Vector(0,0,-1);
    
    test.set_significance(ray.get_significance()*surface.refract);
    test.set_start(start_of_inside_test_ray);
    
    //test.set_direction(i);
    
    double n1=ray.get_ior();
    double n2=inside?1:surface.ior;
    
    double
     eta=n1/n2,    
     c1=-dot(i, n),
     cs2=1.0 - eta*eta*(1.0 - c1*c1);
    
    //cout << eta << "\t";
    
    if (cs2<0)
    {
     //Total internal reflection
     reflect=reflect+surface.refract;
    } else
    {
     //cout << "eta*c1: " << eta*c1 << "\tsqrt(cs2): " << sqrt(cs2) << "\n";

     Vector r=eta*i + (eta*c1-sqrt(cs2))*n;
     
     r.normalize();
     
     test.set_direction(r);
     
     //test.get_direction().full_dump();
     
     //Nigel's dodgy calculation
     //double ray_refracted=(*contact).get_refract()*c1*c1, ray_reflected=(*contact).get_refract()-ray_refracted;
     //reflect+=ray_reflected;

     //Pauldoo's pure dead genius method
     double
      ia=acos(dot(Vector(0,0,0)-i,n)),
      ir=acos(dot(Vector(0,0,0)-r,n)),
      sin_i_plus_r=sin( ia+ir ),
      sin_i_minus_r=sin( ia-ir ),
      rp=(sin_i_minus_r*sin_i_minus_r)/(sin_i_plus_r*sin_i_plus_r);
     
     reflect+=rp * surface.refract;
     double ray_refracted=(1.0-rp) * surface.refract;
     
     test.set_ior(n2);
     retval=retval +
      surface.color*ray_refracted*trace_ray(test);
    }

/*
//This is the code that was sent to me originaly by email
TransmissionDirection(m1, m2, I, N, T)
   double   m1, m2;		// the index of refraction 
   Vector3  I, N, T;		// incoming, normal and Transmitted 
{
   double eta, c1, cs2 ;

   eta = n1 / n2 ;			
   c1 = -VecDot(I, N) ;
   cs2 = 1 - eta * eta * (1 - c1 * c1) ;

   if (cs2 < 0)
      return 0 ;		// total internal reflection
	
   // 
   // VecComb(a, v1, b, v2, v3)
   // computes v3 = a * v1 + b * v2, 
   // where a & b are scalars, and v1, v2, v3 are vectors 

   VecComb(eta, I, eta * c1 - sqrt(cs2), N, T) ;

   return 1;
}
*/    
    
   }

//***************
//* Reflections *
//***************
   
   if((ray.get_significance()*reflect)>ray_threshold)
   {
    Ray temp; 
     temp.set_start(start_of_test_ray);
     temp.set_direction(Vreflect);

    temp.set_significance(ray.get_significance()*reflect);
    retval=retval+
     reflect*trace_ray(temp);
   }

  }
 }
 
 delete isect;
 isect=0;
 //Finally return the answer
 //return 42;
 return retval;
}
