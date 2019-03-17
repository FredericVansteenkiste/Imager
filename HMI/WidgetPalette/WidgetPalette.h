#ifndef WIDGETPALETTE_H
#define WIDGETPALETTE_H
#pragma once

#include <QtWidgets>

#include "WidgetPaletteElement.h"
#include "../SubWindow.h"
#include "../WidgetManipColor/WidgetManipColor.h"

class SubWindow;
class WidgetPaletteElement;
class WidgetManipColor;

class WidgetPalette : public QWidget
{
   Q_OBJECT

public:
   explicit WidgetPalette(const QVector<QRgb>& aqColorPalette,
                          QWidget* pParent = nullptr);
   virtual ~WidgetPalette();

   // Cette méthode passe toutes les couleurs utilisé par la palette pour
   // l'image courante
   void SetPalette(const QVector<QRgb>& aqColorPalette);
   // Cette méthode permet de récupérer un pointeur sur la fenêtre correspondant
   // à la palette
   SubWindow* pqSubWindow(void) const;

   void RearrangePalette(const int& iWidth);

   int iIndElementSelectionne(void) const;

public slots:
   void SetIndElementSelectionne(const int& iIndElement);

protected:
   virtual void resizeEvent(QResizeEvent* pqEvent) override;

private:
   // Le vecteur suivant contient les éléments de la palette utilisé pour
   // l'image courante
   QVector<WidgetPaletteElement*> m_apPaletteElement;
   // Les membres suivants détermine la forme de la palette dans le layout
   QGridLayout* m_pLayoutPalette;
   int          m_iNbrColumn;
   int          m_iNbrLine;
   // Le pointeur suivant permet de retrouver la fenêtre correspondante à la
   // palette courante
   SubWindow* m_pqSubWindow;
   // L'indice suivant indique l'élément de la palette qui est sélectionné
   int m_iIndElementSelectionne;

signals:
   void IndElementSelectionnedChanged(const QColor& qColor,
                                      const QColor& qBckGrndColor);
};

#endif // WIDGETPALETTE_H
