#include <bits/stdc++.h>

using namespace std;

struct Point{ double x, y; };

// Find the distance between two pts
double dist(Point p1, Point p2)
{
	return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y), 2));
}

// Sort
int sortbyX(const void* a, const void* b)
{
    Point *p1 = (Point *)a;
	Point *p2 = (Point *)b;
    return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}

int sortbyY(const void* a, const void* b)
{
	Point *p1 = (Point *)a;
	Point *p2 = (Point *)b;
    return (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
}


double minDist_BF(Point P[], int n)
{
	double min = DBL_MAX;
	for (int i = 0; i < n; ++i)
	{
		for(int j = i+1; j < n; ++j)
		{
			if(dist(P[i], P[j]) < min)
			{
				min = dist(P[i], P[j]);
			}
		}
	}
	return min;
}

double stripeClosest(Point stripe[], int size, double d) 
{ 
    double mindist = d;

    for (int i = 0; i < size; ++i)
    {
    	for (int j = i+1; j < size && (stripe[j].y - stripe[i].y) < mindist; ++j)
    	{
    		if (dist(stripe[i], stripe[j]) < mindist)
    		{
    			mindist = dist(stripe[i], stripe[j]); 
			}
		}
	}
    return mindist; 
} 

double min(double x, double y) 
{
    return (x < y)? x : y; 
} 

//////////////////////////////////////////////////////////////////////
///             1. closest dist in the left region                 ///
///             2. closest dist in the right region                ///
///             3. closest dist cross the two regions              ///
//////////////////////////////////////////////////////////////////////

// Divide and Conquer
double closest_DivandConq(Point Px[], Point Py[], int n) 
{ 
    // If there are only 2 or 3 points, then use brute force 
    if (n <= 3) 
    {
    	return minDist_BF(Px, n);
	}
	
	// All pts seperate to left and right region
    // Find the middle point 
    int mid = n/2; 
    Point midPoint = Px[mid];

    // Divide points in y sorted array around the vertical line
    Point Pyl[mid];
    Point Pyr[n-mid];
    int left_idx = 0, right_idx = 0;
    for (int i = 0; i < n; i++) 
    {
	    if ((Py[i].x < midPoint.x || (Py[i].x == midPoint.x && Py[i].y < midPoint.y)) && left_idx < mid)
	    {
	    	Pyl[left_idx++] = Py[i];
		}
	    else
	    {
	    	Pyr[right_idx++] = Py[i]; 
		}
    } 

    // Consider the vertical line passing through the middle point 
    // calculate the smallest distance dl on left of middle point and dr on right side 
    double dl = closest_DivandConq(Px, Pyl, mid); 
    double dr = closest_DivandConq(Px + mid, Pyr, n-mid); 

    // Find the smallest dist. on the left and right regions respectively
    double d = min(dl, dr); 

    // Points close (closer than d) to the line passing through the middle point 
    Point stripe[n]; 
    int j = 0; 
    for (int i = 0; i < n; i++) 
    {
    	// Only consider points within d of the cut
    	// other points must have dist. larger than d
    	if (abs(Py[i].x - midPoint.x) < d) 
    	{
    		stripe[j] = Py[i];
			j++; 
		}
	}
	
    // Find the closest points in strip
    return stripeClosest(stripe, j, d); 
} 

double closestDist(Point P[], int n) 
{ 
    Point Px[n]; 
    Point Py[n]; 
    for (int i = 0; i < n; i++) 
    { 
        Px[i] = P[i]; 
        Py[i] = P[i]; 
    } 

    qsort(Px, n, sizeof(Point), sortbyX); 
    qsort(Py, n, sizeof(Point), sortbyY); 

    return closest_DivandConq(Px, Py, n); 
} 

int main()
{
	int n, T;
	double minDist;
	Point p[100000];
	
	cin >> T;
 	for(int t = 0; t < T; t++)
	{
		cin >> n;
		for(int i = 0; i < n; i++)
		{
			cin >> p[i].x >> p[i].y;
		}
	
		minDist = closestDist(p, n);
	
	    cout << minDist << endl;
	}
    
    return 0;
}
