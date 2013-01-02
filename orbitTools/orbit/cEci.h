//
// cEci.h
//
// Copyright (c) 2003-2012 Michael F. Henry
// Version 06/2012
#pragma once

#include "globals.h"
#include "cVector.h"
#include "cJulian.h"
#include "coord.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

//////////////////////////////////////////////////////////////////////
// class cEci
//////////////////////////////////////////////////////////////////////
class cEci
{
public:
   cEci(const cVector &pos);
   cEci(const cVector &pos, const cVector &vel);
   virtual ~cEci() {};

   const cVector& Position() const { return m_Position; }
   const cVector& Velocity() const { return m_Velocity; }

   void ScalePosVector(double factor) { m_Position.Mul(factor); }
   void ScaleVelVector(double factor) { m_Velocity.Mul(factor); }

protected:
   cEci();

   cVector  m_Position;
   cVector  m_Velocity;
};

//////////////////////////////////////////////////////////////////////
// class cEciTime
//////////////////////////////////////////////////////////////////////
class cEciTime : public cEci
{
public:
   cEciTime(const cGeoTime &geo);
   cEciTime(const cGeo &geo, const cJulian &date);
   cEciTime(const cVector &pos, const cJulian &date);
   cEciTime(const cVector &pos, const cVector &vel, const cJulian &date);
   virtual ~cEciTime() {};

   cJulian Date() const { return m_Date; }

   cGeoTime ToGeoTime(); 

protected:
   void FromGeoTime(const cGeoTime &geo);

   cJulian m_Date;
};

}
}

