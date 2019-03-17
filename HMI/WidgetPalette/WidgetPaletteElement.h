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
                                 const int&    iIndPalette,
                                 QWidget* pParent = nullptr);
   virtual ~WidgetPaletteElement() override;

   QColor qColor(void) const;
   void SetColor(const QColor& qColor);

   virtual QSize sizeHint(void) const override;

protected:
   virtual void enterEvent(QEvent* pqEvent) override;
   virtual void leaveEvent(QEvent* pqEvent) override;
   virtual void paintEvent(QPaintEvent* pqEvent) override;
   virtual void mousePressEvent(QMouseEvent* pqEvent) override;

private:
   QColor m_qColor;
   // Le membre suivant permet de retrouver l'indice de la couleur dans la
   // palette
   int m_iIndPalette;

signals:
   void ColorChanged(void) const;
   void LabelColorPixel(const QString& qstrLabel) const;
   void clickOnElement(const int& iIndElement) const;
};

#endif // WIDGETPALETTEELEMENT_H
