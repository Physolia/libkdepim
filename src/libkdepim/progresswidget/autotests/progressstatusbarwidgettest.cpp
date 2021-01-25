/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "progressstatusbarwidgettest.h"
#include "../progressstatusbarwidget.h"
#include <QTest>
#include "../progressdialog.h"
#include "../statusbarprogresswidget.h"
QTEST_MAIN(ProgressStatusBarWidgetTest)

ProgressStatusBarWidgetTest::ProgressStatusBarWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void ProgressStatusBarWidgetTest::shouldHaveDefaultValue()
{
    auto widget = new QWidget;
    KPIM::ProgressStatusBarWidget w(widget, widget);
    widget->show();

    auto *progressDialog = widget->findChild<KPIM::ProgressDialog *>(QStringLiteral("progressDialog"));
    QVERIFY(progressDialog);
    QVERIFY(progressDialog->isHidden());

    auto *mLittleProgress = widget->findChild<KPIM::StatusbarProgressWidget *>(QStringLiteral("littleprogress"));
    QVERIFY(mLittleProgress);
    QVERIFY(mLittleProgress->isVisible());

    QCOMPARE(mLittleProgress, w.littleProgress());
}
