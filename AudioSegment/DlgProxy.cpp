// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��� 
	//	�����ڻ״̬ʱһֱ�������У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó���
	//  ��������ָ�������ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CAudioSegmentDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CAudioSegmentDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAudioSegmentDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IAudioSegment ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID �����븽���� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {2A88D239-A4A3-4295-B9BF-DDE43FA8E81E}
static const IID IID_IAudioSegment =
{ 0x2A88D239, 0xA4A3, 0x4295, { 0xB9, 0xBF, 0xDD, 0xE4, 0x3F, 0xA8, 0xE8, 0x1E } };

BEGIN_INTERFACE_MAP(CAudioSegmentDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CAudioSegmentDlgAutoProxy, IID_IAudioSegment, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {7511E10C-432A-47A8-8047-6E893780C0F1}
IMPLEMENT_OLECREATE2(CAudioSegmentDlgAutoProxy, "AudioSegment.Application", 0x7511e10c, 0x432a, 0x47a8, 0x80, 0x47, 0x6e, 0x89, 0x37, 0x80, 0xc0, 0xf1)


// CAudioSegmentDlgAutoProxy ��Ϣ�������
