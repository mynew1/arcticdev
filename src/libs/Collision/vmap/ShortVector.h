/*
 * Arctic MMORPG Server Software
 * Copyright (c) 2008-2014 Arctic Server Team
 * See COPYING for license details.
 */

#ifndef _SHORTVECTOR_H
#define _SHORTVECTOR_H

#include <Collision/g3dlite/G3D/Vector3.h>

using namespace G3D;
namespace VMAP
{
	/**
	Vector with 16 bit fix point values 12.4 bit.
	*/

	class ShortVector
	{
		private:
			short iX;
			short iY;
			short iZ;

			const static short maxvalue = 0x7fff;
			const static short minvalue = -0x7fff;
			const static int fixpointdiv = 16;
			const static short fixpoint_maxvalue = maxvalue / fixpointdiv;
			const static short fixpoint_minvalue = minvalue / fixpointdiv;

			inline short float2Short(float fv) const
			{
				short sv;
				debugAssert((fv <= fixpoint_maxvalue || fv >= 1000000) && (fv >= fixpoint_minvalue || fv <= -1000000));
				if(fv >= fixpoint_maxvalue)
					sv=maxvalue;
				else if(fv <= fixpoint_minvalue)
					sv=minvalue;
				else
					sv = (short) (fv * fixpointdiv + 0.5);
				return(sv);
			}
			inline float short2Float(short sv) const
			{
				float fv;
				if(sv >= maxvalue)
					fv=inf();
				else if(sv <= minvalue)
					fv=-inf();
				else
					fv = ((float)sv) / fixpointdiv;
				return fv;
			}

			inline float getFX() const { return(short2Float(iX)); }
			inline float getFY() const { return(short2Float(iY)); }
			inline float getFZ() const { return(short2Float(iZ)); }
		public:
			inline ShortVector() {}
			inline ShortVector(const Vector3& pVector)
			{
				iX = float2Short(pVector.x);
				iY = float2Short(pVector.y);
				iZ = float2Short(pVector.z);
			}

			inline ShortVector(float pX, float pY, float pZ)
			{
				iX = float2Short(pX);
				iY = float2Short(pY);
				iZ = float2Short(pZ);
			}
			inline ShortVector(short pX, short pY, short pZ)
			{
				iX = pX;
				iY = pY;
				iZ = pZ;
			}
			inline ShortVector(const ShortVector& pShortVector)
			{
				iX = pShortVector.iX;
				iY = pShortVector.iY;
				iZ = pShortVector.iZ;
			}

			inline float getX() const { return(iX);		}
			inline float getY() const { return(iY);		}
			inline float getZ() const { return(iZ);		}

			inline Vector3 getVector3() const  { return(Vector3(getFX(), getFY(), getFZ())); }

			inline ShortVector min(const ShortVector pShortVector)
			{
				ShortVector result = pShortVector;
				if(pShortVector.iX > iX) { result.iX = iX; }
				if(pShortVector.iY > iY) { result.iY = iY; }
				if(pShortVector.iZ > iZ) { result.iZ = iZ; }
				return(result);
			}

			inline ShortVector max(const ShortVector pShortVector)
			{
				ShortVector result = pShortVector;
				if(pShortVector.iX < iX) { result.iX = iX; }
				if(pShortVector.iY < iY) { result.iY = iY; }
				if(pShortVector.iZ < iZ) { result.iZ = iZ; }
				return(result);
			}

			inline bool operator==(const ShortVector& v) const
			{
				return (iX == v.iX && iY == v.iY && iZ == v.iZ);
			}

			inline bool operator!=(const ShortVector& v) const
			{
				return !(iX == v.iX && iY == v.iY && iZ == v.iZ);
			}

	};
}
#endif
