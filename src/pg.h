/*
 * pg.h
 *
 *  Created on: 5 avr. 2015
 *      Author: jfellus
 */

#ifndef PG_H_
#define PG_H_

#include "utils.h"

//////////////////////////////////
// TYPE-CHECKING AND CONVERSION //
//////////////////////////////////

#ifndef OUTPUT
#define OUTPUT(type,member) inline operator type &() {return member;}
#endif

/////////////
// IN-OUTS //
/////////////

template <typename T> class In {
	T* e;
public:
	inline void init() {e=0;}
	inline void process(T& _e) { e=&_e; }
	OUTPUT(T, *e);
};

template <typename T> class Out {
	T* e;
public:
	inline void init() {e=0;}
	inline void process(T& _e) { e=&_e; }
	OUTPUT(T, *e);
};

class NOP {
public:
	inline void init() {}
	inline void process() {  }
};


/////////////////////
// ERROR REPORTING //
/////////////////////

#define ERROR(x) do { throw std::runtime_error(TOSTRING(__PRETTY_FUNCTION__ << "@" << __LINE__ << " : " << x)); } while(0);


///////////////
// DEBUG NOP //
///////////////

#ifndef ___dbs
#define ___dbs(plug)
#endif

#ifndef PARAM
#define PARAM(type,var,callback)
#endif

#ifndef PGDB_PAUSE
#define PGDB_PAUSE
#endif

#endif /* PG_H_ */
