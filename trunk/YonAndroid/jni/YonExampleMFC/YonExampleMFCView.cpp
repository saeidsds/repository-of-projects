// YonExampleMFCView.cpp : CYonExampleMFCView 类的实现
//

#include "stdafx.h"
#include "YonExampleMFC.h"

#include "YonExampleMFCDoc.h"
#include "YonExampleMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYonExampleMFCView

IMPLEMENT_DYNCREATE(CYonExampleMFCView, CFormView)

BEGIN_MESSAGE_MAP(CYonExampleMFCView, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CYonExampleMFCView 构造/析构

CYonExampleMFCView::CYonExampleMFCView()
	: CFormView(CYonExampleMFCView::IDD)
{
	// TODO: 在此处添加构造代码

}

CYonExampleMFCView::~CYonExampleMFCView()
{
}

void CYonExampleMFCView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CYonExampleMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CYonExampleMFCView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CYonExampleMFCView 诊断

#ifdef _DEBUG
void CYonExampleMFCView::AssertValid() const
{
	CFormView::AssertValid();
}

void CYonExampleMFCView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CYonExampleMFCDoc* CYonExampleMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYonExampleMFCDoc)));
	return (CYonExampleMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CYonExampleMFCView 消息处理程序

int CYonExampleMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	HWND hWnd=this->GetSafeHwnd();
	if(hWnd==NULL)
	{
		AfxMessageBox(TEXT("获取渲染区窗口对象时HWND为空"));
		return -1;
	}

	SYonEngineParameters params;
	params.windowId=hWnd;
	m_hWnd=hWnd;
	engine=CreateEngine(params);

	driver=engine->getVideoDriver();
	sceneMgr=engine->getSceneManager();
	fs=engine->getFileSystem();

	initEGL(hWnd);

	//geometryFty=sceneMgr->getGeometryFactory();

	//camera=sceneMgr->addCamera(core::vector3df(0,0,300));
	//animatorFty=sceneMgr->getAnimatorFactory();

	IMaterial* material;
	IShap *shap,*shap1,*shap2;
	IUnit* unit;
	scene::IEntity* entity;

	/*shap=geometryFty->createSphere(80,64,64);
	unit=geometryFty->createUnit(shap);
	unit->setHardwareBufferUsageType(video::ENUM_HARDWARDBUFFER_USAGE_TYPE_STATIC);
	entity=geometryFty->createEntity(unit);
	sphereModel=sceneMgr->addModel(entity);
	material=sphereModel->getMaterial(0);
	material->setMaterialType(ENUM_MATERIAL_TYPE_SOLID);
	//material->setPolygonMode(ENUM_POLYGON_MODE_LINE);
	sphereModel->setPosition(core::vector3df(100,100,0));
	material->setTexture(0,driver->getTexture("../media/earth.png"));
	shap->drop();
	unit->drop();
	entity->drop();*/

	/*shap=geometryFty->createCube(50,50,50);
	unit=geometryFty->createUnit(shap);
	entity=geometryFty->createEntity(unit);
	cubeModel=sceneMgr->addModel(entity);
	material=cubeModel->getMaterial(0);
	material->setMaterialType(ENUM_MATERIAL_TYPE_TRANSPARENT_BLEND_COLOR);
	cubeModel->setPosition(core::vector3df(50,50,200));
	material->setTexture(0,driver->getTexture("../media/test.png"));
	shap->drop();
	unit->drop();
	entity->drop();


	shap=geometryFty->createTorus(10,30,16,16,COLOR_BLUE);
	unit=geometryFty->createUnit(shap);
	unit->setHardwareBufferUsageType(video::ENUM_HARDWARDBUFFER_USAGE_TYPE_STATIC);
	entity=geometryFty->createEntity(unit);
	toruseModel=sceneMgr->addModel(entity);
	material=toruseModel->getMaterial(0);
	material->setMaterialType(ENUM_MATERIAL_TYPE_TRANSPARENT_BLEND_COLOR);
	material->setPolygonMode(ENUM_POLYGON_MODE_FILL);
	toruseModel->setPosition(core::vector3df(130,130,100));
	material->setTexture(0,driver->getTexture("../media/gunny.png"));
	shap->drop();
	unit->drop();
	entity->drop();

	shap=geometryFty->createXYRectangle2D(-25,-25,25,25);
	unit=geometryFty->createUnit(shap);
	unit->setHardwareBufferUsageType(video::ENUM_HARDWARDBUFFER_USAGE_TYPE_STATIC);
	entity=geometryFty->createEntity(unit);
	planeModel=sceneMgr->addModel(entity);
	material=planeModel->getMaterial(0);
	material->setMaterialType(ENUM_MATERIAL_TYPE_LIGHTEN);
	planeModel->setPosition(core::vector3df(150,120,0));
	material->setTexture(0,driver->getTexture("../media/aura.png"));
	shap->drop();
	unit->drop();
	entity->drop();

	shap=geometryFty->createXYRectangle2D2T(-25,-50,25,50,0,0,1,0.1f);
	unit=geometryFty->createUnit(shap);
	unit->setHardwareBufferUsageType(video::ENUM_HARDWARDBUFFER_USAGE_TYPE_DYNAMIC);
	entity=geometryFty->createEntity(unit);
	IModel* waterfallModel=sceneMgr->addModel(entity);
	material=waterfallModel->getMaterial(0);
	material->setMaterialType(ENUM_MATERIAL_TYPE_MASK);
	waterfallModel->setPosition(core::vector3df(90,100,120));
	material->setTexture(0,driver->getTexture("../media/waterfall.png"));
	material->setTexture(1,driver->getTexture("../media/mask.png"));
	shap->drop();
	unit->drop();
	entity->drop();

	SAnimatorParam aniParam;
	aniParam.type=ENUM_ANIMATOR_TYPE_UV;
	aniParam.animatorUV.unitIndex=0;
	aniParam.animatorUV.stage=0;
	IAnimator* uvAnimator=animatorFty->createAnimator(aniParam);
	waterfallModel->addAnimator(uvAnimator);
	uvAnimator->drop();*/


	SetTimer(WM_RENDER_FRAME,RENDER_INTERVAL,NULL);// n 替换为你需要定时的周期，单位毫秒。

	return 0;
}

