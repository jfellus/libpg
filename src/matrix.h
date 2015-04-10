/*
 * matrix.h
 *
 *  Created on: 9 avr. 2015
 *      Author: jfellus
 */

#ifndef PG_MATRIX_H_
#define PG_MATRIX_H_


#include "pg.h"
#include "image.h"


class Matrix {
public:
	uint h,w;
	float* data;

	OUTPUT(float*, data)

public:
	Matrix() {data = 0; w = h = 0;}
	Matrix(uint h, uint w, float* data) : h(h),w(w),data(data) {}
	Matrix(uint h, uint w) {init(w,h);}

	~Matrix() {delete data;}

	inline void init() { if(w && h) init(w,h); }

	inline void init(uint w, uint h) {
		this->w = w; this->h = h;
		data = new float[w*h];
	}

	inline void process(){}

	inline float& operator()(int i, int j) {return data[i*w+j];}
	inline float& operator[](int i) {return data[i];}
};

















////////// TOOL MODULES ///////////////


class DumpMatrix {
public:
	void init() {}

	void process(Matrix& m) {
		for(uint i=0; i<m.h; i++) {
			for(uint j=0; j<m.w; j++) {
				if(j!=0) std::cout << " ";
				std::cout << m(i,j);
			}
			std::cout << "\n";
		}
	}

};


#endif /* PG_MATRIX_H_ */
