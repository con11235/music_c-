// MasterInfo2.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "MasterInfo2.h"
#include "afxdialogex.h"


// MasterInfo2 대화 상자
#include"TabAlbum.h"
#include"MainDlg.h"

IMPLEMENT_DYNAMIC(MasterInfo2, CDialogEx)

MasterInfo2::MasterInfo2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFO_MASTER2, pParent)
{

}

MasterInfo2::~MasterInfo2()
{
}

void MasterInfo2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, mSongList);
}


BEGIN_MESSAGE_MAP(MasterInfo2, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// MasterInfo2 메시지 처리기


BOOL MasterInfo2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (TabAlbum *)AfxGetMainWnd();
	mparent = (CMainDlg*)AfxGetApp()->GetMainWnd();

	TCHAR fileName[500];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	CString path = L"albumImages/", str;
	path += mAlbum.getName();
	path += _T(".png");
	CFileFind pFind;
	if (!pFind.FindFile(path))
		path = L"albumImages/Unknown.png";

	m_Img.Load(path);

	SetDlgItemText(IDC_STATIC4, mAlbum.getName());
	SetDlgItemText(IDC_STATIC5, mAlbum.getComeout());
	SetDlgItemText(IDC_STATIC6, mAlbum.getGenre());
	SetDlgItemText(IDC_STATIC7, mAlbum.getType());
	str.Format(_T("%d"), mAlbum.getNumLikes());
	SetDlgItemText(IDC_STATIC8, str);
	SetDlgItemText(IDC_STATIC9, mSinger.getName());
	SetDlgItemText(IDC_STATIC10, mSinger.getDebutYear());
	SetDlgItemText(IDC_STATIC11, mSinger.getType());
	SetDlgItemText(IDC_STATIC12, mSinger.getGenre());
	str.Format(_T("%d"), mSinger.getNumLikes());
	SetDlgItemText(IDC_STATIC13, str);


	CRect rt;
	mSongList.GetWindowRect(&rt);
	mSongList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mSongList.InsertColumn(0, TEXT("ID"), LVCFMT_CENTER, rt.Width()*0.3);
	mSongList.InsertColumn(1, TEXT("곡 명"), LVCFMT_CENTER, rt.Width()*0.3);
	mSongList.InsertColumn(2, TEXT("좋아요 수"), LVCFMT_CENTER, rt.Width()*0.3);
	

	mparent->mData.ResetSongPointer();
	SongType song;
	int num = 0;
	for (int i = 0; i < mparent->mData.GetSongLength(); i++) {
		mparent->mData.GetNextSong(song);
		if (song.getAlbum() == mAlbum.getName()) {
			mSongList.InsertItem(num, song.getId());
			mSongList.SetItem(num, 1, LVIF_TEXT, song.getName(), NULL, NULL, NULL, NULL);
			str.Format(_T("%d"), song.getNumLikes());
			mSongList.SetItem(num, 2, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
			num++;
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MasterInfo2::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pInfoDlg = NULL;

	delete this;


	CDialogEx::PostNcDestroy();
}


void MasterInfo2::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
	//CDialogEx::OnOK();
}


void MasterInfo2::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
	//CDialogEx::OnCancel();
}


void MasterInfo2::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	this->DestroyWindow();
	//CDialogEx::OnClose();
}


void MasterInfo2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_Img.Draw(dc, 50, 50, 300, 300);
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}
