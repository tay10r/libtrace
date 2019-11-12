//list.cc

#include <iostream>

#include "list.h"

List::List(void)
{
 set_parent(0);
 set_child(0);
}

List::List(List* p)
{
 set_parent(p);
 set_child(0);
}

void List::set_parent(List* p)
{
 if ((parent!=p)&&(p!=this))
 {
  parent=p;
  if (parent!=0)
   (*parent).set_child(this);
 }
}

void List::set_child(List* c)
{
 if ((child!=c)&&(c!=this))
 {
  child=c;
  if (child!=0)
   (*child).set_parent(this);
 }
}

List* List::find_head(void)
{
 List *retval;
 
 if (parent!=0)
  retval=(*parent).find_head();
 else
  retval=this;
 
 return retval;
}

List* List::find_tail(void)
{
 List *retval;
 
 if (child!=0)
  retval=(*child).find_tail();
 else
  retval=this;
  
 return retval;
}

void List::full_dump(void)
{
 std::cout
  << "List: " << this << ":"
  << "\n\t" << "parent: " << parent
  << "\n\t" << "child: " << child
  << "\n\t" << "head: " << find_head()
  << "\n\t" << "tail: " << find_tail()
  << "\n\n";
}

void merge(List *a, List *b)
{
 (*((*a).find_tail())).set_child((*b).find_head());
}

void List::unlink(void)
{
 if (parent!=0)
  (*parent).set_child(child);
 if (child!=0)
  (*child).set_parent(parent);
  
 parent=child=0;
}

void destroy_list(List *l)
{
 l=(*l).find_head();
 List *a=0;
 
 while (l!=a)
 {
  a=(*l).find_tail();
  delete a;  
 }
}

List::~List(void)
{
 unlink();
}

List* List::get_parent(void)
{
 return parent;
}

List* List::get_child(void)
{
 return child;
}

int List::members(void)
{
 return (*find_head()).members_();
}

int List::members_(void)
{
 int retval;
 
 if (child!=0)
  retval=1+(*child).members_();
 else
  retval=1;
 
 return retval;
}
