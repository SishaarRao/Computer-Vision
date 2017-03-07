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
   for(int i=start; i<end; i++){
      for(int j=i+1; j<end; j++){
	 float dist = distance(data[i][0], data[i][1], data[j][0], data[j][1]);
	 if(dist < min){
	    min = dist;
	 }
      }
   }
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

// Start the clock
//clock_t START = clock();
// Find elapsed time
//double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;

double UPPER_LOWER_ELAPSED = 0.0;
double BRUTE_ELAPSED = 0.0;
double MINIMUM_ELAPSED = 0.0;
double CALCULATIONS_ELAPSED = 0.0;

float planar(std::vector< std::vector<float> > data, int start, int end){
   clock_t START;
   START = clock();
   int mid = ((end - start)/2) + start;
   CALCULATIONS_ELAPSED += (double)(clock() - START) / CLOCKS_PER_SEC;
   //Solve the problem recursively in the left and right subsets. This yields the left-side and right-side minimum distances dLmin and dRmin, respectively

   //Case where subset is small enough to bruteforce
   START = clock();
   if(end - start <= 3)
     return bruteforce(data, start, end);
   BRUTE_ELAPSED += (double)(clock() - START) / CLOCKS_PER_SEC;
   
   //Case where we need to split the dataset and recur
   float dLmin = planar(data, start, mid);
   float dRmin = planar(data, mid, end);
   START = clock();
   float myMin = minimum(dLmin, dRmin);
   MINIMUM_ELAPSED += (double)(clock() - START) / CLOCKS_PER_SEC;
   
   // Find upper and lower bound
   START = clock();
   int lower = start; int upper = end; 
   for(int i= mid; i >= start; i--){
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
   UPPER_LOWER_ELAPSED += (double)(clock() - START) / CLOCKS_PER_SEC;

   // Loop through and find min
   START = clock();
   float dLRmin = bruteforce(data, lower, upper);
   BRUTE_ELAPSED += (double)(clock() - START) / CLOCKS_PER_SEC;
   
   //minimum among dLmin, dRmin, and dLRmin
   START = clock();
   float smallest0 = smallest(dLmin, dRmin, dLRmin);
   MINIMUM_ELAPSED += (double)(clock() - START) / CLOCKS_PER_SEC;
   return smallest0;
}

int main(){
  std::vector< std::vector<float> > data = createData();
  clock_t START = clock();
  cout << "Planar: " << planar(data, 0, data.size()) << endl;
  double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
  cout << "Time: " << T_ELAPSED << endl << endl;
  START = clock();
  cout << "Brute Force: " << bruteforce2(data) <<endl;
  T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
  cout << "Time: " << T_ELAPSED << endl << endl;

  cout << "Brute elapsed: " << BRUTE_ELAPSED << endl;
  cout << "Minimum elapsed: " << MINIMUM_ELAPSED << endl;
  cout << "Upper Lower elapsed: " << UPPER_LOWER_ELAPSED << endl;
  cout << "Calculations elapsed: " << CALCULATIONS_ELAPSED << endl << endl;
}

