// #419begin #type=3 #src=https://subversion.ews.illinois.edu/svn/sp14-cs225/yangli15

/**
 * @file rgbapixel.cpp
 * Implementation of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#include "rgbapixel.h"

//const RGBAPixel RED = RGBAPixel(255,0,0);
const RGBAPixel BLUE = RGBAPixel(0,255,0);
const RGBAPixel GREEN = RGBAPixel(0,0,255);

RGBAPixel::RGBAPixel() : red(255), green(255), blue(255), alpha(255)
{
	/* nothing */
}

RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b)
	: red(r), green(g), blue(b), alpha(255)
{
	/* nothing */
}

RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b,
		unsigned char a) : red(r), green(g), blue(b), alpha(a)
{
	/* nothing */
}

RGBAPixel& RGBAPixel::operator= (const RGBAPixel& rhs){
    if(this == &rhs)
        return(*this);
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    alpha = rhs.alpha;
    return (*this);
}

bool RGBAPixel::operator==(RGBAPixel const & other) const
{
	return red == other.red && green == other.green && blue == other.blue &&
		alpha == other.alpha;
}

bool RGBAPixel::operator!=(RGBAPixel const & other) const
{
	return !(*this == other);
}

bool RGBAPixel::operator<(RGBAPixel const & other) const
{
	if (red != other.red)
		return red < other.red;
	if (green != other.green)
		return green < other.green;
	return blue < other.blue;
}

void RGBAPixel::operator()(unsigned char r, unsigned char g, unsigned char b){
    red = r;
    green = g;
    blue = b;
}

void RGBAPixel::operator()(RGBAPixel const & other){
    red = other.red;
    green = other.green;
    blue = other.blue;
}

std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel)
{
	out << "(" << (int) pixel.red << "," << (int) pixel.green << ","
		<< (int) pixel.blue << ")";
	if (pixel.alpha != 255)
		out << " a:" << pixel.alpha;
	return out;
}

// #419end