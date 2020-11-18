//
//  main.cpp
//  stats.cxx
//
//  Created by Emma Athow on 2/4/20.
//  Copyright © 2020 Emma Athow. All rights reserved.
//
#include <cstdlib>
#include <iostream>
#include "stats.h"
using namespace std;

namespace main_savitch_2C {

statistician :: statistician() {
    //Postcondition: Object has been initialized & is ready to accept a sequence of numbers. Various statistics will be calculated about the sequence.
    count = 0;
    total = 0;
}

void statistician :: next(double r) {
    //Postcondition: The number r has been given to the statistician as the next number in its sequence of numbers.
    if (length() == 0) {
        //Sets the first value given equal to both the tinyest AND the largest
        tinyest = r;
        largest = r;
    }
    //Checks new inputs and REPLACES as seen fit (if new number < r, tinyest has new number & vise versa for largest)
    if (r <= tinyest) { tinyest = r;}
    if (r >= largest) { largest = r;}
    count ++;
    total += r;
      
}

void statistician :: reset() {
    //Postcondition: The statistician has been cleared, as if no numbers had yet been given to it.
    count = 0;
    total = 0;
}

int statistician :: length() const {
   //Postcondition: The return value is the length of the sequence that has been given to the statistician (i.e., the number of times that the next(r) function has been activated).
    return count;
}

double statistician :: sum() const {
    //Postcondition: The return value is the sum of all the numbers in the statistician's sequence.
    return total;
}

double statistician :: mean() const {
    //Precondition: length( ) > 0
    //Postcondition: The return value is the arithmetic mean (i.e., the average of all the numbers in the statistician's sequence).
    assert(length()>0);
    return total/count;
}

double statistician :: minimum() const {
    //Precondition: length( ) > 0
    //Postcondition: The return value is the tinyest number in the statistician's sequence.
    assert(length() > 0);
    return tinyest;
}

double statistician :: maximum() const {
    //Precondition: length( ) > 0
    //Postcondition: The return value is the largest number in the statistician's sequence.
    assert(length() > 0);
    return largest;
}

statistician operator+ (const statistician& s1, const statistician& s2) {
    if(s1.length() == 0) { return s2;}
    if(s2.length() == 0) { return s1;} //Gives s3 length of s1, s2 != 0
    statistician s3;
    s3.count = s1.length() + s2.length(); //The number of values in s3 is equivalent to those in s1 + s2
    s3.total = s1.sum() +s2.sum(); //The sum of s3 is equivalent to that of s1 + s2
    if (s1.tinyest < s2.tinyest) { s3.tinyest = s1.tinyest;}
    else { s3.tinyest = s2.tinyest;} //s3 takes the smallest value out of s1 & s2
    if(s1.largest > s2.largest) {s3.largest = s1.largest;}
    else { s3.largest = s2.largest;} //s3 takes the largest value out of s1 & s2
    return s3;
}

statistician operator* (double scale, const statistician& s){
    if(s.length() == 0) { return s;}
    statistician t;
    t.count = s.length(); //Length is NOT multiplied and does NOT change
    t.total = s.sum() * scale;
    if(scale > 0) {
        //Min and max are being multiplied by a positive double, "scale"
        t.tinyest = s.minimum() * scale;
        t.largest = s.maximum() * scale;
    }
    else {
        //Here, the min and max FLIP because we are multiplying them by a NEGATIVE number
        t.tinyest = s.maximum() * scale;
        t.largest = s.minimum() * scale;
    }
    return t;
}

bool operator== (const statistician& s1, const statistician& s2){
    bool val = false; //This makes it so that val MUST be proven true
    if (s1.length() == 0 && s2.length() == 0) { val = true;} //If s1 & s2 are both zero, then they are equivalent and val is tue
    else if(s1.length() > 0 && s2.length() > 0) {
        //If  s1 & s2 have lengths greater than equal, we muct check that all their values (mean, min, max, sum,length) are equivalent for val to be true
        if((s1.length() == s2.length()) && (s1.sum() == s2.sum()) && (s1.mean() == s2.mean()) && (s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum())) { val = true;}
    }
    return val; //Returns either true, or false
}
}
