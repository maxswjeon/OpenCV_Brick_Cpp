#include "Frame.h"

Frame::Frame(cv::Mat frame)
{
	_frame = frame;
	_status = FrameStatus::READ;
	_timestamp[int(FrameStatus::READ)] = time(0);
}

