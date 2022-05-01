// Mypage.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "Mypage.h"
#include "afxdialogex.h"

#include"UserDlg.h"
#include"MainDlg.h"
// Mypage 대화 상자

IMPLEMENT_DYNAMIC(Mypage, CDialogEx)

Mypage::Mypage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYPAGE, pParent)
{

}

Mypage::~Mypage()
{
}

void Mypage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mPlayList);
	DDX_Control(pDX, IDC_SORT_LIST, mComboSort);
}


BEGIN_MESSAGE_MAP(Mypage, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_SORT_LIST, &Mypage::OnCbnSelchangeSortList)
	ON_BN_CLICKED(IDC_DEL, &Mypage::OnBnClickedDel)
	ON_BN_CLICKED(IDC_PLAYSONG, &Mypage::OnBnClickedPlaysong)
	ON_BN_CLICKED(IDC_NEXT, &Mypage::OnBnClickedNext)
	ON_BN_CLICKED(IDC_BEFORE, &Mypage::OnBnClickedBefore)
	ON_BN_CLICKED(IDC_BUTTON3, &Mypage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Mypage::OnBnClickedButton4)
END_MESSAGE_MAP()


// Mypage 메시지 처리기


BOOL Mypage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (UserDlg*)AfxGetMainWnd();
	mparent = (CMainDlg*)AfxGetApp()->GetMainWnd();

	

	//List Control 초기화
	CRect rt;
	mPlayList.GetWindowRect(&rt);
	mPlayList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mPlayList.InsertColumn(0, TEXT("Num"), LVCFMT_CENTER, rt.Width()*0.15);
	mPlayList.InsertColumn(1, TEXT("곡명"), LVCFMT_CENTER, rt.Width()*0.28);
	mPlayList.InsertColumn(2, TEXT("가수명"), LVCFMT_CENTER, rt.Width()*0.28);
	mPlayList.InsertColumn(3, TEXT("앨범"), LVCFMT_CENTER, rt.Width()*0.28);


	CString str;
	mparent->mData.UpdatePL();
	mparent->mData.ResetPLPointer();
	PlayItemType song;
	for (int i = 0; i < mparent->mData.GetPLLength(); i++) {
		mparent->mData.GetNextPL(song);
		str.Format(_T("%d"), i + 1);
		mPlayList.InsertItem(i, str);
		mPlayList.SetItem(i, 1, LVIF_TEXT, song.getSong(), NULL, NULL, NULL, NULL);
		mPlayList.SetItem(i, 2, LVIF_TEXT, song.getSinger(), NULL, NULL, NULL, NULL);
		mPlayList.SetItem(i, 3, LVIF_TEXT, song.getAlbum(), NULL, NULL, NULL, NULL);

	}
	mparent->mData.mPlaying = mparent->mData.GetPLItem(0);

	TCHAR fileName[500];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	CString path = L"albumImages/";
	path += mparent->mData.mPlaying.getAlbum();
	path += _T(".png");
	CFileFind pFind;
	if (!pFind.FindFile(path))
		path = L"albumImages/Unknown.png";
	if (pFind.FindFile(path))
		m_Img.Load(path);

	mComboSort.AddString(TEXT("앨범순"));
	mComboSort.AddString(TEXT("곡명순"));
	mComboSort.AddString(TEXT("가수순"));
	mComboSort.AddString(TEXT("사용자 설정 순"));
	mComboSort.AddString(TEXT("최근 추가순"));
	mComboSort.AddString(TEXT("인기순"));
	mComboSort.SetCurSel(3);

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Mypage::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pMypageDlg = NULL;
	delete this;

	CDialogEx::PostNcDestroy();
}


void Mypage::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
//	CDialogEx::OnOK();
}


void Mypage::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
	//CDialogEx::OnCancel();
}


void Mypage::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	this->DestroyWindow();
//	CDialogEx::OnClose();
}


void Mypage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_Img.Draw(dc, 50, 50, 300, 300);
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


void Mypage::OnCbnSelchangeSortList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int selS = mComboSort.GetCurSel();
	if (selS == 3)
		selS = 5;
	mparent->mData.UpdatePL(selS);
	mparent->mData.ResetPLPointer();
	PlayItemType song;
	CString str;
	mPlayList.DeleteAllItems();
	for (int i = 0; i < mparent->mData.GetPLLength(); i++) {
		mparent->mData.GetNextPL(song);
		str.Format(_T("%d"), i + 1);
		mPlayList.InsertItem(i, str);
		mPlayList.SetItem(i, 1, LVIF_TEXT, song.getSong(), NULL, NULL, NULL, NULL);
		mPlayList.SetItem(i, 2, LVIF_TEXT, song.getSinger(), NULL, NULL, NULL, NULL);
		mPlayList.SetItem(i, 3, LVIF_TEXT, song.getId(), NULL, NULL, NULL, NULL);

	}
}


void Mypage::OnBnClickedDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mPlayList.GetFirstSelectedItemPosition();
	int idx = mPlayList.GetNextSelectedItem(pos);
	mparent->mData.DeletePL(mparent->mData.GetPLItem(idx));
	mPlayList.DeleteItem(idx);
}


void Mypage::OnBnClickedPlaysong()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mPlayList.GetFirstSelectedItemPosition();
	int idx = mPlayList.GetNextSelectedItem(pos);
	mparent->mData.mPlaying = mparent->mData.GetPLItem(idx);

	TCHAR fileName[500];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	CString path = L"albumImages/", str;
	CPaintDC dc(this);
	path += mparent->mData.mPlaying.getAlbum();
	path += _T(".png");
	CFileFind pFind;
	m_Img.Destroy();
	if (!pFind.FindFile(path))
		path = L"albumImages/Unknown.png";
	if (pFind.FindFile(path)) {
		m_Img.Load(path);
		m_Img.Draw(dc, 50, 50, 300, 300);
	}
	Invalidate(FALSE);
}


void Mypage::OnBnClickedNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	mparent->mData.GetNextPLItem();

	TCHAR fileName[500];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	CString path = L"albumImages/", str;
	CPaintDC dc(this);
	path += mparent->mData.mPlaying.getAlbum();
	path += _T(".png");
	CFileFind pFind;
	m_Img.Destroy();
	if (!pFind.FindFile(path))
		path = L"albumImages/Unknown.png";
	if (pFind.FindFile(path)) {
		m_Img.Load(path);
		m_Img.Draw(dc, 50, 50, 300, 300);
	}
	Invalidate(FALSE);
	
}


void Mypage::OnBnClickedBefore()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mparent->mData.GetBeforePLItem();

	TCHAR fileName[500];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	CString path = L"albumImages/", str;
	CPaintDC dc(this);
	path += mparent->mData.mPlaying.getAlbum();
	path += _T(".png");
	CFileFind pFind;
	m_Img.Destroy();
	if (!pFind.FindFile(path))
		path = L"albumImages/Unknown.png";
	if (pFind.FindFile(path)) {
		m_Img.Load(path);
		m_Img.Draw(dc, 50, 50, 300, 300);
	}
	Invalidate(FALSE);

}


void Mypage::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PlaySound(NULL, AfxGetInstanceHandle(), NULL);
}


void Mypage::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString path = L"songFiles/";
	path += mparent->mData.mPlaying.getId();
	path += _T(".wav");
	CFileFind pFind;
	if (pFind.FindFile(path))
		PlaySound(path, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP);
}
