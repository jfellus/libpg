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

private:
	bool bOwn;
public:
	ImageRGB() {		data = 0; w = h = 0; bOwn = false;	}
	ImageRGB(uint w, uint h) : w(w), h(h) {init();}
	ImageRGB(const ImageRGB& i) { w = i.w; h = i.h; data = i.data; ((ImageRGB&)i).bOwn = false; bOwn = true;}

	~ImageRGB() {if(bOwn) delete data; data = 0;}

	void init() {if(!data) {data = new unsigned char[w*h*3]; bOwn = true; }}
	void init(uint w, uint h) { this->w = w; this->h = h; init(); }

	void free() {if(data) delete data; this->w = this->h = 0; data = NULL; bOwn = false;}

	inline void process(){}

	inline unsigned char* operator()(int x, int y) { return &data[(y*w+x)*3]; }
	inline const unsigned char* operator()(int x, int y) const { return &data[(y*w+x)*3]; }
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

private:
	bool bOwnData;

public:
	ImageFloat() { w = h = n = 0; data = 0; bOwnData = false;}
	ImageFloat(uint w, uint h, float* data) : w(w),h(h),data(data) { init(); }
	ImageFloat(uint w, uint h) : w(w), h(h), data(0) {init();}
	ImageFloat(ImageFloat& i) { w = i.w; h = i.h; n = w*h; data = i.data; i.bOwnData = false; bOwnData = true; }

	~ImageFloat() {if(bOwnData) delete data;}

	void init() {if(!data) {data = new float[w*h]; bOwnData=true;} n = w*h;}
	void init(uint w, uint h) { this->w = w; this->h = h; init(); }
	void free() {if(data) delete data; this->w = this->h = 0; data = NULL; }

	inline void process(){}

	inline float& operator()(int x, int y) { return data[y*w+x]; }
	inline const float& operator()(int x, int y) const { return data[y*w+x]; }
	inline float& operator[](int i) {return data[i];}
	inline const float& operator[](int i) const {return data[i];}
	inline operator const float*() const {return data;}

	inline ImageFloat& operator=(float f) {
		if(f==0) memset(data, 0, n*sizeof(float));
		else for(uint i=n;i--;) data[i] = f;
		return *this;
	}

	inline ImageFloat& operator=(const ImageFloat& i) {
		if(!data) init(i.w, i.h);
		memcpy(data, i.data, n*sizeof(float));
		return *this;
	}

	inline ImageFloat& operator=(ImageFloat& i) {
		if(data) memcpy(data, i.data, n*sizeof(float));
		else { w = i.w; h = i.h; data = i.data; i.bOwnData = false; bOwnData = true;}
		return *this;
	}

	inline operator bool() { return data; }

	inline ImageFloat& trim(float min, float max) {for (uint i = n;i--;) data[i] = TRIM(data[i],min,max); return *this;}

	inline ImageFloat& operator/=(float s) { for(uint i=n;i--;) data[i]/=s; return *this;}
	inline ImageFloat& operator*=(float s) { for(uint i=n;i--;) data[i]*=s; return *this;}


	void dump() {
		for(uint i=0; i<h; i++) {
			for(uint j=0; j<w; j++) {
				printf("%f ", data[i*w+j]);
			}
			printf("\n");
		}
	}

};



class ImageChar {
public:
	uint w, h;
	size_t n;
	unsigned char* data;

	OUTPUT(unsigned char*, data)

private:
	bool bOwnData;

public:
	ImageChar() { w = h = n = 0; data = 0; bOwnData = false;}
	ImageChar(uint w, uint h, unsigned char* data) : w(w),h(h),data(data) { init(); }
	ImageChar(uint w, uint h) : w(w), h(h), data(0) {init();}
	ImageChar(ImageChar& i) { w = i.w; h = i.h; n = w*h; data = i.data; i.bOwnData = false; bOwnData = true; }

	~ImageChar() {if(bOwnData) delete data;}

	void init() {if(!data) {data = new unsigned char[w*h]; bOwnData = true;} n = w*h;}
	void init(uint w, uint h) { this->w = w; this->h = h; init(); }

	inline void process(){}

	inline unsigned char& operator()(int x, int y) { return data[(y*w+x)]; }
	inline const unsigned char& operator()(int x, int y) const { return data[(y*w+x)]; }
	inline unsigned char& operator[](int i) {return data[i];}
	inline const unsigned char& operator[](int i) const {return data[i];}
	inline operator const unsigned char*() const {return data;}

	inline ImageChar& operator=(unsigned char c) {	memset(data, c, n*sizeof(unsigned char));	return *this; }


	inline ImageChar& operator=(const ImageChar& i) {
		if(!data) init(i.w, i.h);
		memcpy(data, i.data, n*sizeof(unsigned char));
		return *this;
	}

	inline ImageChar& operator=(ImageChar& i) {
		if(data) memcpy(data, i.data, n*sizeof(unsigned char));
		else { w = i.w; h = i.h; data = i.data; i.bOwnData = false; bOwnData = true;}
		return *this;
	}

	inline operator bool() { return data; }
};


typedef ImageFloat Image;

#endif /* PG_IMAGE_H_ */
