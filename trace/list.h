//list.h

#ifndef LIST
#define LIST

#include "defines.h"

class List
{
 public:
  List(void);
  List(List* p);
  virtual ~List(void);
  
  void set_parent(List *p);
  void set_child(List *p);
  List* get_parent(void);
  List* get_child(void);
    
  List* find_head(void);
  List* find_tail(void);
  void unlink(void);
  
  int members(void);
  
  void full_dump(void);
 protected:

 private:
  List *parent, *child;
  int members_(void);  
};

void merge(List *a, List *b);
void destroy_list(List *l);

#endif
