/*
Eric Wang, twang173, Programming Assignment 8
*/
#include<iostream>
#include<string>
#include <fstream>
#include"Dictionary.h"

using namespace std;

int main(void){
   Dictionary A;
   //int x;
   // Test size and setValue 
   //cout << A.size() << endl;
   A.setValue("a", 1);
    A.setValue("b", 5);
    cout << A << endl;
    A.setValue("e", 10);
    A.end();
    A.setValue("h", 15);
    A.setValue("f", 20);
    A.setValue("i", 100);
    cout << A << endl;
    if (A.currentKey() != "e" || A.currentVal() != 10)
     printf("hello");
    A.end();
    A.prev();
    A.prev();
    cout << A << endl;
    cout << A.currentVal() << endl;
    if (A.currentKey() != "f" || A.currentVal() != 20)
     printf("you suck!");
    // return 0;

   // Test assignment
    Dictionary B = A;
    A.clear();
    B.clear();
    if (!(A == B))
      printf("dang\n");

    A.setValue("a", 1);
    //cout << A << endl;
    A.setValue("b", 5);
    A.setValue("e", 10);
    //cout << A << endl;
    A.setValue("h", 15);
    A.setValue("f", 20);
    //cout << A << endl;
    A.setValue("i", 100);
    //cout << A << endl;
    
    // cout << A << endl;
    if ((A == B))
     printf("oh wow\n");
    //cout << B << endl;
    B.setValue("a", 1);
    cout << B << endl;
    B.setValue("b", 5);
    B.setValue("e", 10);
    B.setValue("h", 15);
    B.setValue("f", 20);
    B.setValue("i", 100);

    cout << B << endl;
    if (!(A == B))
      printf("no way\n");

    B.clear();
    cout <<"B \n" << B << endl;
    B.setValue("i", 100);
    B.setValue("f", 20);
    B.setValue("h", 15);
    B.setValue("e", 10);
    B.setValue("b", 5);
    B.setValue("a", 1);

    cout <<"A \n" << A << endl;  
    cout <<"B \n" << B << endl;
    if (!(A == B))
      printf("oh naur\n");

    //return 0;
  //  // Test remove
  //  A.remove("yo");

  //  cout << A << endl;
  //  cout << B << endl;
   
  //  // Test contains, getValue, hasCurrent
  //  x = A.contains("hi");
  //  printf("%d\n", x);

  //  x = A.getValue("hi");
  //  printf("%d\n", x);

  //  x = A.hasCurrent();
  //  printf("%d\n", x);

  //  // Test begin, clear, end, prev, next, and equals
  //  A.begin();
  //  cout << A.currentKey() << endl;
  //  cout << A.currentVal() << endl;

  //  B.clear();
  //  cout << B << endl;

  //  A.end();
  //  cout << A.currentKey() << endl;
   
  //  A.prev();
  //  cout << A.currentKey() << endl;

  //  A.next();
  //  cout << A.currentKey() << endl;

  //  A.clear();
   
  //  if (A == B){
  //     printf("it works!");
  //  }  

   return 0;
}