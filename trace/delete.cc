//delete.cc

#include <iostream>

#include "delete.h"

// TODO: implement some kind of texture inheritance
/*
 If sphere A was being cut into by sphere B then the surface that B forms with A
 should be the texture of B.  This will require the texture classes to be
 changed and will be similar to the merge texture system.
*/

Delete::Delete(void)
{
 set_objects(0, 0); 
 ins=new bool;
 norm=new Vector;
}

Delete::Delete(Object* a, Object* b)
{
 set_objects(a, b);
 ins=new bool;
 norm=new Vector;
}

Delete::~Delete(void)
{
 delete ins;
 delete norm;
}

void Delete::set_objects(Object* a, Object *b)
{
 parta.set_objects(a);
 partb.set_objects(b);
}

Vector Delete::normal(void) const
{
 return (*norm);
}

bool Delete::inside(void) const
{
 return (*ins);
}

Vector Delete::_intersection(Line line) const
{
 //cout << "\nDelete\n";
 Vector
  isecta=parta.intersection(line),
  isectb=partb.intersection(line),
  norma=parta.normal(),
  normb=partb.normal();
 
 norma.normalize();
 normb.normalize();

 Vector retval(false);
 
 //line.get_start().full_dump();
 //cout << isecta.valid << ", " << isectb.valid << "\t";
 //cout << parta.inside() << ", " << partb.inside() << "\n";
 
 if (isecta.valid || isectb.valid)
 {
  double
   dista=(line.get_start()-isecta).magnitude(),
   distb=(line.get_start()-isectb).magnitude(); 

  if ( parta.inside()&&(!partb.inside()) )
  {
   //We are inside the object so find the exit
  
   if ( isecta.valid && isectb.valid )  
   {
    //Both are valid so find the closest
    if (dista<distb)
    { 
     retval=isecta;
     (*norm)=norma;//parta.normal();
    } else
    {
     retval=isectb;
     (*norm)=normb;//partb.normal();
    }
   } else
   {
    if ( isecta.valid )
    {
     //Only parta is valid
     retval=isecta;
     (*norm)=norma;//parta.normal();
    } else
    {
     //Only partb is valid
     retval=isectb;
     (*norm)=normb;//partb.normal();
    }
   }
  
  } else
  {
   //We are outside the object
   
   //Possible ways in:
   // 1) End of partb before end of parta
   // 2) Start of parta before start of partb
    
   if ( parta.inside() && partb.inside() )
   {
    //We are looking for #1
    //We are inside parta and partb
    if ( isecta.valid && isectb.valid )
    {
     //cout << "!\n";
     //There is a definite way out of both parts
     if (distb<dista)
     {
      //cout << "#\n";
      //partb ended before parta
      retval=isectb;
      (*norm)=normb;//partb.normal();
     } else
     {
      //parta ended berofe partb
      //Maybe there's another way in after this so lets recurse
      
      //This recursed ray has to begin on the other side of partb
      line.set_start( isectb-(0.000001*normb) );//partb.normal()) );
      retval=intersection(line);
     }
    } else
    {
     if ( isectb.valid )
     {
      //There is only a way out of partb
      retval=isectb;
      (*norm)=normb;//partb.normal();
     }
     //If there's no way out of partb then there is no exit anyway
    }
   } else
   {
    if ( (!parta.inside()) && (!partb.inside()) )
    {
     //We are looking for #2
     //We are outside parta and partb
     if ( isecta.valid && isectb.valid )
     {
      //There is a definite entry to both parts
      if (dista<distb)
      {
       retval=isecta;
       (*norm)=norma;//parta.normal();
      } else
      {
       //partb started before parta
       //Maybe there's another way in after this section of partb so lets recurse
       //This recursed ray has to begin on the other side of partb
       line.set_start( isectb-(0.000001*normb) );//partb.normal() );
       retval=intersection(line);
      }
     } else
     {
      if ( isecta.valid )
      {
       //Only parta is valid
       retval=isecta;
       (*norm)=norma;//parta.normal();
      }
      //If there's no way into parta then there's no entry point
     }
    } else
    {
     //We are inside partb but outside parta
     //This is kinda like entry #1
     //We must check to see if partb ends before the end of parta
     
     if ( isecta.valid && isectb.valid )
     {
      if (distb<dista)
      {
       //partb ends before we even reach parta
       //There may be another section of partb in the way so we must recurse

       //This recursed ray has to begin on the other side of partb
       line.set_start( isectb-(0.000001*normb) );//partb.normal() );
       retval=intersection(line);
      } else
      {
       //cout << ",\n";
       //parta starts before the end of partb
       //parta may stop again before the end of partb so we must recurse
       //This recursed ray has to begin on the other side of parta
       line.set_start( isecta-(0.000001*norma) );//parta.normal() );
       retval=intersection(line);
      }
     }
     
     //If there's no proper exit from partb or no proper entry to parta then we're fooked
    }
   }
  }
 }

 (*ins)=false;
 if ( parta.inside()&&(!partb.inside()) )
 {
  (*ins)=true;
 }
 
 return retval;
}
