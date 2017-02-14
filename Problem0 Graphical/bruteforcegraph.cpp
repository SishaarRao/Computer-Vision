/*
*		Created by Sishaar Rao
*		2/13/16
*		This is the Brute Force solution for the minimum distance problem
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

float distance(float x1, float y1, float x2, float y2) {
   return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}


std::vector< std::vector<float> > solve(int in) {
   int input = in;
   std::vector< std::vector<float> > data;

   // Fill Array
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
   int index1;
   int index2;
   const clock_t START = clock();

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
   const double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;

   //   cout << "Point 1: " << data[index1][0] << "  " << data[index1][1] << endl << "Point 2: " << data[index2][0] << "  " << data[index2][1] << endl;
   cout << input << "  " << T_ELAPSED;


   cout << endl;
   return data;
}

int generateImage(std::vector< std::vector<float> > data){

}

int main(){
   int input = 1000;
   std::vector< std::vector<float> > data = solve(input);
   /* Print Data Vectory
   for(int i=0; i<input; i++){
      for(int j=0; j<2; j++){
	cout << data[i][j]  << "  ";
      }
      cout << endl;
   }
   cout << endl << endl;
   */
   
}

