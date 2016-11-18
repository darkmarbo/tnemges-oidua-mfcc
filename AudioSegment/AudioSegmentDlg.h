// AudioSegmentDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "AutoSegmenter.h"
#include <vector>
using namespace std;
class CAudioSegmentDlgAutoProxy;


// CAudioSegmentDlg �Ի���
class CAudioSegmentDlg : public CDialog
{
	DECLARE_DYNAMIC(CAudioSegmentDlg);
	friend class CAudioSegmentDlgAutoProxy;

// ����
public:
	CAudioSegmentDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CAudioSegmentDlg();

// �Ի�������
	enum { IDD = IDD_AUDIOSEGMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CAudioSegmentDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedMoveup();
	afx_msg void OnBnClickedMovedown();
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedDo();
	afx_msg void OnBnClickedDefault();

	BOOL CreateMultipleDirectory(CString szPath) ;

	// ��������ļ��б�
	CListBox m_cList;
	// Log
	CListBox m_cLog;
	afx_msg void OnBnClickedExportLog();
	afx_msg void OnBnClickedClearLog();

public:
	// ��С����ֵ
	double m_fMinPitch;
	// ����
	double m_fTimeStep;
	// ��̾�侲������
	double m_fMinSilence;
	// Threshold coefficient
	double m_fThresholdCoef;
	// ���ڷָ�ͨ�����
	int m_nChannelIdx;
	// ͷ��������
	double m_fBeginPad;
	// β��������
	double m_fEndPad;
	// ��ʼ���
	int m_nStartIdx;
	// ���Ŀ¼
	CString m_csOutpath;
	afx_msg void OnBnClickedButton2();
	void FileSearch(CString strPath,vector<CString>& list);
	BOOL m_bChkIterFolder;
};
