#pragma once

#include "Threads/Thread.h"
#include "Utils/Queue.hpp"
#include "Utils/Logger.h"

#include "../../Frame.h"

#include <opencv2/opencv.hpp>

class WebcamThread : public Thread
{
private:
	cv::VideoCapture _cap;
	std::shared_ptr<Queue<Frame>> _queue;
	Logger* _logger;
public:
	bool Valid;

	WebcamThread(int, std::shared_ptr<Queue<Frame>>);

	void run() override;
};

