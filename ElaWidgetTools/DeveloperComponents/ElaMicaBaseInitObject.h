#ifndef ELAMICABASEINITOBJECT_H
#define ELAMICABASEINITOBJECT_H

#include <QObject>
#include <QImage>
class ElaApplicationPrivate;
class ElaMicaBaseInitObject : public QObject
{
    Q_OBJECT
public:
    explicit ElaMicaBaseInitObject(ElaApplicationPrivate* appPrivate, QObject* parent = nullptr);
    ~ElaMicaBaseInitObject();
    Q_SLOT void onInitMicaBase(QImage lightImg, QImage darkImg);
Q_SIGNALS:
    Q_SIGNAL void initFinished();

private:
    ElaApplicationPrivate* _appPrivate{nullptr};
    QImage _createMicaBaseImage(QImage img, bool isLight);
};

#endif // ELAMICABASEINITOBJECT_H
