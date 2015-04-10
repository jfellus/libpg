/*
 * image.h
 *
 *  Created on: 9 avr. 2015
 *      Author: jfellus
 */

#ifndef PG_IMAGE_H_
#define PG_IMAGE_H_

#include "pg.h"
#include "matrix.h"


class ImageRGB {
public:
	unsigned char* data;
	uint w, h;

	OUTPUT(unsigned char*, data)
public:
	ImageRGB() {		data = 0; w = h = 0;	}
	ImageRGB(uint w, uint h) : w(w), h(h) {init();}

	~ImageRGB() {delete data;}

	void init() {if(!data) data = new unsigned char[w*h*3];}
	void init(uint w, uint h) { this->w = w; this->h = h; init(); }

	inline void process(){}

	inline unsigned char* operator()(int x, int y) { return &data[(y*w+x)*3]; }
	inline unsigned char& operator[](int i) {return data[i];}
	inline const unsigned char& operator[](int i) const {return data[i];}

	inline operator const unsigned char*() const {return data;}

};

class ImageFloat {
public:
	uint w, h;
	size_t n;
	float* data;

	OUTPUT(float*, data)

public:
	ImageFloat() { w = h = n = 0; data = 0;}
	ImageFloat(uint w, uint h, float* data) : w(w),h(h),data(data) { init(); }
	ImageFloat(uint w, uint h) : w(w), h(h) {init();}

	~ImageFloat() {delete data;}

	void init() {if(!data) data = new float[w*h]; n = w*h;}
	void init(uint w, uint h) { this->w = w; this->h = h; init(); }

	inline void process(){}

	inline float& operator()(int x, int y) { return data[(y*w+x)]; }
	inline float& operator[](int i) {return data[i];}
	inline const float& operator[](int i) const {return data[i];}

	inline ImageFloat& operator=(const ImageFloat& i) {
		if(!data) init(i.w, i.h);
		memcpy(data, i.data, n*sizeof(float));
		return *this;
	}

	inline operator bool() { return data; }

};



class ImageChar {
public:
	uint w, h;
	size_t n;
	unsigned char* data;

	OUTPUT(unsigned char*, data)
public:
	ImageChar() { w = h = n = 0; data = 0; }
	ImageChar(uint w, uint h, unsigned char* data) : w(w),h(h),data(data) { init(); }
	ImageChar(uint w, uint h) : w(w), h(h) {init();}

	~ImageChar() {delete data;}

	void init() {if(!data) data = new unsigned char[w*h]; n = w*h;}
	void init(uint w, uint h) { this->w = w; this->h = h; init(); }

	inline void process(){}

	inline unsigned char& operator()(int x, int y) { return data[(y*w+x)]; }
	inline unsigned char& operator[](int i) {return data[i];}
	inline const unsigned char& operator[](int i) const {return data[i];}

	inline ImageChar& operator=(const ImageChar& i) {
		if(!data) init(i.w, i.h);
		memcpy(data, i.data, n*sizeof(unsigned char));
		return *this;
	}

	inline operator bool() { return data; }
};


typedef ImageFloat Image;

#endif /* PG_IMAGE_H_ */
