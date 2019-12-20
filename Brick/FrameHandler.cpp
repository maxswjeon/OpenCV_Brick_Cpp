#include "FrameHandler.h"

FrameHandler::FrameHandler(int device, int pool_size) : _logger(Logger::GetInstance())
{
	_device = device;
	_flag = false;

	for (int i = 0; i < pool_size; ++i)
	{
		_thread_process.push_back(std::thread([&]
			{
				while (true)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					Frame f;
					if (_queue.try_pop(f))
					{
						f.Process();
					}
				}
			}));
	}
}

int FrameHandler::Start()
{
	_flag = true;

	int _first = 0;
	
	_thread_capture = std::thread([&]
		{
			cv::VideoCapture cap = cv::VideoCapture(_device);
			cap.set(cv::CAP_PROP_FPS, 60);

			cv::Mat fframe;
			cap.read(fframe);

			if (fframe.empty())
			{
				_logger.Error("Failed to Read Frame");
				_first = 2;
				return;
			}
			_logger.Info("Read First Frame From Webcam");
			_first = 1;
		
			while (_flag)
			{
				cv::Mat frame;
				auto start = std::chrono::system_clock::now();
				cap.read(frame);

				if (frame.empty())
				{
					_logger.Error("Failed to Read Frame");
				}
				
				Frame f = Frame(frame, start);
				_queue.push(f);
			}
		});

	while (!_first)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return _first - 1;
}

