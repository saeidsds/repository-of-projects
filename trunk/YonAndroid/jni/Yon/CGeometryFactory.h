#ifndef _YON_SCENE_CGEOMETRYFACTORY_H_
#define _YON_SCENE_CGEOMETRYFACTORY_H_

#include "IGeometryFactory.h"

namespace yon{
	namespace scene{

		class CGeometryFactory : public IGeometryFactory{
		public:

			/*virtual IEntity* createXYPlane2D(const core::dimension2df& size) const;
			virtual IEntity* createXYPlane(const core::dimension2df& size,f32 z) const;
			virtual IEntity* createCube(const core::dimension3df& size) const;*/

			virtual IShap* createTorus(f32 cirRadius,f32 orbitRadius,u32 cirSteps,u32 orbitSteps,const video::SColor& color) const;
			virtual IShap* createSphere(f32 radius,u32 hSteps,u32 vSteps) const;
			virtual IShap* createCube(f32 width,f32 height,f32 depth,const video::SColor& color) const;
			virtual IShap* createXYRectangle(s32 x0,s32 y0,s32 x1,s32 y1,f32 u0,f32 v0,f32 u1,f32 v1,const video::SColor& color) const;
			virtual IShap* createXYRectangle(s32 x0,s32 y0,s32 x1,s32 y1,f32 z,f32 u0,f32 v0,f32 u1,f32 v1,const video::SColor& color) const;
			virtual IShap* createXYRectangle2T(s32 x0,s32 y0,s32 x1,s32 y1,f32 u0,f32 v0,f32 u1,f32 v1,f32 s0,f32 t0,f32 s1,f32 t1,const video::SColor& color) const;

			virtual IUnit* createUnit(IShap* shap)const;
			virtual IEntity* createEntity(IUnit* unit)const;
		};
	}
}
#endif