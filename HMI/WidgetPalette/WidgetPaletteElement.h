#ifndef WIDGETPALETTEELEMENT_H
#define WIDGETPALETTEELEMENT_H
#pragma once

#include <QtWidgets>

#include "../SubWindow.h"

// Cette constante indique la taille en pixel du widget sachant que le widget
// est un carré
#define WIDGET_PALETTE_ELEM_SIZE_PIXEL (10)

class WidgetPaletteElement : public QWidget
{
   Q_OBJECT

public:
   explicit WidgetPaletteElement(const QColor& qColor,
                                 QWidget* pParent = nullptr);
   virtual ~WidgetPaletteElement() override;

   QColor qColor(void) const;
   void SetColor(const QColor& qColor);

   virtual QSize sizeHint(void) const override;

protected:
   virtual void mousePressEvent(QMouseEvent* pqEvent) override;
   virtual void paintEvent(QPaintEvent* pqEvent) override;

private:
   QColor m_qColor;

signals:
   void ColorChanged(void) const;
};

#endif // WIDGETPALETTEELEMENT_H
