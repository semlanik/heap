#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickView>

#include <universallistmodel.h>
#include "sampleobject.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    UniversalListModel<SampleObject> testModel;
    testModel.add(new SampleObject(1, 0.1, "Some Object number 1"));
    testModel.add(new SampleObject(2, 0.2, "Some Object number 2"));
    testModel.add(new SampleObject(4, 0.4, "Some Object number 3"));
    testModel.add(new SampleObject(8, 0.8, "Some Object number 4"));
    testModel.add(new SampleObject(16, 1.0, "Some Object number 5"));
    testModel.add(new SampleObject(3, 2.0, "Some Object number 6"));
    testModel.add(new SampleObject(4, 3.0, "Some Object number 7"));
    QQuickView testView;
    testView.rootContext()->setContextProperty("_universalModel", &testModel);
    testView.setSource(QUrl("qrc:/main.qml"));
    testView.setResizeMode(QQuickView::SizeRootObjectToView);
    testView.showMaximized();
    return app.exec();
}
