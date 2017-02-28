/*
*		Created by Sishaar Rao
*		2/9/16
*		This is the side by side comparison of a Brute Force solution
*               and a Planar solution for the min distance problem
*		The Planar solution will be utilizing the "Divide and Conquer" approach
*               This will compare the times for varying dataset sizes
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

std::vector< std::vector<float> > createData(int input) {
   // Init 2D Array
   
   //float data[input][2];
   std::vector< std::vector<float> > data;
   //cout << "Generating" << endl;
   // Fill Array
   srand(std::time(0));
   for (int i = 0; i < input; i++) {
     std::vector<float> temp;
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     data.push_back(temp);
   }
   //cout << "Generated" << endl;

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
   //cout << "Time to Sort the Array: " << T_ELAPSED0 << endl << endl << endl;

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

float bruteforce(std::vector< std::vector<float> > data) {
   // Find min pair
   const clock_t START0 = clock();
   float min = sqrt(2);
   int index1; int index2;
   for(int i=0; i<data.size(); i++)
   {
     for(int j=i+1; j<data.size(); j++)
      {
	 if (distance(data[i][0], data[i][1], data[j][0], data[j][1]) < min)
	 {
	    min = distance(data[i][0], data[i][1], data[j][0], data[j][1]);
	    index1 = i; index2 = j;
	 }
      }
   }
   const double T_ELAPSED0 = (double)(clock() - START0) / CLOCKS_PER_SEC;



   //   cout << "Point 1: " << data[index1][0] << "  " << data[index1][1] << endl << "Point 2: " << data[index2][0] << "  " << data[index2][1] << endl;
   //cout << "Minimum Point: " << index1 << "  " << index2 << endl;
   //cout << "Minimum: " << min << endl;
   //cout << "Time to Calculate: " << T_ELAPSED0 << endl << endl << endl;
   return T_ELAPSED0;
}



float planar(std::vector< std::vector<float> > data){
   const clock_t START = clock();
   //Split the set of points into two equal-sized subsets by a vertical line x=xmid
   std::vector< std::vector<float> > dataL, dataR;
   for(int i = 0; i < data.size(); i++){
      if(i < data.size()/2) dataL.push_back(data[i]);
      else dataR.push_back(data[i]);
   }

   //Solve the problem recursively in the left and right subsets. This yields the left-side and right-side minimum distances dLmin and dRmin, respectively
   
	   // Index1 and Index2 will be the two closest entries in DataL
   int index1; int index2;
   float dLmin = sqrt(2);
   for(int i=0; i<dataL.size(); i++){
      for(int j=i+1; j<dataL.size(); j++){
      	 if (distance(dataL[i][0], dataL[i][1], dataL[j][0], dataL[j][1]) < dLmin){
	    dLmin = distance(dataL[i][0], dataL[i][1], dataL[j][0], dataL[j][1]);
	    index1 = i; index2 = j;
	 }
      }
   }

   	// Index3 and Index4 will be the two closest entries in DataR
   int index3; int index4;
   float dRmin = sqrt(2);
   for(int i=0; i<dataR.size(); i++){
      for(int j=i+1; j<dataR.size(); j++){
	 if (distance(dataR[i][0], dataR[i][1], dataR[j][0], dataR[j][1]) < dRmin){
	    dRmin = distance(dataR[i][0], dataR[i][1], dataR[j][0], dataR[j][1]);
	    index3 = i; index4 = j;
	 }
      }
   }

   float myMin = minimum(dLmin, dRmin);
   
   //Find the minimal distance dLRmin among the set of pairs of points in which one point lies on the left of the dividing vertical and the other point lies to the right.
   
	   // Find upper and lower bound
   int lower; int upper;
   for(int i= dataL.size() - 1; i > 0; i--){
     if(dataL[dataL.size()-1][0] - dataL[i][0] > myMin){
       lower = i;
       break;
     }
   }

   for(int i= 0; i < dataR.size(); i++){
     if(dataR[i][0] - dataR[0][0] > myMin){
       upper = i;
       break;
     }
   }
   //cout << "Lower: " << lower << endl;
   //cout << "Upper: " << upper << endl;
	   // Loop through and find min
   float dLRmin = sqrt(2);
   // Index 5 and Index 6 are the closest entries in dLRmin
   int index5; int index6;
   for(int i = lower; i < dataL.size(); i++){
      for(int j = 0; j < upper; j++){
	 if (distance(dataL[i][0], dataL[i][1], dataR[j][0], dataR[j][1]) < dLRmin){
	    dLRmin = distance(dataL[i][0], dataL[i][1], dataR[j][0], dataR[j][1]);
	    index5 = i; index6 = j;
	 }
      }
   }


   //minimum among dLmin, dRmin, and dLRmin

   float min = smallest(dLmin, dRmin, dLRmin);
   /*cout << "Minimum Point: ";
   if(dLmin == min) cout << index1 << "  " << index2 << endl;
   else if(dRmin == min) cout << index3+data.size()/2 << "  " << index4+data.size()/2 << endl;
   else cout << index5+upper << "  " << index6+upper << endl;
   */
   //cout << "Minimum: " << min << endl;
   // Print the minimums
   /*
   cout << "All Indexes:" << endl;
   cout << "dLmin: " << index1 << " , " << index2 << endl;
   cout << "dRmin: " << index3 << " , " << index4 << endl;
   cout << "dLRmin: " << index5 << " , " << index5 << endl;
   cout << "Minimum: " << min << endl << endl;
   */
   
   const double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;

   //   cout << "Point 1: " << data[index1][0] << "  " << data[index1][1] << endl << "Point 2: " << data[index2][0] << "  " << data[index2][1] << endl;
   //   cout << "Distance: " << min << endl;
   //cout << "Time to Calculate: " << T_ELAPSED;
   //cout << endl << endl << endl;
   return T_ELAPSED;
}

int main(){
  int i = 500;
  while(i<15000){
    std::vector< std::vector<float> > data = createData(i);
    cout << i << "   " << planar(data) << "   " << bruteforce(data) <<endl;
    i += 500;
  }
}

