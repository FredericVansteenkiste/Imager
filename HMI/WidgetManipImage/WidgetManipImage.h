#ifndef WidgetManipImage_H
#define WidgetManipImage_H
#pragma once

#include <QtWidgets>

#include "../../global.h"

#define ADRESS_CHECKED_BACKGROUND_PICTURE (":/Icones/ArrierePlan.png")

class WidgetManipImage : public QAbstractScrollArea
{
   Q_OBJECT

public:
   // Constructor, create the scene and set parameters
   explicit WidgetManipImage(const QImage& qImage,
                             const QBrush& qBckgrndBrush = Qt::black,
                             QWidget* pParent = nullptr);
   virtual ~WidgetManipImage();

   // Set the image in the widget
   // QImage to display
   void SetImage(const QImage& qImage);
   QImage& qImage(void);

   // J'indique quelle pinceau utiliser pour le background
   void setBackgroundBrush(const QBrush& qBckgrndBrush);
   QBrush backgroundBrush() const;

private:
   // Le membre suivant enregistre l'image affichée par le widget.
   QImage m_qImage;
   // Le membre suivant indique quel est le pinceau utilisé pour dessiner
   // l'arrière plan
   QBrush m_qBckgrndBrush;
   // Le membre suivant indique quel est le crayon (QPen) a utilisé pour
   // dessiner le pointillé autour de l'image.
   QPen m_qPenCadre;
   // Le membre suivant enregistre la valeur du zoom sur l'image
   qreal m_dScale;

   void setContextMenu(void);

   // J'interdis toute forme de recopie de ma classe:
   WidgetManipImage(const WidgetManipImage&);
   WidgetManipImage& operator=(const WidgetManipImage&);

private slots:
   // Display the contextual menu (on right click)
   // Position of the mouse in the widget
   void showContextMenu(const QPoint& qPos);

   // This function set the zoom to 1
   void ResetZoom(void);

signals:
   void SizeImage(const QString& qstrLabel);
   void CoordMouse(const QString& qstrLabel);
   void ColorPixel(const QString& qstrlabel);
};

#endif // WidgetManipImage_H
