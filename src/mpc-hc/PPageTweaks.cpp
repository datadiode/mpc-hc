/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2015, 2017 see Authors.txt
 *
 * This file is part of MPC-HC.
 *
 * MPC-HC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-HC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "stdafx.h"
#include <VersionHelpersInternal.h>
#include "mplayerc.h"
#include "PPageTweaks.h"
#include "MainFrm.h"
#include "SimpleIni.h"


// CPPageTweaks dialog

IMPLEMENT_DYNAMIC(CPPageTweaks, CMPCThemePPageBase)
CPPageTweaks::CPPageTweaks()
    : CMPCThemePPageBase(CPPageTweaks::IDD, CPPageTweaks::IDD)
    , m_nJumpDistS(0)
    , m_nJumpDistM(0)
    , m_nJumpDistL(0)
    , m_x1(1)
    , m_x2(0)
    , m_x3(0)
    , m_x4(0)
    , m_x5(1)
    , m_x6(0)
    , m_fNotifySkype(TRUE)
    , m_fPreventMinimize(FALSE)
    , m_fUseSearchInFolder(FALSE)
    , m_bHideWindowedMousePointer(TRUE)
    , m_MatrixCalcSluLink(_T("https://matrixcalc.org/slu.html"))
    , m_fFastSeek(FALSE)
    , m_fLCDSupport(FALSE)
{
}

CPPageTweaks::~CPPageTweaks()
{
}

void CPPageTweaks::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_nJumpDistS);
    DDX_Text(pDX, IDC_EDIT2, m_nJumpDistM);
    DDX_Text(pDX, IDC_EDIT3, m_nJumpDistL);
    DDX_Text(pDX, IDC_EDIT4, m_x1);
    DDX_Text(pDX, IDC_EDIT5, m_x2);
    DDX_Text(pDX, IDC_EDIT6, m_x3);
    DDX_Text(pDX, IDC_EDIT7, m_x4);
    DDX_Text(pDX, IDC_EDIT8, m_x5);
    DDX_Text(pDX, IDC_EDIT9, m_x6);
    DDX_Check(pDX, IDC_CHECK4, m_fNotifySkype);
    DDX_Check(pDX, IDC_CHECK6, m_fPreventMinimize);
    DDX_Check(pDX, IDC_CHECK7, m_fUseSearchInFolder);
    DDX_Control(pDX, IDC_COMBO4, m_FastSeekMethod);
    DDX_Control(pDX, IDC_STATICLINK, m_MatrixCalcSluLink);
    DDX_Check(pDX, IDC_FASTSEEK_CHECK, m_fFastSeek);
    DDX_Check(pDX, IDC_CHECK_LCD, m_fLCDSupport);
    DDX_Check(pDX, IDC_CHECK3, m_bHideWindowedMousePointer);
}

