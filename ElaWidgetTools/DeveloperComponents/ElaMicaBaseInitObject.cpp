#include "ElaMicaBaseInitObject.h"

#include <QColor>
#include <QImage>

#include "ElaApplicationPrivate.h"
#include "ElaExponentialBlur.h"
ElaMicaBaseInitObject::ElaMicaBaseInitObject(ElaApplicationPrivate* appPrivate, QObject* parent)
    : QObject{parent}
{
    _appPrivate = appPrivate;
}

ElaMicaBaseInitObject::~ElaMicaBaseInitObject()
{
}

QImage ElaMicaBaseInitObject::_createMicaBaseImage(QImage img, bool isLight)
{
    img = img.scaled(QSize(1920, 1080), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QImage blurImage = ElaExponentialBlur::doExponentialBlur(img, 500).toImage();
    QImage baseImage = blurImage;
    QColor originColor;
    QColor baseColor;
    int h, s, v;
    for (int y = 0; y < blurImage.height(); y++)
    {
        QRgb* line = (QRgb*)blurImage.scanLine(y);
        for (int x = 0; x < blurImage.width(); x++)
        {
            originColor = QColor(line[x]).toHsv();
            h = originColor.hsvHue();
            s = originColor.hsvSaturation();
            v = originColor.value();
            if (isLight)
            {
                baseColor.setHsv(h, s / 20 > 11 ? (s / 20 + 11) / 2 : 11, 250);
            }
            else
            {
                baseColor.setHsv(h, s / 2, v / 1.1 > 40 ? (v / 1.1 + 40) / 2 : 40);
            }
            baseColor = baseColor.toRgb();
            baseImage.setPixel(x, y, qRgb(baseColor.red(), baseColor.green(), baseColor.blue()));
        }
    }
    return baseImage;
}

void ElaMicaBaseInitObject::onInitMicaBase(QImage lightImg, QImage darkImg)
{
    _appPrivate->_lightBaseImage = _createMicaBaseImage(lightImg, true);
    _appPrivate->_darkBaseImage = _createMicaBaseImage(darkImg, false);
    Q_EMIT initFinished();
}
