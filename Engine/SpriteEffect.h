#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "Vec2.h"
#include <cassert>

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(Color c)
			:
			chroma(c)
		{}
		void operator() (Color Src, Vei2& pos, Graphics& gfx) const
		{
			if (Src != chroma)
			{
				gfx.PutPixel(pos.x, pos.y, Src);
			}
		}
	private:
		Color chroma;
	};

	class NoChroma
	{
	public:
		void operator() (Color Src, Vei2& pos, Graphics& gfx) const
		{
			gfx.PutPixel(pos.x, pos.y, Src);
		}
	};

	class Substitute
	{
	public:
		Substitute(Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}
		void operator() (Color Src, Vei2& pos, Graphics& gfx)
		{
			if (Src != chroma)
			{
				gfx.PutPixel(pos.x, pos.y, sub);
			}
		}
	private:
		Color sub;
		Color chroma;
	};

	class ChromaSub			//vaihtaa chroma värin
	{
	public:
		ChromaSub(Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}
		void operator() (Color Src, Vei2& pos, Graphics& gfx)
		{
			if (Src == chroma)
			{
				gfx.PutPixel(pos.x, pos.y, sub);
			}
			else
			{
				gfx.PutPixel(pos.x, pos.y, Src);
			}
		}
	private:
		Color chroma;
		Color sub;
	};
	class Ghost
	{
	public:
		Ghost(Color c, float Ghosteffect)
			:
			chroma(c),
			Ghosteffect(Ghosteffect)
		{}
		void operator() (Color Src, Vei2& pos, Graphics& gfx)
		{
			assert(Ghosteffect <= 1.0f);
			if (Src != chroma)
			{
				const Color dest = gfx.GetPixel(pos.x, pos.y);
				const Color haalea = {
					unsigned char((Src.GetR() + dest.GetR()) * Ghosteffect),
					unsigned char((Src.GetG() + dest.GetG()) * Ghosteffect),
					unsigned char((Src.GetB() + dest.GetB()) * Ghosteffect)
				};
				gfx.PutPixel(pos.x, pos.y, haalea);
			}
		}
	private:
		Color chroma;
		float Ghosteffect;
	};

	class GhostNochroma			//korjaa nimet
	{
	public:
		GhostNochroma(float Ghosteffect)
			:
			Ghosteffect(Ghosteffect)
		{}
		void operator() (Color Src, Vei2& pos, Graphics& gfx)
		{
			assert(Ghosteffect <= 1.0f);
			const Color dest = gfx.GetPixel(pos.x, pos.y);
			const Color haalea = {
				unsigned char((Src.GetR() + dest.GetR()) * Ghosteffect),
				unsigned char((Src.GetG() + dest.GetG()) * Ghosteffect),
				unsigned char((Src.GetB() + dest.GetB()) * Ghosteffect)
			};
			gfx.PutPixel(pos.x, pos.y, haalea);
		}
	private:
		float Ghosteffect;
	};
}

