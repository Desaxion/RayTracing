#pragma once
#include "Def.h"
#include "ColorDBL.h"


class Pixel {
public:
    
    Pixel() = default;
    
    //vec3 getColor() const {return color.getColor(); };
    void setColor(ColorDBL _color) { color = _color; }
   
    //ColorDBL color;
    
private:
    ColorDBL color;
    
    friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
    
};

