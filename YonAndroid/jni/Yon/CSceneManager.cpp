#include "CSceneManager.h"
#include "CGeometryFactory.h"
#include "CModel.h"
#include "COrthoCamera.h"
#include "CPerspCamera.h"
#include "CWindowOrthoCamera.h"
#include "CGeomipmapTerrain.h"

#include "ILogger.h"

namespace yon{
namespace scene{

	CSceneManager::CSceneManager()
		:m_geometryFactory(new CGeometryFactory()),
		m_pAnimatorFactory(animator::createAnimatorFactory()),
		m_activeCamera(NULL),m_renderingPass(ENUM_SCENE_PASS_NONE),m_cameraPosition(core::ORIGIN_VECTOR3DF),
		IModel(NULL){
			Logger->info(YON_LOG_SUCCEED_FORMAT,"Instance CSceneManager");
	}

	CSceneManager::~CSceneManager(){
		m_geometryFactory->drop();
		m_pAnimatorFactory->drop();

		for(u32 i=0;i<m_cameras.size();++i){
			m_cameras[i]->drop();
		}

		if (m_activeCamera)
			m_activeCamera->drop();
		m_activeCamera = NULL;

		Logger->info(YON_LOG_SUCCEED_FORMAT,"Release CSceneManager");
	}

	IModel* CSceneManager::addModel(IEntity* entity){
		CModel* model=new CModel(this,entity);
		addChild(model);
		model->drop();

		Logger->debug("CSceneManager::addModel size:%d\n",m_children.size());
		return model;
	}

	terrain::ITerrainModel* CSceneManager::addTerrainModel(IModel* parent,const core::vector3df& pos,
		const core::vector3df& rot,const core::vector3df& scale){
			if(parent==NULL)
				parent=this;
			terrain::ITerrainModel* model=new terrain::CGeomipmapTerrain(parent,pos,rot,scale);
			model->drop();
			return model;
	}

	camera::ICamera* CSceneManager::addCamera(camera::ENUM_CAMERA_TYPE cameraType,
		const core::vector3df& pos,const core::vector3df& up,
		const core::vector3df& lookat,bool makeActive){
			camera::ICamera* camera=NULL;
			switch(cameraType)
			{
			case camera::ENUM_CAMERA_TYPE_ORTHO:
				camera=new camera::COrthoCamera(pos,up,lookat);
				break;
			case camera::ENUM_CAMERA_TYPE_ORTHO_WINDOW:
				camera=new camera::CWindowOrthoCamera(pos,up,lookat);
				break;
			default:
				camera=new camera::CPerspCamera(pos,up,lookat);
			}
			m_cameras.push_back(camera);
			if(makeActive){
				setActiveCamera(camera);
			}
			Logger->debug("CSceneManager::addCamera size:%d\n",m_cameras.size());
			return camera;
	}
	void CSceneManager::setActiveCamera(camera::ICamera* camera){
		if(camera){
			camera->grab();
			camera->setNeedUpload();
		}
		if(m_activeCamera){
			m_activeCamera->drop();
		}
		m_activeCamera=camera;
	}

	bool CSceneManager::registerForRender(IModel* model,ENUM_SCENE_PASS pass){
		switch(pass)
		{
		case ENUM_SCENE_PASS_SOLID:
			if (!isCulled(model))
			{
				m_solids.push_back(model);
				return true;
			}
			break;
		case ENUM_SCENE_PASS_TRANSPARENT:
			if (!isCulled(model))
			{
				TransparentModelEntry t(model, m_cameraPosition);
				m_transparents.push_back(t);
				return true;
			}
			break;
		case ENUM_SCENE_PASS_EFFECT:
			if (!isCulled(model))
			{
				TransparentModelEntry t(model, m_cameraPosition);
				m_effects.push_back(t);
				return true;
			}
			break;
		case ENUM_SCENE_PASS_AUTOMATIC:
			if (!isCulled(model))
			{
				const u32 count=model->getMaterialCount();
				bool transparent=false;
				bool solid=false;
				for (u32 i=0; i<count; ++i)
				{
					if(isTransparent(model->getMaterial(i)->getMaterialType()))
						transparent=true;
					else
						solid=true;

					if(transparent&&solid)
						break;
				}
				if(transparent)
				{
					// register as transparent node
					TransparentModelEntry t(model, m_cameraPosition);
					m_transparents.push_back(t);
				}
				if(solid)
				{
					DefaultModelEntry d(model);
					m_solids.push_back(d);
				}
				return true;
			}
			break;
		case ENUM_SCENE_PASS_NONE: //ignore
			break;
		}
		return false;
	}

	void CSceneManager::onRegisterForRender(ISceneManager* manager){
		if (m_bVisible)
		{
			core::list<IModel*>::Iterator it = m_children.begin();
			for (; it != m_children.end(); ++it)
				(*it)->onRegisterForRender(manager);
			//Logger->debug("CSceneManager::onRegisterForRender:%d\r\n",m_children.size());
		}
	}

	void CSceneManager::render(video::IVideoDriver* driver){
		YON_DEBUG_BREAK_IF(m_activeCamera==NULL);

		// do animations and other stuff.
		//onAnimate(time);
		u32 i;

		m_activeCamera->render(driver);
		m_cameraPosition=m_activeCamera->getAbsolutePosition();

		//core::list<IModel*>::Iterator it = m_children.begin();
		//for (; it != m_children.end(); ++it)
		//{
		//	(*it)->render(driver);
		//}

		// let all nodes register themselves
		onRegisterForRender(this);


		// render default objects
		{
			m_renderingPass=ENUM_SCENE_PASS_SOLID;

			m_solids.sort(); // sort by textures

			for (i=0; i<m_solids.size(); ++i)
				m_solids[i].m_pModel->render(driver);

			m_solids.set_used(0);
		}

		//TODO render shadows

		// render transparent objects.
		{
			m_renderingPass=ENUM_SCENE_PASS_TRANSPARENT;

			m_transparents.sort(); // sort by distance from camera

			for (i=0; i<m_transparents.size(); ++i)
				m_transparents[i].m_pModel->render(driver);

			m_transparents.set_used(0);
		}

		// render transparent effect objects.
		{
			m_renderingPass=ENUM_SCENE_PASS_EFFECT;

			m_effects.sort(); // sort by distance from camera

			for (i=0; i<m_effects.size(); ++i)
				m_effects[i].m_pModel->render(driver);

			m_effects.set_used(0);
		}

		m_renderingPass=ENUM_SCENE_PASS_NONE;

	}

	void CSceneManager::onResize(const core::dimension2du& size){
		for(u32 i=0;i<m_cameras.size();++i){
			m_cameras[i]->onResize(size);
		}
	}

	IGeometryFactory* CSceneManager::getGeometryFactory() const{
		return m_geometryFactory;
	}

	animator::IAnimatorFactory* CSceneManager::getAnimatorFactory() const{
		return m_pAnimatorFactory;
	}

	bool CSceneManager::postEventFromUser(const event::SEvent& evt){
		//TODO
		//Logger->debug("%d,%d,%d,%d\n",evt.type,evt.mouseInput.type,evt.mouseInput.x,evt.mouseInput.y);
		return false;
	}

	ISceneManager* createSceneManager(){
		return new CSceneManager();
	}
}//scene
}//yon