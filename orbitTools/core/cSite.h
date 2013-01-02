//
// cSite.h: interface for the cSite class.
//
// Copyright 2002-2012 Michael F. Henry
// Version 08/2012

#pragma once

#include "coord.h"
#include "cEci.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

//////////////////////////////////////////////////////////////////////
// class cSite
// This class represents a ground site location on the earth.
class cSite  
{
public:
   cSite(double degLat, double degLon, double kmAlt);
   cSite(const cGeo &geo);
   virtual ~cSite();

   cGeo GetGeo() const { return m_geo; }

   cEciTime GetPosition(const cJulian&) const;  // calc ECI of geo location.
   cTopo GetLookAngle(const cEciTime&) const;   // calc topo coords to ECI object

   double LatitudeRad()  const { return m_geo.LatitudeRad();  }
   double LongitudeRad() const { return m_geo.LongitudeRad(); }

   double LatitudeDeg()  const { return m_geo.LatitudeDeg();  }
   double LongitudeDeg() const { return m_geo.LongitudeDeg(); }

   double AltitudeKm()   const { return m_geo.AltitudeKm();   }

   string ToString() const;

protected:
   cGeo m_geo;  // lat, lon, alt of Earth site
};
}
}

