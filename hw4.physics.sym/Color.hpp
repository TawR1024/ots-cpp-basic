#pragma once
#include <fstream>

class Color
{
   public:
    Color ();
    Color (double red, double green, double blue);
    double red () const;
    double green () const;
    double blue () const;

   private:
    double r{};
    double g{};
    double b{};
};

inline std::istream& operator>> (std::istream& stream, Color& color)
{
    double red, green, blue;
    if (!(stream >> red >> green >> blue))
    {
        return stream;
    }

    color = Color (red, green, blue);
    return stream;
}