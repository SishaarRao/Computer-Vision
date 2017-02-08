#include <iostream>
#include <cmath>

using namespace std;

float distance(float x1, float y1, float x2, float y2) {
   return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}

int main() {
   cout << distance(0,0,1,1);


   return 0;
}
