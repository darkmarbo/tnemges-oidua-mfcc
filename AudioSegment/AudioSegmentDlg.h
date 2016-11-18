// AudioSegmentDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "AutoSegmenter.h"
#include <vector>
using namespace std;
class CAudioSegmentDlgAutoProxy;


// CAudioSegmentDlg 对话框
class CAudioSegmentDlg : public CDialog
{
	DECLARE_DYNAMIC(CAudioSegmentDlg);
	friend class CAudioSegmentDlgAutoProxy;

// 构造
public:
	CAudioSegmentDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CAudioSegmentDlg();

// 对话框数据
	enum { IDD = IDD_AUDIOSEGMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CAudioSegmentDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
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

	// 但处理的文件列表
	CListBox m_cList;
	// Log
	CListBox m_cLog;
	afx_msg void OnBnClickedExportLog();
	afx_msg void OnBnClickedClearLog();

public:
	// 最小音高值
	double m_fMinPitch;
	// 步长
	double m_fTimeStep;
	// 最短句间静音长度
	double m_fMinSilence;
	// Threshold coefficient
	double m_fThresholdCoef;
	// 用于分隔通道序号
	int m_nChannelIdx;
	// 头静音长度
	double m_fBeginPad;
	// 尾静音长度
	double m_fEndPad;
	// 起始序号
	int m_nStartIdx;
	// 输出目录
	CString m_csOutpath;
	afx_msg void OnBnClickedButton2();
	void FileSearch(CString strPath,vector<CString>& list);
	BOOL m_bChkIterFolder;
};
