# pragma once
# include <Siv3D.hpp>
# include "../ELMap.h"
# include "../ELObjectInfo.h"
# include "../ELItem.h"

enum class ELEnemySize;
enum class ELEnemyName;
enum class ELEnemyState;

class EvBase
{
public:
	virtual ~EvBase(){}


	virtual void update(const ELMap& map, const Point& playerpos, ELObjectInfo& object, ELItem &item, const Point &camerapos) = 0;

	virtual void evDraw()const = 0;

	virtual bool evUpdate(const ELMap& map, const Point& playerpos, ELObjectInfo& object, ELItem &item, const Point &camerapos){ return false; }


	virtual void draw
		(
		const Point& camerapos
		) const = 0;

	virtual ELEnemySize getEnemySize() const = 0; 

	virtual Point getPos() const = 0; 

	virtual bool isHit(const Rect &body) const = 0;

	virtual int getDamage() const = 0;

	virtual Rect getHitRect() const = 0;

	virtual void giveDamage(int damage) = 0;

	virtual Point getStartPos() const = 0;

	virtual bool isErased() const = 0;

	virtual bool isDamaged() const = 0;

	virtual void addFramecount() = 0;

	virtual bool ready() {return false;}

	virtual ELEnemyName getName() const = 0;
	
	virtual int getLife() const = 0;

	virtual ELEnemyState getEnemyState() const = 0;

	virtual ELCameraEffect getCameraEffect() const {return ELCameraEffect::null;}

	virtual Point getBurstPos() const {return Point(0,0);}
};
