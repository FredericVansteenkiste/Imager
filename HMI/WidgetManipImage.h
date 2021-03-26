#ifndef WidgetManipImage_H
#define WidgetManipImage_H
#pragma once

#include <QtWidgets>

#include "../global.h"
#include "WidgetManipColor/CStateMouse.h"
#include "MainWindow.h"

class MainWindow;
class SubWindow;
class MdiArea;

// Default zoom factors
#define DEFAULT_ZOOM_FACTOR               (1.15)
#define DEFAULT_ZOOM_CTRL_FACTOR          (1.01)
#define SCALE_MAX                         (15)
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

protected:
   // Overload this function to process mouse button pressed
   // mouse event
   void mousePressEvent(QMouseEvent* pqEvent) override;

   // Overload this function to process mouse moves
   // mouse move event
   void mouseMoveEvent(QMouseEvent* pqEvent) override;

   // Overload this function to process mouse button released
   // mouse event
   void mouseReleaseEvent(QMouseEvent* pqEvent) override;

#if QT_CONFIG(wheelevent)
   // Overload this function to process mouse wheel event
   // mouse wheel event
   void wheelEvent(QWheelEvent* pqEvent) override;
#endif

   // Overload this event to act on the resize event
   void resizeEvent(QResizeEvent *pqEvent) override;

   // Overload this event to draw the widget
   void paintEvent(QPaintEvent* pqEvent) override;

   // Overload to intercept the event which are going to the scroll bar
   bool eventFilter(QObject* pqObj, QEvent* pqEvent) override;

private:
   // Le membre suivant enregistre l'image affichée par le widget.
   QImage m_qImage;
   // Le membre suivant indique quel est le pinceau utilisé pour dessiner
   // l'arrière plan
   QBrush m_qBckgrndBrush;
   // Le membre suivant indique quel est le crayon (QPen) a utilisé pour
   // dessiner le pointillé autour de l'image.
   QPen m_qPenCadre;
   // Le membre suivant enregistre où se trouve le coin TopLeft de l'image dans
   // le widget
   QPoint m_qTopLeftCorner;
   // Le membre suivant enregistre la valeur du zoom sur l'image
   qreal m_dScale;
   // Lorsque la souris clique sur l'image, le membre suivant mémorise où
   // l'utilisateur a cliqué
   QPoint m_qCoordMouseClicked;

   void setContextMenu(void);

   // La fonction suivante permet de retrouver l'état de la souris.
   CSubStateMouse::e_state_machine eGetStateMouse(void);

   // Les méthodes suivantes permettent de retrouver des pointeurs sur
   // MainWindow et SubWindow
   MainWindow* pMainWindow(void) const;
   MdiArea*    pMdiArea(void) const;
   SubWindow*  pSubWindow(void) const;

   // La méthode suivante permet de s'assurer que l'image reste bien dans le
   // viewport et qu'elle soit centré si le viewport est plus grand que l'image
   // en agissant sur le point m_qTopLeftCorner
   void CheckCoordTopLeftImage(void);

   // La méthode suivante permet de s'assurer que lorsqu'on bouge ou
   // redimensionne une image, les scrollbars se repositionne correctement.
   void CheckScroolBar(void);

   // Les méthodes suivantes permettent de convertir des coordonnées du widget
   // dans des coordonnées de l'image ou l'inverse.
   QPointF qMapWidgetToImage(const QPointF qPointInWidgetF) const;
   QPointF qMapImageToWidget(const QPointF qPointInImageF) const;

   // La méthode suivante indique si l'on a cliqué dans l'image ou pas
   bool IsPointWidgetInImage(const QPoint& qPointInWidget) const;

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
   void CoordMouse(const QString& qstrLabel);
   void ColorPixel(const QString& qstrlabel);
};

#endif // WidgetManipImage_H