void CYonExampleMFCView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	KillTimer(WM_RENDER_FRAME);
	Logger->debug("CYonExampleMFCView::OnDestroy\n");
	destroyEGL();
	engine->drop();
}
f32 factor=1.01f;
void CYonExampleMFCView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	if(engine->run())
	{
		/*const core::vector3df crot=cubeModel->getRotation();
		cubeModel->setRotation(core::vector3df(crot.x,crot.y+0.5f ,crot.z));

		//const core::vector3df srot=sphereModel->getRotation();
		//sphereModel->setRotation(core::vector3df(srot.x,srot.y-0.8f ,srot.z));

		const core::vector3df psca=planeModel->getScale();
		if(psca.x>4)
			factor=0.99f;
		else if(psca.x<2)
			factor=1.01f;
		planeModel->setScale(psca*factor);

		const core::vector3df trot=toruseModel->getRotation();
		toruseModel->setRotation(core::vector3df(trot.x+1.0f,trot.y,trot.z));*/

		//driver->begin(true,COLOR_BLACK);

		//sceneMgr->render(driver);

		//Logger->drawString(core::stringc("FPS:%d",driver->getFPS()),core::ORIGIN_POSITION2DI,COLOR_GREEN);

		//driver->end();
	}
}

BOOL CYonExampleMFCView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

void CYonExampleMFCView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	engine->onResize(cx,cy);
}

void CYonExampleMFCView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==WM_RENDER_FRAME)
	{
		//更新窗口整个客户区域，同时重画时不擦除背景。
		InvalidateRect(NULL,FALSE);
	}

	CFormView::OnTimer(nIDEvent);
}

