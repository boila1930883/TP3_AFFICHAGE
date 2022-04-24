#include "Nation.h"
#include <string>
#include <opencv2/opencv.hpp>

Nation::Nation(std::string name, std::string color, cv::Scalar colorCv) {
	this->name = name;
	this->color = color;
	this->colorCv = colorCv;
}

std::string Nation::toString() { return "Nation : " + name + " -> " + color; }
cv::Scalar Nation::getColor() { return colorCv; }