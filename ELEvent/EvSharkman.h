
# pragma once
# include <Siv3D.hpp>
# include "../ELMap.h"
# include "EvBase.h"
# include "../ELEnemyInfo.h"
# include "../ELObjectInfo.h"
# include "../ELItem.h"
# include "../ELCommon.h"
# include "../ELAttack.h"

enum class ELEnemyName;

enum class ELEnemySize;

enum ELEnemyFace;

enum class ELEnemyState;

class EvSharkman : public EvBase
{
private:
	String m_csvFilename;
	CSVReader m_csv;

	int m_frameCount;
	int m_oldFrameCount;
	int m_jumpH;
	int m_speed;
	ELEnemyState m_oldState;

	ELEnemyName m_name;
	ELEnemySize m_size;
	int m_HP;
	Point m_pos;
	Point m_startPos;
	ELEnemyState m_state;
	ELEnemyFace m_face;

	Rect m_hitRect;
	Rect m_hitArea;
	bool m_erased;

	void gravity(const ELMap& map, ELObjectInfo& object, const Point &camerapos);
	void MoveXAxis(const ELMap& map, int speed, const Point &camerapos);
	void jump(const ELMap& map, int jumpH, const Point &camerapos);
	void IdentifyState(const ELMap& map, ELObjectInfo& object);
	static bool intersectBody(const Point& foot,const Point& head, const ELMap& map);
	
public:
	
	EvSharkman(const String& csvFilename,
		const Point& Pos);
		
	void evDraw()const;

	void update(const ELMap& map, const Point& playerpos, ELObjectInfo& object, ELItem &item, const Point &camerapos);

	bool evUpdate(const ELMap& map, const Point& playerpos, ELObjectInfo& object, ELItem &item, const Point &camerapos);

	void draw(const Point& camerapos)const;

	ELEnemySize getEnemySize() const; 

	Point getPos() const; 

	bool isHit(const Rect &body) const;

	int getDamage() const;

	Rect getHitRect() const;

	void giveDamage(int damage);

	Point getStartPos() const;

	bool isErased() const;

	bool isDamaged() const;

	int getLife() const {return m_HP;}

	ELEnemyName getName() const
	{
		return m_name;
	}

	void addFramecount()
	{
		++m_frameCount;
	}

	ELEnemyState getEnemyState() const
	{
		return m_state;
	}
};