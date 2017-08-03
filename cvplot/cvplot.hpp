#ifndef CVPLOT_HPP
#define CVPLOT_HPP

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <vector>

class CVPlot{

	class point_inf{
	public:
		cv::Point2d p;
		cv::Scalar c;
		int b;
		char t;
		int thickness;
		int cvaa;

		point_inf(){}
		point_inf(cv::Point2d points_in, cv::Scalar color_in, int size_in, char type_in, int thickness_in, int cvaa_in){
			p = points_in;
			c = color_in;
			b = size_in;
			t = type_in;
			thickness = thickness_in;
			cvaa = cvaa_in;
		}
	};

	cv::Point graph_size;
	char graph_name[64];
	cv::Mat graph;

	double scale_x;
	double scale_y;

	double min_x;
	double max_x;
	double min_y;
	double max_y;

	double range_x;
	double range_y;

	double limx1;
	double limx2;
	double limy1;
	double limy2;

	double white_space;
	double yohaku;


	std::vector<point_inf> points;

	int count;

	int r(double i){
		return int(round(i));
	}
	int UpdateMinMax(cv::Point2d &p){
		bool flag = false;
		if (limx1 || limx2){
			min_x = limx1;
			max_x = limx2;
			flag = flag || true;
		}
		else{
			if (p.x < min_x){
				min_x = p.x;
				flag = flag || true;
			}
			if (p.x > max_x){
				max_x = p.x;
				flag = flag || true;
			}
		}

		if (limy1 || limy2){
			min_y = limy1;
			max_y = limy2;
			flag = flag || true;
		}
		else{
			if (p.y < min_y){
				min_y = p.y;
				flag = flag || true;
			}
			if (p.y > max_y){
				max_y = p.y;
				flag = flag || true;
			}
		}
		UpdateRange();
		return flag;
	}
	int UpdateRange(){
		range_x = max_x - min_x;
		range_y = max_y - min_y;
		return 0;
	}
	int UpdateScale(){
		scale_x = (graph_size.x - 1) / range_x * white_space;
		scale_y = (graph_size.y - 1) / range_y * white_space;

		return 0;
	}

	cv::Point ApplyScale(cv::Point2d p){
		return cv::Point(
			r(scale_x * (p.x - min_x) + yohaku * graph_size.x),
			r(scale_y * (p.y - min_y) + yohaku * graph_size.y));
	}
	cv::Point2d CoordinateConvert(cv::Point2d p){
		return cv::Point2d(p.x, graph_size.y - p.y);
	}

