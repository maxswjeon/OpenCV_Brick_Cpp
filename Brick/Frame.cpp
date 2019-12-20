#include "FrameHandler.h"

Frame::Frame() : _logger(Logger::GetInstance())
{
	
}

Frame::Frame(cv::Mat frame, std::chrono::system_clock::time_point time) : _logger(Logger::GetInstance())
{
	Timestamps[int(FrameTimestamp::FRAME_READ_START)] = time;
	RawFrame = std::move(frame);
	Timestamp(FrameTimestamp::FRAME_READ);
}

Frame::Frame(const Frame& other) : _logger(Logger::GetInstance())
{
	RawFrame = other.RawFrame.clone();
	Timestamps = other.Timestamps;
}

Frame::Frame(Frame&& other) noexcept : _logger(Logger::GetInstance())
{
	RawFrame = std::move(other.RawFrame);
	Timestamps = other.Timestamps;	
}

Frame& Frame::operator=(const Frame& other)
{
	RawFrame = other.RawFrame.clone();
	Timestamps = other.Timestamps;
	return *this;
}

Frame& Frame::operator=(Frame&& other) noexcept
{
	RawFrame = std::move(other.RawFrame);
	Timestamps = other.Timestamps;
	return *this;
}

cv::Mat Frame::Blur(cv::Mat frame)
{
	// Blur Frame for Noise Reduction
	cv::Mat frame_blur;
	cv::GaussianBlur(frame, frame_blur, cv::Size(11, 11), 0);
	Timestamp(FrameTimestamp::FRAME_BLUR);

	return frame_blur;
}

void Frame::Timestamp(FrameTimestamp time)
{
	Timestamps[int(time)] = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Timestamps[int(time)] - Timestamps[int(time) - 1]);
	_logger.Debug("Timestamp #%d in %dms", int(time), elapsed.count());
}

void Frame::MethodHSV(bool full)
{
	cv::Mat frame_blur = Blur(RawFrame);
	
	cv::Mat frame_converted;
	cv::cvtColor(frame_blur, frame_converted, full ? cv::COLOR_BGR2HSV_FULL : cv::COLOR_BGR2HSV);
	Timestamp(FrameTimestamp::FRAME_CONVERT);

	int high[3] = {
		ConfigLoader::GetInt("Frame.Recognition.HSVRange.High.H"),
		ConfigLoader::GetInt("Frame.Recognition.HSVRange.High.S"),
		ConfigLoader::GetInt("Frame.Recognition.HSVRange.High.V")
	};

	int low[3] = {
		ConfigLoader::GetInt("Frame.Recognition.HSVRange.Low.H"),
		ConfigLoader::GetInt("Frame.Recognition.HSVRange.Low.S"),
		ConfigLoader::GetInt("Frame.Recognition.HSVRange.Low.V")
	};
}

void Frame::MethodAdaptive()
{
	
}

void Frame::MethodAdaptiveG()
{
	
}



void Frame::Process()
{
	Timestamp(FrameTimestamp::FRAME_PROCESS);

	const char* method = ConfigLoader::GetString("Frame.Recognition.Method").c_str();

	switch (strhash(method))
	{
	case strhash("HSVRange"):
		MethodHSV(ConfigLoader::GetBool("Frame.Recognition.HSVRange.Full"));
		break;
	case strhash("AdaptiveThreshold"):
		MethodAdaptive();
		break;
	case strhash("AdaptiveThresholdG"):
		MethodAdaptiveG();
		break;
	}
}

