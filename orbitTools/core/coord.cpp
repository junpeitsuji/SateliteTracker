//
// coord.cpp
//
// Copyright (c) 2003-2012 Michael F. Henry
// Version 08/2012
//
#include "stdafx.h"
#include "globals.h"
#include "coord.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

//////////////////////////////////////////////////////////////////////
// cGeo Class
//////////////////////////////////////////////////////////////////////

cGeo::cGeo():
   m_Lat(0.0), m_Lon(0.0), m_Alt(0.0)
{
}

cGeo::cGeo(double latRad, double lonRad, double altKm):
   m_Lat(latRad), m_Lon(lonRad), m_Alt(altKm)
{
}

/// <summary>
/// Converts to a string representation of the form "38.0N 045.0W 500m".
/// </summary>
string cGeo::ToString() const
{
   const int BUF_SIZE = 128;
   char sz[BUF_SIZE];

   bool isNorth = (LatitudeRad()  >= 0.0);
   bool isEast  = (LongitudeRad() >= 0.0);

   snprintf(sz, BUF_SIZE, 
               "%04.3f%c %05.3f%c %.1fm", 
               fabs(LatitudeDeg()),  (isNorth ? 'N' : 'S'),
               fabs(LongitudeDeg()), (isEast  ? 'E' : 'W'),
               AltitudeKm() * 1000.0);

   string strLoc = sz;

   return strLoc;
}

//////////////////////////////////////////////////////////////////////
// cGeoTime Class
//////////////////////////////////////////////////////////////////////
cGeoTime::cGeoTime(const cGeo &geo, const cJulian &date)
   : cGeo(geo),
     m_Date(date)
{
}

cGeoTime::cGeoTime(double latRad, double lonRad, double altKm, const cJulian &date)
   : cGeo(latRad, lonRad, altKm),
     m_Date(date)
{
}

//////////////////////////////////////////////////////////////////////
// cTopo Class
//////////////////////////////////////////////////////////////////////

cTopo::cTopo():
   m_Az(0.0), m_El(0.0), m_Range(0.0), m_RangeRate(0.0) 
{
}

cTopo::cTopo(double azRad, double elRad, double rangeKm, double rateKmSec) :
   m_Az(azRad), m_El(elRad), m_Range(rangeKm), m_RangeRate(rateKmSec)
{
}

}
}

