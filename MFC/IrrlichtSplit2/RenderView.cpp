// RenderView.cpp : 实现文件
//

#include "stdafx.h"
#include "IrrlichtSplit2.h"
#include "RenderView.h"


IMPLEMENT_DYNCREATE(CRenderView, CFormView)

CRenderView::CRenderView()
	: CFormView(CRenderView::IDD)
{
	TRACE("Initiate CRenderView\r\n");
}

CRenderView::~CRenderView()
{
}

void CRenderView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRenderView, CFormView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


#ifdef _DEBUG
void CRenderView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRenderView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CRenderView::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==WM_RENDER_FRAME)
	{
		//更新窗口整个客户区域，同时重画时不擦除背景。
		InvalidateRect(NULL,FALSE);
	}
	CFormView::OnTimer(nIDEvent);
}

BOOL CRenderView::PreCreateWindow(CREATESTRUCT& cs)
{
	TRACE("PreCreateWindow\r\n");
	//WS_CLIPCHILDREN：当在父窗口内绘图时，排除子窗口区域。在创建父窗口时使用这个风格。
	//WS_CLIPSIBLINGS：排除子窗口之间的相对区域，也就是说，当一个特定的窗口接收到WM_PAINT消息时，
	//WS_CLIPSIBLINGS风格将所有层叠窗口排除在绘图之外，只重绘指定的子窗口。
	//如果未指定WS_CLILPSIBLINGS风格，并且子窗口是层叠的，则在重绘子窗口的客户区时，就会重绘邻近的子窗口。
	cs.style |=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	return CFormView::PreCreateWindow(cs);
}

int CRenderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TRACE("OnCreate\r\n");
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitIrrlicht();
	SetTimer(WM_RENDER_FRAME,RENDER_INTERVAL,NULL);// n 替换为你需要定时的周期，单位毫秒。

	return 0;
}

void CRenderView::OnSize(UINT nType, int cx, int cy)
{
	TRACE("OnSize:%d,%d\r\n",cx,cy);
	CFormView::OnSize(nType, cx, cy);
	ResizeIrrlicht(cx,cy);
}

BOOL CRenderView::OnEraseBkgnd(CDC* pDC)
{
	//不重绘背景
	return TRUE;
}


void CRenderView::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	DrawIrrlicht();
}



void CRenderView::OnDestroy()
{
	TRACE("OnDestroy\r\n");
	CFormView::OnDestroy();
	DestroyIrrlicht();
}



void CRenderView::OnMouseMove(UINT nFlags, CPoint point)
{
	int x=point.x;
	int y=point.y;

	SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
	irrevent.MouseInput.X = x;
	irrevent.MouseInput.Y = y;
    irrevent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
	irrevent.MouseInput.ButtonStates ^= irr::EMBSM_LEFT;  
	//TRACE("post move event\r\n");
    device->postEventFromUser(irrevent);

	CFormView::OnMouseMove(nFlags, point);
}

BOOL CRenderView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int x=pt.x;
	int y=pt.y;

	SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
	irrevent.MouseInput.X = x;
	irrevent.MouseInput.Y = y;
	irrevent.MouseInput.Wheel=(short)(zDelta/120);
    irrevent.MouseInput.ButtonStates = irr::EMBSM_MIDDLE;
    irrevent.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
	TRACE("post wheel event:%d\r\n",zDelta);
    device->postEventFromUser(irrevent);

	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}

void CRenderView::OnLButtonDown(UINT nFlags, CPoint point)
{
	int x=point.x;
	int y=point.y;

	SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
	irrevent.MouseInput.X = x;
	irrevent.MouseInput.Y = y;
    irrevent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN; 
	irrevent.MouseInput.ButtonStates ^= irr::EMBSM_LEFT;
	//TRACE("post left press event\r\n");
    device->postEventFromUser(irrevent);

	CFormView::OnLButtonDown(nFlags, point);
}

void CRenderView::OnLButtonUp(UINT nFlags, CPoint point)
{
	int x=point.x;
	int y=point.y;

	SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
	irrevent.MouseInput.X = x;
	irrevent.MouseInput.Y = y;
    irrevent.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
	irrevent.MouseInput.ButtonStates ^= irr::EMBSM_LEFT;  
	//TRACE("post left release event\r\n");
    device->postEventFromUser(irrevent);

	mouseReleased(x,y);

	CFormView::OnLButtonUp(nFlags, point);
}

void CRenderView::OnRButtonDown(UINT nFlags, CPoint point)
{
	int x=point.x;
	int y=point.y;

	SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
	irrevent.MouseInput.X = x;
	irrevent.MouseInput.Y = y;
    irrevent.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN; 
	irrevent.MouseInput.ButtonStates = irr::EMBSM_RIGHT;
	//TRACE("post right press event\r\n");
    device->postEventFromUser(irrevent);

	CFormView::OnRButtonDown(nFlags, point);
}

