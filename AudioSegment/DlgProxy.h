// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CAudioSegmentDlg;


// CAudioSegmentDlgAutoProxy ����Ŀ��

class CAudioSegmentDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CAudioSegmentDlgAutoProxy)

	CAudioSegmentDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CAudioSegmentDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CAudioSegmentDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CAudioSegmentDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

