// UserDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Main.h"
#include "UserDlg.h"
#include "afxdialogex.h"


// UserDlg 대화 상자
#include"MainDlg.h"
#include"UserInfo.h"
#include"Mypage.h"

CFont mfont3;

IMPLEMENT_DYNAMIC(UserDlg, CDialogEx)

UserDlg::UserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER, pParent)
{

}

UserDlg::~UserDlg()
{
}

void UserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART, mChart);
	DDX_Control(pDX, IDC_CHART_SORT, mSortChart);
}


BEGIN_MESSAGE_MAP(UserDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_CHART_SORT, &UserDlg::OnCbnSelchangeChartSort)
	ON_BN_CLICKED(IDC_ADD_PL, &UserDlg::OnBnClickedAddPl)
	ON_BN_CLICKED(IDC_MYPAGE, &UserDlg::OnBnClickedMypage)
	ON_BN_CLICKED(IDC_INFO, &UserDlg::OnBnClickedInfo)
END_MESSAGE_MAP()


// UserDlg 메시지 처리기


void UserDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	parent->pUserDlg = NULL;
	
	delete this;

	CDialogEx::PostNcDestroy();
}


BOOL UserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	parent = (CMainDlg*)AfxGetMainWnd();
	pInfoDlg = NULL;
	pMypageDlg = NULL;

	CRect rt;
	mChart.GetWindowRect(&rt);
	mChart.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	mChart.InsertColumn(0, TEXT("순위"), LVCFMT_CENTER, rt.Width()*0.15);
	mChart.InsertColumn(1, TEXT("곡명"), LVCFMT_CENTER, rt.Width()*0.28);
	mChart.InsertColumn(2, TEXT("가수명"), LVCFMT_CENTER, rt.Width()*0.28);
	mChart.InsertColumn(3, TEXT("앨범"), LVCFMT_CENTER, rt.Width()*0.28);

	parent->mData.UpdateChart();
	parent->mData.ResetChartPointer();
	PlayItemType song;
	CString str;
	for (int i = 0; i < parent->mData.GetChartLength(); i++) {

		parent->mData.GetNextChart(song);
		str.Format(_T("%d"), i+1);
		mChart.InsertItem(i,str);
		mChart.SetItem(i, 1, LVIF_TEXT, song.getSong(), NULL, NULL, NULL, NULL);
		mChart.SetItem(i, 2, LVIF_TEXT, song.getSinger(), NULL, NULL, NULL, NULL);
		mChart.SetItem(i, 3, LVIF_TEXT, song.getAlbum(), NULL, NULL, NULL, NULL);

	}

	mSortChart.AddString(TEXT("앨범순"));
	mSortChart.AddString(TEXT("곡명순"));
	mSortChart.AddString(TEXT("가수순"));
	mSortChart.AddString(TEXT("인기순"));
	mSortChart.SetCurSel(3);
	
	mfont3.CreateFont(20, 8, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("휴먼엑스포"));
	GetDlgItem(IDC_TITLE)->SetFont(&mfont3);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void UserDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
	//CDialogEx::OnCancel();
}


void UserDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	this->DestroyWindow();
	//CDialogEx::OnClose();
}


void UserDlg::OnCbnSelchangeChartSort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int selS = mSortChart.GetCurSel();
	if (selS == 3)
		selS = 5;
	parent->mData.UpdateChart(selS);
	parent->mData.ResetChartPointer();
	PlayItemType song;
	CString str;
	mChart.DeleteAllItems();
	for (int i = 0; i < parent->mData.GetChartLength(); i++) {
		parent->mData.GetNextChart(song);
		str.Format(_T("%d"), i + 1);
		mChart.InsertItem(i, str);
		mChart.SetItem(i, 1, LVIF_TEXT, song.getSong(), NULL, NULL, NULL, NULL);
		mChart.SetItem(i, 2, LVIF_TEXT, song.getSinger(), NULL, NULL, NULL, NULL);
		mChart.SetItem(i, 3, LVIF_TEXT, song.getId(), NULL, NULL, NULL, NULL);

	}
}



void UserDlg::OnBnClickedAddPl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = mChart.GetFirstSelectedItemPosition();
	int idx = mChart.GetNextSelectedItem(pos);
	PlayItemType item = parent->mData.GetChartItem(idx);
	parent->mData.AddToPL(item);
}


void UserDlg::OnBnClickedMypage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pMypageDlg = new Mypage();
	pMypageDlg->Create(IDD_MYPAGE, GetDesktopWindow());
	pMypageDlg->ShowWindow(SW_SHOW);
}


void UserDlg::OnBnClickedInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	POSITION pos;
	pos = mChart.GetFirstSelectedItemPosition();
	int idx = mChart.GetNextSelectedItem(pos);
	if (idx == -1)
		idx = 0;
	pInfoDlg = new UserInfo();
	PlayItemType item = parent->mData.GetChartItem(idx);
	SongType song;
	AlbumType album;
	SingerType singer;
	song.setId(item.getId());
	album.setName(item.getAlbum());
	singer.setName(item.getSinger());
	parent->mData.GetSong(song);
	parent->mData.GetAlbum(album);
	parent->mData.GetSinger(singer);
	pInfoDlg->mSong = song;
	pInfoDlg->mAlbum = album;
	pInfoDlg->mSinger = singer;
	pInfoDlg->Create(IDD_INFO_USER, GetDesktopWindow());
	pInfoDlg->ShowWindow(SW_SHOW);
}
