#ifndef _DATABASE_
#define _DATABASE_

#include <string>
#include "DRT.h"
using namespace std;

class DRT;
class Database {

 public:

  virtual DRT * search (string key) = 0;

  virtual DRT * modify (string key, string data) = 0;

};

#endif

/*

Both search and modify return DRT's (Database Return Types).  Neither
method EVER returns a value of NULL; they always return DRT's.  However,
some of the fields in the returned DRT might be "".

search (string key):

if key is "", then set the following fields in the DRT:
  data = ""
  next = the first key in the database (or "" if empty)
  prev = the last key in the database (or "" if empty)

if key is not "" but is not present in the database:
  data = ""
  next = the first key in the database following key (or "")
  prev = the last key in the database preceding key (or "")

if key is present in the database:
  data = the data corresponding to key
  next = the first key in the database following key (or "")
  prev = the last key in the database preceding key (or "")

modify (string key, string data):

At all times, modify returns the DRT that search would have returned
JUST PRIOR to the modification made by modify.  Discussed below are
the modifications made by modify.

if key is "", do nothing.

if key is not "" but not present in the database and data is "", do
nothing.

if key is not "" but not present in the database and data is not "",
add <key,data> to the database.

if key is present in the database and data is "", remove key from the
database.

if key is present in the database and data is not "", replace the data
associated with key with the new data.

*/
