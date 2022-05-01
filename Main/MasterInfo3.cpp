// MasterInfo3.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "MasterInfo3.h"
#include "afxdialogex.h"


// MasterInfo3 대화 상자
#include"TabSinger.h"
#include"MainDlg.h"


IMPLEMENT_DYNAMIC(MasterInfo3, CDialogEx)

MasterInfo3::MasterInfo3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFO_MASTER3, pParent)
{

}

MasterInfo3::~MasterInfo3()
{
}

void MasterInfo3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, mAlbumList);
	DDX_Control(pDX, IDC_LIST3, mSongList);
}


BEGIN_MESSAGE_MAP(MasterInfo3, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &MasterInfo3::OnNMClickList2)
END_MESSAGE_MAP()


// MasterInfo3 메시지 처리기


BOOL MasterInfo3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (TabSinger *)AfxGetMainWnd();
	mparent = (CMainDlg*)AfxGetApp()->GetMainWnd();

	TCHAR fileName[500];
	GetModuleFileName(NULL, fileName, MAX_PATH);
	CString path = L"singerImages/", str;
	path += mSinger.getName();
	path += _T(".png");
	CFileFind pFind;
	if (!pFind.FindFile(path))
		path = L"singerImages/Unknown.png";

	m_Img.Load(path);

	SetDlgItemText(IDC_STATIC9, mSinger.getName());
	SetDlgItemText(IDC_STATIC10, mSinger.getDebutYear());
	SetDlgItemText(IDC_STATIC11, mSinger.getType());
	SetDlgItemText(IDC_STATIC12, mSinger.getGenre());
	str.Format(_T("%d"), mSinger.getNumLikes());
	SetDlgItemText(IDC_STATIC13, str);


	CRect rt;
	mAlbumList.GetWindowRect(&rt);
	mAlbumList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mAlbumList.InsertColumn(0, TEXT("앨범명"), LVCFMT_CENTER, rt.Width()*0.2);
	mAlbumList.InsertColumn(1, TEXT("발매일"), LVCFMT_CENTER, rt.Width()*0.2);
	mAlbumList.InsertColumn(2, TEXT("장르"), LVCFMT_CENTER, rt.Width()*0.2);
	mAlbumList.InsertColumn(3, TEXT("타입"), LVCFMT_CENTER, rt.Width()*0.2);
	mAlbumList.InsertColumn(4, TEXT("좋아요 수"), LVCFMT_CENTER, rt.Width()*0.2);


	mparent->mData.ResetAlbumPointer();
	AlbumType album;
	int num = 0;
	for (int i = 0; i < mparent->mData.GetAlbumLength(); i++) {
		mparent->mData.GetNextAlbum(album);
		if (album.getSinger() == mSinger.getName()) {
			mAlbumList.InsertItem(num, album.getName());
			mAlbumList.SetItem(num, 1, LVIF_TEXT, album.getComeout(), NULL, NULL, NULL, NULL);
			mAlbumList.SetItem(num, 2, LVIF_TEXT, album.getGenre(), NULL, NULL, NULL, NULL);
			mAlbumList.SetItem(num, 3, LVIF_TEXT, album.getType(), NULL, NULL, NULL, NULL);
			str.Format(_T("%d"), album.getNumLikes());
			mAlbumList.SetItem(num, 4, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
			num++;
		}
	}

	mSongList.GetWindowRect(&rt);
	mSongList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mSongList.InsertColumn(0, TEXT("ID"), LVCFMT_CENTER, rt.Width()*0.3);
	mSongList.InsertColumn(1, TEXT("곡 명"), LVCFMT_CENTER, rt.Width()*0.3);
	mSongList.InsertColumn(2, TEXT("좋아요 수"), LVCFMT_CENTER, rt.Width()*0.3);


	mparent->mData.ResetSongPointer();
	SongType song;
	num = 0;
	for (int i = 0; i < mparent->mData.GetSongLength(); i++) {
		mparent->mData.GetNextSong(song);
		if (song.getSinger() == mSinger.getName()) {
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


void MasterInfo3::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pInfoDlg = NULL;

	delete this;

	CDialogEx::PostNcDestroy();
}


void MasterInfo3::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
//	CDialogEx::OnOK();
}


void MasterInfo3::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
//	CDialogEx::OnCancel();
}


void MasterInfo3::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	this->DestroyWindow();
//	CDialogEx::OnClose();
}


void MasterInfo3::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_Img.Draw(dc, 50, 50, 300, 300);
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
}


void MasterInfo3::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mAlbumList.GetFirstSelectedItemPosition();
	int idx = mAlbumList.GetNextSelectedItem(pos);
	if (idx == -1)
		idx = 0;
	CString albumName = mAlbumList.GetItemText(idx, 0), str;
	mSongList.DeleteAllItems();
	mparent->mData.ResetSongPointer();
	SongType song;
	int num = 0;
	for (int i = 0; i < mparent->mData.GetSongLength(); i++) {
		mparent->mData.GetNextSong(song);
		if (song.getAlbum() == albumName) {
			mSongList.InsertItem(num, song.getId());
			mSongList.SetItem(num, 1, LVIF_TEXT, song.getName(), NULL, NULL, NULL, NULL);
			str.Format(_T("%d"), song.getNumLikes());
			mSongList.SetItem(num, 2, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
			num++;
		}
	}

	*pResult = 0;
}
