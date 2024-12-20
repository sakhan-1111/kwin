/*
    SPDX-FileCopyrightText: 2021 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/inputdevice.h"

#include <QSet>

namespace KWin
{

class KWIN_EXPORT FakeInputDevice : public InputDevice
{
    Q_OBJECT

public:
    explicit FakeInputDevice(QObject *parent = nullptr);

    QString name() const override;

    bool isEnabled() const override;
    void setEnabled(bool enabled) override;

    bool isKeyboard() const override;
    bool isPointer() const override;
    bool isTouchpad() const override;
    bool isTouch() const override;
    bool isTabletTool() const override;
    bool isTabletPad() const override;
    bool isTabletModeSwitch() const override;
    bool isLidSwitch() const override;

    void setAuthenticated(bool authenticated);
    bool isAuthenticated() const;

    QSet<quint32> pressedButtons;
    QSet<quint32> pressedKeys;
    QSet<quint32> activeTouches;

private:
    QString m_name;
    bool m_authenticated = false;
};

} // namespace KWin
