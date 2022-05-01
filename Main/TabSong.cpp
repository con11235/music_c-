// TabSong.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "TabSong.h"
#include "afxdialogex.h"


// TabSong 대화 상자
#include"MasterDlg.h"
#include"MainDlg.h"
#include"MasterInfo.h"


IMPLEMENT_DYNAMIC(TabSong, CDialogEx)

TabSong::TabSong(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SONGLIST, pParent)
{

}

TabSong::~TabSong()
{
}

void TabSong::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL, mListCtrl);
	DDX_Control(pDX, IDC_COMBO_SINGER, mComboSinger);
	DDX_Control(pDX, IDC_COMBO_ALBUM, mComboAlbum);
}


BEGIN_MESSAGE_MAP(TabSong, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &TabSong::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_REPLACE, &TabSong::OnBnClickedReplace)
	ON_BN_CLICKED(IDC_DEL, &TabSong::OnBnClickedDel)
	ON_BN_CLICKED(IDC_INFO, &TabSong::OnBnClickedInfo)
	ON_BN_CLICKED(IDC_SAVEFILE, &TabSong::OnBnClickedSavefile)
	ON_BN_CLICKED(IDC_GETFILE, &TabSong::OnBnClickedGetfile)
	ON_CBN_SELCHANGE(IDC_COMBO_SINGER, &TabSong::OnCbnSelchangeComboSinger)
END_MESSAGE_MAP()


// TabSong 메시지 처리기


void TabSong::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pSongDlg = NULL;

	delete this;

	CDialogEx::PostNcDestroy();
}


