#pragma once
#include "Def.h"
#include "ColorDBL.h"
class Surface {
public:
    
    Surface() : reflectionModel{ DIFFUSE }, color{ ColorDBL(dvec3(1.0, 0.0, 0.0)) }, reflectionCoeff{ 0.0 } {};
    
    Surface(int _reflectionModel, ColorDBL _color, double _reflectionCoeff) : reflectionModel{ _reflectionModel }, color{ _color }, reflectionCoeff{ _reflectionCoeff } {};
    
    ColorDBL getColor() { return color; }
    
    int getRefl() const { return reflectionModel; }
    
private:

    int reflectionModel;
    ColorDBL color;
    double reflectionCoeff;
    
};
