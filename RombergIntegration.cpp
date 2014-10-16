#include "RombergIntegration.h"
#include "RecursiveIntegration.h"
#include "QueueLinked.h"
#include "Double.h"
using CSC2110::Double;

#include <math.h>

#include <iostream>
#include <cmath>
using namespace std;

//a is the lower limit and b is the upper limit
double RombergIntegration::accurateRomberg(MultiVarFunction* f, double a, double b, int level)
{
   Double* db;  //use this variable to place and retrieve values on the queue
   
   QueueLinked<Double>* q1 = new QueueLinked<Double>();
   QueueLinked<Double>* q2 = new QueueLinked<Double>();


   int counter = 0;
   int n = 1;  //current number of intervals
   while (counter <= level)
   {
      //DO THIS
      //obtain the required number of trapezoid evaluations depending on the number of levels requested
      //put all of the level 0 results on the q1
  
      double temp = RecursiveIntegration::romberg(f,a,b,n);
      db = new Double(temp);
      q1 -> enqueue(db);
      
      n = 2*n;  //double the number of intervals
      counter++;
   }

   //q1 now has all of the level 0 integration results

   double factor;  //use this to compute the current Romberg Factor (4^k stuff)
   int power = 1;  //k, used to compute the Romberg Factor

   //if level 0 has been requested, the loop will not execute
   //the total number of executions of the loop is ??

   //DO THIS
   int iterations = 0;               //can be precomputed

   int i = level;
   while(i > 0)
   {
      iterations = iterations + i;
      i--;
   }

   while (iterations > 0)
   {
      //DO THIS
      //use the algorithm described in the lab to improve the accuracy of your level 0 results
 
      Double* D_i_m = q1 -> dequeue();
      Double* D_i_l = q1 -> peek();

      if(D_i_l != NULL)
      {
         double i_m = D_i_m-> getValue();
         double i_l = D_i_l -> getValue();        

         factor = pow(4, power);
         double funct = (((factor * i_m) - i_l)/(factor - 1));
         db = new Double(funct);
  
         q2 -> enqueue(db);
      } 

      else
      {
         iterations++;
      }   

      if((iterations-1) == 0 || D_i_l == NULL)
      {
         db = q1 -> dequeue();
         delete db;

         db = q2 -> peek();
         while(db != NULL)
         {
            db = q2 -> dequeue();
            q1 -> enqueue(db);

            db = q2 -> peek();
         }

         power++;
      }

      iterations--;
   }

   //obtain the final answer
   db = q1->dequeue();
   double result = db->getValue();

   delete db;

   delete q1;
   delete q2;

   return result;
}
