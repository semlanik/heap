#ifndef WAYLANDHANDLER_H
#define WAYLANDHANDLER_H

#include <QObject>

class QWaylandWlShellSurface;
class QQuickView;
class QQuickItem;
class QWaylandClient;
class QWaylandQuickCompositor;
class QWaylandQuickOutput;
class QWaylandWlShell;

class WaylandHandler : public QObject
{
    Q_OBJECT
public:
    WaylandHandler(QQuickView* window, QObject *parent = 0);

public slots:
    void onShellSurfaceCreated(QWaylandWlShellSurface *shellSurface);
    void createSurface(QWaylandClient *client, uint id, int version);
private:
    QQuickItem* m_outItem;
    QWaylandQuickCompositor *m_compositor;
    QWaylandQuickOutput *m_output;
    QWaylandWlShell*  m_wlShell;
};

#endif // WAYLANDHANDLER_H
