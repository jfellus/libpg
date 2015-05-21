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

#define OUTPUT(type,member) inline operator type &() {return member;}


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


#endif /* PG_H_ */
