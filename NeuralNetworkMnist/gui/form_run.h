#ifndef FORMRUN_H
#define FORMRUN_H

#include<QtWidgets>

class GraphicsViewHandwriting:public QGraphicsView{
    Q_OBJECT
public:
    explicit GraphicsViewHandwriting(QWidget*parent=0);
    ~GraphicsViewHandwriting();
    const QPixmap* getCurrentPixmap();
private:
    int _widthImageHandwriting;
    int _heightImageHandwriting;
    QImage* _imageHandwriting;

    int _xMinCroppedArea;
    int _xMaxCroppedArea;
    int _yMinCroppedArea;
    int _yMaxCroppedArea;
    int _widthCroppedArea;
    int _heightCroppedArea;
    int _requiredHeightCroppedArea;
    int _topLeftYCroppedArea;
    int _topLeftXCroppedArea;
    QImage* _imageCroppedArea;
    QImage* _imageHeighthAdjustedCroppedArea;

    int _widthImageSample;
    int _heightImageSample;
    QPixmap* _pixmapSample;
    QImage* _imageSample;

    QPen* _pen;
    QPointF* _firstPoint;
    QPointF* _secondPoint;
    QGraphicsScene* _sceneHandwriting;

    void _createImageHandwritten();
    void _calculateCroppedAreaMinMaxXY();
    void _calculateCroppedAreaRectangle();
    void _createImageCroppedArea();
    void _createImageHeighthAdjustedCroppedArea();
    void _updateTopLeftYCroppedArea();
    void _createImageSample();

public slots:
    void mousePressEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
signals:
    void signalWriting(const QPixmap*);
};

class FormRun : public QWidget{
    Q_OBJECT
public:
    FormRun();
    ~FormRun();
private:
    QVBoxLayout* _mainLayout;

    GraphicsViewHandwriting* _graphicsViewHandwriting;

    QHBoxLayout* _layoutTop;
    QPushButton* _pushButtonClear;

    QHBoxLayout* _layoutBottom;
    QGraphicsView* _graphicsViewSample;
    QGraphicsScene* _sceneSample;
    QPushButton* _pushButtonSubmit;

signals:
    void signalRunParameters(int*const);
private slots:
    void slotPushButtonSubmitClicked();
    void slotPushButtonClearClicked();
    void slotWriting(const QPixmap*);
};

#endif // FORMRUN_H