void CRenderView::OnRButtonUp(UINT nFlags, CPoint point)
{
	int x=point.x;
	int y=point.y;

	SEvent irrevent;
    irrevent.EventType = irr::EET_MOUSE_INPUT_EVENT;
	irrevent.MouseInput.X = x;
	irrevent.MouseInput.Y = y;
    irrevent.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
	irrevent.MouseInput.ButtonStates = irr::EMBSM_RIGHT;
	//TRACE("post right release event\r\n");
    device->postEventFromUser(irrevent);

	CFormView::OnRButtonUp(nFlags, point);
}

void CRenderView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	irr::EKEY_CODE key;
	switch(nChar)
	{
	case 'W':
		key = irr::KEY_UP;
		break;
	case 'S':
		key = irr::KEY_DOWN;
		break;
	case 'A':
		key = irr::KEY_LEFT;
		break;
	case 'D':
		key = irr::KEY_RIGHT;
		break;
	default:
		return;
	}
	SEvent irrevent;
	irrevent.KeyInput.Key = key;
	irrevent.EventType = irr::EET_KEY_INPUT_EVENT;
	irrevent.KeyInput.Char = nChar;
	irrevent.KeyInput.PressedDown = true;
	device->postEventFromUser(irrevent);
	//TRACE("post key down event\r\n");

	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRenderView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	irr::EKEY_CODE key;
	switch(nChar)
	{
	case 'W':
		key = irr::KEY_UP;
		break;
	case 'S':
		key = irr::KEY_DOWN;
		break;
	case 'A':
		key = irr::KEY_LEFT;
		break;
	case 'D':
		key = irr::KEY_RIGHT;
		break;
	default:
		return;
	}
	SEvent irrevent;
	irrevent.KeyInput.Key = key;
	irrevent.EventType = irr::EET_KEY_INPUT_EVENT;
	irrevent.KeyInput.Char = nChar;
	irrevent.KeyInput.PressedDown = false;
	device->postEventFromUser(irrevent);
	//TRACE("post key up event\r\n");

	CFormView::OnKeyUp(nChar, nRepCnt, nFlags);
}

/**
 * 初始化编辑体

void CRenderView::initEditing(void)
{
	ISceneNode * arrowX = smgr->addAnimatedMeshSceneNode(smgr->addArrowMesh("ArrowX",
				video::SColor(255, 255, 0, 0),
				video::SColor(255, 255, 0, 0),
				8,8,
				2.f, 1.3f,
				0.1f, 0.6f
				)); 
	arrowX->setMaterialFlag(video::EMF_LIGHTING, false); 
	arrowX->setScale(vector3df(5, 15, 5));
	arrowX->setRotation(vector3df(90,0,0));
	//arrowX->setMaterialFlag(video::EMF_ZBUFFER, false);

	ISceneNode * arrowY = smgr->addAnimatedMeshSceneNode(smgr->addArrowMesh("ArrowY",
				video::SColor(255, 0, 255, 0),
				video::SColor(255, 0, 255, 0),
				8,8,
				2.f, 1.3f,
				0.1f, 0.6f
				)); 
	arrowY->setMaterialFlag(video::EMF_LIGHTING, false); 
	arrowY->setScale(vector3df(5, 15, 5));
	//arrowY->setMaterialFlag(video::EMF_ZBUFFER, false);

	ISceneNode * arrowZ = smgr->addAnimatedMeshSceneNode(smgr->addArrowMesh("ArrowZ",
				video::SColor(255, 0, 0, 255),
				video::SColor(255, 0, 0, 255),
				8,8,
				2.f, 1.3f,
				0.1f, 0.6f
				)); 
	arrowZ->setMaterialFlag(video::EMF_LIGHTING, false); 
	arrowZ->setScale(vector3df(5, 15, 5));
	arrowZ->setRotation(vector3df(0,0,-90));
	//arrowZ->setMaterialFlag(video::EMF_ZBUFFER, false);

	this->m_editing.arrowX=arrowX;
	this->m_editing.arrowY=arrowY;
	this->m_editing.arrowZ=arrowZ;

	this->m_editing.setArrowVisible(false);
}
 */

/**
 * 初始化Irrlicht上下文
 */
