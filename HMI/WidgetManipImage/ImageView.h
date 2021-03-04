#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#pragma once

#include <QtWidgets>

#include "ImageScene.h"
#include "../WidgetManipColor/CStateMouse.h"
#include "../MainWindow.h"

class MainWindow;
class SubWindow;

// Default zoom factors
#define DEFAULT_ZOOM_FACTOR               (1.15)
#define DEFAULT_ZOOM_CTRL_FACTOR          (1.01)
#define SCALE_MAX                         (15)
#define ADRESS_CHECKED_BACKGROUND_PICTURE (":/Icones/ArrierePlan.png")

class ImageView : public QGraphicsView
{
   Q_OBJECT

public:
   explicit ImageView(QWidget* pParent = nullptr,
                      QBrush   qBckgrndBrush = QBrush());
   virtual ~ImageView();

   // void setContextMenu(void);

   // Set the zoom factor when the CTRL key is not pressed
   // param factor            zoom factor (>1)
   void setZoomFactor(const double dFactor);

   // Set the zoom factor when the CTRL key is pressed
   // zoom factor (>1)
   void setZoomCtrlFactor(const double dFactor);

   // La méthode suivante renvoie un pointeur sur ImageScene. C'est équivalent à
   // scene()
   ImageScene* pqImageScene(void) const;

   // La méthode suivante permet de convertir les coordonnées de la vue en
   // coordonnées de l'image
   QPointF mapToPixmapItem(const QPoint& qCoordView);
   // La méthode suivante permet de convertir les coordonnées de l'image en
   // coordonnées de la vue
   QPoint mapFromPixmapItem(const QPointF& qCoordPixmap);

protected:
   // Display the tool tip over the mouse
   // Coordinates of the mouse in the image's frame
   // The function returns the QString that is displayed over the image
   virtual QString setToolTipText(QPoint qImageCoordinates);

   // Overload this function to process mouse button pressed
   // mouse event
   virtual void mousePressEvent(QMouseEvent* pqEvent);

   // Overload this function to process mouse button released
   // mouse event
   virtual void mouseReleaseEvent(QMouseEvent* pqEvent);

   // Overload this function to process mouse wheel event
   // mouse wheel event
   virtual void wheelEvent(QWheelEvent* pqEvent);

   // Overload this function to process mouse moves
   // mouse move event
   virtual void mouseMoveEvent(QMouseEvent* pqEvent);

   // Overload to intercept the event which are going to the scroll bar
//   virtual bool eventFilter(QObject* pqObj, QEvent* pqEvent);

private:
   // Zoom factor
   double m_dZoomFactor;
   // Zoom factor when the CTRL key is pressed
   double m_dZoomCtrlFactor;

   // La fonction suivante permet de retrouver l'état de la souris.
   CSubStateMouse::e_state_machine eGetStateMouse(void);

   // Les méthodes suivantes permettent de retrouver des pointeurs sur
   // MainWindow et SubWindow
   MainWindow* pMainWindow(void) const;
   SubWindow*  pSubWindow(void) const;

   // J'interdis toute forme de recopie de ma classe:
   ImageView(const ImageView&);
   ImageView& operator=(const ImageView&);

private slots:
   // // Display the contextual menu (on right click)
   // // Position of the mouse in the widget
   // virtual void showContextMenu(const QPoint& qPos);

   // // This function set the zoom to 1
   // void ResetZoom(void);

signals:
   void SizeImage(const QString& qstrLabel);
   void CoordMouse(const QString& qstrLabel);
   void ColorPixel(const QString& qstrlabel);
};

#endif // IMAGEVIEW_H
