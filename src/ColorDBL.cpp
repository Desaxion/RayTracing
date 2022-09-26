
#include <stdio.h>
#include "ColorDBL.h"

double ColorDBL::randomDouble() {
    srand(std::time(NULL));
    return (0.1*(rand()%11));
    
}
