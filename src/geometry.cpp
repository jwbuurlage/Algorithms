//Max signed integer: 2,147,483,647
typedef double NUM; //use either double or long long

//Two large prime numbers
//982451653
//81253449

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

//Distance SQUARED from a to line through bc
double sqDistPointLine(point a, point b, point c)
{
    a = a-b;
    c = c-b;
    return (a^c)*(a^c)/((double)c*c);
}

//Distance SQUARED from point a to line segment bc
double sqDistPointSegment(point a, point b, point c)
{
    a = a-b;
    c = c-b;
    NUM dot = a*c;
    if( dot <= 0 ) return a*a;
    else
    {
        NUM len = c*c;
        if( dot >= len ) return (a-c)*(a-c);
        else return a*a - dot*dot/((double)len); //OR: (a^c)*(a^c) / ((double)len);
        //point projection = c * (dot/((double)len);
    }
}

//point a on segment bc
bool pointOnSegment(point a, point b, point c)
{
    a = a-b;
    c = c-b;
    NUM cross = a^c;
    if( cross != 0 ) return false;
    //a is on the line through b and c
    NUM dot = a*c;
    if( dot < 0 ) return false;
    if( dot > c*c ) return false;
    return true;
}

//Line segment a1---a2 intersects with b1---b2
bool segmentsIntersect(const point& a1, const point& a2, const point& b1, const point& b2)
{
    point q = a2-a1;
    point r = b2-b1;
    point s = b1-a1;
    NUM cross = q^r;
    if( cross == 0 ){ //parallel
        NUM cross2 = q^s;
        if( cross2 != 0 ) return false; //no intersection
        //line segments lie in the extension of each other
        NUM v1 = s*q;
        NUM v2 = (b2-a1)*q;
        NUM v3 = q*q;
        if( v1 >= 0 && v1 <= v3 ) return true; //b1 is between a1 and a2
        if( v2 >= 0 && v2 <= v3 ) return true; //b2 is between a1 and a2
        if( v1 <= 0 && v2 >= v3 ) return true; //b1 is before a1 and b2 is after a2
        return false;
    }
    NUM c1 = s^r;
    NUM c2 = s^q;
    //We must check if 0 <= c1/cross <= 1 and 0 <= c2/cross <= 1
    if( cross > 0 ){
        if( c1 < 0 ) return false;
        if( c1 > cross ) return false;
        if( c2 < 0 ) return false;
        if( c2 > cross ) return false;
    }else{
        if( c1 > 0 ) return false;
        if( c1 < cross ) return false;
        if( c2 > 0 ) return false;
        if( c2 < cross ) return false;
    }
    //double t = (s^r) / ((double)cross);
    //double u = (s^q) / ((double)cross);
    //point intersect = a1*(1-t) + a2*t;
    //point intersect = b1*(1-u) + b2*u;
    return true;
}

//This returns TWICE the area of a polygon because then it will always be an integer if the input is integers
NUM polygonTwiceArea(const vector<point>& polygon)
{
    //if( polygon.empty() ) return 0;
    NUM area = 0;
    point p0 = polygon[0];
    for(unsigned int i = 1; i+1 < polygon.size(); ++i) area += (polygon[i] - p0)^(polygon[i+1]-p0);
    return (area > 0 ? area : -area); //abs(area)
}

int pointInPolygon(point p, const vector<point>& polygon)
{
    //Check crossings with horizontal semi-line though p to +x
    int crosscount = 0;
    unsigned int N = polygon.size();
    for(unsigned int i = 0, j = N-1; i < N; j = i++)
    {
        if( pointOnSegment( p , polygon[j], polygon[i] ) ) return 2; //p on boundary
        //Check if it crosses the y=p.y line
        if( polygon[j].y > p.y ){
            if( polygon[i].y > p.y ) continue; //same side of line
            if( (p.x-polygon[i].x)*(polygon[j].y - polygon[i].y) < (polygon[j].x - polygon[i].x)*(p.y - polygon[i].y) )
                ++crosscount;
        }else{
            if( !(polygon[i].y > p.y) ) continue; //same side of line
            if( (p.x-polygon[i].x)*(polygon[j].y - polygon[i].y) > (polygon[j].x - polygon[i].x)*(p.y - polygon[i].y) )
                ++crosscount;
        }
    }
    if( crosscount % 2 == 0 ) return 0; //p was outside polygon
    else return 1; //p was inside polygon
}

//Assumes that polygon has unique points!
int pointInConvex(point p, const vector<point>& polygon, int whenOnBoundary = 0)
{
    //The cross product should always have the same sign when the point is inside the convex
    unsigned int N = polygon.size();
    int sign = 0;
    bool onExtendedBoundary = false;
    for(unsigned int i = 0, j = N-1; i < N; j = i++)
    {
        NUM cross = ((polygon[j] - p)^(polygon[i] - p));
        if( cross == 0 ) //epsilon when doubles
            onExtendedBoundary = true; //point is either on the boundary, or on the extended line of a boundary segment
        else
        {
            if( sign == 0 ) sign = cross > 0 ? 1 : -1;
            else if( (sign == 1 && cross < 0) || (sign == -1 && cross > 0) ) return 0; //outside convex
        }
    }
    //Either inside, or on boundary
    if(onExtendedBoundary) return whenOnBoundary;
    return 1; //inside convex
}

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
        //A = second to last element is output[output.size()-2]
        //B = last element is output.back()
        //C = next element is ordered[i]
        //We need to check wether the line ABC makes a right-turn at B, if so, delete it
        //Use the cross product on (A-B) and (C-B): delete the point if (A-B)^(C-B) > 0

        //NOTE: >  INCLUDES points on the hull-line
        //      >= EXCLUDES points on the hull-line
        while( output.size() > 1 && ((points[output[output.size()-2]] - points[output.back()])^(points[ordered[i]] - points[output.back()])) > 0 )
            output.pop_back();

        output.push_back(ordered[i]);
    }
    return;
}
