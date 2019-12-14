#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <SDL.h>

namespace cv
{
	void SDL_MatToTexture(const Mat&, SDL_Texture*);
}