#ifndef KDEPIM_STATUSBARPROGRESSWIDGET_H
#define KDEPIM_STATUSBARPROGRESSWIDGET_H
/*
  statusbarprogresswidget.h

  (C) 2004 Till Adam <adam@kde.org>
           Don Sanders
           David Faure <dfaure@kde.org>
  Copyright 2004 David Faure <faure@kde.org>

  KMail is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  KMail is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  In addition, as a special exception, the copyright holders give
  permission to link the code of this program with any edition of
  the Qt library by Trolltech AS, Norway (or with modified versions
  of Qt that use the same license as Qt), and distribute linked
  combinations including the two.  You must obey the GNU General
  Public License in all respects for all of the code used other than
  Qt.  If you modify this file, you may extend this exception to
  your version of the file, but you are not obligated to do so.  If
  you do not wish to do so, delete this exception statement from
  your version.
*/
/**
  *  A specialized progress widget class, heavily based on
  *  kio_littleprogress_dlg (it looks similar)
  */

#include "kdepim_export.h"

#include <QFrame>

class QEvent;
class QProgressBar;
class QPushButton;
class QStackedWidget;
class QLabel;
class QTimer;

namespace KPIM {
class SSLLabel;
class ProgressItem;
class ProgressDialog;

class KDEPIM_EXPORT StatusbarProgressWidget : public QFrame
{
    Q_OBJECT

public:

    explicit StatusbarProgressWidget(ProgressDialog *progressDialog, QWidget *parent, bool button = true);

    void setShowTypeProgressItem(unsigned int type);
public Q_SLOTS:

    void slotClean();

    void slotProgressItemAdded(KPIM::ProgressItem *i);
    void slotProgressItemCompleted(KPIM::ProgressItem *i);
    void slotProgressItemProgress(KPIM::ProgressItem *i, unsigned int value);
    void slotProgressButtonClicked();

protected Q_SLOTS:
    void slotProgressDialogVisible(bool);
    void slotShowItemDelayed();
    void slotBusyIndicator();
    void updateBusyMode(KPIM::ProgressItem *);

protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    enum Mode {
        Progress,
        Clean
    };
    void setMode(Mode mode);
    void updateProgressButton(bool showingProgress);
    void connectSingleItem();
    void activateSingleItemMode();

    unsigned int mShowTypeProgressItem = 0;
    QProgressBar *mProgressBar = nullptr;
    QLabel *mLabel = nullptr;
    SSLLabel *mSslLabel = nullptr;
    QPushButton *mButton = nullptr;

    Mode mMode = Clean;
    bool mShowButton = false;
    bool mShowDetailedProgress = false;

    QStackedWidget *mStackedWidget = nullptr;
    ProgressItem *mCurrentItem = nullptr;
    ProgressDialog *mProgressDialog = nullptr;
    QTimer *mDelayTimer = nullptr;
    QTimer *mBusyTimer = nullptr;
    QTimer *mCleanTimer = nullptr;
};
} // namespace

#endif
