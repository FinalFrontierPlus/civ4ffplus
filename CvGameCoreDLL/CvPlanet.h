#pragma once

// CvPlanet.h
// The second step to handling planets, solar systems, etc. in C++!
// How hard can it be?

#ifndef CIV4_PLANETS_H
#define CIV4_PLANETS_H

// Should these go in one of the other headers? I forget how to DLL.
#define PLANET_RANGE_2 4
#define PLANET_RANGE_3 6

class CvPlanet
{

public:

	CvPlanet();
	virtual ~CvPlanet();

	void init(int iX, int iY, int iPlanetType = 0, int iPlanetSize = 0, int iOrbitRing = 0, bool bMoon = false, bool bRings = false);
	void reset(int iX = -1, int iY = -1, int iPlanetType = 0, int iPlanetSize = 0, int iOrbitRing = 0, bool bMoon = false, bool bRings = false, bool bConstructorCall = false);
	void uninit();

	int getX();
	int getY();

	int getPlanetType();
	int getPlanetSize();
	int getOrbitRing();
	int getPopulation();

	BonusTypes getBonusType();

	bool isMoon();
	bool isRings();
	bool isDisabled();
	bool isBonus();

	bool isHasBonus(BonusTypes eBonusType);
	bool isHasBuilding(BuildingTypes eBuildingType);

	int getBuildingProduction(BuildingTypes eBuildingType);

	bool isPlanetWithinCulturalRange();
	int getPlanetCulturalRange();

	int getPopulationLimit(PlayerTypes eOwner);
	int getBaseYield(YieldTypes eYield);
	int getExtraYield(PlayerTypes eOwner, YieldTypes eYield);
	int getTotalYield(PlayerTypes eOwner, YieldTypes eYield);

	// These setters don't exist in Python, but then again, Python is actually sane.
	void setPlanetType(int iPlanetType);
	void setPlanetSize(int iPlanetSize);
	void setOrbitRing(int iOrbitRing);

	void setPopulation(int iValue);
	void changePopulation(int iChange);

	void setBonusType(BonusTypes eNewBonus);
	void setHasBuilding(BuildingTypes eBuildingType, bool bValue);
	void setBuildingProduction(BuildingTypes eBuildingType, int iValue);

	void setMoon(bool bMoon);
	void setRings(bool bRings);
	void setDisabled(bool bDisabled);

	void read(FDataStreamBase* pStream);
	void write(FDataStreamBase* pStream);

protected:

	int m_iX;
	int m_iY;

	int m_iPlanetType;
	int m_iPlanetSize;
	int m_iOrbitRing;
	int m_iPopulation;

	bool m_bMoon;
	bool m_bRings;
	bool m_bDisabled;

	// I hate Hungarian notation. "pai"?
	// The building array is a boolean array in Python.
	int* m_pabBuildings;
	int* m_paiBuildingProduction;

	short /*BonusTypes*/ m_eBonusType;
};

#endif
