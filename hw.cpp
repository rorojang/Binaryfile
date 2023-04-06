#include <iostream>
#include <fstream>
using namespace std;
int main() {
	char header[12];
	int* n;
	n = (int*)header;
	*n = 500;
	float* f;
	f = (float*)(header + 4);
	*f = 1000;
	short* p;
	p = (short*)(header + 10);  *p = 12;  // 12 means 12
	short* a;
	a = (short*)(header + 8);  *a = 10000;
	const float pi = 3.141592;
	float dt;
	dt = 1. / *f / 20.0;
	ofstream xx("a.dat", ios::binary | ios::out);
	if (!xx) return 666;// 만일 파일이 열리지 않으면 프로그램을 끝낸다. 
	xx.write(header, 12 * sizeof(char));
	float* samples;
	samples = new float[*n];

	for (int i = 0; i < 500; i++) {
		samples[i] = (float)*a * sin(2.0 * pi * *f * i * dt);
	}
	xx.write((char*)samples, 500 * sizeof(float));
	xx.close();

	
	ifstream yy("a.dat", ios::binary | ios::in);
	if (!yy) return 666;  // 만일 파일이 열리지 않으면 프로그램을 끝낸다. 
	yy.read(header, 12 * sizeof(char));
	cout << " n" << *n << endl;
	cout << " f" << *f << endl;
	cout << " a" << *a << endl;
	cout << " p" << *p << endl;
	*f = 700.0;
	for (int i = 0; i < 500; i++) {
		samples[i] = (float)*a * sin(2.0 * pi * *f * i * dt);
	}
	yy.close();

	ofstream xxx("b.dat", ios::binary | ios::out);
	if (!xxx) return 666;// 만일 파일이 열리지 않으면 프로그램을 끝낸다. 
	xxx.write(header, 12 * sizeof(char));
	xxx.write((char*)samples, 500 * sizeof(float));
	xxx.close();
	
	ifstream x1("a.dat", ios::binary | ios::in);
	if (!x1) return 666;
	x1.read(header, 12 * sizeof(char));
	float *data1; data1 = new float[*n];
	x1.read((char*)data1, *n * sizeof(float));
	x1.close();

	ifstream x2("b.dat", ios::binary | ios::in);
	if (!x2) return 666;
	x2.read(header, 12 * sizeof(char));
	float* data2; data2 = new float[*n];
	x2.read((char*)data2, *n * sizeof(float));
	x2.close();

	ofstream x3("c.txt");
	if(!x3) return 666;  // 만일 파일이 열리지 않으면 프로그램을 끝낸다. 
	for (int i = 0; i < *n; i++) {
		x3 << i * dt << " " << data1[i] << " " << data2[i] << endl;
	}
	x3.close();

	
}