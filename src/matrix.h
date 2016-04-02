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
#include <vector>
#include <fstream>


class Matrix {
public:
	uint h,w;
	size_t n;
	float* data;
	bool bOwn;

	OUTPUT(float*, data)

public:
	Matrix() {data = 0; w = h = n = 0; bOwn = false;}
	Matrix(uint h, uint w, float* data) : h(h),w(w),data(data) {n=w*h; bOwn = false;}
	Matrix(uint h, uint w) {init(w,h);}
	Matrix(Matrix& m) {	w = m.w; h=m.h; n = m.n; bOwn = true; m.bOwn = false; data = m.data;}
	Matrix(const Matrix& m) {init(m.w,m.h); *this = m;}

	~Matrix() {if(bOwn && data) delete data;}

	inline void init() { if(w && h) init(w,h); }
	inline void init(uint h, uint w, float* data) {
		this->w = w; this->h = h;
		this->n = w*h;
		this->data = data;
		bOwn = false;
	}

	inline void init(uint h, uint w) {
		this->w = w; this->h = h;
		this->n = w*h;
		data = new float[n];
		bOwn = true;
	}

	inline void free() {
		if(data && bOwn) delete data;
		data = NULL;
		w = h = 0;
		bOwn = false;
	}

	inline void clear() {		memset(data, 0, sizeof(float)*n);	}

	Matrix& map(Matrix& m) { free(); return *this = m;}

	void set_height(uint h) {this->h = h; this->n = this->w*this->h;}

	void randf(float min = 0, float max = 1) {
		for(uint i=n; i--;) data[i] = (float)rand()/INT_MAX;
	}

	inline Matrix& operator=(Matrix& m) {
		if(data) { memcpy(data, m.data, m.n*sizeof(float)); }
		else { data = m.data; w = m.w; h = m.h; n = m.n; bOwn = false; }
		return *this;
	}

	inline Matrix& operator=(const Matrix& m) {
		if(!data) init(m.w, m.h);
		memcpy(data, m.data, m.n*sizeof(float));
		return *this;
	}

	inline Matrix& operator=(float v) { for(uint i=n;i--;) data[i] = v; return *this;}

	inline float* get_row(int i) {return &data[i*w];}
	inline const float* get_row(int i) const {return &data[i*w];}

	inline void process(){}

	inline float& operator()(int i, int j) {return data[i*w+j];}
	inline const float& operator()(int i, int j) const {return data[i*w+j];}
	inline float& operator[](int i) {return data[i];}
	inline const float& operator[](int i) const {return data[i];}

	inline void dump() const {
		for(uint i=0; i<h; i++) {
			for(uint j=0;j<w; j++) {
				if(j!=0) printf(" ");
				printf("%f", data[i*w+j]);
			}
			printf("\n");
		}
		printf("\n");
	}
};


inline void read_matrix(const std::string& filename, Matrix& m) {
	if(!str_ends_with(filename, ".mat")) ERROR("Matrix format reader Not implemented yet ! (" << filename << ")");
	std::ifstream f(filename.c_str(), std::ios::binary);
	f.read((char*)&m.w, sizeof(m.w));
	f.read((char*)&m.h, sizeof(m.h));
	m.init(m.h,m.w);
	f.read((char*)m.data, m.w*m.h*sizeof(float));
}

inline void write_matrix(const std::string& filename, Matrix& m) {
	if(!str_ends_with(filename, ".mat")) ERROR("Matrix format reader Not implemented yet ! (" << filename << ")");
	std::ofstream f(filename.c_str(), std::ios::binary);
	f.write((char*)&m.w, sizeof(m.w));
	f.write((char*)&m.h, sizeof(m.h));
	f.write((char*)m.data, m.w*m.h*sizeof(float));
}


inline void read_matrix_list(const std::string& filename, std::vector<Matrix>& list) {
	if(!str_ends_with(filename, ".matl")) ERROR("Matrix format reader Not implemented yet ! (" << filename << ")");
	std::ifstream f(filename.c_str(), std::ios::binary);
	if(!f.good()) ERROR("No such file : " << filename);
	size_t nb; f.read((char*)&nb, sizeof(nb));
	DBG(nb);
	for(uint i=0; i<nb; i++) {
		Matrix m;
		uint w,h;
		f.read((char*)&w, sizeof(w));
		f.read((char*)&h, sizeof(h));
		m.init(h,w);
		f.read((char*)m.data, w*h*sizeof(float));
		list.push_back(m);
	}
}

inline void write_matrix_list(const std::string& filename, const std::vector<Matrix>& list) {
	if(!str_ends_with(filename, ".matl")) ERROR("Matrix format writer Not implemented yet ! (" << filename << ")");
	std::ofstream f(filename.c_str(), std::ios::binary);
	size_t n = list.size();
	f.write((char*)&n, sizeof(n));
	for(uint i=0; i<n; i++) {
		f.write((char*)&list[i].w, sizeof(list[i].w));
		f.write((char*)&list[i].h, sizeof(list[i].h));
		f.write((char*)list[i].data, list[i].w*list[i].h*sizeof(float));
	}
}











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
