/*
*		Created by Sishaar Rao
*		2/9/16
*               This is a recursive implementation of the divide and conquer method 
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

float distance(float x1, float y1, float x2, float y2) {
   return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}

float minimum(float x1, float x2){
  if(x1 >= x2) return x2;
  else return x1;
}

float smallest(float x, float y, float z){
  //return std::min({x, y, z});
  if(x <= y and x <= z) return x;
  else if(y <= x and y <= z) return y;
  else return z;
}

std::vector< std::vector<float> > createData() {
   int input;
   cout << "Input: ";
   cin >> input;

   // Init 2D Array
   
   //float data[input][2];
   std::vector< std::vector<float> > data;
   cout << "Generating" << endl;
   // Fill Array
   srand(std::time(0));
   for (int i = 0; i < input; i++) {
     std::vector<float> temp;
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     data.push_back(temp);
   }
   cout << "Generated" << endl;

   // Print an Unsorted Array
   /*
   for (int i = 0; i < data.size(); i++)
   {
      for (int j = 0; j < data[i].size(); j++)
      {
	cout << data[i][j] << "  ";
      }
      cout << endl;
   }
   */
   // Sort the Vector
   const clock_t START0 = clock();
   std::sort(begin(data), end(data));
   const double T_ELAPSED0 = (double)(clock() - START0) / CLOCKS_PER_SEC;
   cout << "Time to Sort the Array: " << T_ELAPSED0 << endl << endl << endl;

   // Print a Sorted Array
   /*
   for (int i = 0; i < data.size(); i++)
   {
      for (int j = 0; j < data[i].size(); j++)
      {
	cout << data[i][j] << "  ";
      }
      cout << endl;
   }
   */
   return data;
}

float bruteforce(std::vector< std::vector<float> > data, int start, int end) {
   float min = sqrt(2);
   for(int i=start; i<end; i++)
     for(int j=i+1; j<end; j++)
	 if (distance(data[i][0], data[i][1], data[j][0], data[j][1]) < min)
	    min = distance(data[i][0], data[i][1], data[j][0], data[j][1]);
   return min;
}

float bruteforce2(std::vector< std::vector<float> > data) {
   float min = sqrt(2);
   for(int i=0; i<data.size(); i++)
      for(int j=i+1; j<data.size(); j++)
	 if (distance(data[i][0], data[i][1], data[j][0], data[j][1]) < min)
	    min = distance(data[i][0], data[i][1], data[j][0], data[j][1]);
   return min;
}


float planar(std::vector< std::vector<float> > data, int start, int end){
   int mid = ((end - start)/2) + start;
   //Solve the problem recursively in the left and right subsets. This yields the left-side and right-side minimum distances dLmin and dRmin, respectively

   //Case where subset is small enough to bruteforce
   cout << start << " " << end << endl;
   if(end - start <= 3)
      return bruteforce(data, start, end);

   //Case where we need to split the dataset and recur
   float dLmin = planar(data, start, mid);
   float dRmin = planar(data, mid, end);
   
   float myMin = minimum(dLmin, dRmin);
   //Find the minimal distance dLRmin among the set of pairs of points in which one point lies on the left of the dividing vertical and the other point lies to the right.
   //   cout << "Mid: " << mid << endl;
   //   cout << "Min: " << myMin << endl;
   // Find upper and lower bound
   int lower = start; int upper = end; 
   for(int i= mid; i >= start; i--){
      // cout << "calc: " << data[mid][0] - data[i][0] << endl;
     if(data[mid][0] - data[i][0] > myMin){
       lower = i;
       break;
     }
   }

   for(int i= mid; i < end; i++){
     if(data[i][0] - data[mid][0] > myMin){
       upper = i;
       break;
     }
   }
   cout << "Lower: " << lower << endl;
   cout << "Upper: " << upper << endl;

   // Loop through and find min
   float dLRmin = bruteforce(data, upper, lower);


   //minimum among dLmin, dRmin, and dLRmin
   return smallest(dLmin, dRmin, dLRmin);
}

int main(){
  std::vector< std::vector<float> > data = createData();
  cout << "Planar: " << planar(data, 0, data.size()) << endl;
  cout << "Brute Force: " << bruteforce2(data) <<endl;
}

