#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QtWidgets>

#include "ImageScene.h"

// Default zoom factors
#define DEFAULT_ZOOM_FACTOR         (1.15)
#define DEFAULT_ZOOM_CTRL_FACTOR    (1.01)
#define SCALE_MAX                   (15)
#define ADRESS_BACKGROUND_PICTURE   (":/HMI/Icones/ArrierePlan.png")

class ImageView : public QGraphicsView
{
public:
   ImageView(QWidget* pParent = nullptr);
   virtual ~ImageView();

   void setContextMenu(void);

   // Set the zoom factor when the CTRL key is not pressed
   // param factor            zoom factor (>1)
   void setZoomFactor(const double dFactor);

   // Set the zoom factor when the CTRL key is pressed
   // zoom factor (>1)
   void setZoomCtrlFactor(const double dFactor);

protected:
   // Overload this function to draw over the image
   // Painter for drawing
   // Size of the image
   virtual void drawOnImage(QPainter* pqPainter, QSize qImageSize);

   // Overload this function to draw in the view port
   // Painter for drawing
   // Size of the view port
   virtual void drawInViewPort(QPainter* pqPainter, QSize qPortSize);

   // Drawing he foreground of the scene
   // When overloading this function, you must call it parent before
   // exiting the function, otherwise drawOnImage and drawInViewPort
   // will not work properly
   // Painter for drawing
   // The area of the scene displayed in the view port
   virtual void drawForeground(QPainter* pqPainter, const QRectF& qRrect);

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

   // Overload this function to process the window resizing event
   // resize event
   virtual void resizeEvent(QResizeEvent* pqEvent);

private slots:
   // Display the contextual menu (on right click)
   // Position of the mouse in the widget
   virtual void showContextMenu(const QPoint& qPos);

   // This function fit the image in the view while keeping aspect ratio
   void FitImage(void);

private:
   // Zoom factor
   double            m_dZoomFactor;
   // Zoom factor when the CTRL key is pressed
   double            m_dZoomCtrlFactor;
};

#endif // IMAGEVIEW_H
