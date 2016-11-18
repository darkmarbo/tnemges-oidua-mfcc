// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "AudioSegment.h"
#include "DlgProxy.h"
#include "AudioSegmentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAudioSegmentDlgAutoProxy

IMPLEMENT_DYNCREATE(CAudioSegmentDlgAutoProxy, CCmdTarget)

CAudioSegmentDlgAutoProxy::CAudioSegmentDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化 
	//	对象处于活动状态时一直保持运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序
	//  的主窗口指针来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CAudioSegmentDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CAudioSegmentDlg)))
		{
			m_pDialog = reinterpret_cast<CAudioSegmentDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CAudioSegmentDlgAutoProxy::~CAudioSegmentDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CAudioSegmentDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清除代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CAudioSegmentDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAudioSegmentDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IAudioSegment 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须与附加在 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {2A88D239-A4A3-4295-B9BF-DDE43FA8E81E}
static const IID IID_IAudioSegment =
{ 0x2A88D239, 0xA4A3, 0x4295, { 0xB9, 0xBF, 0xDD, 0xE4, 0x3F, 0xA8, 0xE8, 0x1E } };

BEGIN_INTERFACE_MAP(CAudioSegmentDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CAudioSegmentDlgAutoProxy, IID_IAudioSegment, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {7511E10C-432A-47A8-8047-6E893780C0F1}
IMPLEMENT_OLECREATE2(CAudioSegmentDlgAutoProxy, "AudioSegment.Application", 0x7511e10c, 0x432a, 0x47a8, 0x80, 0x47, 0x6e, 0x89, 0x37, 0x80, 0xc0, 0xf1)


// CAudioSegmentDlgAutoProxy 消息处理程序
