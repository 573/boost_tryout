#pragma once
     
// A simple class, which will act as the unit to be tested.
class Adder
{
public:
    Adder(void);
    ~Adder(void);
     
    // Should return the sum of a and b, hopefully...
    int add(int a, int b) const;
};
     
