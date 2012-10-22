using namespace std;

//Replace with int if possible for more speed
typedef double NUM;

//Generic point
struct point
{
	NUM x, y;

	point(NUM _x, NUM _y) : x(_x), y(_y) {}

	//scalar product
	point operator*(NUM scalar) const { return point(scalar*x, scalar*y); }

	//dot product
	NUM operator*(const point& b) const { return x*b.x + y*b.y; }

	//cross product
	NUM operator^(const point& b) const { return x*b.y - y*b.x; }

	//addition and subtraction
	point operator+(const point& b) const { return point(x+b.x, y+b.y); }
	point operator-(const point& b) const { return point(x-b.x, y-b.y); }
};

#include <math.h> //for sqrt

//Distance SQUARED from point a to line segment bc
double distpointline(point a, point b, point c)
{
	a = a-b;
	c = c-b;
	NUM dot = a*c;
	NUM len = c*c;
	if( dot <= 0 ) return a*a;
	else if( dot >= len ) return (a-c)*(a-c);
	else return a*a - dot/sqrt((double)len);
	//point projection = c * (dot/((double)len);
}

//http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

//Line segment a1---a2 intersects with b1---b2
bool segmentsIntersect(const point& a1, const point& a2, const point& b1, const point& b2)
{
	NUM cross = (a2-a1)^(b2-b1);
	if( cross == 0 ) return false; //parallel
	double t = ( (b1-a1)^(b2-b1) ) / ((double)cross);
	if( t < 0 || t > 1 ) return false; //intersection point is not on the segments
	//point intersect = a1*(1-t) + a2*t;
	return true;
}

#include <vector> //for polygon point list

//This returns TWICE the area of a polygon because then it will always be an integer if the input is integers
NUM polygonTwiceArea(const vector<point>& polygon)
{
	//if( polygon.empty() ) return 0;
	NUM area = 0;
	point p0 = polygon[0];
	for(unsigned int i = 1; i+1 < polygon.size(); ++i) area += (polygon[i] - p0)^(polygon[i+1]-p0);
	return (area > 0 ? area : -area); //abs(area)
}

bool pointInPolygon(point p, const vector<point>& polygon)
{
	point outside(10000, 10000); //EDIT this to a point that is SURELY outside the polygon
	int crosscount = 0;
	unsigned int N = polygon.size();
	for(unsigned int i = 0; i < N; ++i)
	{
		if( distpointline( p , polygon[i], polygon[(i+1)%N] ) == 0 ) //if double change to <= 1e-8
			return true; //POINT ON BOUNDARY: change true to false if wanted
		if( segmentsIntersect( p, outside, polygon[i], polygon[(i+1)%N] ) ) ++crosscount;
	}
	if( crosscount % 2 == 0 ) return false; //p was outside polygon
	else return true; //p was inside polygon
}


//
//TESTING
//

#include <iostream>
#include <time.h> //clock
#include <cstdlib> //rand

using namespace std;

NUM randomd(){ return (rand()%2001)-1000; } //random in [-1000,1000] range

int main()
{
	srand(0);
	cout << "Start!" << endl;

	clock_t begin = clock();
	for(int i = 0; i < 100000000; ++i)
		distpointline(point(randomd(),randomd()), point(randomd(),randomd()), point(randomd(), randomd()));
	clock_t end = clock();

	cout << "Time taken: " << ((double)(end-begin))/((double)CLOCKS_PER_SEC) << endl;
	cin.get();
	return 0;
}
