//merge.cc

#include <iostream>

#include "merge.h"

// TODO: implement some kind of texture inheritance
/*
 This would require changes to the texture classes since this object would be in
 charge of its own texture.
*/

Merge::Merge(void)
{
 objects=0;
 norm=new Vector;
 ins=new bool;
}

Merge::Merge(Object* obj)
{
 norm=new Vector;
 ins=new bool;
 set_objects(obj);
}

Merge::~Merge(void)
{
 delete norm;
 delete ins;
}

void Merge::set_objects(Object* obj)
{
 objects=obj;
 if (objects!=0)
  objects=static_cast<Object *>((*objects).find_head());
}

Object* Merge::get_objects(void) const
{
 return objects;
}

Vector Merge::normal(void) const
{
 return (*norm);
}

bool Merge::inside(void) const
{
 return (*ins);
}

Vector Merge::_intersection(Line line) const
{
 Object *cur_obj=objects, *contact=0;
 Vector isect(false), d;
 double closest=-1, dist;
 int prims=(*objects).members(), count=0;
 Vector *isects = new Vector[prims];
 
#define NEXT cur_obj=static_cast<Object *>((*cur_obj).get_child()); 

 //Pre-calculate all the intersections
 while (cur_obj!=0)
 {
  isects[count]=(*cur_obj).intersection(line);
  count++;
  NEXT
 }
 
 bool temp_ins=false;
 
 //Calculate if the start of the line is inside or outside the merge-o-being
 cur_obj=objects;
 count=0;
 while ( (cur_obj!=0)&&(!temp_ins) )
 {
  //cout << (*cur_obj).inside() << ", ";
  if ( (*cur_obj).inside() )
  {
   temp_ins=true;
  }
  NEXT
 }
 
 //cout << "\n";
 
 Vector retval(false);
 
 if ( !temp_ins )
 {
  //We are not inside the object so simply find the closest intersection
  cur_obj=objects;
  count=0;
  while (cur_obj!=0)
  {
   if (isects[count].valid)
   {
    d=isects[count]-line.get_start();
    dist=d.magnitude();
    if ( (dist<closest)||(closest<0) )
    { 
     closest=dist;
     isect=isects[count];
     contact=cur_obj;
    }
   }
   count++;
   NEXT
  }
  
  if (contact!=0)
  {
   retval=isect;
   Surface surface=(*contact).get_surface();
   (*norm)=surface.normal;
  }
  
 } else
 {
  //We are inside so we need to find the exiting intersection
  // Basic plan:
  // 1) Find the first exiting intersection (ie, inside=true for that object)
  //    If there are none then report invalid
  // 2) Fire a ray from the other side of this exit
  // 3) If this ray reports that it's outside all of the objects then this is the spot
  //    Otherwize loop back to step 1
   
  bool still_inside=true;
  
  while (still_inside)
  {
   //cout << "SI\n";
   //**********
   //* Step 1 *
   //**********
   
   //line.get_start().full_dump();
   
   contact=0;
   
   cur_obj=objects;
   count=0;
   closest=-1;
   while (cur_obj!=0)
   {
    //cout << isects[count].valid << ", " << (*cur_obj).inside() << "\n";
    if ( (isects[count].valid) && ((*cur_obj).inside()) )
    {
     d=isects[count]-line.get_start();
     dist=d.magnitude();
     if ( (dist<closest)||(closest<0) )
     {
      //cout << "Contact\n";
      closest=dist;
      isect=isects[count];
      contact=cur_obj;
     }
    }
    count++;
    NEXT
   }
  
   if (contact==0)
   {
    retval.valid=still_inside=false;
   } else
   {
    //**********
    //* Step 2 *
    //**********
    //cout << "Contact p2\n";
    
    retval=isect;
    //retval.full_dump();
    Surface surface=(*contact).get_surface();
    (*norm)=surface.normal;
    line.set_start( retval-(0.000001*(*norm)) );
    //line.set_direction(line.get_direction());
    
    //cout << "Firing test ray: ";
    //line.get_start().full_dump();
    
    cur_obj=objects;
    count=0;
    while (cur_obj!=0)
    {
     isects[count]=(*cur_obj).intersection(line);
     count++;
     NEXT
    }
   
    //**********
    //* Step 3 *
    //**********
   
    still_inside=false;
    cur_obj=objects;
    count=0;
    while ( (cur_obj!=0) && (!still_inside) )
    {
     //cout << (*cur_obj).inside() << ", ";
     if ( (*cur_obj).inside() ) 
     {
      still_inside=true;
     }
     count++;
     NEXT
    }
    //cout << "\n";
   }
  }
 }
 
 //cout << "\n";
 
#undef NEXT 

 delete [] isects; 

 (*ins)=temp_ins;
 
 //retval.full_dump();

 //cout << "End of M\n";
 
 return retval;
}
