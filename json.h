// Author: Dr Stephen Braithwaite.
// This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

#include <stdio.h>
#include "std.h"
#include "cstr.h"

typedef struct csc_jsonArr_s csc_jsonArr_t;
typedef struct csc_json_s csc_json_t;

typedef enum csc_jsonErr_e
{   csc_jsonErr_Ok = 0
,   csc_jsonErr_Null   // Requested element had null value.
,   csc_jsonErr_Missing   // Requested element not there.
,   csc_jsonErr_WrongType  // e.g. Requested int is a float.
,   csc_jsonErr_OutOfRange  // Too big or too small.
,   csc_jsonErr_BadParse  // Expected something else while parsing.
} csc_jsonErr_t;


typedef enum csc_jsonType_e
{   csc_jsonType_Bad = 0
,   csc_jsonType_Missing 
,   csc_jsonType_Null
,   csc_jsonType_Obj 
,   csc_jsonType_Arr
,   csc_jsonType_String
,   csc_jsonType_Bool
,   csc_jsonType_Int
,   csc_jsonType_Float
} csc_jsonType_t;


//------- Constructor and Desctructor -------------

// ... Constructors ...

// Create an empty JSON object.
csc_json_t *csc_json_new();

// Create a JSON object by reading one from an input stream.
// Returns NULL on EOF.
csc_json_t *csc_json_newParseFILE(FILE *fin);

// Create a JSON object by reading one from an input string.
// Returns NULL on EOF.
csc_json_t *csc_json_newParseStr(const char *str);

// ... Error feedback ...

// Gets a description of error.
// Return NULL on no error.
const char *csc_json_getErrStr(const csc_json_t *js);

// Gets line number of error.
int csc_json_getErrLinePos(const csc_json_t *js);

// Gets the character position of error.
int csc_json_getErrPos(const csc_json_t *js);

// ... Destructor ...

// Release a JSON object.
void csc_json_free(csc_json_t *js);

// ... JSON array.

// Create empty JSON array.
csc_jsonArr_t *csc_jsonArr_new();

// Release a JSON array.
void csc_jsonArr_free(csc_jsonArr_t *ja);


//------- Input and output -------------

// Write a JSON object to a string.
void csc_json_writeCstr(const csc_json_t *js, csc_str_t *cstr);

// Write a JSON object to a stream.
void csc_json_writeFILE(const csc_json_t *js, FILE *fout);


//------- Add to a JSON object -------------

// Add an element with no value to a JSON object.
void csc_json_addNull(csc_json_t *js, const char *name);

// Add a string value to a JSON object.  This makes its own copy of the
// string 'val'.
void csc_json_addStr(csc_json_t *js, const char *name, const char *val);

// Add a boolean value to a JSON object.
void csc_json_addBool(csc_json_t *js, const char *name, csc_bool_t val);

// Add an integer value to a JSON object.
void csc_json_addInt(csc_json_t *js, const char *name, int val);

// Add an floating value to a JSON object.
void csc_json_addFloat(csc_json_t *js, const char *name, double val);

// Add a child JSON object to a parent JSON object.  After this call, the
// parent OWNS the child, and freeing the parent will free the child.
void csc_json_addObj(csc_json_t *parent, const char *name, csc_json_t *child);

// Add a JSON array to a JSON object.  After this call, the
// object OWNS the child, and freeing the object will free the array.
void csc_json_addArr(csc_json_t *js, const char *name, csc_jsonArr_t *arr);


//------- Get from a JSON object -------------

// Get the type of an element of a JSON object.
// Returns csc_jsonType_Missing if no such element.
csc_jsonType_t csc_json_getType(const csc_json_t *js, const char *name);

// Get a string value from a JSON object.
// The caller may inspect, but not alter or free the returned string.
// Returned value is freed and becomes invalid if JSON object is freed.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const char *csc_json_getStr(const csc_json_t *js, const char *name, csc_jsonErr_t *errNum);

// Get a boolean value from a JSON object.
// Returns FALSE if returned errNum is not csc_jsonErr_Ok.
csc_bool_t csc_json_getBool(const csc_json_t *js, const char *name, csc_jsonErr_t *errNum);

// Get an integer value from a JSON object.
// Returns 0 if returned errNum is not csc_jsonErr_Ok.
int csc_json_getInt(const csc_json_t *js, const char *name, csc_jsonErr_t *errNum);

// Get a floating value from a JSON object.
// Returns 0 if returned errNum is not csc_jsonErr_Ok.
double csc_json_getFloat(const csc_json_t *js, const char *name, csc_jsonErr_t *errNum);

// Get a JSON child object from a JSON object.
// The caller may inspect, but not alter or free the returned object.
// Returned JSON object is freed and becomes invalid if the parent JSON object is freed.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const csc_json_t *csc_json_getObj(const csc_json_t *js, const char *name, csc_jsonErr_t *errNum);

// Get a JSON array from a JSON object.
// The caller may inspect, but not alter or free the returned array.
// Returned value is freed and becomes invalid if JSON object is freed.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const csc_jsonArr_t *csc_json_getArr(const csc_json_t *js, const char *name, csc_jsonErr_t *errNum);

