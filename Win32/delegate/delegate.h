#ifndef __DELEGATE_H__
#define __DELEGATE_H__
// lrhnfs@gmail.com [2011/2/22 YMD] [12:58:39]
// 代码修改自MyGUI
// http://mygui.info/
// 能实现0-5个参数的单个委托或委托列表
// CDelegateX (单)
// CMultiDelegateX (多)
// X>=0 && X<=5 (X范围)
// CDelegateX cDelegate = newDelegate(&ClassIns, &Class::Method); (类委托)
// CDelegateX fDelegate = newDelegate(Method); (函数委托)

#include <typeinfo>
#include <list>
#include <cassert>


#define MYGUI_SUFFIX        0
#define MYGUI_TEMPLATE
#define MYGUI_TEMPLATE_PARAMS
#define MYGUI_TEMPLATE_ARGS
#define MYGUI_T_TEMPLATE_PARAMS         <typename T>
#define MYGUI_T_TEMPLATE_ARGS       <T>
#define MYGUI_PARAMS
#define MYGUI_ARGS
#define MYGUI_TYPENAME

#include "delegate_impl.h"

#define MYGUI_SUFFIX        1
#define MYGUI_TEMPLATE      template
#define MYGUI_TEMPLATE_PARAMS       <typename TP1>
#define MYGUI_TEMPLATE_ARGS     <TP1>
#define MYGUI_T_TEMPLATE_PARAMS         <typename T, typename TP1>
#define MYGUI_T_TEMPLATE_ARGS       <T, TP1>
#define MYGUI_PARAMS        TP1 p1
#define MYGUI_ARGS      p1
#define MYGUI_TYPENAME typename

#include "delegate_impl.h"

#define MYGUI_SUFFIX        2
#define MYGUI_TEMPLATE      template
#define MYGUI_TEMPLATE_PARAMS       <typename TP1, typename TP2>
#define MYGUI_TEMPLATE_ARGS         <TP1, TP2>
#define MYGUI_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2>
#define MYGUI_T_TEMPLATE_ARGS       <T, TP1, TP2>
#define MYGUI_PARAMS        TP1 p1, TP2 p2
#define MYGUI_ARGS      p1, p2
#define MYGUI_TYPENAME      typename

#include "delegate_impl.h"

#define MYGUI_SUFFIX        3
#define MYGUI_TEMPLATE      template
#define MYGUI_TEMPLATE_PARAMS       <typename TP1, typename TP2, typename TP3>
#define MYGUI_TEMPLATE_ARGS         <TP1, TP2, TP3>
#define MYGUI_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2, typename TP3>
#define MYGUI_T_TEMPLATE_ARGS       <T, TP1, TP2, TP3>
#define MYGUI_PARAMS        TP1 p1, TP2 p2, TP3 p3
#define MYGUI_ARGS      p1, p2, p3
#define MYGUI_TYPENAME      typename

#include "delegate_impl.h"

#define MYGUI_SUFFIX        4
#define MYGUI_TEMPLATE      template
#define MYGUI_TEMPLATE_PARAMS       <typename TP1, typename TP2, typename TP3, typename TP4>
#define MYGUI_TEMPLATE_ARGS         <TP1, TP2, TP3, TP4>
#define MYGUI_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2, typename TP3, typename TP4>
#define MYGUI_T_TEMPLATE_ARGS       <T, TP1, TP2, TP3, TP4>
#define MYGUI_PARAMS        TP1 p1, TP2 p2, TP3 p3, TP4 p4
#define MYGUI_ARGS      p1, p2, p3, p4
#define MYGUI_TYPENAME      typename

#include "delegate_impl.h"

#define MYGUI_SUFFIX        5
#define MYGUI_TEMPLATE      template
#define MYGUI_TEMPLATE_PARAMS       <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
#define MYGUI_TEMPLATE_ARGS         <TP1, TP2, TP3, TP4, TP5>
#define MYGUI_T_TEMPLATE_PARAMS         <typename T, typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
#define MYGUI_T_TEMPLATE_ARGS       <T, TP1, TP2, TP3, TP4, TP5>
#define MYGUI_PARAMS        TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5
#define MYGUI_ARGS      p1, p2, p3, p4, p5
#define MYGUI_TYPENAME      typename

#include "delegate_impl.h"


#endif // __DELEGATE_H__
