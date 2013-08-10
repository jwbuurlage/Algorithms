//Even when coordinates are in [-10000,10000] range the square distances can get up to billions
//Max signed integer: 2,147,483,647
typedef double NUM; //use either double or long long

struct point
{
    NUM x, y;
    point(){}
    point(NUM _x, NUM _y) {x= _x; y= _y;}
    point(const point& p) {x=p.x; y=p.y;}
    point operator*(NUM scalar)       const { return point(scalar*x, scalar*y); }//scalar
    NUM   operator*(const point& rhs) const { return x*rhs.x + y*rhs.y; }        //dot product
    NUM   operator^(const point& rhs) const { return x*rhs.y - y*rhs.x; }        //cross product
    point operator+(const point& rhs) const { return point(x+rhs.x, y+rhs.y); }  //addition
    point operator-(const point& rhs) const { return point(x-rhs.x, y-rhs.y); }  //subtraction
};

NUM sqDist(const point& a, const point& b)  { return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y); }

//--- Distance between two segments: ---
//Compute the distance both points from the first line segment to the full second segment
//BUT ALSO the distance from both points of the second line segment to the first segment
//Take the minimum of these four. (Or zero if they intersect)

//Distance SQUARED from point a to line segment bc
double sqDistPointSegment(point a, point b, point c)
{
    a = a-b;
    c = c-b;
    long long dot = a*c;
    if( dot <= 0 ) return a*a;
    else
    {
        long long len = c*c;
        if( dot >= len ) return (a-c)*(a-c);
        else return a*a - dot*dot/((double)len); //OR: (a^c)*(a^c) / ((double)len);
        //point projection = c * (dot/((double)len);
    }
}

//Line segment a1---a2 intersects with b1---b2
//If they TOUCH then it can fail
bool segmentsIntersect(const point& a1, const point& a2, const point& b1, const point& b2)
{
    NUM cross = (a2-a1)^(b2-b1);
    if( cross == 0 ) return false; //parallel
    double t = ((b1-a1)^(b2-b1)) / ((double)cross);
    if( t < 0 || t > 1 ) return false;
    double u = ((b1-a1)^(a2-a1)) / ((double)cross);
    if( u < 0 || u > 1 ) return false;
    //point intersect = a1*(1-t) + a2*t;
    //point intersect = b1*(1-u) + b2*u;
    return true;
}

#include <vector> //for polygon point list
using namespace std;

//This returns TWICE the area of a polygon because then it will always be an integer if the input is integers
NUM polygonTwiceArea(const vector<point>& polygon)
{
    //if( polygon.empty() ) return 0;
    NUM area = 0;
    point p0 = polygon[0];
    for(unsigned int i = 1; i+1 < polygon.size(); ++i) area += (polygon[i] - p0)^(polygon[i+1]-p0);
    return (area > 0 ? area : -area); //abs(area)
}

//WHEN POSSIBLE USE pointInConvex
bool pointInPolygon(point p, const vector<point>& polygon)
{
    point outside(982451653, 881253449); //Choose prime numbers!!
    int crosscount = 0;
    unsigned int N = polygon.size();
    for(unsigned int i = 0; i < N; ++i)
    {
        if( sqDistPointSegment( p , polygon[i], polygon[(i+1)%N] ) <= 1e-11 )
            return true; //POINT ON BOUNDARY: change true to false if wanted
        if( segmentsIntersect( p, outside, polygon[i], polygon[(i+1)%N] ) ) ++crosscount;
    }
    if( crosscount % 2 == 0 ) return false; //p was outside polygon
    else return true; //p was inside polygon
}

int pointInConvex(point p, const vector<point>& polygon, int whenOnBoundary = 0)
{
    //The cross product should always have the same sign when the point is inside the convex
    unsigned int N = polygon.size();
    int sign = 0;
    for(unsigned int i = 0; i < N; ++i)
    {
        long long cross = ((polygon[i] - p)^(polygon[(i+1)%N] - p));
        if( cross == 0 )
            return whenOnBoundary;
        else
        {
            if( sign == 0 ) sign = cross > 0 ? 1 : -1;
            else if( (sign == 1 && cross < 0) || (sign == -1 && cross > 0) ) return 0; //outside convex
        }
    }
    return 1; //inside convex
}

//
//Convex Hull (Graham scan)
//

#include <vector>
#include <algorithm>

struct comp //for sorting the points at the start of the scan
{
    comp(const vector<point>& p, const point& r) : points(p), reference(r) {};

    const vector<point>& points;
    const point& reference;

    bool operator() (int a, int b) const
    {
        //return true if points[a] is seen LOWER THAN points[b] when seen from reference
        //when on same line, return true if a is CLOSER to the reference
        NUM cross = ( (points[a]-reference)^(points[b]-reference) );
        if( cross > 0 ) return true;
        else if( cross == 0 ) return sqDist(reference, points[a]) < sqDist(reference,points[b]);
        return false;
    }
};

//in the output vector are the indices of the points array that belong to the hull
void convexHull(const vector<point>& points, vector<int>& output)
{
    output.clear();

    //IMPORTANT: If possible that the points array is LESS than 3 points, make this special case:
    //if( points.empty() ) return;
    //else if( points.size() == 1 ){ output.push_back(0); return; }
    //else if( points.size() == 2 ){ output.push_back(0); output.push_back(1); return; }

    unsigned int bestIndex = 0;
    NUM minX = points[0].x;
    NUM minY = points[0].y;
    for(unsigned int i = 1; i < points.size(); ++i)
        if( points[i].x < minX || (points[i].x == minX && points[i].y < minY) ){ bestIndex = i; minX = points[i].x; minY = points[i].y; }

    vector<int> ordered; //index into points
    for(unsigned int i = 0; i < points.size(); ++i)
        if( i != bestIndex ) ordered.push_back(i);

    comp compare(points, points[bestIndex]);
    sort(ordered.begin(), ordered.end(), compare);

    output.push_back(bestIndex);
    output.push_back(ordered[0]);
    output.push_back(ordered[1]);
    for(unsigned int i = 2; i < ordered.size(); ++i)
    {
        //A = second to last element is output[count-1]
        //B = last element is output[count];
        //C = next element is ordered[i]
        //We need to check wether the line ABC makes a right-turn at B, if so, delete it
        //Use the cross product on (A-B) and (C-B): delete the point if (A-B)^(C-B) > 0

        //NOTE: >  INCLUDES points on the hull-line
        //      >= EXCLUDES points on the hull-line
        while( output.size() > 1 && ((points[output[count-1]] - points[output[count]])^(points[ordered[i]] - points[output[count]])) > 0 )
            output.pop_back();

        output.push_back(ordered[i]);
    }
    return;
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

    cout << "Starting timing" << endl;

    clock_t begin = clock();
    for(int i = 0; i < 100000000; ++i)
        sqDistPointSegment(point(randomd(),randomd()), point(randomd(),randomd()), point(randomd(), randomd()));
    clock_t end = clock();

    cout << "Time taken: " << ((double)(end-begin))/((double)CLOCKS_PER_SEC) << endl;
    cin.get();
    return 0;
}
