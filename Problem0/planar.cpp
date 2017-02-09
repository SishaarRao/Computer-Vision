/*
*		Created by Sishaar Rao
*		2/9/16
*		This is the Planar solution for the minimum distance problem
*		This will be utilizing the "Divide and Conquer approach"
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

float distance(float x1, float y1, float x2, float y2) {
   return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}

int main() {
   int input;
   cout << "Input: ";
   cin >> input;

   // Init 2D Array
   
   //float data[input][2];
   std::vector< std::vector<float> > data;
   cout << "Generating" << endl;
   // Fill Array
   for (int i = 0; i < input; i++) {
     std::vector<float> temp;
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     data.push_back(temp);
   }
   cout << "Generated" << endl;

   // Print Array
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
   const clock_t START = clock();

   

   const double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;

   //   cout << "Point 1: " << data[index1][0] << "  " << data[index1][1] << endl << "Point 2: " << data[index2][0] << "  " << data[index2][1] << endl;
   //   cout << "Distance: " << min << endl;
   cout << "Time to Calculate: " << T_ELAPSED;
   cout << endl << endl << endl;
   return 0;
}

