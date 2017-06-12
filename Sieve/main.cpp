#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

class Point {
private:
  float xval, yval;
public:
  // Constructor uses default arguments to allow calling with zero, one,
  // or two values.
  Point(float x = 0.0, float y = 0.0) {
    xval = x;
    yval = y;
  }
  // Extractors.
  float x() { return xval; }
  float y() { return yval; }
  
  // Distance to another point.  Pythagorean thm.
  float dist(Point other) {
    float xd = xval - other.xval;
    float yd = yval - other.yval;
    return sqrt(xd*xd + yd*yd);
  }
  // Add or subtract two points.
  Point add(Point b)
  {
    return Point(xval + b.xval, yval + b.yval);
  }
  Point sub(Point b)
  {
    return Point(xval - b.xval, yval - b.yval);
  }
  
  // Move the existing point.
  void move(float a, float b)
  {
    xval += a;
    yval += b;
  }
  
  // Print the point on the stream.  The class ostream is a base class
  // for output streams of various types.
  void print()
  {
    cout << "(" << xval << "," << yval << ")";
  }
};

int main() {
   int input;
   cout << "Input: ";
   cin >> input;

   // Init Array
   Point data[input];
	cout << "Generating" << endl;
   // Fill Array
   for (int i = 0; i < input; i++) {
      float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      data[i] = Point(x,y);
   }
	cout << "Generated" << endl;

   // Find min pair
   float min = sqrt(2);
   int index1; int index2;
   const clock_t START = clock();

   for(int i=0; i<input; i++)
   {
      for(int j=i+1; j<input; j++)
      {
	 if (data[i].dist(data[j]) < min)
	 {
	   min = data[i].dist(data[j]);
	    index1 = i; index2 = j;
	 }
      }
   }
   const double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;

   cout << "Point 1: "; data[index1].print(); cout << endl << "Point 2: "; data[index2].print(); cout << endl;
   cout << "Distance: " << min << endl;
   cout << "Time to Calculate: " << T_ELAPSED;

   cout << endl << endl << endl;
   return 0;
}
