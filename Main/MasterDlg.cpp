// MasterDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "MasterDlg.h"
#include "afxdialogex.h"


// MasterDlg 대화 상자
#include"MainDlg.h"
#include"TabSong.h"
#include"TabAlbum.h"
#include"TabSinger.h"

IMPLEMENT_DYNAMIC(MasterDlg, CDialogEx)

MasterDlg::MasterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MASTER, pParent)
{

}

MasterDlg::~MasterDlg()
{
}

void MasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, mTab);
}


BEGIN_MESSAGE_MAP(MasterDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &MasterDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// MasterDlg 메시지 처리기


BOOL MasterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (CMainDlg*)AfxGetMainWnd();

	mTab.InsertItem(0, _T("곡 목록"));
	mTab.InsertItem(1, _T("앨범 목록"));
	mTab.InsertItem(2, _T("가수 목록"));

	mTab.SetCurSel(0);

	CRect rect;
	mTab.GetWindowRect(&rect);

	pSongDlg = new TabSong();
	pSongDlg->Create(IDD_SONGLIST, &mTab);
	pSongDlg->MoveWindow(0, 25, rect.Width(), rect.Height());
	pSongDlg->ShowWindow(SW_SHOW);

	pAlbumDlg = new TabAlbum();
	pAlbumDlg->Create(IDD_ALBUMLIST, &mTab);
	pAlbumDlg->MoveWindow(0, 25, rect.Width(), rect.Height());
	pAlbumDlg->ShowWindow(SW_HIDE);

	pSingerDlg = new TabSinger();
	pSingerDlg->Create(IDD_SINGERLIST, &mTab);
	pSingerDlg->MoveWindow(0, 25, rect.Width(), rect.Height());
	pSingerDlg->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void MasterDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pMasterDlg = NULL;

	delete this;

	CDialogEx::PostNcDestroy();
}




void MasterDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int sel = mTab.GetCurSel();
	SingerType singer;
	AlbumType album;
	CString str;

	switch (sel) {
	case 0:
		pSongDlg->ShowWindow(SW_SHOW);
		pAlbumDlg->ShowWindow(SW_HIDE);
		pSingerDlg->ShowWindow(SW_HIDE);
		pSongDlg->mComboSinger.ResetContent();
		pSongDlg->mComboAlbum.ResetContent();
		pSongDlg->mComboSinger.AddString(TEXT("Unknown"));
		pSongDlg->mComboAlbum.AddString(TEXT("Unknown"));
		parent->mData.ResetSingerPointer();
		for (int i = 0; i < parent->mData.GetSingerLength(); i++) {
			parent->mData.GetNextSinger(singer);
			pSongDlg->mComboSinger.AddString(singer.getName());
		}
		pSongDlg->mComboSinger.SetCurSel(0);
		pSongDlg->mComboAlbum.SetCurSel(0);
		break;
	case 1:
		pSongDlg->ShowWindow(SW_HIDE);
		pAlbumDlg->ShowWindow(SW_SHOW);
		pSingerDlg->ShowWindow(SW_HIDE);
		pAlbumDlg->mComboSinger.ResetContent();
		pAlbumDlg->mComboSinger.AddString(TEXT("Unknown"));
		parent->mData.ResetSingerPointer();
		for (int i = 0; i < parent->mData.GetSingerLength(); i++) {
			parent->mData.GetNextSinger(singer);
			pAlbumDlg->mComboSinger.AddString(singer.getName());
		}
		pAlbumDlg->mComboSinger.SetCurSel(0);
		parent->mData.ResetAlbumPointer();
		for (int i = 0; i < parent->mData.GetAlbumLength(); i++) {
			parent->mData.GetNextAlbum(album);
			str.Format(_T("%d"), parent->mData.GetSongLength(album));
			pAlbumDlg->mListCtrl.SetItem(i, 2, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		}
		break;
	case 2:
		pSongDlg->ShowWindow(SW_HIDE);
		pAlbumDlg->ShowWindow(SW_HIDE);
		pSingerDlg->ShowWindow(SW_SHOW);
		parent->mData.ResetSingerPointer();
		for (int i = 0; i < parent->mData.GetSingerLength(); i++) {
			parent->mData.GetNextSinger(singer);
			str.Format(_T("%d"), parent->mData.GetAlbumLength(singer));
			pSingerDlg->mListCtrl.SetItem(i, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
			str.Format(_T("%d"), parent->mData.GetSongLength(singer));
			pSingerDlg->mListCtrl.SetItem(i, 2, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		}
		break;
	}

	*pResult = 0;
}
