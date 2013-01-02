//
// cEci.cpp
//
// Copyright (c) 2002-2012 Michael F. Henry
// Version 09/2012
//
#include "stdafx.h"

#include "cEci.h"
#include "globals.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

//////////////////////////////////////////////////////////////////////
// Class cEci
//////////////////////////////////////////////////////////////////////
cEci::cEci(const cVector &pos)
{
}

cEci::cEci(const cVector &pos, const cVector &vel)
   : m_Position (pos),
     m_Velocity (vel)
{
}

cEci::cEci()
{
}

//////////////////////////////////////////////////////////////////////
// Class cEciTime
//////////////////////////////////////////////////////////////////////
cEciTime::cEciTime(const cGeo &geo, const cJulian &date)
{
   FromGeoTime(cGeoTime(geo, date));
}

cEciTime::cEciTime(const cGeoTime &geo)
{
   FromGeoTime(geo);
}

void cEciTime::FromGeoTime(const cGeoTime &geo)
{
   // Calculate the ECI coordinates of the location "geo" at time "date".
   // Reference: The 1992 Astronomical Almanac, page K11
   // Reference: www.celestrak.com (Dr. T.S. Kelso)
   m_Date = geo.Date();

   double mfactor = TWOPI * (OMEGA_E / SEC_PER_DAY);
   double lat = geo.LatitudeRad();
   double lon = geo.LongitudeRad();
   double alt = geo.AltitudeKm();

   // Calculate Local Mean Sidereal Time (theta)
   double theta = m_Date.ToLmst(lon);
   double c = 1.0 / sqrt(1.0 + F * (F - 2.0) * sqr(sin(lat)));
   double s = sqr(1.0 - F) * c;
   double achcp = (XKMPER_WGS72 * c + alt) * cos(lat);

   m_Position.m_x = achcp * cos(theta);               // km
   m_Position.m_y = achcp * sin(theta);               // km
   m_Position.m_z = (XKMPER_WGS72 * s + alt) * sin(lat); // km
   m_Position.m_w = sqrt(sqr(m_Position.m_x) + 
                    sqr(m_Position.m_y) + 
                    sqr(m_Position.m_z));             // range, km

   m_Velocity.m_x = -mfactor * m_Position.m_y;        // km / sec
   m_Velocity.m_y =  mfactor * m_Position.m_x;
   m_Velocity.m_z = 0.0;
   m_Velocity.m_w = sqrt(sqr(m_Velocity.m_x) +        // range rate km/sec^2
                    sqr(m_Velocity.m_y));
}

cEciTime::cEciTime(const cVector &pos, const cJulian &date)
   : cEci(pos),
     m_Date(date)
{
}

cEciTime::cEciTime(const cVector &pos, const cVector &vel, const cJulian &date)
   : cEci(pos, vel),
     m_Date(date)
{
}

//////////////////////////////////////////////////////////////////////////////
// Return the corresponding geodetic position of the ECI coordinates 
// based on the current Julian date.
// Reference: The 1992 Astronomical Almanac, page K12. 
// Reference: www.celestrak.com (Dr. T.S. Kelso)
cGeoTime cEciTime::ToGeoTime()
{
   double theta = AcTan(m_Position.m_y, m_Position.m_x);
   double lon   = fmod(theta - m_Date.ToGmst(), TWOPI);
   
   if (lon < 0.0) 
   {
      lon += TWOPI;  // "wrap" negative modulo
   }

   double r   = sqrt(sqr(m_Position.m_x) + sqr(m_Position.m_y));
   double e2  = F * (2.0 - F);
   double lat = AcTan(m_Position.m_z, r);

   const double delta = 1.0e-07;
   double phi;
   double c;

   do   
   {
      phi = lat;
      c   = 1.0 / sqrt(1.0 - e2 * sqr(sin(phi)));
      lat = AcTan(m_Position.m_z + XKMPER_WGS72 * c * e2 * sin(phi), r);
   }
   while (fabs(lat - phi) > delta);
   
   double alt = r / cos(lat) - XKMPER_WGS72 * c;

   return cGeoTime(lat, lon, alt, m_Date); // radians, radians, kilometers
}

}
}