	int IsRageOut(cv::Point2d p){
		if ((p.x < 0) || (graph_size.x <= p.x) || (p.y < 0) || (graph_size.y <= p.y)){
			return 1;
		}
		return 0;
	}
	int DrawPoint(cv::Point2d p, cv::Scalar color = cv::Scalar(0, 0, 0), int b = 1, char line_type = '.'){
		if (line_type == '.'){
			for (int i = r(p.y) - b; i < r(p.y) + b; ++i){
				for (int j = r(p.x) - b; j < r(p.x) + b; ++j){
					if (IsRageOut(cv::Point(j, i))){ continue; }

					graph.at<cv::Vec3b>(cv::Point(j, i))[0] = color[0];
					graph.at<cv::Vec3b>(cv::Point(j, i))[1] = color[1];
					graph.at<cv::Vec3b>(cv::Point(j, i))[2] = color[2];
				}
			}
			return 0;
		}
		if (line_type == '*'){
			for (int i = 0; i < b; ++i){
				if (IsRageOut(cv::Point(p) + cv::Point(i, i))){ continue; }
				if (IsRageOut(cv::Point(p) + cv::Point(-i, -i))){ continue; }
				if (IsRageOut(cv::Point(p) + cv::Point(i, -i))){ continue; }
				if (IsRageOut(cv::Point(p) + cv::Point(-i, i))){ continue; }

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, i))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, i))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, i))[2] = color[2];

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, 0))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, 0))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, 0))[2] = color[2];

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, i))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, i))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, i))[2] = color[2];

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, -i))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, -i))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, -i))[2] = color[2];

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, 0))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, 0))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, 0))[2] = color[2];

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, -i))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, -i))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, -i))[2] = color[2];

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, -i))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, -i))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, -i))[2] = color[2];

				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, i))[0] = color[0];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, i))[1] = color[1];
				graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, i))[2] = color[2];
			}
			return 0;
		}
	}
	int DrawPoints(){
		for (int n = 0; n < points.size(); ++n){
			cv::Point p = CoordinateConvert(ApplyScale(points[n].p));

			if (points[n].t == 's'){
				cv::rectangle(
					graph,
					cv::Point(p.x - points[n].b, p.y - points[n].b),
					cv::Point(p.x + points[n].b, p.y + points[n].b),
					points[n].c,
					points[n].thickness,
					points[n].cvaa
					);

				//for (int i = p.y - points[n].b; i < p.y + points[n].b; ++i){
				//	for (int j = p.x - points[n].b; j < p.x + points[n].b; ++j){
				//		if (IsRageOut(cv::Point(j, i))){ continue; }

				//		graph.at<cv::Vec3b>(cv::Point(j, i))[0] = points[n].c[0];
				//		graph.at<cv::Vec3b>(cv::Point(j, i))[1] = points[n].c[1];
				//		graph.at<cv::Vec3b>(cv::Point(j, i))[2] = points[n].c[2];
				//	}
				//}
			}
			if (points[n].t == '.'){
				cv::line(graph, cv::Point(p), cv::Point(p), points[n].c, points[n].b);
			}
			if (points[n].t == 'o'){
				cv::circle(
					graph, 
					p, points[n].b, 
					points[n].c, 
					points[n].thickness,
					points[n].cvaa
					);

				//cv::line(graph, cv::Point(p), cv::Point(p), points[n].c, points[n].b, CV_AA);
			}
			if (points[n].t == '*'){
				for (int i = 0; i < points[n].b; ++i){
					if (IsRageOut(cv::Point(p) + cv::Point(i, i))){ continue; }
					if (IsRageOut(cv::Point(p) + cv::Point(-i, -i))){ continue; }
					if (IsRageOut(cv::Point(p) + cv::Point(i, -i))){ continue; }
					if (IsRageOut(cv::Point(p) + cv::Point(-i, i))){ continue; }

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, i))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, i))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, i))[2] = points[n].c[2];

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, 0))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, 0))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, 0))[2] = points[n].c[2];

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, i))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, i))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, i))[2] = points[n].c[2];

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, -i))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, -i))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(0, -i))[2] = points[n].c[2];

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, 0))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, 0))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, 0))[2] = points[n].c[2];

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, -i))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, -i))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, -i))[2] = points[n].c[2];

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, -i))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, -i))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(i, -i))[2] = points[n].c[2];

					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, i))[0] = points[n].c[0];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, i))[1] = points[n].c[1];
					graph.at<cv::Vec3b>(cv::Point(p) + cv::Point(-i, i))[2] = points[n].c[2];
				}
			}
			if (points[n].t == '-'){
				if (n < 1){
					cv::line(
						graph,
						cv::Point(p),
						cv::Point(p),
						points[n].c,
						points[n].b,
						points[n].cvaa
						);
				}
				else{
					cv::line(graph, 
						CoordinateConvert(ApplyScale(points[n - 1].p)), 
						cv::Point(p), 
						points[n].c, 
						points[n].b,
						points[n].cvaa
						);
				}
			}
		}
		return 0;
	}

	int DrawText(double n, cv::Point p){
		char num[64];
		sprintf(num, "%g", n);
		cv::putText(graph, num,
			p,
			cv::FONT_HERSHEY_COMPLEX,
			(graph_size.x + graph_size.y) / 3000.0,
			cv::Scalar::all(0),
			(graph_size.x + graph_size.y) / 2000.0,
			CV_AA);

		return 0;
	}
	
	int DrawMainAxis(){
		cv::line(graph,
			cv::Point(r(graph_size.x * yohaku), 0),
			cv::Point(r(graph_size.x * yohaku), graph_size.y),
			cv::Scalar(100, 100, 100));

		cv::line(graph,
			cv::Point(0, r(graph_size.y * (1 - yohaku))),
			cv::Point(graph_size.x, r(graph_size.y * (1 - yohaku))),
			cv::Scalar(100, 100, 100));

		return 0;
	}
	int DrawSubAxis(){
		for (int i = 1; i < 11; ++i){
			cv::line(graph,
				cv::Point(r(graph_size.x * (white_space)) * (i / 10.0) + r(graph_size.x * yohaku), 0),
				cv::Point(r(graph_size.x * (white_space)) * (i / 10.0) + r(graph_size.x * yohaku), graph_size.y),
				cv::Scalar(240, 240, 240));
		}
		for (int i = 0; i < 10; ++i){
			cv::line(graph,
				cv::Point(0, r(graph_size.y * (white_space)) * (i / 10.0) + r(graph_size.y * yohaku)),
				cv::Point(graph_size.x, r(graph_size.y * (white_space)) * (i / 10.0) + r(graph_size.y * yohaku)),
				cv::Scalar(240, 240, 240));
		}
		return 0;
	}
	int DrawAxisNum(){
		for (int i = 0; i < 11; ++i){
			DrawText(min_x + range_x * (i / 10.0), cv::Point(graph_size.x * (yohaku + white_space * (i / 10.0)), graph_size.y                                       * 0.99));
			DrawText(max_y - range_y * (i / 10.0), cv::Point(graph_size.x * yohaku                             , graph_size.y * (yohaku + white_space * (i / 10.0)) * 0.99));
		}
		return 0;
	}
	int Draw(){
		graph = cv::Scalar::all(255);

		DrawSubAxis();
		DrawMainAxis();
		DrawAxisNum();

		DrawPoints();

		return 0;
	}
