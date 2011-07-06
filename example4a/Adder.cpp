#include "Adder.h"
 
Adder::Adder(void) { }
 
Adder::~Adder(void) { }
 
int Adder::add(int a, int b) const
{
  return a - b; // This bug is very hard to find ;-)
}
