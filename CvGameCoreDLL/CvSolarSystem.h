#pragma once

// CvSolarSystem.h
// The first step to handling planets, solar systems, etc. in C++!
// How hard can it be?

#ifndef CIV4_SOLAR_SYSTEMS_H
#define CIV4_SOLAR_SYSTEMS_H

class CvSolarSystem
{

public:

	CvSolarSystem();
	virtual ~CvSolarSystem();

	void init(int iX, int iY);
	void reset(int iX = -1, int iY = -1);
	void uninit();

	int getNumPlanets();
	int getSunType();
	int getSelectedPlanet();
	int getBuildingPlanetRing();

	bool isNeedsUpdate();
	void setNeedsUpdate(bool bValue);

	void read(FDataStreamBase* pStream);
	void write(FDataStreamBase* pStream);

protected:

	int m_iX;
	int m_iY;

	int m_iNumPlanets;
	int m_iSunType;
	int m_iSelectedPlanet;
	int m_iBuildingPlanetRing;

	bool m_bNeedsUpdate;

};

#endif
