#pragma once
#pragma comment(lib, "winmm")
#include <mmsystem.h>
#include<atlimage.h>

class UserDlg;
class CMainDlg;
// Mypage 대화 상자


class Mypage : public CDialogEx
{
	DECLARE_DYNAMIC(Mypage)

public:
	Mypage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Mypage();

	UserDlg *parent;
	CMainDlg *mparent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CImage m_Img;
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	CListCtrl mPlayList;
	CComboBox mComboSort;
	afx_msg void OnCbnSelchangeSortList();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedPlaysong();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedBefore();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
