#include "Pixel.h"



std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
    os << p.color.getColor().r*255 << " " << p.color.getColor().g*255 << " " << p.color.getColor().b*255 << " ";
    return os;
}
