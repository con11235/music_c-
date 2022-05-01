// TabAlbum.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "TabAlbum.h"
#include "afxdialogex.h"

#include "AlbumType.h"


// TabAlbum 대화 상자
#include"MasterDlg.h"
#include"MainDlg.h"
#include"MasterInfo2.h"

IMPLEMENT_DYNAMIC(TabAlbum, CDialogEx)

TabAlbum::TabAlbum(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALBUMLIST, pParent)
{

}

TabAlbum::~TabAlbum()
{
}

void TabAlbum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL, mListCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, mDate);
	DDX_Control(pDX, IDC_COMBO_GENRE, mComboGenre);
	DDX_Control(pDX, IDC_COMBO_SINGER, mComboSinger);
	DDX_Control(pDX, IDC_COMBO_TYPE, mComboType);
}


BEGIN_MESSAGE_MAP(TabAlbum, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &TabAlbum::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &TabAlbum::OnBnClickedDel)
	ON_BN_CLICKED(IDC_REPLACE, &TabAlbum::OnBnClickedReplace)
	ON_BN_CLICKED(IDC_INFO, &TabAlbum::OnBnClickedInfo)
	ON_BN_CLICKED(IDC_SAVEFILE, &TabAlbum::OnBnClickedSavefile)
	ON_BN_CLICKED(IDC_GETFILE, &TabAlbum::OnBnClickedGetfile)
END_MESSAGE_MAP()


// TabAlbum 메시지 처리기


void TabAlbum::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pAlbumDlg = NULL;

	delete this;

	CDialogEx::PostNcDestroy();
}


