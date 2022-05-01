// TabSinger.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "TabSinger.h"
#include "afxdialogex.h"

#include "SingerType.h"

// TabSinger 대화 상자
#include"MasterDlg.h"
#include"MainDlg.h"
#include"MasterInfo3.h"

IMPLEMENT_DYNAMIC(TabSinger, CDialogEx)

TabSinger::TabSinger(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SINGERLIST, pParent)
{

}

TabSinger::~TabSinger()
{
}

void TabSinger::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL, mListCtrl);
	DDX_Control(pDX, IDC_COMBO_TYPE, mComboType);
	DDX_Control(pDX, IDC_COMBO_GENRE, mComboGenre);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, mDate);
}


BEGIN_MESSAGE_MAP(TabSinger, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &TabSinger::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &TabSinger::OnBnClickedDel)
	ON_BN_CLICKED(IDC_REPLACE, &TabSinger::OnBnClickedReplace)
	ON_BN_CLICKED(IDC_SAVEFILE, &TabSinger::OnBnClickedSavefile)
	ON_BN_CLICKED(IDC_GETFILE, &TabSinger::OnBnClickedGetfile)
	ON_BN_CLICKED(IDC_INFO, &TabSinger::OnBnClickedInfo)
END_MESSAGE_MAP()


// TabSinger 메시지 처리기


void TabSinger::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pSingerDlg = NULL;

	delete this;

	CDialogEx::PostNcDestroy();
}


