#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QtWidgets>

// Default zoom factors
#define DEFAULT_ZOOM_FACTOR      (1.15)
#define DEFAULT_ZOOM_CTRL_FACTOR (1.01)

class SubWindow;

class DisplayImage : public QGraphicsView
{
   Q_OBJECT

public:
   // Constructor, create the scene and set parameters
   // When set to true, the contextual menu is initialize
   // If you don't want contextual menu or need to create a
   // custom one, set to false.
   DisplayImage(bool bIsContextualMenu = true, QWidget* pParent = nullptr);
   virtual ~DisplayImage();


   // Set the image in the widget
   // QImage to display
   void setImage(const QImage& qImage);

   // Set the image from raw data
   // Pointer to the raw data (data format is RGBRGBRGBRGB ...)
   // Size of the image to display
   // The raw data MUST be compliant with the size
   void setImageFromRawData(const uchar* pucData,
                            int iWidth,
                            int iHeight,
                            bool bMirrorHorizontally = false,
                            bool bMirrorVertically = false);


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
   // Scene where the image is drawn
   QGraphicsScene*      m_pqGraphicsScene;
   // Pixmap item containing the image
   QGraphicsPixmapItem* m_pqGraphicsPixmapItem;
   // Size of the current image
   QSize                m_qImageSize;
   // Zoom factor
   double               m_dZoomFactor;
   // Zoom factor when the CTRL key is pressed
   double               m_dZoomCtrlFactor;
   // Current pixmap
   QPixmap              m_qPixmap;
};

#endif // DISPLAYIMAGE_H