BOOL TabAlbum::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (MasterDlg*)GetParent();
	mparent = (CMainDlg*)AfxGetApp()->GetMainWnd();
	pInfoDlg = NULL;

	CRect rt;
	mListCtrl.GetWindowRect(&rt);
	mListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mListCtrl.InsertColumn(0, TEXT("앨범명"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(1, TEXT("가수"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(2, TEXT("곡 수"), LVCFMT_CENTER, rt.Width()*0.1);
	mListCtrl.InsertColumn(3, TEXT("발매일"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(4, TEXT("장르"), LVCFMT_CENTER, rt.Width()*0.1);
	mListCtrl.InsertColumn(5, TEXT("타입"), LVCFMT_CENTER, rt.Width()*0.1);
	mListCtrl.InsertColumn(6, TEXT("좋아요"), LVCFMT_CENTER, rt.Width()*0.1);

	mparent->mData.ResetAlbumPointer();
	AlbumType album;
	CString str;
	for (int i = 0; i < mparent->mData.GetAlbumLength(); i++) {

		mparent->mData.GetNextAlbum(album);
		mListCtrl.InsertItem(i, album.getName());
		mListCtrl.SetItem(i, 1, LVIF_TEXT, album.getSinger(), NULL, NULL, NULL, NULL);
		str.Format(_T("%d"), mparent->mData.GetSongLength(album));
		mListCtrl.SetItem(i, 2, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 3, LVIF_TEXT, album.getComeout(), NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 4, LVIF_TEXT, album.getGenre(), NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 5, LVIF_TEXT, album.getType(), NULL, NULL, NULL, NULL);
		str.Format(_T("%d"), album.getNumLikes());
		mListCtrl.SetItem(i, 6, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

	}


	mComboType.AddString(TEXT("Unknown"));
	mComboType.AddString(TEXT("정규"));
	mComboType.AddString(TEXT("OST"));
	mComboType.AddString(TEXT("싱글"));
	mComboGenre.AddString(TEXT("Unknown"));
	mComboGenre.AddString(TEXT("알앤비/소울"));
	mComboGenre.AddString(TEXT("일렉트로닉"));
	mComboGenre.AddString(TEXT("댄스/팝"));
	mComboGenre.AddString(TEXT("팝"));
	mComboGenre.AddString(TEXT("발라드"));

	mComboType.SetCurSel(0);
	mComboGenre.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TabAlbum::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num, selS = mComboSinger.GetCurSel(), selG = mComboGenre.GetCurSel(), selT = mComboType.GetCurSel();

	CString str, str1, str2, str3, str4, str5, str6;
	AlbumType album;

	GetDlgItemTextW(IDC_EDIT_NAME, str);
	album.setName(str);
	mComboSinger.GetLBText(selS, str1);
	album.setSinger(str1);
	str2.Format(_T("%d"), 0);
	CTime date;
	mDate.GetTime(date);
	str3 = date.Format("%Y%m%d");
	album.setComeout(str3);
	mComboGenre.GetLBText(selG, str4);
	album.setGenre(str4);
	mComboType.GetLBText(selT, str5);
	album.setType(str5);
	GetDlgItemTextW(IDC_EDIT_LIKES, str6);
	album.setNumLikes(_ttoi(str6));
	num = mparent->mData.AddAlbum(album);

	mListCtrl.InsertItem(num, str);
	mListCtrl.SetItem(num, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 5, LVIF_TEXT, str5, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 6, LVIF_TEXT, str6, NULL, NULL, NULL, NULL);
}


void TabAlbum::OnBnClickedDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mListCtrl.GetFirstSelectedItemPosition();
	int idx = mListCtrl.GetNextSelectedItem(pos);
	mparent->mData.DeleteAlbum(idx);
	mListCtrl.DeleteItem(idx);
}


void TabAlbum::OnBnClickedReplace()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int selS = mComboSinger.GetCurSel(), selG = mComboGenre.GetCurSel(), selT = mComboType.GetCurSel(), rep;

	AlbumType album;
	CString str, str1, str2, str3, str4, str5, str6;

	GetDlgItemTextW(IDC_EDIT_NAME, str);
	album.setName(str);
	mComboSinger.GetLBText(selS, str1);
	CTime date;
	mDate.GetTime(date);
	str3 = date.Format("%Y%m%d");
	album.setComeout(str3);
	mComboGenre.GetLBText(selG, str4);
	album.setGenre(str4);
	mComboType.GetLBText(selT, str5);
	album.setType(str5);
	GetDlgItemTextW(IDC_EDIT_LIKES, str6);
	album.setNumLikes(_ttoi(str6));

	rep = mparent->mData.ReplaceAlbum(album);
	if (rep == -1) {
		rep = mparent->mData.AddAlbum(album);
		mListCtrl.InsertItem(rep, str);
	}
	str2.Format(_T("%d"), mparent->mData.GetSongLength(album));
	mListCtrl.SetItem(rep, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 5, LVIF_TEXT, str5, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 6, LVIF_TEXT, str6, NULL, NULL, NULL, NULL);
}


void TabAlbum::OnBnClickedInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mListCtrl.GetFirstSelectedItemPosition();
	int idx = mListCtrl.GetNextSelectedItem(pos);
	if (idx == -1)
		idx = 0;
	pInfoDlg = new MasterInfo2();
	AlbumType album = mparent->mData.GetAlbum(idx);
	SingerType singer;
	album.setName(album.getName());
	singer.setName(album.getSinger());
	mparent->mData.GetAlbum(album);
	mparent->mData.GetSinger(singer);
	pInfoDlg->mAlbum = album;
	pInfoDlg->mSinger = singer;
	pInfoDlg->Create(IDD_INFO_MASTER2, GetDesktopWindow());
	pInfoDlg->ShowWindow(SW_SHOW);
}


void TabAlbum::OnBnClickedSavefile()
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

	CString str, str1, str3, str4, str5, str6;

	int count = mListCtrl.GetItemCount();
	ar << count;
	for (int i = 0; i < count; i++) {
		str = mListCtrl.GetItemText(i, 0);
		str1 = mListCtrl.GetItemText(i, 1);
		str3 = mListCtrl.GetItemText(i, 3);
		str4 = mListCtrl.GetItemText(i, 4);
		str5 = mListCtrl.GetItemText(i, 5);
		str6 = mListCtrl.GetItemText(i, 6);

		ar << str << str1 << str3 << str4 << str5 << str6;
	}
	ar.Flush();

	ar.Close();
	file.Close();
}


void TabAlbum::OnBnClickedGetfile()
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

	AlbumType album;
	CString str, str1, str2, str3, str4, str5, str6;
	int count, num;
	ar >> count;

	for (int i = 0; i < count; i++) {
		ar >> str >> str1 >> str3 >> str4 >> str5 >> str6;

		album.setName(str);
		album.setSinger(str1);
		album.setComeout(str3);
		album.setGenre(str4);
		album.setType(str5);
		album.setNumLikes(_ttoi(str6));

		num = mparent->mData.AddAlbum(album);
		if (num != -1) {
			mListCtrl.InsertItem(num, str);
		}
		else {
			num = mparent->mData.ReplaceAlbum(album);
		}
		str2.Format(_T("%d"), mparent->mData.GetSongLength(album));
		mListCtrl.SetItem(num, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 5, LVIF_TEXT, str5, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(num, 6, LVIF_TEXT, str6, NULL, NULL, NULL, NULL);
	}

	ar.Close();
	file.Close();
}
