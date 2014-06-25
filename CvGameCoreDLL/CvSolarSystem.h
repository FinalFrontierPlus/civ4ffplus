#pragma once

// CvSolarSystem.h
// The first step to handling planets, solar systems, etc. in C++!
// How hard can it be?

#ifndef CIV4_SOLAR_SYSTEMS_H
#define CIV4_SOLAR_SYSTEMS_H

// Maybe this doesn't belong here.
// Well, it probably belongs as a global define, if that can be done.
#define MAX_PLANETS 8

// Ints here and in CvSolarSystem should probably be the enum'd types, but I'm not a huge fan of those.
// So this can be filed as a "fix later".

class CvSolarSystem
{

public:

	CvSolarSystem();
	virtual ~CvSolarSystem();

	void init(int iX, int iY);
	void reset(int iX = -1, int iY = -1, bool bConstructorCall = false);
	void uninit();

	int getNumPlanets();
	SunTypes getSunType();
	int getSelectedPlanet();
	int getBuildingPlanetRing();
	int getPopulationLimit(bool bFactorHappiness = false);

	int getX();
	int getY();

	int getOwner();
	CvCity* getCity();
	int getPopulation();

	// The Python implementation has both because addPlanet() just adds to the end of the planets array
	// However, we're in C++ and it's more convenient to have a fixed-length planets array anyway
	// So we'll have both functions, but one will just call the other.
	CvPlanet* getPlanetByIndex(int iPlanet);
	CvPlanet* getPlanet(int iPlanet);

	bool isNeedsUpdate();
	void setNeedsUpdate(bool bValue);

	void addPlanet(PlanetTypes ePlanetType = NO_PLANET, int iPlanetSize = 0, int iOrbitRing = 0, bool bMoon = false, bool bRings = false);
	void setBuildingPlanetRing(int iID);

	void setSunType(SunTypes eNewValue);

	void read(FDataStreamBase* pStream);
	void write(FDataStreamBase* pStream);

protected:

	int m_iX;
	int m_iY;

	int m_iNumPlanets;
	short /* SunTypes */ m_eSunType;
	int m_iSelectedPlanet;
	int m_iBuildingPlanetRing;

	bool m_bNeedsUpdate;

	CvPlanet* m_apPlanets;
};

#endif
