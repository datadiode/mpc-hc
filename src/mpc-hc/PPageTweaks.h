/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2013, 2015 see Authors.txt
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

#pragma once

#include "CMPCThemePPageBase.h"
#include "CMPCThemeComboBox.h"
#include "CMPCThemeSpinButtonCtrl.h"
#include "CMPCThemeStaticLink.h"

// CPPageTweaks dialog

class CPPageTweaks : public CMPCThemePPageBase
{
    DECLARE_DYNAMIC(CPPageTweaks)

public:
    CPPageTweaks();
    virtual ~CPPageTweaks();

    // Dialog Data
    enum { IDD = IDD_PPAGETWEAKS };
    int m_nJumpDistS;
    int m_nJumpDistM;
    int m_nJumpDistL;
    double m_x1;
    double m_x2;
    double m_x3;
    double m_x4;
    double m_x5;
    double m_x6;
    BOOL m_fNotifySkype;

    BOOL m_fPreventMinimize;
    BOOL m_fUseSearchInFolder;
    BOOL m_bHideWindowedMousePointer;
    CMPCThemeComboBox m_FastSeekMethod;
    CMPCThemeStaticLink m_MatrixCalcSluLink;

    BOOL m_fFastSeek;
    BOOL m_fLCDSupport;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual BOOL OnApply();

    DECLARE_MESSAGE_MAP()

public:
    afx_msg BOOL OnToolTipNotify(UINT id, NMHDR* pNMH, LRESULT* pResult);
    afx_msg void OnUpdateFastSeek(CCmdUI* pCmdUI);
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
};
