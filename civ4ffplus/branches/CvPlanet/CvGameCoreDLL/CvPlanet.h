#pragma once

// CvPlanet.h
// The second step to handling planets, solar systems, etc. in C++!
// How hard can it be?

#ifndef CIV4_PLANETS_H
#define CIV4_PLANETS_H

class CvPlanet
{

public:

	CvPlanet();
	virtual ~CvPlanet();

	void init(int iX, int iY, int iPlanetType = 0, int iPlanetSize = 0, int iOrbitRing = 0, bool bMoon = false, bool bRings = false);
	void reset(int iX = -1, int iY = -1, int iPlanetType = 0, int iPlanetSize = 0, int iOrbitRing = 0, bool bMoon = false, bool bRings = false);
	void uninit();

	int getX();
	int getY();

	int getPlanetType();
	int getPlanetSize();
	int getOrbitRing();

	bool isMoon();
	bool isRings();

	// These setters don't exist in Python, but then again, Python is actually sane.
	void setPlanetType(int iPlanetType);
	void setPlanetSize(int iPlanetSize);
	void setOrbitRing(int iOrbitRing);

	void setMoon(bool bMoon);
	void setRings(bool bRings);

	void read(FDataStreamBase* pStream);
	void write(FDataStreamBase* pStream);

protected:

	int m_iX;
	int m_iY;

	int m_iPlanetType;
	int m_iPlanetSize;
	int m_iOrbitRing;

	bool m_bMoon;
	bool m_bRings;

};

#endif
