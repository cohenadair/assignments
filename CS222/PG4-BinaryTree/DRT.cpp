#include <string>
#include "DRT.h"
using namespace std;

DRT::DRT (string d, string n, string p) {

 data = d; next = n; prev = p;
}

string DRT::getdata () {return data;}

string DRT::getnext () {return next;}

string DRT::getprev () {return prev;}
