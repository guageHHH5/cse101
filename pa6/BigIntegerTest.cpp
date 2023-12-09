/*
Eric Wang, twang173, Programming Assignment 6
*/
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
   
   BigInteger A= BigInteger("-123456789");
   BigInteger B = BigInteger("123456789");
   cout << A.sign() << endl;
   cout << A.compare(B) << endl;
   A.makeZero();
   B.negate();
   
   cout << A+B << endl;
   cout << B-B << endl;
   cout << A-B << endl;

   BigInteger C = BigInteger("123456789");
   //C.makeZero();
   BigInteger D = BigInteger("123456789");
   //D.makeZero();
   cout << C+D << endl;


   // A = BigInteger("12");
   // B = BigInteger("14");
   // if (B>A){
   //    cout << "B is bigger" << endl;
   // }
   // if (B<A){
   //    cout << "B is smaller" << endl;
   // }
   // if (B==A){
   //    cout << "B is equal" << endl;
   // }
   // if (B>=A){
   //    cout << "B is bigger than or equal" << endl;
   // }
   // if (B<=A){
   //    cout << "B is less than or equal" << endl;
   // }

   // // test exceptions
   // try{
   //    BigInteger T = BigInteger("");
   // }catch( std::invalid_argument& e ){
   //    cout << e.what() << endl;
   //    cout << "   continuing" << endl;
   // }
   // try{
   //    BigInteger T = BigInteger("-");
   // }catch( std::invalid_argument& e ){
   //    cout << e.what() << endl;
   //    cout << "   continuing" << endl;
   // }
   // try{
   //    BigInteger T = BigInteger("495867584985@2343");
   // }catch( std::invalid_argument& e ){
   //    cout << e.what() << endl;
   //    cout << "   continuing" << endl;
   // }
   // try{
   //    BigInteger T = BigInteger("---5654324--12");
   // }catch( std::invalid_argument& e ){
   //    cout << e.what() << endl;
   //    cout << "   continuing   " << endl;
   // }

   cout << endl;

   return EXIT_SUCCESS;
}