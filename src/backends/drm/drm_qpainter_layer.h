/*
    KWin - the KDE window manager
    This file is part of the KDE project.

    SPDX-FileCopyrightText: 2022 Xaver Hugl <xaver.hugl@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "drm_layer.h"

#include <QImage>

namespace KWin
{

class DumbSwapchain;
class DrmPipeline;
class DrmVirtualOutput;
class DrmQPainterBackend;
class DrmDumbBuffer;

class DrmQPainterLayer : public DrmPipelineLayer
{
public:
    DrmQPainterLayer(DrmQPainterBackend *backend, DrmPipeline *pipeline);

    OutputLayerBeginFrameInfo beginFrame() override;
    void endFrame(const QRegion &damagedRegion, const QRegion &renderedRegion) override;
    QSharedPointer<DrmBuffer> testBuffer() override;
    QSharedPointer<DrmBuffer> currentBuffer() const override;
    QRegion currentDamage() const override;

private:
    bool doesSwapchainFit() const;

    QSharedPointer<DumbSwapchain> m_swapchain;
    QRegion m_currentDamage;
};

class DrmVirtualQPainterLayer : public DrmOutputLayer
{
public:
    DrmVirtualQPainterLayer(DrmVirtualOutput *output);

    OutputLayerBeginFrameInfo beginFrame() override;
    void endFrame(const QRegion &damagedRegion, const QRegion &renderedRegion) override;

    QRegion currentDamage() const override;

private:
    QImage m_image;
    QRegion m_currentDamage;
    DrmVirtualOutput *const m_output;
};

class DrmLeaseQPainterLayer : public DrmPipelineLayer
{
public:
    DrmLeaseQPainterLayer(DrmQPainterBackend *backend, DrmPipeline *pipeline);

    OutputLayerBeginFrameInfo beginFrame() override;
    void endFrame(const QRegion &damagedRegion, const QRegion &renderedRegion) override;

    QSharedPointer<DrmBuffer> testBuffer() override;
    QSharedPointer<DrmBuffer> currentBuffer() const override;

private:
    QSharedPointer<DrmDumbBuffer> m_buffer;
};

}
