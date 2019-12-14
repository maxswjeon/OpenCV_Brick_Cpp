#pragma once

#include <time.h>
#include <opencv2/opencv.hpp>

enum class FrameStatus
{
	READ,
	CALCULATED,
	CONVERTED
};

class Frame
{
private:
	long _timestamp[10];
	FrameStatus _status;
	
	cv::Mat _frame;
public:
	Frame(cv::Mat frame);
};