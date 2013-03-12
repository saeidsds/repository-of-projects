#include "framework.h"

SYonEngineParameters params;
IYonEngine* engine=NULL;
IVideoDriver* videoDriver=NULL;
IAudioDriver* audioDriver=NULL;
ISceneManager* sceneMgr=NULL;
IGraphicsAdapter* gfAdapter=NULL;
IFileSystem* fs=NULL;
ICamera* pCamera=NULL;
ILogger* logger=NULL;

ISceneNode* cubeModel=NULL;
ISceneNode* planeModel=NULL;
ISceneNode* teapotModel=NULL;
video::ITexture* rtt=NULL;
f32 factor=1.1f;

ISound* sound1=NULL;
ISound* sound2=NULL;

void swap(){
	if(sound1)
	{
		if(sound1->isPaused())
			sound1->play();
		else
			sound1->pause();
	}

	if(sound2)
	{
		if(sound2->isPaused())
			sound2->play();
		else
			sound2->pause();
	}
}

class MyEventReceiver : public IEventReceiver{
public:
	virtual bool onEvent(const SEvent& evt){
		switch(evt.type)
		{
		case event::ENUM_EVENT_TYPE_MOUSE:
			switch(evt.mouseInput.type)
			{
			case event::ENUM_MOUSE_INPUT_TYPE_LDOWN:
				logger->debug("[LP]%d,%d\n",evt.mouseInput.x,evt.mouseInput.y);
				swap();
				return true;
			case event::ENUM_MOUSE_INPUT_TYPE_LUP:
				logger->debug("[LR]%d,%d\n",evt.mouseInput.x,evt.mouseInput.y);
				return true;
			}
			break;
		case event::ENUM_EVENT_TYPE_TOUCH:
			switch(evt.touchInput.type)
			{
			case event::ENUM_TOUCH_INPUT_TYPE_DOWN:
				swap();
				//logger->debug("[P]%.2f,%.2f\n",evt.touchInput.x,evt.touchInput.y);
				return true;
			case event::ENUM_TOUCH_INPUT_TYPE_UP:
				//logger->debug("[R]%.2f,%.2f\n",evt.touchInput.x,evt.touchInput.y);
				return true;
			}
			break;
		case event::ENUM_EVENT_TYPE_SYSTEM:
			switch(evt.systemInput.type)
			{
			case event::ENUM_SYSTEM_INPUT_TYPE_DOZE:
				YON_INFO("ENUM_SYSTEM_INPUT_TYPE_DOZE\r\n");
				return true;
			case event::ENUM_SYSTEM_INPUT_TYPE_WAKE:
				YON_INFO("ENUM_SYSTEM_INPUT_TYPE_WAKE\r\n");
				return true;
			}
			break;
		default:
			YON_WARN(YON_LOG_WARN_FORMAT,"unexpect event type:%d",evt.type);
		}
		return false;
	}
};

bool init(void *pJNIEnv,const c8* appPath,const c8* resPath,u32 width,u32 height){
	params.windowSize.w=width;
	params.windowSize.h=height;
	params.pJNIEnv=pJNIEnv;
	params.fpsLimit=0;
	params.resourcesPath=resPath;
	params.pEventReceiver=new MyEventReceiver();
	engine=CreateEngine(params);
	videoDriver=engine->getVideoDriver();
	audioDriver=engine->getAudioDriver();
	sceneMgr=engine->getSceneManager();
	gfAdapter=engine->getGraphicsAdapter();
	const IGeometryFactory* geometryFty=sceneMgr->getGeometryFactory();
	fs=engine->getFileSystem();
	pCamera=sceneMgr->addCamera(ENUM_CAMERA_TYPE_ORTHO,NULL,core::vector3df(0,0,300));
	logger=Logger;

#ifdef YON_COMPILE_WITH_WIN32
	fs->addWorkingDirectory("../media/");
#elif defined(YON_COMPILE_WITH_ANDROID)
	fs->addWorkingDirectory("media/");
#endif

	//PROFILE_REGISTER_FRAME();
	//PROFILE_START_CALL(PROFILE_ID_1,Driver->begin);
	//sound1=audioDriver->getSound("bg.ogg");
	sound2=audioDriver->getSound("xyg.ogg");
	//sound2=audioDriver->getSound("helloworld.wav");
	//audioDriver->grabSound(sound);
	//audioDriver->dropSound(sound);
	//sound1->setLooping(true);
	//sound2->setLooping(false);
	//sound1->play();
	//sound1->setGain(0.2f);

	sound2->play();
	sound2->setGain(0.5f);
	//sound=audioDriver->getSound("helloworld.wav");
	//sound->play();
	//PROFILE_END_CALL(PROFILE_ID_1);
	//PROFILE_REGISTER_FRAME();

	return true;
}
void resize(u32 width,u32 height){
	engine->onResize(width,height);
}
void drawFrame(){

	videoDriver->begin();

	sceneMgr->render(videoDriver);

	Logger->drawString(videoDriver,core::stringc("FPS:%d",videoDriver->getFPS()),core::ORIGIN_POSITION2DI,COLOR_GREEN);

	videoDriver->end();
}
void destroy(){
	PROFILE_REPORT();
	engine->drop();
	delete params.pEventReceiver;
}

IYonEngine* getEngine(){
	return engine;
}