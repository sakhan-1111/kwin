/*
    KWin - the KDE window manager
    This file is part of the KDE project.

    SPDX-FileCopyrightText: 2018 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QPainter>

#include <KDecoration3/Decoration>
#include <KPluginFactory>

class FakeDecoWithShadows : public KDecoration3::Decoration
{
    Q_OBJECT

public:
    explicit FakeDecoWithShadows(QObject *parent = nullptr, const QVariantList &args = QVariantList())
        : Decoration(parent, args)
    {
    }
    ~FakeDecoWithShadows() override
    {
    }

    void paint(QPainter *painter, const QRectF &repaintRegion) override
    {
    }

public Q_SLOTS:
    bool init() override
    {
        const int shadowSize = 128;
        const int offsetTop = 64;
        const int offsetLeft = 48;
        const QRect shadowRect(0, 0, 4 * shadowSize + 1, 4 * shadowSize + 1);

        QImage shadowTexture(shadowRect.size(), QImage::Format_ARGB32_Premultiplied);
        shadowTexture.fill(Qt::transparent);

        const QMargins padding(
            shadowSize - offsetLeft,
            shadowSize - offsetTop,
            shadowSize + offsetLeft,
            shadowSize + offsetTop);

        auto decoShadow = std::make_shared<KDecoration3::DecorationShadow>();
        decoShadow->setPadding(padding);
        decoShadow->setInnerShadowRect(QRect(shadowRect.center(), QSize(1, 1)));
        decoShadow->setShadow(shadowTexture);

        setShadow(decoShadow);
        return true;
    }
};

K_PLUGIN_FACTORY_WITH_JSON(
    FakeDecoWithShadowsFactory,
    "fakedecoration_with_shadows.json",
    registerPlugin<FakeDecoWithShadows>();)

#include "fakedecoration_with_shadows.moc"