//------- Get by index from a JSON object -------------

// Get the number of elements in a JSON object.
int csc_json_length(const csc_json_t *js);

// Get the name of nth element of a JSON object.
// Returns NULL if no such element.
const char *csc_json_ndxName(const csc_json_t *js, int ndx);

// Get the type of nth element of a JSON object.
// Returns NULL if no such element.
csc_jsonType_t csc_json_ndxType(const csc_json_t *js, int ndx);

// Get a string value from a JSON object.
// The caller may inspect, but not alter or free the returned string.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const char *csc_json_ndxStr(const csc_json_t *js, int ndx, csc_jsonErr_t *errNum);

// Get a boolean value from a JSON object.
// Returns FALSE if returned errNum is not csc_jsonErr_Ok.
csc_bool_t csc_json_ndxBool(const csc_json_t *js, int ndx, csc_jsonErr_t *errNum);

// Get an integer value from a JSON object.
// Returns 0 if returned errNum is not csc_jsonErr_Ok.
int csc_json_ndxInt(const csc_json_t *js, int ndx, csc_jsonErr_t *errNum);

// Get a floating value from a JSON object.
// Returns 0 if returned errNum is not csc_jsonErr_Ok.
double csc_json_ndxFloat(const csc_json_t *js, int ndx, csc_jsonErr_t *errNum);

// Get a JSON child object from a JSON object.
// The caller may inspect, but not alter or free the returned object.
// Returned value is freed and becomes invalid if parent JSON object is freed.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const csc_json_t *csc_json_ndxObj(const csc_json_t *js, int ndx, csc_jsonErr_t *errNum);

// Get a JSON array from a JSON object.
// The caller may inspect, but not alter or free the returned array.
// Returned value is freed and becomes invalid if JSON object is freed.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const csc_jsonArr_t *csc_json_ndxArr(const csc_json_t *js, int ndx, csc_jsonErr_t *errNum);

//------- Append to a JSON array -------------

// Add an element with no value to a JSON array.
void csc_jsonArr_apndNull(csc_jsonArr_t *jas);

// Append a string value to a JSON array.  This makes its own copy of the
// string 'val'.
void csc_jsonArr_apndStr(csc_jsonArr_t *js, const char *val);

// Append a boolean value to a JSON array.
void csc_jsonArr_apndBool(csc_jsonArr_t *js, csc_bool_t val);

// Append an integer value to a JSON array.
void csc_jsonArr_apndInt(csc_jsonArr_t *js, int val);

// Append an floating value to a JSON array.
void csc_jsonArr_apndFloat(csc_jsonArr_t *js, double val);

// Append a JSON object to a JSON array.  After this call, the
// array OWNS the object, and freeing the array will free the object.
void csc_jsonArr_apndObj(csc_jsonArr_t *parent, csc_json_t *obj);

// Append a child JSON array to a parent JSON array.  After this call, the
// parent OWNS the child, and freeing the parent will free the child.
void csc_jsonArr_apndArr(csc_jsonArr_t *parent, csc_jsonArr_t *child);


//------- Get from a JSON array -------------

// Get the number of elements in a JSON array.
int csc_jsonArr_length(const csc_jsonArr_t *jas);

// Get the type of nth element of a JSON object.
// Returns csc_jsonType_Missing if no such element.
csc_jsonType_t csc_jsonArr_getType(const csc_jsonArr_t *jas, int ndx);

// Get a string value from a JSON array.
// The caller may inspect, but not alter or free the returned string.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const char *csc_jsonArr_getStr(const csc_jsonArr_t *jas, int ndx, csc_jsonErr_t *errNum);

// Get a boolean value from a JSON array.
// Returns FALSE if returned errNum is not csc_jsonErr_Ok.
csc_bool_t csc_jsonArr_getBool(const csc_jsonArr_t *jas, int ndx, csc_jsonErr_t *errNum);

// Get an integer value from a JSON array.
// Returns 0 if returned errNum is not csc_jsonErr_Ok.
int csc_jsonArr_getInt(const csc_jsonArr_t *jas, int ndx, csc_jsonErr_t *errNum);

// Get a floating value from a JSON array.
// Returns 0 if returned errNum is not csc_jsonErr_Ok.
double csc_jsonArr_getFloat(const csc_jsonArr_t *jas, int ndx, csc_jsonErr_t *errNum);

// Get a JSON object from a JSON array.
// The caller may inspect, but not alter or free the returned object.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const csc_json_t *csc_jsonArr_getObj(const csc_jsonArr_t *jas, int ndx, csc_jsonErr_t *errNum);

// Get a JSON child array from a JSON parent array.
// The caller may inspect, but not alter or free the returned array.
// Returns NULL if returned errNum is not csc_jsonErr_Ok.
const csc_jsonArr_t *csc_jsonArr_getArr(const csc_jsonArr_t *jas, int ndx, csc_jsonErr_t *errNum);


