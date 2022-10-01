#include "ComplexPlane.h"
#include <sstream>
#include <complex>

using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = (BASE_HEIGHT * m_aspectRatio) * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	//Set text size
	text.setCharacterSize(25);

	//Set color to text
	text.setFillColor(Color::Black);
	
	//Position text to upper left corner
	text.setPosition(0, 0);

	//Obtain center coordinates for text
	Vector2f centerCoord;
	centerCoord = m_view.getCenter();

	//Update text
	stringstream ss;
	ss << "Mandelbrot Set" << endl;
	ss << "Center: (" << centerCoord.x << ", " << centerCoord.y << ")" << endl;
	ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
	ss << "Left-click to Zoom in" << endl;
	ss << "Right-click to Zoom out" << endl;
	text.setString(ss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	//Set coordinates in complex plane
	float re = coord.x;
	float im = coord.y;

	//Set variables c and z for calculation
	complex<float> c (re, im);
	complex<float> z (0, 0);

	//Set number of iterations for return value
	size_t iterations = 0;

	//Create while loop to make calculation
	//Loop ends when absolute value of z reaches 2.0 or higher
	//If condition above does not meet, loop also ends when number of iterations has reached max (64)
	while(abs(z) < 2.0 && iterations < MAX_ITER)
	{
		z = z * z + c;
		iterations++;
	}

	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	switch(count)
	{
		case 1: { r = 163; g = 0; b = 0; break; }
		case 2: { r = 163; g = 3; b = 0; break; }
		case 3: { r = 168; g = 6; b = 0; break; }
		case 4: { r = 168; g = 8; b = 0; break; }
		case 5: { r = 173; g = 12; b = 0; break; }
		case 6: { r = 173; g = 14; b = 0; break; }
		case 7: { r = 179; g = 18; b = 0; break; }
		case 8: { r = 179; g = 21; b = 0; break; }
		case 9: { r = 184; g = 24; b = 0; break; }
		case 10: { r = 184; g = 28; b = 0; break; }
		case 11: { r = 189; g = 31; b = 0; break; }
		case 12: { r = 189; g = 35; b = 0; break; }
		case 13: { r = 194; g = 39; b = 0; break; }
		case 14: { r = 194; g = 42; b = 0; break; }
		case 15: { r = 199; g = 46; b = 0; break; }
		case 16: { r = 199; g = 50; b = 0; break; }
		case 17: { r = 204; g = 54; b = 0; break; }
		case 18: { r = 204; g = 58; b = 0; break; }
		case 19: { r = 209; g = 63; b = 0; break; }
		case 20: { r = 209; g = 66; b = 0; break; }
		case 21: { r = 214; g = 71; b = 0; break; }
		case 22: { r = 214; g = 75; b = 0; break; }
		case 23: { r = 219; g = 80; b = 0; break; }
		case 24: { r = 219; g = 84; b = 0; break; }
		case 25: { r = 224; g = 90; b = 0; break; }
		case 26: { r = 224; g = 94; b = 0; break; }
		case 27: { r = 230; g = 99; b = 0; break; }
		case 28: { r = 230; g = 103; b = 0; break; }
		case 29: { r = 235; g = 109; b = 0; break; }
		case 30: { r = 235; g = 113; b = 0; break; }
		case 31: { r = 240; g = 120; b = 0; break; }
		case 32: { r = 240; g = 124; b = 0; break; }
		case 33: { r = 245; g = 131; b = 0; break; }
		case 34: { r = 245; g = 135; b = 0; break; }
		case 35: { r = 250; g = 142; b = 0; break; }
		case 36: { r = 250; g = 146; b = 0; break; }
		case 37: { r = 255; g = 153; b = 0; break; }
		case 38: { r = 255; g = 157; b = 0; break; }
		case 39: { r = 255; g = 163; b = 5; break; }
		case 40: { r = 255; g = 168; b = 5; break; }
		case 41: { r = 255; g = 173; b = 10; break; }
		case 42: { r = 255; g = 177; b = 10; break; }
		case 43: { r = 255; g = 183; b = 15; break; }
		case 44: { r = 255; g = 187; b = 15; break; }
		case 45: { r = 255; g = 192; b = 20; break; }
		case 46: { r = 255; g = 196; b = 20; break; }
		case 47: { r = 255; g = 201; b = 26; break; }
		case 48: { r = 255; g = 205; b = 26; break; }
		case 49: { r = 255; g = 210; b = 31; break; }
		case 50: { r = 255; g = 214; b = 31; break; }
		case 51: { r = 255; g = 218; b = 36; break; }
		case 52: { r = 255; g = 222; b = 36; break; }
		case 53: { r = 255; g = 226; b = 41; break; }
		case 54: { r = 255; g = 230; b = 41; break; }
		case 55: { r = 255; g = 234; b = 46; break; }
		case 56: { r = 255; g = 238; b = 46; break; }
		case 57: { r = 255; g = 241; b = 51; break; }
		case 58: { r = 255; g = 245; b = 51; break; }
		case 59: { r = 255; g = 248; b = 56; break; }
		case 60: { r = 255; g = 252; b = 56; break; }
		case 61: { r = 255; g = 255; b = 61; break; }
		case 62: { r = 252; g = 255; b = 61; break; }
		case 63: { r = 249; g = 255; b = 66; break; }
		default: { r = 255; g = 255; b = 255; break; }
	}

}