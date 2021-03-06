# include "ELFade.h"

ELFade::ELFade()
	:m_framecount(0)
{

}

bool ELFade::FadeOut()
{
	Rect(0,0,1280,720).draw(Color(0,0,0,m_framecount));

	if(m_framecount == 255)
	{
		return true;
	}

	++m_framecount;

	return false;
}

bool ELFade::CircleFadeOut()
{
	if (m_framecount > 1000/* + 468*/)
	{
		return true;
	}

	m_framecount+=20;

	return false;
}

void ELFade::CircleFadeOutDraw(const Point& pos)
{
	//Point pos(640, 360);
	Circle(pos, 1468).drawFrame(468+m_framecount, 0.0, Palette::Black);
}