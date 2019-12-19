#pragma once
#pragma comment(lib, "opencv_world412.lib")

#include "ConfigLoader.h"
#include "Utilities.h"

#include <chrono>
#include <array>
#include <vector>
#pragma comment(lib, "opencv_world412.lib")
#pragma comment(lib, "opencv_img_hash412.lib")

#include <thread>

#include <tbb/concurrent_queue.h>

#include <opencv2/opencv.hpp>

enum class FrameTimestamp : int 
{
	FRAME_READ_START,
	FRAME_READ,
	FRAME_PROCESS,
	FRAME_BLUR,
	FRAME_CONVERT,
	FRAME_RANGE,
	FRAME_CONTOUR,
	FRAME_ROUND,
	FRAME_RESIZE,
	FRAME_SHOWN
};

class Frame
{
private:
	cv::Mat Blur(cv::Mat);

	inline void Timestamp(FrameTimestamp);
	void MethodHSV(bool);
	void MethodAdaptiveG();
	void MethodAdaptive();
public:
	cv::Mat RawFrame;
	
	std::array<std::chrono::system_clock::time_point, 10> Timestamps;

	Frame() = default;
	Frame(cv::Mat, std::chrono::system_clock::time_point time);
	void Process();
};

class FrameHandler
{
	tbb::concurrent_queue<Frame> _queue;
	
	std::thread _thread_capture;
	std::vector<std::thread> _thread_process;

public:
	FrameHandler(int device, int pool_size);

};