BOOL TabSinger::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (MasterDlg*)AfxGetMainWnd();
	mparent = (CMainDlg*)AfxGetApp()->GetMainWnd();
	pInfoDlg = NULL;

	//List Control 초기화
	CRect rt;
	mListCtrl.GetWindowRect(&rt);
	mListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mListCtrl.InsertColumn(0, TEXT("가수명"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(1, TEXT("앨범 수"), LVCFMT_CENTER, rt.Width()*0.1);
	mListCtrl.InsertColumn(2, TEXT("곡 수"), LVCFMT_CENTER, rt.Width()*0.1);
	mListCtrl.InsertColumn(3, TEXT("데뷔일"), LVCFMT_CENTER, rt.Width()*0.2);
	mListCtrl.InsertColumn(4, TEXT("장르"), LVCFMT_CENTER, rt.Width()*0.1);
	mListCtrl.InsertColumn(5, TEXT("타입"), LVCFMT_CENTER, rt.Width()*0.1);
	mListCtrl.InsertColumn(6, TEXT("좋아요"), LVCFMT_CENTER, rt.Width()*0.1);

	
	mparent->mData.ResetSingerPointer();
	SingerType singer;
	CString str;
	for (int i = 0; i < mparent->mData.GetSingerLength(); i++) {
	
		mparent->mData.GetNextSinger(singer);
		mListCtrl.InsertItem(i, singer.getName());
		str.Format(_T("%d"), mparent->mData.GetAlbumLength(singer));
		mListCtrl.SetItem(i, 1, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		str.Format(_T("%d"), mparent->mData.GetSongLength(singer));
		mListCtrl.SetItem(i, 2, LVIF_TEXT, str, NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 3, LVIF_TEXT, singer.getDebutYear(), NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 4, LVIF_TEXT, singer.getGenre(), NULL, NULL, NULL, NULL);
		mListCtrl.SetItem(i, 5, LVIF_TEXT, singer.getType(), NULL, NULL, NULL, NULL);
		str.Format(_T("%d"), singer.getNumLikes());
		mListCtrl.SetItem(i, 6, LVIF_TEXT, str, NULL, NULL, NULL, NULL);

	}
	

	mComboType.AddString(TEXT("Unknown"));
	mComboType.AddString(TEXT("솔로(여성)"));
	mComboType.AddString(TEXT("그룹(여성)"));
	mComboType.AddString(TEXT("솔로(남성)"));
	mComboType.AddString(TEXT("그룹(남성)"));
	mComboGenre.AddString(TEXT("Unknown"));
	mComboGenre.AddString(TEXT("알앤비/소울"));
	mComboGenre.AddString(TEXT("일렉트로닉"));
	mComboGenre.AddString(TEXT("댄스/팝"));
	mComboGenre.AddString(TEXT("인디"));
	mComboGenre.AddString(TEXT("발라드"));

	mComboType.SetCurSel(0);
	mComboGenre.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TabSinger::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num, selG = mComboGenre.GetCurSel(), selT = mComboType.GetCurSel();

	CString str, str1, str2, str3, str4, str5, str6;
	SingerType singer;

	GetDlgItemTextW(IDC_EDIT_NAME, str);
	singer.setName(str);
	str1.Format(_T("%d"), 0);
	str2.Format(_T("%d"), 0);
	CTime date;
	mDate.GetTime(date);
	str3 = date.Format("%Y%m%d");
	singer.setDebutYear(str3);
	mComboGenre.GetLBText(selG, str4);
	singer.setGenre(str4);
	mComboType.GetLBText(selT, str5);
	singer.setType(str5);
	GetDlgItemTextW(IDC_EDIT_LIKES, str6);
	singer.setNumLikes(_ttoi(str6));
	num = mparent->mData.AddSinger(singer);

	mListCtrl.InsertItem(num, str);
	mListCtrl.SetItem(num, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 5, LVIF_TEXT, str5, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(num, 6, LVIF_TEXT, str6, NULL, NULL, NULL, NULL);
}


void TabSinger::OnBnClickedDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mListCtrl.GetFirstSelectedItemPosition();
	int idx = mListCtrl.GetNextSelectedItem(pos);
	mparent->mData.DeleteSinger(idx);
	mListCtrl.DeleteItem(idx);
}


void TabSinger::OnBnClickedReplace()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int selG = mComboGenre.GetCurSel(), selT = mComboType.GetCurSel(),rep;

	SingerType singer;
	CString str, str1, str2, str3, str4, str5, str6;

	GetDlgItemTextW(IDC_EDIT_NAME, str);
	singer.setName(str);
	CTime date;
	mDate.GetTime(date);
	str3 = date.Format("%Y%m%d");
	singer.setDebutYear(str3);
	mComboGenre.GetLBText(selG, str4);
	singer.setGenre(str4);
	mComboType.GetLBText(selT, str5);
	singer.setType(str5);
	GetDlgItemTextW(IDC_EDIT_LIKES, str6);
	singer.setNumLikes(_ttoi(str6));

	rep = mparent->mData.ReplaceSinger(singer);
	if (rep == -1) {
		rep = mparent->mData.AddSinger(singer);
		mListCtrl.InsertItem(rep, str);
	}
	str1.Format(_T("%d"), mparent->mData.GetAlbumLength(singer));
	str2.Format(_T("%d"), mparent->mData.GetSongLength(singer));
	mListCtrl.SetItem(rep, 1, LVIF_TEXT, str1, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 2, LVIF_TEXT, str2, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 3, LVIF_TEXT, str3, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 4, LVIF_TEXT, str4, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 5, LVIF_TEXT, str5, NULL, NULL, NULL, NULL);
	mListCtrl.SetItem(rep, 6, LVIF_TEXT, str6, NULL, NULL, NULL, NULL);
}


void TabSinger::OnBnClickedSavefile()
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

	CString str, str3, str4, str5, str6;

	int count = mListCtrl.GetItemCount();
	ar << count;
	for (int i = 0; i < count; i++) {
		str = mListCtrl.GetItemText(i, 0);
		str3 = mListCtrl.GetItemText(i, 3);
		str4 = mListCtrl.GetItemText(i, 4);
		str5 = mListCtrl.GetItemText(i, 5);
		str6 = mListCtrl.GetItemText(i, 6);

		ar << str << str3 << str4 << str5 << str6;
	}
	ar.Flush();

	ar.Close();
	file.Close();
}


void TabSinger::OnBnClickedGetfile()
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

	SingerType singer;
	CString str, str1, str2, str3, str4, str5, str6;
	int count, num;
	ar >> count;

	for (int i = 0; i < count; i++) {
		ar >> str >> str3 >> str4 >> str5 >> str6;

		singer.setName(str);
		singer.setDebutYear(str3);
		singer.setGenre(str4);
		singer.setType(str5);
		singer.setNumLikes(_ttoi(str6));

		num = mparent->mData.AddSinger(singer);
		if (num != -1) {
			mListCtrl.InsertItem(num, str);
		}
		else {
			num = mparent->mData.ReplaceSinger(singer);
		}
		str1.Format(_T("%d"), mparent->mData.GetAlbumLength(singer));
		str2.Format(_T("%d"), mparent->mData.GetSongLength(singer));
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


void TabSinger::OnBnClickedInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mListCtrl.GetFirstSelectedItemPosition();
	int idx = mListCtrl.GetNextSelectedItem(pos);
	if (idx == -1)
		idx = 0;
	pInfoDlg = new MasterInfo3();
	SingerType singer = mparent->mData.GetSinger(idx);
	pInfoDlg->mSinger = singer;
	pInfoDlg->Create(IDD_INFO_MASTER3, GetDesktopWindow());
	pInfoDlg->ShowWindow(SW_SHOW);

}