void CRenderView::InitIrrlicht(void)
{
	//获取本窗口对象（CWnd的派生对象）指针的句柄
	HWND hWnd=this->GetSafeHwnd();
	if(hWnd==NULL)
	{
		AfxMessageBox(TEXT("获取渲染区窗口对象时HWND为空"));
		return;
	}

	//定义文档指针
	pDoc=(CIrrlichtSplitDoc*)this->GetDocument();

	//初始化Irrlicht设备
	SIrrlichtCreationParameters param;
	param.WindowId = reinterpret_cast<void*>(hWnd);
	param.DriverType = irr::video::EDT_OPENGL;
	this->device = irr::createDeviceEx(param);
	this->env = device->getGUIEnvironment();
	this->driver = device->getVideoDriver();
	this->smgr = device->getSceneManager();

	/*this->collMan = smgr->getSceneCollisionManager();

	//添加Irrlicht Logo
	this->env->addImage(driver->getTexture("./media/irrlichtlogo2.png"),core::position2d<s32>(10,10));

	//初始化编辑体
	//this->initEditing();

	//添加妖精模型
	scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("./media/faerie.md2"),0, IDFlag_IsPickable|IDFlag_IsHighlightable);
	node->setPosition(core::vector3df(0,0,-20));
	node->updateAbsolutePosition();
	node->setMD2Animation(scene::EMAT_POINT);
	node->setAnimationSpeed(20.f);
	video::SMaterial material;
	material.setTexture(0, driver->getTexture("./media/faerie2.bmp"));
	material.Lighting = false;
	material.NormalizeNormals = true;
	node->getMaterial(0) = material;

	ITriangleSelector* selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();*/

	//添加高度图
	/*terrain = smgr->addTerrainSceneNode("./media/terrain-heightmap2.bmp",
			0,					// parent node
			-1,					// node id
			core::vector3df(0.f, 0.f, 0.f),		// position
			core::vector3df(0.f, 0.f, 0.f),		// rotation
			core::vector3df(40.f, 4.4f, 40.f),	// scale
			video::SColor ( 255, 255, 255, 255 ),	// vertexColor
			5,					// maxLOD
			scene::ETPS_17,		// patchSize
			4					// smoothFactor
			);
	terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0,driver->getTexture("./media/grass.bmp"));
	terrain->setMaterialTexture(1,driver->getTexture("./media/grass-detail.bmp"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
	terrain->scaleTexture(20.0f, 20.0f);

	


	//添加编辑型摄相机
	//camera = new EditorCamera(device,smgr->getRootSceneNode(),smgr,-1,-100.0f,50.0f,50.0f);
	//camera->grab();
	camera = smgr->addCameraSceneNodeMaya();

	camera->setPosition(core::vector3df(0,0,100));
	camera->setTarget(core::vector3df(0,0,0));
	camera->setFarValue(42000.0f);*/
}

/**
 * 调整Irrlicht渲染区大小
 */
void CRenderView::ResizeIrrlicht(int cx, int cy)
{
	/*irr::core::dimension2d<unsigned int> size;
	size.Width = cx;
	size.Height = cy;
	//Event handler for resize events. Only used by the engine internally. 
	//Used to notify the driver that the window was resized. Usually, there is no need to call this method.
	driver->OnResize(size);
	//调用视口长宽比
	camera->setAspectRatio((float)cx/cy);*/
}

/**
 * 渲染Irrlicht各组件
 */
void CRenderView::DrawIrrlicht(void)
{
	/*if(pDoc->HasUpdated())
	{
		//TODO 更新数据
	}

	device->run();

	driver->beginScene(true, true, video::SColor(255,23,45,68));
	//绘制射线
	//driver->draw3DLine(ray.start,ray.end,video::SColor(255,0,0,255));
	
	smgr->drawAll();
	env->drawAll();

	/*
	if(this->m_editing.exist())
	{
		m_editing.update();
		driver->draw3DBox(m_editing.box);
	}
	driver->endScene();*/
}

/**
 * 销毁Irrlicht上下文及各组件
 */
void CRenderView::DestroyIrrlicht(void)
{
	device->drop();
	//camera->drop();
	TRACE("has drop device\r\n");
}
void CRenderView::mouseReleased(int x,int y)
{
	/*position2d<s32> pos;
	pos.X=x;
	pos.Y=y;
	ray = collMan->getRayFromScreenCoordinates(pos,camera);
	TRACE("ray:{%.2f,%.2f,%.2f},{%.2f,%.2f,%.2f}",ray.start.X,ray.start.Y,ray.start.Z,
					ray.end.X,ray.end.Y,ray.end.Z);
	ISceneNode* node =collMan->getSceneNodeAndCollisionPointFromRay(
					ray,
					intersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					IDFlag_IsPickable, // This ensures that only nodes that we have
									// set up to be pickable are considered
					0);*/
	//this->m_editing.setNode(node);
}