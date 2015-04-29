/*
 * utils.h
 *
 *  Created on: 9 avr. 2015
 *      Author: jfellus
 */

#ifndef PG_UTILS_H_
#define PG_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <linux/limits.h>
#include <algorithm>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>
#include <libgen.h>
#include <math.h>

/////////////////////
// ERROR REPORTING //
/////////////////////

#define PRINT_FATAL_ERROR(x) do { DBG("FATAL ERROR in " << x); exit(1); } while(0);

#define DBG(x) std::cout << x << "\n";



///////////
// MATHS //
///////////

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#define TRIM(x,min,max) ( ((x) < (min)) ? (min) : ((x) > (max) ? (max) : (x) ) )

inline bool is_diff(float x, float y) { return (fabs(x - y) > 1e-30); }

///////////
// FILES //
///////////

inline bool file_exists(const std::string& filename) {
	  struct stat   buffer;
	  return (stat (filename.c_str(), &buffer) == 0);
}

inline bool file_is_directory(const std::string& filename) {
	struct stat   buffer;
	if(stat (filename.c_str(), &buffer) != 0) return false;
    return (S_ISDIR (buffer.st_mode));
}


/////////////
// STRINGS //
/////////////

#define TOSTRING(x) ((std::ostringstream&)(std::ostringstream().flush() << x)).str()
#define TOINT(x) toInt(x)
#define TOFLOAT(x) toFloat(x)

#define REPEAT_STR(x, nb) str_repeat(TOSTRING(x),nb)




inline int toInt(const std::string& s) {int i = -1; std::istringstream iss(s); iss >> i; return i;}
inline float toFloat(const std::string& s) {float i = -1; std::istringstream iss(s); iss >> i; return i;}

inline std::string str_replace(std::string subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

inline bool str_ends_with(const std::string& s, const std::string& suffix) {
	if(s.length() < suffix.length()) return false;
	return s.compare (s.length() - suffix.length(), suffix.length(), suffix) == 0;
}

inline bool str_starts_with(const std::string& s, const std::string& prefix) {
	return s.compare(0, prefix.length(), prefix)==0;
}

inline std::string str_after(const std::string& s, const std::string& prefix) {
	uint i = s.find(prefix);
	if(i==std::string::npos) return s;
	return s.substr(i+prefix.length());
}

inline std::string str_before(const std::string& s, const std::string& suffix) {
	uint i = s.find(suffix);
	if(i==std::string::npos) return s;
	return s.substr(0,i);
}

inline std::string str_between(const std::string& s, const std::string& prefix, const std::string& suffix) {
	return str_before(str_after(s,prefix), suffix);
}

inline bool str_has(const std::string& s, const std::string& needle) {
	return s.find(needle)!=std::string::npos;
}

inline std::string str_to_lower(const std::string& s) {
	std::string a = s;
	std::transform(a.begin(), a.end(), a.begin(), ::tolower);
	return a;
}

inline std::string str_trim(const std::string& s) {
	int i=0;
	while(isspace(s[i])) i++;
	int j=s.length()-1;
	while(isspace(s[j])) j--;
	return s.substr(i,j-i+1);
}


inline void str_remove(std::string& s, const std::string& what) {
	size_t i = s.find(what);
	if(i!=std::string::npos) s.erase(s.find(what), what.length());
}

inline std::string str_align(const std::string& s, int nbchars) {
	std::ostringstream str; str << s;
	for(int i=s.length(); i<=nbchars; i++) str << " ";
	return str.str();
}


inline std::string str_repeat(std::string s, int nb) {
	std::ostringstream ss;
	for(;nb>0; nb--) ss << s;
	return ss.str();
}


//////////////
// COMMANDS //
//////////////

#define SYSTEM(x) do { int z = system(TOSTRING(x).c_str()); (void) z;} while(0);

inline void mkdir(const std::string& s) { SYSTEM("mkdir -p " << s); }
inline void mkrmdir(const std::string& s) { SYSTEM("rm -rf " << s); mkdir(s); }

inline std::string cwd();

inline std::string str_dirname(const std::string& path) {	char s[PATH_MAX];strcpy(s,path.c_str());return dirname((char*)s);}
inline std::string str_basename(const std::string& path) {	char s[PATH_MAX];strcpy(s,path.c_str());return basename((char*)s);}


#endif /* PG_UTILS_H_ */