BOOL CPPageTweaks::OnInitDialog()
{
    __super::OnInitDialog();

    SetHandCursor(m_hWnd, IDC_COMBO1);

    m_MatrixCalcSluLink.SetWindowText(_T("https://matrixcalc.org/slu.html"));

    const CAppSettings& s = AfxGetAppSettings();

    m_nJumpDistS = s.nJumpDistS;
    m_nJumpDistM = s.nJumpDistM;
    m_nJumpDistL = s.nJumpDistL;
    m_fNotifySkype = s.bNotifySkype;

    m_x1 = s.x1;
    m_x2 = s.x2;
    m_x3 = s.x3;
    m_x4 = s.x4;
    m_x5 = s.x5;
    m_x6 = s.x6;

    m_fPreventMinimize = s.fPreventMinimize;

    m_fUseSearchInFolder = s.fUseSearchInFolder;


    m_fFastSeek = s.bFastSeek;
    m_FastSeekMethod.AddString(ResStr(IDS_FASTSEEK_LATEST));
    m_FastSeekMethod.AddString(ResStr(IDS_FASTSEEK_NEAREST));
    m_FastSeekMethod.SetCurSel(s.eFastSeekMethod);
    m_bHideWindowedMousePointer = s.bHideWindowedMousePointer;

    m_fLCDSupport = s.fLCDSupport;

    CreateToolTip();
    EnableThemedDialogTooltips(this);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPPageTweaks::OnApply()
{
    UpdateData();

    CAppSettings& s = AfxGetAppSettings();

    s.nJumpDistS = m_nJumpDistS;
    s.nJumpDistM = m_nJumpDistM;
    s.nJumpDistL = m_nJumpDistL;
    s.bNotifySkype = !!m_fNotifySkype;

    s.x1 = m_x1;
    s.x2 = m_x2;
    s.x3 = m_x3;
    s.x4 = m_x4;
    s.x5 = m_x5;
    s.x6 = m_x6;

    s.fPreventMinimize = !!m_fPreventMinimize;
    s.fUseSearchInFolder = !!m_fUseSearchInFolder;

    s.bHideWindowedMousePointer = !!m_bHideWindowedMousePointer;


    s.fLCDSupport = !!m_fLCDSupport;

    s.bFastSeek = !!m_fFastSeek;
    s.eFastSeekMethod = static_cast<decltype(s.eFastSeekMethod)>(m_FastSeekMethod.GetCurSel());
    return __super::OnApply();
}

BEGIN_MESSAGE_MAP(CPPageTweaks, CMPCThemePPageBase)
    ON_UPDATE_COMMAND_UI(IDC_COMBO4, OnUpdateFastSeek)
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
END_MESSAGE_MAP()


// CPPageTweaks message handlers

void CPPageTweaks::OnUpdateFastSeek(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(IsDlgButtonChecked(IDC_FASTSEEK_CHECK));
}

void CPPageTweaks::OnBnClickedButton1()
{
    m_nJumpDistS = DEFAULT_JUMPDISTANCE_1;
    m_nJumpDistM = DEFAULT_JUMPDISTANCE_2;
    m_nJumpDistL = DEFAULT_JUMPDISTANCE_3;

    UpdateData(FALSE);
    SetModified();
}

void CPPageTweaks::OnBnClickedButton2()
{
    CFileDialog dlg(TRUE, _T("ini"), _T("mpc-hc-gps.ini"), OFN_FILEMUSTEXIST, _T("*.ini|*.ini|"));
    if (CMainFrame::DoFileDialogWithLastFolder(dlg, AfxGetAppSettings().lastGpsImportExportPath) == IDOK) {
        CSimpleIni ini;
        if (SI_Error err = ini.LoadFile(dlg.GetPathName()); err >= 0) {
            m_x1 = ini.GetDoubleValue(_T("Settings"), _T("x1"), 1);
            m_x2 = ini.GetDoubleValue(_T("Settings"), _T("x2"), 0);
            m_x3 = ini.GetDoubleValue(_T("Settings"), _T("x3"), 0);
            m_x4 = ini.GetDoubleValue(_T("Settings"), _T("x4"), 0);
            m_x5 = ini.GetDoubleValue(_T("Settings"), _T("x5"), 1);
            m_x6 = ini.GetDoubleValue(_T("Settings"), _T("x6"), 0);
            UpdateData(FALSE);
            SetModified();
        } else {
            CString msg;
            msg.Format(_T("CSimpleIni::LoadFile() failed with error %d"), err);
            AfxMessageBox(msg, MB_ICONSTOP);
        }
    }
}

void CPPageTweaks::OnBnClickedButton3()
{
    if (!UpdateData())
        return;
    CFileDialog dlg(FALSE, _T("ini"), _T("mpc-hc-gps.ini"), OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, _T("*.ini|*.ini|"));
    if (CMainFrame::DoFileDialogWithLastFolder(dlg, AfxGetAppSettings().lastGpsImportExportPath) == IDOK) {
        CSimpleIni ini;
        ini.SetDoubleValue(_T("Settings"), _T("x1"), m_x1);
        ini.SetDoubleValue(_T("Settings"), _T("x2"), m_x2);
        ini.SetDoubleValue(_T("Settings"), _T("x3"), m_x3);
        ini.SetDoubleValue(_T("Settings"), _T("x4"), m_x4);
        ini.SetDoubleValue(_T("Settings"), _T("x5"), m_x5);
        ini.SetDoubleValue(_T("Settings"), _T("x6"), m_x6);
        if (SI_Error err = ini.SaveFile(dlg.GetPathName()); err < 0) {
            CString msg;
            msg.Format(_T("CSimpleIni::SaveFile() failed with error %d"), err);
            AfxMessageBox(msg, MB_ICONSTOP);
        }
    }
}

void CPPageTweaks::OnBnClickedButton4()
{
    m_x1 = 1;
    m_x2 = 0;
    m_x3 = 0;
    m_x4 = 0;
    m_x5 = 1;
    m_x6 = 0;

    UpdateData(FALSE);
    SetModified();
}

BOOL CPPageTweaks::OnToolTipNotify(UINT id, NMHDR* pNMH, LRESULT* pResult)
{
    LPTOOLTIPTEXT pTTT = reinterpret_cast<LPTOOLTIPTEXT>(pNMH);

    UINT_PTR nID = pNMH->idFrom;
    if (pTTT->uFlags & TTF_IDISHWND) {
        nID = ::GetDlgCtrlID((HWND)nID);
    }

    BOOL bRet = FALSE;

    switch (nID) {
        case IDC_COMBO4:
            bRet = FillComboToolTip(m_FastSeekMethod, pTTT);
            break;
    }

    if (bRet) {
        PlaceThemedDialogTooltip(nID);
    }

    return bRet;
}
