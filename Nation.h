#pragma once
#include <string>
#include <opencv2/opencv.hpp>

class Nation {

private:
	std::string name;
	std::string color;
	cv::Scalar colorCv;
	
public:
	Nation(std::string name, std::string color, cv::Scalar colorCv);

	std::string toString();
	cv::Scalar getColor();
	std::string getName() { return name; }

};