/*
*		Created by Sishaar Rao
*		2/8/16
*		This is the Brute Force solution for the minimum distance problem
*/

#include <iostream>
#include <cmath>

using namespace std;

float distance(float x1, float y1, float x2, float y2) {
   return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}


int solve(int in) {
   int input = in;
   // 2D Array
   float data[input][2];

   // Fill Array
   for (int i = 0; i < input; i++) {
      data[i][0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      data[i][1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
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
   return 0;
}


int main(){
  int i = 3;
  while(i < 3000){
    solve(i);
    i = i*2;
  }

  while(i < 15000){
     solve(i);
     i = i+1000;
  }

  solve(15000);

}

