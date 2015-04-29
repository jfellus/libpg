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
#include <limits.h>


class Matrix {
public:
	uint h,w;
	size_t n;
	float* data;

	OUTPUT(float*, data)

public:
	Matrix() {data = 0; w = h = n = 0;}
	Matrix(uint h, uint w, float* data) : h(h),w(w),data(data) {n=w*h;}
	Matrix(uint h, uint w) {init(w,h);}

	~Matrix() {delete data;}

	inline void init() { if(w && h) init(w,h); }
	inline void init(uint h, uint w, float* data) {
		this->w = w; this->h = h;
		this->n = w*h;
		this->data = data;
	}

	inline void init(uint h, uint w) {
		this->w = w; this->h = h;
		this->n = w*h;
		data = new float[n];
	}

	inline void free() {
		if(data) delete data;
		data = NULL;
		w = h = 0;
	}

	void set_height(uint h) {this->h = h; this->n = this->w*this->h;}

	void randf(float min = 0, float max = 1) {
		for(uint i=n; i--;) data[i] = (float)rand()/INT_MAX;
	}

	inline Matrix& operator=(float v) { for(uint i=n;i--;) data[i] = v; return *this;}

	inline float* get_row(int i) {return &data[i*w];}
	inline const float* get_row(int i) const {return &data[i*w];}

	inline void process(){}

	inline float& operator()(int i, int j) {return data[i*w+j];}
	inline const float& operator()(int i, int j) const {return data[i*w+j];}
	inline float& operator[](int i) {return data[i];}
	inline const float& operator[](int i) const {return data[i];}
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
