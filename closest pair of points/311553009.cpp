#include <bits/stdc++.h>

using namespace std;

const int N = 100000;
 
struct Point
{ 
	double x, y; 
}point[N];

int n;
int stripe[N];

// find the distance between two pts
double dis(int i, int j)
{
    return sqrt(pow((point[i].x-point[j].x), 2) + pow((point[i].y-point[j].y), 2));
}


// sort
bool cmpxy(const Point& a, const Point& b)
{
    if(a.x != b.x)
    {
    	return a.x < b.x;
	}
    return a.y < b.y;
}
 
bool cmpy(const int& a, const int& b)
{
    return point[a].y < point[b].y;
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
double Closest_Pair(int left, int right)
{
    double d = DBL_MAX;
    
    if(left == right)
    {
    	return d;
	}
    else if(left + 1 == right)
    {
    	return dis(left, right);
	}
	
    int mid = (left + right) / 2;
    
    // Consider the vertical line passing through the middle point 
    // calculate the smallest distance dl on left of middle point and dr on right side 
    double dl = Closest_Pair(left, mid);
    double dr = Closest_Pair(mid + 1, right);
    
    // Find the smallest dist. on the left and right regions respectively
    d = min(dl, dr);
    
	int i, j, k = 0;
   	
   	// Only consider points within d of the cut
    // other points must have dist. larger than d
    for(i = left; i <= right; i++)
    {
        if(abs(point[mid].x - point[i].x) <= d)
        {
        	stripe[k] = i;
            k++;
		}
    }
    
    sort(stripe, stripe + k, cmpy);
   
    for(i = 0; i < k; i++)
    {
        for(j = i + 1; j < k && point[stripe[j]].y - point[stripe[i]].y < d; j++)
        {
            double mindist = dis(stripe[i],stripe[j]);
            if(d > mindist)
            {
            	d = mindist;
			}
        }
    }
    return d;
}
 
 
int main()
{
	int T;
	
	cin >> T;
	//scanf("%d", &T)
	for(int t = 0; t < T; t++)
	{
        cin >> n;
        //scanf("%d", &n)
        if(n == 0)
        {
        	break;
		}
        for(int i = 0; i < n; i++)
        {
        	cin >> point[i].x >> point[i].y;
        	//scanf("%lf %lf", &point[i].x,&point[i].y);
		}
        sort(point, point+n, cmpxy);
        
        cout << Closest_Pair(0,n-1) << endl;
        //printf("%.6f\n",Closest_Pair(0,n-1));
	}
    return 0;
}
