// MasterInfo.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "MasterInfo.h"
#include "afxdialogex.h"


// MasterInfo 대화 상자
#include "TabSong.h"

IMPLEMENT_DYNAMIC(MasterInfo, CDialogEx)

MasterInfo::MasterInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFO_MASTER, pParent)
{

}

MasterInfo::~MasterInfo()
{
}

void MasterInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALBUM_IMG, mAlbumImage);
}


BEGIN_MESSAGE_MAP(MasterInfo, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// MasterInfo 메시지 처리기


BOOL MasterInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (TabSong *)AfxGetMainWnd();

	
	TCHAR fileName[500];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	CString path = L"albumImages/",str;
	path += mSong.getAlbum();
	path += _T(".png");
	CFileFind pFind;
	if (!pFind.FindFile(path))
		path = L"albumImages/Unknown.png";

	m_Img.Load(path);

	SetDlgItemText(IDC_STATIC1,mSong.getName());
	SetDlgItemText(IDC_STATIC2, mSong.getId());
	str.Format(_T("%d"), mSong.getNumLikes());
	SetDlgItemText(IDC_STATIC3, str);
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





	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MasterInfo::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pInfoDlg = NULL;

	delete this;

	CDialogEx::PostNcDestroy();
}


void MasterInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_Img.Draw(dc, 50, 50, 300, 300);
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}
