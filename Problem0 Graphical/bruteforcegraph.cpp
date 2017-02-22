/*
*		Created by Sishaar Rao
*		2/13/16
*		This is the Brute Force solution for the minimum distance problem
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

float distance(float x1, float y1, float x2, float y2) {
   return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}

int index1;
int index2;
std::vector< std::vector<float> > solve(int in) {
   int input = in;
   std::vector< std::vector<float> > data;

   // Fill Array
   srand(std::time(0));
   for (int i = 0; i < input; i++) {
     std::vector<float> temp;
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     temp.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
     data.push_back(temp);
   }

   // Print the 2D Array
	/*
   for(int i=0; i<input; i++)
	{
		for(int j=0; j<2; j++)
		{
			cout << data[i][j]  << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
	*/
   // Find min pair
   float min = sqrt(2);
   for(int i=0; i<input; i++)
   {
      for(int j=i+1; j<input; j++)
      {
	 if (distance(data[i][0], data[i][1], data[j][0], data[j][1]) < min)
	 {
	    min = distance(data[i][0], data[i][1], data[j][0], data[j][1]);
	    index1 = i; index2 = j;
	 }
      }
   }

   //   cout << "Point 1: " << data[index1][0] << "  " << data[index1][1] << endl << "Point 2: " << data[index2][0] << "  " << data[index2][1] << endl;
   cout << "Num of Input: " << input << endl;

   cout << "Min distance: " << min << endl;
   return data;
}

int generateImage(std::vector< std::vector<float> > data){
   ofstream output;
   const int dimensions = 200;
   // Create File and Add Header
   output.open("output.ppm");

   output << "P3 " << dimensions << " " << dimensions << " 1" << "\n";

   int outputMatrix[dimensions][dimensions] = {{0}};
   // Begin Looping through and adding pixels
   for(int i=0; i<data.size(); i++){
      outputMatrix[(int)(dimensions*data[i][0])][(int)(dimensions*data[i][1])] = 1;
   }
   // Mark the minimum pixels
   outputMatrix[(int)(dimensions*data[index1][0])][(int)(dimensions*data[index1][1])] = 3;
   outputMatrix[(int)(dimensions*data[index2][0])][(int)(dimensions*data[index2][1])] = 3;

   // Bresenham Algorithm

   float x1temp = (float)(dimensions)*(float)(data[index1][0]);
   float y1temp = (float)(dimensions)*(float)(data[index1][1]);
   float x2temp = (float)(dimensions)*(float)(data[index2][0]);
   float y2temp = (float)(dimensions)*(float)(data[index2][1]);
   float x1; float x2; float y1; float y2;
   if(x1temp < x2temp){
      x1 = x1temp;
      x2 = x2temp;
      y1 = y1temp;
      y2 = y2temp;
   }
   else{
      x1 = x2temp;
      x2 = x1temp;
      y1 = y2temp;
      y2 = y1temp;
   }
   cout << x1 << " " << y1 << endl;
   cout << x2 << " " << y2 << endl;
   float dx = x2 - x1;
   float dy = y2 - y1;

   float m = (dy)/(dx);

   // Case if the slope is positive
   if(m > 0){
      cout << "m: " << m << endl;
      int j = (int)(y1);
      cout << "j: " << j << endl;
      float e = m - 1.0;
      cout << "e: " << e << endl;
      for(int i = (int)(x1); i <= (int)(x2); i++){
	 // Illuminate point
	 outputMatrix[i][j] = 2;
	 if(e >= 0){
	    while(e>0){
	       e -= 1.0;
	       j += 1;
	    }
	 }
	 e += m;
      }
   }
   // Case if the slope is negative
   else{
      cout << "m: " << m << endl;
      int j = (int)(y1);
      cout << "j: " << j << endl;
      float e = m + 1.0;
      cout << "e: " << e << endl;
      for(int i = (int)(x1); i <= (int)(x2); i++){
	 // Illuminate point
	 outputMatrix[i][j] = 2;
	 if(e <= 0){
	    while(e<0){
	       e += 1.0;
	       j -= 1;
	    }
	 }
	 e += m;
      }
   }

   // Highlight the ending points because sometimes we wanna see where
   //    they are so that we can check if the line is drawn correctly

   outputMatrix[(int)(x2)][(int)(y2)] = 3;
   outputMatrix[(int)(x1)][(int)(y1)] = 3;


   // Write to the image
   for(int i=0; i<dimensions; i++){
      for(int j=0; j<dimensions; j++){
	 if(outputMatrix[i][j] == 1) output << "0 0 0 ";
	 else if(outputMatrix[i][j] == 3) output << "0 1 0 ";
	 else if(outputMatrix[i][j] == 2) output << "1 0 0 ";
	 else output << "1 1 1 ";
      }
      output << "\n";
   }

   output.close();
   return 0;
}

int main(){
      const int input = 20;
      clock_t START = clock();
      std::vector< std::vector<float> > data = solve(input);
      double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
      cout << "Time to generate data: " << T_ELAPSED << endl;
      /* Print Data Vector
	 for(int i=0; i<input; i++){
	 for(int j=0; j<2; j++){
	 cout << data[i][j]  << "  ";
	 }
	 cout << endl;
	 }
	 cout << endl << endl;
      */
      START = clock();
      generateImage(data);
      T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
      cout << "Time to generate image: " << T_ELAPSED << endl;
}

