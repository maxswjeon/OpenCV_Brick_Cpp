#include "Utils\Images.h"

void cv::SDL_MatToTexture(const Mat& mat, SDL_Texture* texture)
{
	void* pixels;
	int32_t pitch;

	SDL_LockTexture(texture, nullptr, &pixels, &pitch);
	auto const format{ SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888) };
	reinterpret_cast<uint32_t*>(pixels)[1024] = SDL_MapRGB(format, 255, 255, 255);
	SDL_UnlockTexture(texture);
}
