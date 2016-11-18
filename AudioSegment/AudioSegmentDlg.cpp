// AudioSegmentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AudioSegment.h"
#include "AudioSegmentDlg.h"
#include "DlgProxy.h"

#include "WaveIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void RefreshListBox(CListBox * targetList)
{
	CClientDC myDC(targetList);
	myDC.SelectObject(targetList->GetFont());
	CString item;
	CSize cSize;
	int m_maxItemLength=0;
	for(int i=0; i<targetList->GetCount();i++)
	{
		targetList->GetText(i,item);
		GetTextExtentPoint32(myDC.m_hDC,item,item.GetLength(),&cSize);
		if(m_maxItemLength<cSize.cx) m_maxItemLength = cSize.cx;
	}
	targetList->SetHorizontalExtent(m_maxItemLength+6);
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAudioSegmentDlg 对话框




IMPLEMENT_DYNAMIC(CAudioSegmentDlg, CDialog);

CAudioSegmentDlg::CAudioSegmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAudioSegmentDlg::IDD, pParent)
	, m_fMinPitch(75)
	, m_fTimeStep(0)
	, m_fMinSilence(0.5)
	, m_fThresholdCoef(0.33)
	, m_nChannelIdx(0)
	, m_fBeginPad(0.)
	, m_fEndPad(0.)
	, m_nStartIdx(1)
	, m_csOutpath(_T("D:\\"))
	, m_bChkIterFolder(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CAudioSegmentDlg::~CAudioSegmentDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CAudioSegmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_cList);
	DDX_Control(pDX, IDC_LIST1, m_cLog);
	DDX_Text(pDX, IDC_EDIT1, m_fMinPitch);
	DDV_MinMaxDouble(pDX, m_fMinPitch, 10, 500);
	DDX_Text(pDX, IDC_EDIT2, m_fTimeStep);
	DDV_MinMaxDouble(pDX, m_fTimeStep, 0.0, 10);
	DDX_Text(pDX, IDC_EDIT3, m_fMinSilence);
	DDV_MinMaxDouble(pDX, m_fMinSilence, 0.0, 10);
	DDX_Text(pDX, IDC_EDIT9, m_fThresholdCoef);
	DDV_MinMaxDouble(pDX, m_fThresholdCoef, 0, 10);
	DDX_Text(pDX, IDC_EDIT4, m_nChannelIdx);
	DDV_MinMaxInt(pDX, m_nChannelIdx, 0, 4);
	DDX_Text(pDX, IDC_EDIT5, m_fBeginPad);
	DDV_MinMaxDouble(pDX, m_fBeginPad, 0, 10);
	DDX_Text(pDX, IDC_EDIT6, m_fEndPad);
	DDV_MinMaxDouble(pDX, m_fEndPad, 0, 10);
	DDX_Text(pDX, IDC_EDIT7, m_nStartIdx);
	DDX_Text(pDX, IDC_EDIT8, m_csOutpath);
	DDX_Check(pDX, IDC_CHECK1, m_bChkIterFolder);
}

BEGIN_MESSAGE_MAP(CAudioSegmentDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Add, &CAudioSegmentDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_Remove, &CAudioSegmentDlg::OnBnClickedRemove)
	ON_BN_CLICKED(IDC_MOVEUP, &CAudioSegmentDlg::OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, &CAudioSegmentDlg::OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_BROWSE, &CAudioSegmentDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_DO, &CAudioSegmentDlg::OnBnClickedDo)
	ON_BN_CLICKED(IDC_DEFAULT, &CAudioSegmentDlg::OnBnClickedDefault)
	ON_BN_CLICKED(ID_EXPORT_LOG, &CAudioSegmentDlg::OnBnClickedExportLog)
	ON_BN_CLICKED(IDC_CLEAR_LOG, &CAudioSegmentDlg::OnBnClickedClearLog)
	ON_BN_CLICKED(IDC_BUTTON2, &CAudioSegmentDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAudioSegmentDlg 消息处理程序

BOOL CAudioSegmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOWNORMAL);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAudioSegmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAudioSegmentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CAudioSegmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，
//  如果控制器仍保持着它的某个对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CAudioSegmentDlg::OnClose()
{
	if (CanExit())
		CDialog::OnClose();
}

void CAudioSegmentDlg::OnOK()
{
	if (CanExit())
		CDialog::OnOK();
}

