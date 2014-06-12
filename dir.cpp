//*******************************************************************
//*                         Scoped Enums in C++ before 11
//*******************************************************************

/* I like short scoped enums, but was having a hard time finding as
   syntax that I liked to avoid polluting the global space.
   
   I came across this usage at:
   http://gamesfromwithin.com/stupid-c-tricks-2-better-enums
   
   After toying with several ideas this is now my favorite.  I need
   to use this in Alfred to make motor commands typed.
*/

#include <iostream> 

using namespace std;

namespace Direction {

    enum dir {fwd, back};
}

ostream& operator<<(ostream& os, const Direction::dir d) {
    if (d == Direction::fwd) os<<"fwd";
    else os<<"back";
    return os;
}



int main (int argc, char const *argv[])
{
    Direction::dir d = Direction::fwd;
    cout<<"d is: "<<d<<endl;
    return 0;
}