
// MainDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include"MasterDlg.h"
#include"UserDlg.h"

CFont mfont1, mfont2;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg 대화 상자



CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MASTER, mMaster);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MASTER, &CMainDlg::OnBnClickedMaster)
	ON_BN_CLICKED(IDC_Login, &CMainDlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CMainDlg 메시지 처리기

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	pMasterDlg = NULL;
	pUserDlg = NULL;


	// 자동 불러오기입니다.
	CFile file;
	CFileFind pFind;
	CArchive ar(&file, CArchive::load);
	CString str, str1, str2, str3, str4, str5, str6;
	SongType song;
	AlbumType album;
	SingerType singer;
	int count;

	if (pFind.FindFile(_T("savefile/autosaved"))) {
		file.Open(_T("savefile/autosaved"), CFile::modeRead);
		ar >> count;
		for (int i = 0; i < count; i++) {
			ar >> str >> str1 >> str2 >> str3 >> str4;
			song.setId(str);
			song.setName(str1);
			song.setSinger(str2);
			song.setAlbum(str3);
			song.setNumLikes(_ttoi(str4));
			mData.AddSong(song);
		}
		ar >> count;
		for (int i = 0; i < count; i++) {
			ar >> str >> str1 >> str3 >> str4 >> str5 >> str6;
			album.setName(str);
			album.setSinger(str1);
			album.setComeout(str3);
			album.setGenre(str4);
			album.setType(str5);
			album.setNumLikes(_ttoi(str6));
			mData.AddAlbum(album);
		}
		ar >> count;
		for (int i = 0; i < count; i++) {
			ar >> str >> str3 >> str4 >> str5 >> str6;
			singer.setName(str);
			singer.setDebutYear(str3);
			singer.setGenre(str4);
			singer.setType(str5);
			singer.setNumLikes(_ttoi(str6));
			mData.AddSinger(singer);
		}
		ar.Close();
		file.Close();
	}

	mfont1.CreateFont(65, 29, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("휴먼둥근헤드라인"));
	mfont2.CreateFont(20, 8, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("휴먼엑스포"));
	GetDlgItem(IDC_TITLE)->SetFont(&mfont1);
	GetDlgItem(IDC_MYINFO)->SetFont(&mfont2);
	mMaster.SetFont(&mfont2);
	GetDlgItem(IDC_Login)->SetFont(&mfont2);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnBnClickedMaster()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMasterDlg = new MasterDlg();
	pMasterDlg->Create(IDD_MASTER, GetDesktopWindow());
	pMasterDlg->ShowWindow(SW_SHOW);
}


void CMainDlg::OnBnClickedLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString ID, PW;

	GetDlgItemTextW(IDC_EDIT_ID, ID);
	GetDlgItemTextW(IDC_EDIT_PW, PW);

	if (mData.GetUserId() == ID) {
		if (mData.GetUserPw()== PW) {
			pUserDlg = new UserDlg();
			pUserDlg->Create(IDD_USER, GetDesktopWindow());
			pUserDlg->ShowWindow(SW_SHOW);
		}
		else {
			MessageBox(_T("비밀번호 오류입니다."));
		}
	}
	else {
		MessageBox(_T("아이디 오류입니다."));
	}
}



void CMainDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	CFile file;
	CArchive ar(&file, CArchive::store);
	CreateFolder(_T("savefile"));

	file.Open(_T("savefile/autosaved"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
	SongType song;
	CString str, str1, str2, str3, str4,str5,str6;
	int count = mData.GetSongLength();
	mData.ResetSongPointer();
	ar << count;
	for (int i = 0; i < count; i++) {
		mData.GetNextSong(song);
		str = song.getId();
		str1 = song.getName();
		str2 = song.getSinger();
		str3 = song.getAlbum();
		str4.Format(_T("%d"), song.getNumLikes());
		ar << str << str1 << str2 << str3 << str4;
	}
	AlbumType album;
	count = mData.GetAlbumLength();
	mData.ResetAlbumPointer();
	ar << count;
	for (int i = 0; i < count; i++) {
		mData.GetNextAlbum(album);
		str = album.getName();
		str1 = album.getSinger();
		str3 = album.getComeout();
		str4 = album.getGenre();
		str5 = album.getType();
		str6.Format(_T("%d"), album.getNumLikes());
		ar << str << str1 << str3 << str4 << str5 << str6;
	}
	SingerType singer;
	count = mData.GetSingerLength();
	mData.ResetSingerPointer();
	ar << count;
	for (int i = 0; i < count; i++) {
		mData.GetNextSinger(singer);
		str = singer.getName();
		str3 = singer.getDebutYear();
		str4 = singer.getGenre();
		str5 = singer.getType();
		str6.Format(_T("%d"), singer.getNumLikes());
		ar << str << str3 << str4 << str5 << str6;
	}
	ar.Flush();

	ar.Close();
	file.Close();


	CDialogEx::PostNcDestroy();
}

void CreateFolder(CString csPath)
{
	// UpdateData(TRUE);
	// csPath = m_csTopFolderName + csPath;

	CString csPrefix(_T("")), csToken(_T(""));
	int nStart = 0, nEnd;
	while ((nEnd = csPath.Find('/', nStart)) >= 0)
	{
		CString csToken = csPath.Mid(nStart, nEnd - nStart);
		CreateDirectory(csPrefix + csToken, NULL);

		csPrefix += csToken;
		csPrefix += _T("/");
		nStart = nEnd + 1;
	}
	csToken = csPath.Mid(nStart);
	CreateDirectory(csPrefix + csToken, NULL);
}