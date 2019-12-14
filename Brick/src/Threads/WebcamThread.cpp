#include "Threads/WebcamThread.h"

WebcamThread::WebcamThread(int device, std::shared_ptr<Queue<Frame>> queue)
{
	_queue = queue;
	_logger = Logger::GetInstance();
	_cap = cv::VideoCapture(device);

	if (!_cap.isOpened())
	{
		_logger->Error("Failed to Open Camera Device #%d", device);
		Valid = false;
	}
}

void WebcamThread::run()
{
	int error_count = 0;
	while (_status == ThreadStatus::RUNNING)
	{
		cv::Mat frame;
		_cap.read(frame);

		if (frame.empty())
		{
			error_count++;
			_logger->Warn("Failed to Get Frame - Empty Frame Read");

			if (error_count > 5)
			{
				_logger->Error("Failed to Get Frames %d times in a row", error_count);
				_status = ThreadStatus::STOPPED;
			}
			
			continue;
		}
		
		error_count = 0;

		Frame data = Frame(frame);
		_queue->push(data);
	}
}