bool CYonExampleMFCView::initEGL(const HWND& hwnd){

	EGLConfig config;
	EGLint num_configs;
	m_hDc = ::GetDC(hwnd);

	//First Step：Get EGLDisplay Object
	//The type and format of display_id are implementation-specific,
	//and it describes a specific display provided by the system EGL is running on.
	//For example, an EGL implementation under Microsoft Windows could define 
	//display_id to be a Windows Device Context.
	//If no display matching display_id is available,EGL_NO_DISPLAY is returned;
	//no error condition is raised in this case.
	m_eglDisplay = eglGetDisplay(m_hDc);
	/*if(m_eglDisplay == EGL_NO_DISPLAY)
	{
	m_eglDisplay = eglGetDisplay((NativeDisplayType) EGL_DEFAULT_DISPLAY);
	Logger->info("eglGetDisplay(EGL_DEFAULT_DISPLAY)\n");
	}*/

	//Second Step:Initialize EglDisplay Object
	//EGL_TRUE is returned on success, and major and minor are updated with
	// the major and minor version numbers of the EGL implementation.major 
	//and minor are not updated if they are specified as NULL.
	//EGL_FALSE is returned on failure and major and minor are not updated.
	//An EGL_BAD_DISPLAY error is generated if the dpy argument does not refer
	//to a valid EGLDisplay.An EGL_NOT_INITIALIZED error is generated if EGL cannnot be 
	//initialized for an otherwise valid dpy.
	//Initializing an already-initialized display is allowed,but the only effect of such 
	//a call is to return EGL_TRUE and update the EGL version numbers.
	EGLint majorVersion, minorVersion;
	if (!eglInitialize( m_eglDisplay, &majorVersion, &minorVersion ) )
	{
		//MessageBox(NULL,TEXT("Could not initialize OpenGL-ES1 display."),TEXT("Error"),MB_OK);
		Logger->info(YON_LOG_FAILED_FORMAT,"Initialize EglDisplay Object");
		return false;
	}
	else
	{
		Logger->info("EglDisplay initialized. Egl version %d.%d\n", majorVersion, minorVersion);
	}

	//EGL_RED_SIZE: bits of red in the color buffer
	//EGL_GREEN_SIZE: ...
	//EGL_BLUE_SIZE: ...
	//EGL_ALPHA_SIZE: ...
	//EGL_BUFFER_SIZE: total color component bits in the color buffer
	//EGL_SURFACE_TYPE: a mask indicating capabilities of surfaces that
	//				can be created with the corresponding EGLConfig(Default:EGL_WINDOW_BIT)
	//EGL_DEPTH_SIZE: bits of Z in the depth buffer
	//EGL_STENCIL_SIZE: bits of Stencil in the stencil buffer
	//EGL_SAMPLE_BUFFERS: number of multisample buffers
	//EGL_RENDERABLE_TYPE: a mask indicating which client APIs can render into a surface
	//				created with respect to and EGLConfig.
	//Creation of a client API context based on an EGLConfig will fail unless the EGLConfig's
	//EGL_RENDERABLE_TYPE attribute include the bit corresponding to that API and version.
	//				(Default:EGL_OPENGL_ES_BIT)
	EGLint attribs[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 5,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, 1,
		EGL_BUFFER_SIZE, 16,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_DEPTH_SIZE, 16,
		EGL_STENCIL_SIZE, false,
		EGL_SAMPLE_BUFFERS, 0,
		EGL_SAMPLES, 0,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		EGL_NONE, 0
	};

	//Third Step: Choose EGLConfig
	//API: EGLBoolean eglChooseConfig(EGLDisplay dpy,const EGLint *attrib_list,
	//			EGLConfig* configs,EGLint config_size, EGLint *num_config);
	//If no EGLConfig matching the attribute list exists, then the call
	//succeeds,but num_configs is set to 0.
	//If more than one matching EGLConfig is found,then a list of EGLConfigs is returned.
	//In most cases we just want the first config that meets all criteria, so we limit the
	//number of configs returned to 1.
	if (!eglChooseConfig(m_eglDisplay, attribs, &config, 1, &num_configs))
	{
		//MessageBox(NULL,TEXT("Could not get config for OpenGL-ES1 display."),TEXT("Error"),MB_OK);
		Logger->info(YON_LOG_FAILED_FORMAT,"Choose EGLConfig");
		return false;
	}

	//Fourth Step: Create EGLSurface
	//EGLSurface eglCreateWindowSurface(EGLDisplay dpy,EGLConfig config,
	//			EGLNativeWindowType win,const EGLint *attrib_list)
	//eglCreateWindowSurface creates an onscreen EGLSurface and returns a handle to it.
	//Any EGL context created with a compatible EGLConfig can be used to render into this
	//surface.
	//when the attrib_list is NULL,all attributes use default value as below:
	//EGL_RENDER_BUFFER: EGL_BACK_BUFFER
	//On failure eglCrateWindowSurface returns EGL_NO_SURFACE
	//Use eglMakeCurrent to attach an EGL rendering context to the surface
	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, config, hwnd, NULL);
	if (EGL_NO_SURFACE==m_eglSurface)
		//why?
		//Through platform specific functions we need to create a window that we can
		//use for OpenGL ES output.If there is no window system win should remain 0.
		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, config, NULL, NULL);
	if (EGL_NO_SURFACE==m_eglSurface)
	{
		//MessageBox(NULL,TEXT("Could not create surface for OpenGL-ES1 display."),TEXT("Error"),MB_OK);
		Logger->info(YON_LOG_FAILED_FORMAT,"Create EGLSurface");
		return false;
	}

	//eglBindAPI(EGL_OPENGL_ES_API);

	//The list is terminated with EGL_NONE.
	//If an attribute is not specified in eglAttributes,then the default value is used.
	//If EGL_DONT_CARE is specified as an attribute value,then the attribute will not
	//be checked.
	//EGL_DONT_CARE may be specified for all attributes except EGL_LEVEL.
	EGLint eglAttributes[] = {
		EGL_CONTEXT_CLIENT_VERSION, 1,
		EGL_NONE
	};

	//Fifth Step: Create EGLContext
	//EGL has to create a context for OpenGL ES.Our OpenGL ES resources like textures will only be valid inside this context(or shared contexs).
	//API: EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
	//If eglCreateContext succeeds,it initializes the context to the initial state defined for the current
	//rendering API, and returns a handle to it.The context can be used to render to any compatible EGLSurface.
	//On failure eglCreateContext returns EGL_NO_CONTEXT.If the current rendering api is EGL_NONE,then an EGL_BAD_MATCH error is
	//generated(this situation can only arise in an implementation which does not support OpenGL ES,and prior to the first call to
	//eglBindAPI).
	//attrib_list specifies a list of attributes for the context.The list has the same structure as described for eglChooseConfig.
	//The only attribute that can be specified in attrib_list is EGL_CONTEXT_CLIENT_VERSION, and this attribute may only be
	//specified when creating a OpenGL ES context
	//EGL_CONTEXT_CLIENT_VERSION determines which version of an OpenGL ES context to create.An attribute value of 1 specifies creation
	//of an OpenGL ES 1.x context.An attribute value of 2 specifies creation of an OpenGL ES 2.x context.(Default:1)
	m_eglContext = eglCreateContext(m_eglDisplay, config, EGL_NO_CONTEXT, eglAttributes);
	//m_eglContext = eglCreateContext(m_eglDisplay, config, EGL_NO_CONTEXT, NULL);

	//TODO check error

	//Sixth Step: Bind Contexts and Drawables
	//API: EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
	//eglMakeCurrent binds ctx to the current rendering thread and to the draw and read surfaces
	//For an OpenGL and OpenGL ES context,draw is used for all operations except for any pixel data read
	//back or copied,which is taken from the frame buffer values of read.
	//eglMakeCurrent returns EGL_FALSE on failure.
	if(eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext)==EGL_FALSE){
		Logger->info(YON_LOG_FAILED_FORMAT,"Bind Contexts and Drawables");
		return false;
	}
	return true;
}

