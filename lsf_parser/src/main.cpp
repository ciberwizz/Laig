#include <iostream>
#include "parser.h"
#include "primitives.h"
#include <exception>
#include <cmath>
#include <string>

#include "cgf/CGFapplication.h"
#include "TPscene.h"
#include "DemoScene.h"

using namespace std;


double* multMatrix(double*, double*);
double* createMatrixTranslate(double, double, double);
double* createMatrixScale(double, double, double);
double* createMatrixRotate(string,double);
void displayMat(double*);

int main(int argc, char*argv[]){

	LSFParser a = LSFParser("ster.lsf");

	//teste getElems
	cout << "\n---------getGlobals------------";
	a.getGlobals();

	cout <<"\n\n\n\n\n----------getAppearences--------";
	//teste getElemContainers
	a.getAppearences();

	cout <<"\n\n\n\n\n----------getCameras------------";
	a.getCameras();

	cout <<"\n\n\n\n\n----------getLightingConfig-----";
	a.getLightingConfig();

	cout <<"\n\n\n\n\n----------getLights-------------";
	a.getLights();

	cout <<"\n\n\n\n\n ---------graphrouteid " << a.getGraphRootId();

	cout <<"\n\n\n\n\n----------getnodes-------------\n";
	a.getGraphNodes();


	double *m1 = createMatrixScale(2,3,4);
	double *m2 = createMatrixTranslate(5,6,7);

	displayMat(m1);
	cout << "X\n";
	displayMat(m2);
	cout << " =\n";
	displayMat(multMatrix(m1,m2));


	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new DemoScene());
		app.setInterface(new CGFinterface());
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;





	return 0;

}


double* multMatrix(double* m1, double* m2){
	double *mf = new double[16];


	for(int i=0; i< 4; i++){
		for(int j = 0; j < 4; j++)
			mf[i+j*4] = m1[i]*m2[0+j*4] + m1[i+4]*m2[1+j*4] + m1[i+2*4]*m2[2+j*4] + m1[i+3*4]*m2[3+j*4];
	}

	return mf;

}

double* createMatrixTranslate(double x, double y, double z){
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){
		if( i%5 == 0)
			mat[i] = 1;
		else
			switch(i) {
			case 12:
				mat[i] = x;
				break;
			case 13:
				mat[i] = y;
				break;
			case 14:
				mat[i] = z;
				break;
			default:
				mat[i]=0.0;
				break;
			}
	}

	return mat;

}

double* createMatrixScale(double x, double y, double z){
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){

		switch(i) {
		case 0:
			mat[i] = x;
			break;
		case 5:
			mat[i] = y;
			break;
		case 10:
			mat[i] = z;
			break;
		case 15:
			mat[i] = 1.0;
			break;
		default:
			mat[i]=0.0;
			break;
		}
	}

	return mat;

}


double* createMatrixRotate(string eixo,double rot){
	double *mat = new double[16];
	for( int i = 0 ; i < 16; i++){
		if( i%5 == 0)
			mat[i] = 1.0;
		else
			mat[i]=0.0;
	}

	switch(eixo[0]) {
	case 'x':
		/*
		 * 1  0         0        0
		 * 0 cos(rot) -sin(rot)  0
		 * 0 sin(rot) cos(rot)  0
		 * 0  0         0        1
		 */

		mat[5] = cos(rot);
		mat[6] = sin(rot);
		mat[9] = -sin(rot);
		mat[10] = cos(rot);
		break;
	case 'y':
		/*
		 * cos(rot)  0 sin(rot) 0
		 *   0       1    0     0
		 * -sin(rot) 0 cos(rot) 0
		 *   0       0   0      1
		 */

		mat[0] = cos(rot);
		mat[2] = -sin(rot);
		mat[8] = sin(rot);
		mat[10] = cos(rot);
		break;
	case 'z':
		/*
		 * cos(rot) -sin(rot) 0 0
		 * sin(rot) cos(rot)  0 0
		 *   0       0   1    0 0
		 *   0       0   0    0 1
		 */

		mat[0] = cos(rot);
		mat[1] = sin(rot);
		mat[4] = -sin(rot);
		mat[5] = cos(rot);
		break;
	}


	return mat;

}

void displayMat( double* mat){

	for(int i = 0 ; i < 4 ; i++)
		cout << "| " << mat[i]  << " " << mat[i+4] << " " << mat[i+2*4] << " " << mat[i+3*4] << endl;

}
