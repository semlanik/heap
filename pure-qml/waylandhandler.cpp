#include "waylandhandler.h"

#include <QWaylandWlShellSurface>
#include <QWaylandShellSurface>
#include <QWaylandQuickShellSurfaceItem>
#include <QWaylandQuickSurface>
#include <QWaylandQuickCompositor>
#include <QQuickItem>
#include <QWaylandQuickOutput>
#include <QWaylandWlShell>
#include <QQuickView>

#include <QDebug>

WaylandHandler::WaylandHandler(QQuickView *window, QObject *parent) : QObject(parent)
  ,m_outItem(window->rootObject()->findChild<QQuickItem*>("output"))
  ,m_compositor(new QWaylandQuickCompositor(this))
  ,m_output(new QWaylandQuickOutput())
  ,m_wlShell(new QWaylandWlShell(m_compositor))
{
    m_output->setWindow(window);
    m_output->setCompositor(m_compositor);
    m_output->setWidth(500);
    m_output->setHeight(500);
    m_compositor->addExtension(m_wlShell);

    QObject::connect(m_compositor, &QWaylandCompositor::createSurface, this, &WaylandHandler::createSurface);
    QObject::connect(m_wlShell, &QWaylandWlShell::shellSurfaceCreated, this, &WaylandHandler::onShellSurfaceCreated);

    m_compositor->create();
}

void WaylandHandler::onShellSurfaceCreated(QWaylandWlShellSurface *shellSurface)
{
    QWaylandQuickShellSurfaceItem* shell = new QWaylandQuickShellSurfaceItem(m_outItem);
    shell->setShellSurface(shellSurface);
    shell->setSurface(shellSurface->surface());
    shell->setWidth(500);
    shell->setHeight(500);
    qDebug() << "WaylandHandler::onShellSurfaceCreated";
}


void WaylandHandler::createSurface(QWaylandClient *client, uint id, int version)
{
    QWaylandQuickSurface* defaultSurface = new QWaylandQuickSurface(m_compositor, client, id, version);
//    defaultSurface->initialize();

    qDebug() << m_compositor->surfacesForClient(client);
}