void CAudioSegmentDlg::OnCancel()
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CAudioSegmentDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CAudioSegmentDlg::OnBnClickedAdd()
{
	static char szFilter[] = "Wave Files (*.wav)|*.wav|All files(*.*)|*.*||";
	CFileDialog   Filedlg(TRUE, NULL, NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT|OFN_EXPLORER, 
		szFilter, NULL);
	char bigBuff[MAX_PATH*100]="";
	Filedlg.m_ofn.lpstrFile = bigBuff;
	Filedlg.m_ofn.nMaxFile = sizeof(bigBuff);

	if(Filedlg.DoModal() == IDOK) 
	{ 
		int nCount = 0;
		POSITION pos = Filedlg.GetStartPosition(); 
		while(pos != NULL) 
		{ 
			CString csfilepath =  Filedlg.GetNextPathName(pos); 
			m_cList.AddString(csfilepath);
			m_cList.SetCurSel(m_cList.GetCount()-1);
			nCount++;
		}
		RefreshListBox(&m_cList);
		CString str;
		str.Format("Successfully opened %d files ", nCount);
		AfxMessageBox(str);

		UpdateData(TRUE);
	} 
}

void CAudioSegmentDlg::OnBnClickedRemove()
{
	int nCount = m_cList.GetSelCount();

	int* buffer = new int[nCount];
	memset(buffer, -1, sizeof(int)*nCount);

	m_cList.GetSelItems(nCount, buffer);

	for(int i=nCount-1; i>=0; i--)
	{
		m_cList.DeleteString(buffer[i]);
	}
	RefreshListBox(&m_cList);
	delete[] buffer;
}

void CAudioSegmentDlg::OnBnClickedMoveup()
{

}

void CAudioSegmentDlg::OnBnClickedMovedown()
{

}

BOOL SelectFolder(HWND hwndOwner, CString* pDir)
{
	BROWSEINFO lpbi;

	TCHAR lpDir[MAX_PATH];
	CString path(*pDir);

	lpbi.hwndOwner = hwndOwner;
	lpbi.pidlRoot = NULL;  // 默认路径
	lpbi.pszDisplayName = lpDir;
	lpbi.lpszTitle = _T("请选择文件夹：");
	lpbi.ulFlags = BIF_NEWDIALOGSTYLE;
	lpbi.lpfn = NULL;
	lpbi.lParam = NULL;
	lpbi.iImage = NULL;

	LPITEMIDLIST lpidl = :: SHBrowseForFolder(&lpbi);

	if(lpidl && SHGetPathFromIDList(lpidl, lpDir))
	{
		*pDir = lpDir;
		return TRUE;
	}

	return FALSE;
}

void CAudioSegmentDlg::OnBnClickedBrowse()
{
	UpdateData(TRUE);
	CString strPath = m_csOutpath;
	BOOL b = SelectFolder(this->m_hWnd, &strPath);

	if (b)
	{
		if (strPath.Right(1) != '\\')
			strPath += '\\';
		m_csOutpath = strPath;

		UpdateData(FALSE);
	}
}

void CAudioSegmentDlg::OnBnClickedDo()
{
	UpdateData();

	int nCount = m_cList.GetSelCount();
	if (nCount <= 0) {
		nCount = m_cList.GetCount();
	}

	int* buffer = new int[nCount];
	memset(buffer, -1, sizeof(int)*nCount);

	if (nCount < m_cList.GetCount()) {
		m_cList.GetSelItems(nCount, buffer);
	} else {
		for (int i = 0; i<nCount; i++)
			buffer[i] = i;
	}

	int nWavIdx = m_nStartIdx;
	CString csOutpath = m_csOutpath;

	for(int i=0; i< nCount; i++)
	{
		CString csInWavFile;
		CString csOutpath = m_csOutpath;
		m_cList.GetText(buffer[i], csInWavFile);

		CString strMessage;

		// 逐个文件处理
		// 1. open wave file
		WaveIO wav;
		CString strInfo = wav.openWave(csInWavFile);

		if (strInfo == "done") {
			strMessage = "Open "+csInWavFile+" ... " + strInfo;
			m_cLog.AddString(strMessage);
			m_cLog.SetCurSel(m_cLog.GetCount()-1);
		} else {
			strMessage = "Open "+csInWavFile+" ... " + strInfo;
			m_cLog.AddString(strMessage);
			m_cLog.SetCurSel(m_cLog.GetCount()-1);
			continue;
		}

		// 2. determin channel index
		int nCurChannel = m_nChannelIdx;
		if (nCurChannel >= wav.getChannels()) {
			nCurChannel = 0;
		}
		strMessage.Format("  Select %d channel for segment", nCurChannel);
		m_cLog.AddString(strMessage);
		m_cLog.SetCurSel(m_cLog.GetCount()-1);

		// 3. get speech data
		short *pData = NULL;
		int nSamples = wav.getData(&pData, nCurChannel);

		// 4. do auto segment
		AutoSegmenter segmenter(wav.getSampleRate());
		vector<SEGMENT> vSegs = segmenter.getSegment(pData,nSamples,
			m_fMinPitch,m_fTimeStep,
			m_fMinSilence, m_fThresholdCoef, 
			m_fBeginPad, m_fEndPad);

		delete [] pData;

		strMessage.Format("  %d segments selected", vSegs.size());
		m_cLog.AddString(strMessage);
		m_cLog.SetCurSel(m_cLog.GetCount()-1);

		if (m_bChkIterFolder) {
			nWavIdx = m_nStartIdx;

			csInWavFile.Replace(".wav","");

			CString csSubpath;
			CString csWavpath;
			csWavpath = csInWavFile;
			int pos = csWavpath.ReverseFind('\\');
			csWavpath.Delete(0,pos+1);
			csSubpath.Format("%s%s", csOutpath, csWavpath);

			CreateMultipleDirectory(csSubpath);

			csOutpath = csSubpath;
		}

		// 5. extract segment wave into files
		for (unsigned int j=0;j<vSegs.size(); j++)
		{
			CString strindex;
			strindex.Format("%05d", nWavIdx++);
			CString szOutFile;
			szOutFile.Format("%s\\%s.wav", csOutpath, strindex);

			wav.writeWavFile(szOutFile, vSegs[j].begin, vSegs[j].end);

			strMessage.Format("    segment %d: begin=%.4f end=%.4f name=%s", 
				j+1, vSegs[j].begin, vSegs[j].end, strindex);
			m_cLog.AddString(strMessage);
			m_cLog.SetCurSel(m_cLog.GetCount()-1);
		}
	}
	RefreshListBox(&m_cLog);
	AfxMessageBox("Segmentation Completed!");
}

