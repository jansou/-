# include "EvSharkman.h"


EvSharkman::EvSharkman
		(const String& filename,
		const Point& Pos) :
		m_csvFilename(filename),
		m_hitArea(Rect(0,0,256,256)),
		m_pos(Pos),
		m_startPos(Pos),
		m_state(ELEnemyState::Staying),
		m_face(ELEnemyFace::EnemyLeft),
		m_frameCount(0),
		m_oldFrameCount(0),
		m_jumpH(0),
		m_speed(0),
		m_oldState(ELEnemyState::Jumping),
		m_erased(false),
		m_csv(L"data/ElisEvent/" + filename)
{
	TextureAsset::Register(L"texEvSharkman_stay",
		L"data/Elis/Enemy/Sharkman/sharkman_stay.png");
	TextureAsset::Register(L"texEvSharkman_damaged",
		L"data/Elis/Enemy/Sharkman/sharkman_damaged.png");
	TextureAsset::Register(L"texEvSharkman_dead",
		L"data/Elis/Enemy/Sharkman/sharkman_dead.png");

	
}

namespace
{
	const int kAnimeTiming = 8;
	const int kGravity = 10;
	const int kSpeed = 3;
	const int kMaxJunpH =20;
	const int kInterval = 70;
	const int kDrop = 1;

	const int kRiseOffset = 3;

	const int kDamage = 5;

	const int height(const String &name)
	{
		return TextureAsset(name).height;
	}
};

bool EvSharkman::evUpdate(const ELMap& map, const Point& playerpos, ELObjectInfo& object, ELItem &item, const Point &camerapos)
{
	if (Input::KeyEnter.clicked)
	{
		return false;
	}

	return true;
}

void EvSharkman::evDraw() const
{
	Rect(128, 50, 1024, 180).draw(Color(255, 255, 255));
	/*
	m_talkFont(m_talkPhrases[m_column].text1).draw(370, 80, Palette::Black);
	m_talkFont(m_talkPhrases[m_column].text2).draw(370, 120, Palette::Black);
	m_talkFont(m_talkPhrases[m_column].text3).draw(370, 160, Palette::Black);
	
	switch (m_talkPhrases[m_column].direction)
	{
	case TalkDirection::LeftTalking:
	{
		TextureAsset(L"icon_" + m_talkPhrases[m_column].leftIconName).draw(110, 100);
		TextureAsset(L"icon_" + m_talkPhrases[m_column].rightIconName).mirror().draw(1280 - 110 - 256, 100, Alpha(100));

		break;
	}
	case TalkDirection::RightTalking:
	{
		TextureAsset(L"icon_" + m_talkPhrases[m_column].leftIconName).draw(110, 100, Alpha(100));
		TextureAsset(L"icon_" + m_talkPhrases[m_column].rightIconName).mirror().draw(1280 - 110 - 256, 100);

		break;
	}
	default:
		break;
	}
	*/
}

void EvSharkman::update(const ELMap& map, const Point& playerpos, ELObjectInfo& object, ELItem &item, const Point &camerapos)
{
	if(m_state == ELEnemyState::Dead && m_oldState != ELEnemyState::Dead)SoundAsset(L"sndELEnemyDefeat").play();

	m_oldState = m_state;

	if(m_state == ELEnemyState::Dead)
	{

		//SoundAsset(L"sndEnemyDefeat").play();

		if(m_frameCount == kAnimeTiming*6-1)
		{
			int a = Random(1,10);
			if(a >= 1 && a <= 5)
				item.makeItem(ELItemType::LifeUpM,m_hitRect.center,true);
			if(a >= 6 && a <= 10)
				item.makeItem(ELItemType::MagicUpM,m_hitRect.center,true);

			m_erased = true;

			return;
		}

		m_frameCount+=1;

		return;
	}


	if(playerpos.x-m_pos.x>0)
	{
		m_speed = kSpeed;

		m_face = ELEnemyFace::EnemyRight;
	}
	else
	{
		m_speed -= kSpeed;
		
		m_face = ELEnemyFace::EnemyLeft;
	}

	gravity(map,object,camerapos);

	if(m_state != ELEnemyState::Damaged || m_frameCount>30)
	{
		IdentifyState(map,object);
	}

	m_frameCount+=1;

	if(m_oldState != m_state)
	{
		m_frameCount = 0;
	}

	m_hitRect = Rect(m_pos.x - m_hitArea.size.x/2, m_pos.y - m_hitArea.size.y, m_hitArea.size);

	return;
}

