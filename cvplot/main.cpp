#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300d.lib")            // opencv_core
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300.lib") 
#endif

#include "cvplot.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <list>

using namespace std;
using namespace cv;



int main(){

	CVPlot plta(Point(1024, 512), "a");
	CVPlot pltb(Point(512, 512), "b");

	plta.XLim(0, 10);
	plta.YLim(-0.5, 0.5);

	for (int i = 0; i < 1000; ++i){
		double x = i * 0.1;
		plta.Plot(Point2d(x, sin(x)), Scalar(0, sin(x) * 127 + 127, cos(x) * 127 + 127), 5, 'o', 1, 1);
		pltb.Plot(Point2d(x, cos(x)), Scalar(0, cos(x) * 127 + 127, sin(x) * 127 + 127), 5, 's');
		plta.Show(1, 100);
		pltb.Show(1, 1);
		if (i % 500 == 0){
			pltb.Clear();
		}
	}

	pltb.Close();
	plta.Show(0);
	return 0;
}