void CAudioSegmentDlg::OnBnClickedDefault()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	m_fMinPitch = 75;
	m_fTimeStep = 0.;
	m_fMinSilence = 1.;
	m_nChannelIdx = 0;
	m_fBeginPad = 0.3;
	m_fEndPad = 0.3;
	m_fThresholdCoef = 0.33;
	m_nStartIdx = 1;

	UpdateData(FALSE);
}

void CAudioSegmentDlg::OnBnClickedExportLog()
{
	static char szFilter[] = "Log Files (*.log;*.txt)|*.wav;*.txt|All files(*.*)|*.*||";
	CFileDialog   Filedlg(FALSE, NULL, NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER, 
		szFilter, NULL);

	if(Filedlg.DoModal()   ==   IDOK) 
	{
		CString logname = Filedlg.GetPathName();
		int nCount = m_cLog.GetCount();
		if (nCount > 0) {

			CStdioFile fp;
			fp.Open(logname,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
			for(int i=0; i<nCount; i++)
			{
				CString csRow;
				m_cLog.GetText(i, csRow);
				fp.WriteString(csRow+"\r\n");
			}
			fp.Close();
		} else {
			AfxMessageBox("No log to be save");
		}
	}
}

void CAudioSegmentDlg::OnBnClickedClearLog()
{
	while(m_cLog.GetCount())
		m_cLog.DeleteString(0);
	RefreshListBox(&m_cLog);
}
void CAudioSegmentDlg::FileSearch(CString strPath,vector<CString>& list)
{
		CFileFind fileFinder;
	BOOL bExist = fileFinder.FindFile(strPath+_T("\\*.*"));
	if(!bExist){
		if(strPath.Mid(strPath.GetLength()-4,4) == _T(".wav")){
			list.push_back(strPath);
		}
		else{
			return;
		}
	}
	while (bExist)
	{
		bExist = fileFinder.FindNextFile();
		if(fileFinder.IsDirectory() && !fileFinder.IsDots()){
			FileSearch(fileFinder.GetFilePath(),list);
		}
	}
	bExist = fileFinder.FindFile(strPath+_T("\\*.wav"));
	while (bExist)
	{
		bExist = fileFinder.FindNextFile();
		list.push_back(fileFinder.GetFilePath());
		
	}
	
	fileFinder.Close();
}

void CAudioSegmentDlg::OnBnClickedButton2()
{
	
	UpdateData();

	// 1. select folder to be processed
	/*
	CString strInPath = m_csOutpath;
	BOOL b = SelectFolder(this->m_hWnd, &strInPath);

	if (b == FALSE) return;
	*/
	CString strDir = _T("");
	BROWSEINFO bi = {0};
	TCHAR pszDisplayName[MAX_PATH] = _T("\0");
	bi.pszDisplayName = pszDisplayName;
	bi.lpszTitle = _T("选择文件或文件夹");
	bi.hwndOwner = m_hWnd;
	bi.ulFlags = BIF_BROWSEINCLUDEFILES|BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST lpIL = SHBrowseForFolder(&bi);
	if(lpIL){

		SHGetPathFromIDList(lpIL,bi.pszDisplayName);
		strDir = bi.pszDisplayName;
		UpdateData(FALSE);
	}
	else return;


	
	// 2. get all wave file names in folder
	//CString filename[] = ();//getallwavfils(strInPath);
	vector<CString> filenamelist;
	FileSearch(strDir,filenamelist);
	
	// 3. get the log file name
	
	static char szFilter[] = "Log Files (*.log;*.txt)|*.wav;*.txt|All files(*.*)|*.*||";
	CFileDialog   Filedlg(TRUE, NULL, NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER, 
		szFilter, NULL);
	
	if(Filedlg.DoModal()   ==   IDOK) 
	{

		CString logname = Filedlg.GetPathName();
		CStdioFile file;  
		CString strMessage;
		if (!file.Open(_T(logname),CFile::modeCreate |CFile::modeWrite | CFile::typeText)) {
			MessageBox(_T("打开失败"));
			return;
		}
		
		for (unsigned int i=0; i<filenamelist.size(); i++) 
		{
			// 逐个文件处理
			// 1. open wave file
			if (filenamelist[i].Right(3).CompareNoCase(CString("wav")) != 0)
				continue;

			WaveIO wav;
			CString strInfo = wav.openWave(filenamelist[i]);

			// 2. determin channel index
			int nCurChannel = m_nChannelIdx;
			if (nCurChannel >= wav.getChannels()) {
				nCurChannel = 0;
			}

			// 3. get speech data
			short *pData = NULL;
			int nSamples = wav.getData(&pData, nCurChannel);

			// 4. do auto segment
			AutoSegmenter segmenter(wav.getSampleRate());
			vector<SEGMENT> vSegs = segmenter.getSegment(pData,nSamples,
				m_fMinPitch,m_fTimeStep,
				m_fMinSilence, m_fThresholdCoef, 
				m_fBeginPad, m_fEndPad);

			delete [] pData;

			// 5. get the begining and ending point of the max length segment wave

			double fbegin = 0.0, fend = 0.0;
			double maxlen = 0.0;

			for (unsigned int j=0;j<vSegs.size(); j++)
			{
				if (vSegs[j].end - vSegs[j].begin > maxlen) 
				{
					maxlen = vSegs[j].end - vSegs[j].begin;
					fbegin = vSegs[j].begin;
					fend = vSegs[j].end;
				}
			}
			
			// 6. save strMessage to log file in a line;
			strMessage.Format("%s\t%.4f\t%.4f\n", filenamelist[i],fbegin, fend);
			file.WriteString(strMessage); 
			
			strMessage.Format("%s    %.4f    %.4f\n", filenamelist[i],fbegin, fend);
			m_cLog.AddString(strMessage);
			m_cLog.SetCurSel(m_cLog.GetCount()-1);

		}
		file.Close(); 

		AfxMessageBox("干活完毕啦");
	}
}


BOOL CAudioSegmentDlg::CreateMultipleDirectory(CString szPath)  
{  
    CString strDir(szPath);//存放要创建的目录字符串;  
    //确保以‘/’结尾以创建最后一个目录;  
    if (strDir.GetAt(strDir.GetLength()-1) != _T('/'))  
    {  
        strDir.AppendChar(_T('/'));  
    }  
    std::vector<CString> vPath;//存放每一层目录字符串;  
    CString strTemp;//一个临时变量,存放目录字符串;  
    BOOL bSuccess = FALSE;//成功标志;  
    //遍历要创建的字符串;  
    for (int i=0;i<strDir.GetLength();++i)  
    {  
        if (strDir.GetAt(i) != _T('/'))  
        {  
            //如果当前字符不是‘/’;  
            strTemp.AppendChar(strDir.GetAt(i));  
        }  
        else{  
            //如果当前字符是‘/’;  
            vPath.push_back(strTemp);//将当前层的字符串添加到数组中;  
            strTemp.AppendChar(_T('/'));  
        }  
    }  
    //遍历存放目录的数组，创建每层目录;  
    std::vector<CString>::const_iterator vIter;  
    for (vIter = vPath.begin();vIter!=vPath.end();vIter++)  
    {  
        //如果createDirectory执行成功，返回true，否则返回false;  
        bSuccess = ::CreateDirectory(*vIter,NULL)?TRUE:FALSE;  
    }  
    return bSuccess;  
}