BOOL TabSong::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (MasterDlg*)GetParent();
	mparent = (CMainDlg*)AfxGetApp()->GetMainWnd();
	pInfoDlg = NULL;

	CRect rt;
	mListCtrl.GetWindowRect(&rt);
	mListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mListCtrl.InsertColumn(0, TEXT("ID"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(1, TEXT("곡명"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(2, TEXT("가수"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(3, TEXT("앨범"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(4, TEXT("좋아요"), LVCFMT_CENTER, rt.Width()*0.2);

	mparent->mData.ResetSongPointer();
	SongType song;
	CString str;
	for (int i = 0; i < mparent->mData.GetSongLength(); i++) {

		mparent->mData.GetNextSong(song);
		mListCtrl.InsertItem(i, song.getId());
		mListCtrl.SetItem(i, 1, LVIF_TEXT, song.getName(), NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 2, LVIF_TEXT, song.getSinger(), NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 3, LVIF_TEXT, song.getAlbum(), NULL, NULL, NULL, NULL);
		str.Format(_T("%d"), song.getNumLikes());
		mListCtrl.SetItem(i, 4, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

	}

	SingerType singer;
	AlbumType album;

	mComboSinger.AddString(TEXT("Unknown"));
	mComboAlbum.AddString(TEXT("Unknown"));
	mparent->mData.ResetSingerPointer();
	for (int i = 0; i < mparent->mData.GetSingerLength(); i++) {
		mparent->mData.GetNextSinger(singer);
		mComboSinger.AddString(singer.getName());
	}
	mComboSinger.SetCurSel(0);
	mparent->mData.ResetAlbumPointer();
	for (int i = 0; i < mparent->mData.GetAlbumLength(); i++) {
		mparent->mData.GetNextAlbum(album);
		mComboAlbum.AddString(album.getName());
	}
	mComboAlbum.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void TabSong::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int num, selS = mComboSinger.GetCurSel(), selA = mComboAlbum.GetCurSel();

	CString str, str1, str2, str3,str4;
	SongType song;
	AlbumType album;
	
	GetDlgItemTextW(IDC_EDIT_NAME, str1);
	song.setName(str1);
	mComboSinger.GetLBText(selS, str2);
	song.setSinger(str2);
	mComboAlbum.GetLBText(selA, str3);
	song.setAlbum(str3);
	album.setName(str3);
	GetDlgItemTextW(IDC_EDIT_LIKES, str4);
	song.setNumLikes(_ttoi(str4));
	str.Format(_T("%d"), mparent->mData.GetSongLength(album)+1);
	str = str3 + str;
	song.setId(str);
	num = mparent->mData.AddSong(song);


	mListCtrl.InsertItem(num, str);
	mListCtrl.SetItem(num, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
	mComboSinger.SetCurSel(selS);
	mComboAlbum.SetCurSel(selA);
}


void TabSong::OnBnClickedReplace()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mListCtrl.GetFirstSelectedItemPosition();
	int rep = mListCtrl.GetNextSelectedItem(pos), selS = mComboSinger.GetCurSel(), selA = mComboAlbum.GetCurSel();

	SongType song;
	CString str, str1, str2, str3, str4;

	GetDlgItemTextW(IDC_EDIT_NAME, str1);
	song.setName(str1);
	mComboSinger.GetLBText(selS, str2);
	song.setSinger(str2);
	mComboAlbum.GetLBText(selA, str3);
	song.setAlbum(str3);
	GetDlgItemTextW(IDC_EDIT_LIKES, str4);
	song.setNumLikes(_ttoi(str4));

	mListCtrl.SetItem(rep, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
}


void TabSong::OnBnClickedDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mListCtrl.GetFirstSelectedItemPosition();
	int idx = mListCtrl.GetNextSelectedItem(pos);
	mparent->mData.DeleteSong(idx);
	mListCtrl.DeleteItem(idx);
}


void TabSong::OnBnClickedInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mListCtrl.GetFirstSelectedItemPosition();
	int idx = mListCtrl.GetNextSelectedItem(pos);
	if (idx == -1)
		idx = 0;
	pInfoDlg = new MasterInfo();
	SongType song = mparent->mData.GetSong(idx);;
	AlbumType album;
	SingerType singer;
	album.setName(song.getAlbum());
	singer.setName(song.getSinger());
	mparent->mData.GetAlbum(album);
	mparent->mData.GetSinger(singer);
	pInfoDlg->mSong = song;
	pInfoDlg->mAlbum = album;
	pInfoDlg->mSinger = singer;
	pInfoDlg->Create(IDD_INFO_MASTER, GetDesktopWindow());
	pInfoDlg->ShowWindow(SW_SHOW);
}


void TabSong::OnBnClickedSavefile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString path;
	CFileDialog dlg(false);
	if (dlg.DoModal() == IDOK) {
		path = dlg.GetPathName();
	}
	else { return; }

	CFile file;
	CArchive ar(&file, CArchive::store);
	file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);

	CString str, str1, str2, str3, str4;

	int count = mListCtrl.GetItemCount();
	ar << count;
	for (int i = 0; i < count; i++) {
		str = mListCtrl.GetItemText(i, 0);
		str1 = mListCtrl.GetItemText(i, 1);
		str2 = mListCtrl.GetItemText(i, 2);
		str3 = mListCtrl.GetItemText(i, 3);
		str4 = mListCtrl.GetItemText(i, 4);

		ar << str << str1 << str2 << str3 << str4;
	}
	ar.Flush();

	ar.Close();
	file.Close();
}


void TabSong::OnBnClickedGetfile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString path;
	CFileDialog dlg(true);
	if (dlg.DoModal() == IDOK) {
		path = dlg.GetPathName();
	}
	else { return; }

	CFile file;
	CArchive ar(&file, CArchive::load);
	file.Open(path, CFile::modeRead);

	SongType song;
	CString str, str1, str2, str3, str4;
	int count, num;
	ar >> count;

	for (int i = 0; i < count; i++) {
		ar >> str >> str1 >> str2 >> str3 >> str4;

		song.setId(str);
		song.setName(str1);
		song.setSinger(str2);
		song.setAlbum(str3);
		song.setNumLikes(_ttoi(str4));

		num = mparent->mData.AddSong(song);
		if (num != -1) {
			mListCtrl.InsertItem(num, str);
		}
		else {
			num = mparent->mData.ReplaceSong(song);
		}
		mListCtrl.SetItem(num, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
	}

	ar.Close();
	file.Close();
}


void TabSong::OnCbnSelchangeComboSinger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int selS = mComboSinger.GetCurSel();

	CString str;
	AlbumType album;
	mComboSinger.GetLBText(selS, str);

	mComboAlbum.ResetContent();
	mComboAlbum.AddString(TEXT("Unknown"));
	mparent->mData.ResetAlbumPointer();
	for (int i = 0; i < mparent->mData.GetAlbumLength(); i++) {
		mparent->mData.GetNextAlbum(album);
		if(album.getSinger() ==str)
			mComboAlbum.AddString(album.getName());
	}
	mComboAlbum.SetCurSel(0);
}