void CYonExampleMFCView::destroyEGL(){
	//Finial Step: Terminate OpenGL ES and destroy the window(if present).
	//eglTerminate takes care of destroying any context or surface created with this display,so we don't need to call
	//eglDestroySurface or eglDestroyContext here.
	//To release the current context without assigning a new one, set ctx to EGL_NO_CONTEXT and set draw and read to
	//EGL_NO_SURFACE.
	if(eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT)==EGL_TRUE){
		Logger->info(YON_LOG_SUCCEED_FORMAT,"Unbind GL contexts and surface");
	}else{
		Logger->info(YON_LOG_FAILED_FORMAT,"Unbind GL contexts and surface");
	}
	eglDestroyContext(m_eglDisplay, m_eglContext);
	eglDestroySurface(m_eglDisplay, m_eglSurface);

	//To release resources associated with use of EGL and client APIs on a display, call
	//EGLBoolean eglTerminate(EGLDisplay dpy);
	//Termination marks all EGL-specific resources,such as contexts and surfaces,associated with the specified display for
	//deletion.Handles to all such resources are invalid as soon as eglTerminate returns,but the dpy handle itself remains
	//valid.
	//eglTerminate returns EGL_TRUE on success.
	if(eglTerminate(m_eglDisplay)==EGL_TRUE){
		Logger->info(YON_LOG_SUCCEED_FORMAT,"Release all resources in EGL and display");
	}else{
		Logger->info(YON_LOG_FAILED_FORMAT,"Release all resources in EGL and display");
	}
	if (m_hDc&&::ReleaseDC((HWND)m_hWnd, m_hDc)){
		Logger->info(YON_LOG_SUCCEED_FORMAT,"Release DC");
	}else{
		Logger->info(YON_LOG_FAILED_FORMAT,"Release DC");
	}
}