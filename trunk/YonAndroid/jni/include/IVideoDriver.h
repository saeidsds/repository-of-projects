#ifndef _YON_VIDEO_IVIDEODRIVER_H_
#define _YON_VIDEO_IVIDEODRIVER_H_

#include "IReferencable.h"
#include "dimension2d.h"
#include "rect.h"
#include "matrix4.h"
#include "IUnit.h"
#include "IFileSystem.h"
#include "ITexture.h"
#include "IImageLoader.h"
#include "IMaterial.h"
#include "SColor.h"

namespace yon{

	namespace scene{
		class ISceneManager;
		ISceneManager* createSceneManager();
	}
	namespace io
	{
		IFileSystem* createFileSystem();
	}

	namespace video{

		IImageLoader* createImageLoaderPNG();

		enum ENUM_TRANSFORM{
			ENUM_TRANSFORM_VIEW = 0,		//视图空间矩阵
			ENUM_TRANSFORM_WORLD,			//世界空间矩阵
			ENUM_TRANSFORM_PROJECTION,		//投影空间矩阵
			ENUM_TRANSFORM_COUNT
		};

		/*
		#define GL_POINTS                         0x0000
		#define GL_LINES                          0x0001
		#define GL_LINE_LOOP                      0x0002
		#define GL_LINE_STRIP                     0x0003
		#define GL_TRIANGLES                      0x0004
		#define GL_TRIANGLE_STRIP                 0x0005
		#define GL_TRIANGLE_FAN                   0x0006
		*/
		enum ENUM_PRIMITIVE_TYPE{
			ENUM_PRIMITIVE_TYPE_TRIANGLES = 0x0004,
			ENUM_PRIMITIVE_TYPE_COUNT = 1
		};

		/*
		#define GL_BYTE                           0x1400
		#define GL_UNSIGNED_BYTE                  0x1401
		#define GL_SHORT                          0x1402
		#define GL_UNSIGNED_SHORT                 0x1403
		#define GL_FLOAT                          0x1406
		#define GL_FIXED                          0x140C
		*/
		enum ENUM_INDEX_TYPE{
			ENUM_INDEX_TYPE_8BIT = 0x1401,
			ENUM_INDEX_TYPE_16BIT = 0x1403,
			ENUM_INDEX_TYPE_COUNT = 2
		};

		//视频驱动器接口
		class IVideoDriver:public virtual core::IReferencable{
		protected:
			enum ENUM_RENDER_MODE{
				ENUM_RENDER_MODE_NONE = 0,
				ENUM_RENDER_MODE_2D,
				ENUM_RENDER_MODE_3D,
				ENUM_RENDER_MODE_COUNT
			};
			ENUM_RENDER_MODE m_renderMode;
			io::IFileSystem* m_pFileSystem;
			virtual video::ITexture* createDeviceDependentTexture(IImage* image, const io::path& name) = 0;
		public:
			IVideoDriver(io::IFileSystem* fs)
				:m_renderMode(ENUM_RENDER_MODE_NONE),m_pFileSystem(fs){
					if(m_pFileSystem)
						m_pFileSystem->grab();
			}
			virtual ~IVideoDriver(){
				if(m_pFileSystem)
					m_pFileSystem->drop();
			};
			virtual void begin(bool zBuffer=true,video::SColor c=video::SColor(0x000000FF)) = 0;
			virtual void end() = 0;
			virtual void setViewPort(const core::recti& r) = 0;
			virtual const core::dimension2du& getCurrentRenderTargetSize() const = 0;
			virtual void onResize(const core::dimension2du& size) = 0;

			virtual IImage* createImageFromFile(const io::path& filename) = 0;
			virtual IImage* createImageFromFile(io::IReadFile* file) =0;

			virtual ITexture* getTexture(const io::path& filename) = 0;
			virtual video::ITexture* findTexture(const io::path& filename) = 0;

			virtual void setTransform(ENUM_TRANSFORM transform, const core::matrix4f& mat) =0;
			virtual const core::matrix4f& getTransform(ENUM_TRANSFORM transform) const =0;

			virtual void setMaterial(IMaterial* material) = 0;

			virtual void drawUnit(scene::IUnit* unit) = 0;
			virtual void draw2DImage(const video::ITexture* texture, const core::position2di& destPos,
				const core::recti& sourceRect, const core::recti* clipRect =NULL,
				video::SColor color=video::COLOR_WHITE, bool useAlphaChannelOfTexture=false) =0;
			virtual void drawVertexPrimitiveList(const void* vertices, u32 vertexCount,
				const void* indexList, u32 primCount,
				ENUM_PRIMITIVE_TYPE pType=ENUM_PRIMITIVE_TYPE_TRIANGLES,
				ENUM_INDEX_TYPE iType=ENUM_INDEX_TYPE_16BIT) =0;
			//virtual u32 getFPS() const = 0;
		};
	}
}
#endif