public:
	CVPlot(cv::Point p = cv::Point(512, 512), char *graph_name_in = "\0"){
		graph_size = p;
		sprintf(graph_name, "%s", graph_name_in);
		graph = cv::Mat(graph_size, CV_8UC3, cv::Scalar::all(255));

		scale_x = 1;
		scale_y = 1;

		min_x = 0;
		max_x = 0;
		min_y = 0;
		max_y = 0;

		range_x = 0;
		range_y = 0;

		limx1 = 0;
		limx2 = 0;
		limy1 = 0;
		limy2 = 0;

		white_space = 0.9;
		yohaku = (1 - white_space) / 2;

		count = 0;
	}

	int XLim(double x1, double x2){
		limx1 = x1;
		limx2 = x2;
		return 0;
	}
	int YLim(double y1, double y2){
		limy1 = y1;
		limy2 = y2;
		return 0;
	}

	int Plot(cv::Point2d p, cv::Scalar color = cv::Scalar(0, 0, 0), int b = 1, char line_type = 'o', int thickness = -1, int cvaa = 0){
		if (points.empty()){
			min_x = p.x;
			max_x = p.x;
			min_y = p.y;
			max_y = p.y;

			UpdateRange();
		}
		else{
			UpdateMinMax(p);
			UpdateScale();
		}

		if (cvaa){ cvaa = CV_AA; }
		else { cvaa = 8; }
		points.push_back(point_inf(p, color, b, line_type, thickness, cvaa));

		return 0;
	}
	int Show(int msec = 0, int per = 0){
		if (per){
			if (!(count % per)){
				Draw();

				cv::imshow(graph_name, graph);
				cv::waitKey(msec);
			}
			++count;
		}
		else{
			Draw();

			cv::imshow(graph_name, graph);
			cv::waitKey(msec);
		}
		return 0;
	}
	int Close(){
		cv::destroyWindow(graph_name);
		return 0;
	}
	int Clear(){
		points.clear();
		return 0;
	}
};

#endif