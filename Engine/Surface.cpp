#include "Surface.h"

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmfileheader;  
	file.read(reinterpret_cast<char*>(&bmfileheader), sizeof(bmfileheader));

	BITMAPINFOHEADER bminfoheader;
	file.read(reinterpret_cast<char*>(&bminfoheader), sizeof(bminfoheader));

	assert(bminfoheader.biBitCount == 24 || bminfoheader.biBitCount == 32);
	assert(bminfoheader.biCompression == BI_RGB);

	width = bminfoheader.biWidth;

	const bool is32b = bminfoheader.biBitCount == 32;


	int yStart;
	int yEnd;
	int dy;
	if (bminfoheader.biHeight < 0)
	{
		height = -bminfoheader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		height = bminfoheader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}



	Pixels.resize(width * height);

	file.seekg(bmfileheader.bfOffBits);
	// padding is for the case of of 24 bit depth only
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < width; x++)
		{
			PutPixel(x, y, Color(file.get(), file.get(), file.get()));
			if (is32b)
			{
				file.seekg(1, std::ios::cur);
			}
		}
		if (!is32b)
		{
			file.seekg(padding, std::ios::cur);
		}
	}



}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	Pixels(width * height)
{
}



Surface::Surface(Surface&& donor) noexcept
{
	*this = std::move(donor);
}

Surface& Surface::operator=(Surface&& rhs) noexcept
{
	Pixels = std::move(rhs.Pixels);
	width = rhs.width;
	height = rhs.height;
	rhs.width = 0;
	rhs.height = 0;
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	Pixels.data()[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return Pixels.data()[y * width + x];
}

const Color* Surface::Data()
{
	return Pixels.data();
}

void Surface::Fill(Color c)
{
	std::fill(Pixels.begin(), Pixels.begin() + width * height, c);
}

RectI Surface::GetRect() const
{
	return { 0, GetWidth(), 0, GetHeight() };
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