void EvSharkman::gravity(const ELMap& map, ELObjectInfo& object, const Point &camerapos)
{
	for(int i=0; i<kGravity;++i)
	{
		//LOGFMT_ERR(map.isFloor(enemyPos.x,enemyPos.y+i));
		if(object.isTouchable(Point(m_pos.x,m_pos.y+i-m_hitArea.size.y),Point(m_pos.x,m_pos.y+i),camerapos)
			|| map.isFloor(m_pos.x,m_pos.y+i) )
		{
			m_pos.y += i;
			return;
		}
	}

	m_pos.y +=kGravity;
	return;
}

void EvSharkman::IdentifyState(const ELMap& map, ELObjectInfo& object)
{
	m_state = ELEnemyState::Staying;
	return;
}

void EvSharkman::MoveXAxis(const ELMap& map, int speed, const Point &camerapos)
{
	m_oldState = m_state;

	const int dir = (0<=speed ? 1 : -1);

	for(int i=0;i<std::abs(speed);++i)
	{
		for(int j=0;j<=kRiseOffset;++j)
		{
			const Point foot = m_pos;
			const Point head = m_pos - Point(0,/*kHeight*/m_hitArea.size.y);
			if(!map.isFloor(foot.x+dir,foot.y-j-1) 
				&& !intersectBody(
				Point(foot.x+dir,foot.y-j-1),
				Point(head.x+dir,head.y-j-1),
				map))
			{
				m_pos.moveBy(Point(dir,-j));
				break;
			}
		}	
	}
}

bool EvSharkman::intersectBody(const Point& foot,const Point& head, const ELMap& map)//’Êí°‚Æg‘Ì‚ÌÚG”»’è
{
	for(int i=1;i<foot.y-head.y;++i)
	{
		if(map.isFloor(foot.x,foot.y-i) && map.getFloorType(foot.x,foot.y-i)==ELFloorType::NormalFloor)
		{
			return true;
		}
	}

	return false;
}

void EvSharkman::draw(const Point& camerapos)const
{
	Point modifyDrawPos(128, 256);

	switch(m_state)
	{
	case ELEnemyState::Staying:
		{	
			TextureAsset(L"texEvSharkman_stay")
			(
				256*m_face,
				256*(m_frameCount/kAnimeTiming%(TextureAsset(L"texEvSharkman_stay").height/256)),
				256,
				256
				).draw(m_pos-camerapos-modifyDrawPos);

			break;
		}
	case ELEnemyState::Damaged:
		{
			TextureAsset(L"texEvSharkman_damaged")
				(256*m_face,
				0,
				256,
				256).draw(m_pos-camerapos-modifyDrawPos,Alpha(155));
			break;
		}
	case ELEnemyState::Dead:
		{
			TextureAsset(L"texEvSharkman_dead")
			(256*m_face, (m_frameCount/kAnimeTiming)%(height(L"texEvSharkman_dead")/256)*256, 256, 256).draw(m_pos-camerapos-modifyDrawPos);
			break;
		}
	default:
		break;
	}

	//Rect(m_hitRect.pos-camerapos,m_hitRect.size).drawFrame(10,10,Palette::Black);
}

ELEnemySize EvSharkman::getEnemySize() const
{
	return m_size;
}

Point EvSharkman::getPos() const
{
	return m_pos;
}

bool EvSharkman::isHit(const Rect &body) const
{
	if(m_state == ELEnemyState::Dead || m_state == ELEnemyState::Damaged)
		return false;

	return body.intersects(m_hitRect);
}

int EvSharkman::getDamage() const
{
	return kDamage;
}

Rect EvSharkman::getHitRect() const
{
	return m_hitRect;
}

void EvSharkman::giveDamage(int damage)
{
	if(damage >0 && m_state != ELEnemyState::Dead && m_state != ELEnemyState::Damaged)
	{
		m_HP = Max(m_HP-damage,0);

		SoundAsset(L"sndELEnemyDamaged").play();
		m_state = ELEnemyState::Damaged;
		m_frameCount = 0;
	}

	if(m_HP == 0)
	{
		m_state = ELEnemyState::Dead;
	}
}

Point EvSharkman::getStartPos() const
{
	return m_startPos;
}

bool EvSharkman::isErased() const
{
	return m_erased;
}

bool EvSharkman::isDamaged() const
{
	return m_state == ELEnemyState::Damaged || m_state == ELEnemyState::Dead;
}