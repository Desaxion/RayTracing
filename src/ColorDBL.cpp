
#include <stdio.h>
#include "ColorDBL.h"

double ColorDBL::randomDouble() {
    srand(std::time(NULL));
    return (0.1*(rand()%11));
    
}

/*ColorDBL ColorDBL::operator*(ColorDBL _in) {
    
    color = dvec3(color.x*_in.getColor().x,color.y*_in.getColor().y,color.z*_in.getColor().z);
    return *this;
}


ColorDBL ColorDBL::operator*(double _in) {
    
    color = color*_in;
    return *this;
}
*/
