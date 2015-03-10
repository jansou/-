# pragma once
# include <Siv3D.hpp>
# include "ELCommon.h"
# include "ELPlayer.h"
# include "ELEnemyInfo.h"
# include "ELMyCursor.h"
# include "ELMyCamera.h"
# include "ELTalk.h"
# include "ELItem.h"

# include "ELEvent\EvBase.h"
# include "ELEvent\EvSharkman.h"

struct AutoEvent
{
	AutoEvent(const String &_filename,const Rect &_rect, const String &_term)
		:filename(_filename),actRect(_rect),term(_term)
	{
		readed = false;
	}

	String filename;

	Rect actRect;

	bool readed;

	String term;
};

struct TalkEvent
{
	TalkEvent(const String &_filename, const String& _classFileName) 
		:filename(_filename), className(_classFileName)
	{
		//readed = false;
	}

	TalkEvent()
	{

	}

	String filename;

	//Point pos;

	//Rect actRect;

	//bool readed;

	String className;

	//String term;//èåè
};

class ELEvent
{
private:
	std::vector<AutoEvent> m_setAutoEvents;

	//std::vector<TalkEvent> m_setTalkEvents;
	std::vector< std::shared_ptr<EvBase> > m_setTalkEvents;

	ELPlayState actEvent(
		const String &filename, ELPlayer &player, 
		ELObjectInfo &object, ELMyCamera &mycamera, 
		ELMap &map, ELEnemyInfo &enemy,ELTalk &talk);

	int m_eventIndex;
	bool m_actedAutoEvent;
	bool m_actedTalkEvent;
	bool m_acting;//falseÇ»ÇÁéüÇÃèàóùÇ…à⁄ÇÈ

	CSVReader m_csv;

	String m_mapName;

	int m_column;

public:
	ELEvent();

	bool loadEvent(const String& mapName,const String& stageName);

	void setAutoEvent(const String& filename, const Rect &actrect, const String &term);

	void setTalkEvent(const String& className, const String& filename, const Point& pos);

	ELPlayState update(ELPlayer &player, ELEnemyInfo &enemy, ELMyCamera &mycamera, ELMap &map, ELObjectInfo &object, ELTalk &talk, ELItem &item);

	void clearEvents();

	void draw(Point camerapos);

	void evDraw()const;
};