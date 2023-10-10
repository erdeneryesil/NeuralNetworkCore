#ifndef THREADS_H
#define THREADS_H

#include<QThread>

class ThreadWidgetRowOperation:public QThread{
    Q_OBJECT
public:
    enum class OperationType{AddRow,RemoveRow};
    ThreadWidgetRowOperation();
    ~ThreadWidgetRowOperation();
    void run();
    void setOperationType(const OperationType& operationType,const int& countRow);
private:
    OperationType _operationType;
    int _countRow;
    void _removeRow(const int& countRow);
    void _addRow(const int& countRow);
signals:
    void signalCreateWidgetsInRow();
    void signalDeleteWidgetsInRow();
    void signalWidgetScrollAreaSetHeight(const ThreadWidgetRowOperation::OperationType&);
    void signalOperationFinished();
};

class FormMain;
class ThreadDiagramNN:public QThread{
    Q_OBJECT
public:
    ThreadDiagramNN(const FormMain*const parentGUI);
    ~ThreadDiagramNN();
    void run();
private:
    const FormMain*const _parentGUI;

signals:
    void signalPrepareGraphicScene();
    void signalAddLine(qreal,qreal,qreal, qreal,const QPen&);
    void signalAddEllipse(qreal,qreal,qreal, qreal,const QPen&,const QBrush&);
};

class GraphEW;
class ThreadGraphEW:public QThread{
    Q_OBJECT
public:
    enum class OperationType{DrawPreviousTrainings,DrawPreviousEWOfCurrentTraining,DrawNewEW};
    ThreadGraphEW(const GraphEW*const parentGUI);
    ~ThreadGraphEW();
    void run();

    bool isDrawingNewEWFinished()const;
    bool isReadyToDrawNewEW()const;
    bool isNewEWMaximum()const;
    void setOperationType(const OperationType& operationType);
    OperationType getOperationType()const;
    void setStopAllDrawings(const bool& stop);
    void setYEWActualMaxBasedOnAllTrainings(const bool& basedOnAllTrainnigs);

private:
    const GraphEW*const _parentGUI;

    QVector<qreal>*_xPreviousTrainingVirtual;
    qreal _xCurrentTrainingVirtual;

    qreal _yTopTrainingVirtual;
    qreal _yBottomTrainingVirtual;

    QVector<QVector<qreal>*>*_xPreviousEWVirtual;
    QVector<qreal>* _xCurrentEWVirtual;

    QVector<QVector<qreal>*>*_yPreviousErrorActual;
    QVector<QVector<qreal>*>*_yPreviousErrorVirtual;
    QVector<qreal>*_yCurrentErrorVirtual;

    QVector<QVector<qreal>*>*_yPreviousWeightActual;
    QVector<QVector<qreal>*>*_yPreviousWeightVirtual;
    QVector<qreal>*_yCurrentWeightVirtual;

    QVector<qreal>*_yErrorActualMaxPreviousTrainings;
    QVector<qreal>*_yWeightActualMaxPreviousTrainings;
    qreal _yErrorActualMaxAllTrainings;
    qreal _yWeightActualMaxAllTrainings;
    qreal _yErrorActualMaxCurrentTraining;
    qreal _yWeightActualMaxCurrentTraining;

    qreal _yErrorActualMin;
    qreal _yErrorVirtualMin;
    qreal _yErrorVirtualMax;

    qreal _yWeightActualMin;
    qreal _yWeightVirtualMin;
    qreal _yWeightVirtualMax;

    OperationType _operationType;

    qreal _xCurrent;
    qreal _xVirtualInc;

    bool _isReadyToDrawNewEW;
    bool _isNewEWMaximum;
    bool _isDrawingNewEWFinished;
    bool _stopAllDrawings;
    bool _yEWActualMaxBasedOnAllTrainings;

    void _clearCurrentContainers();
    void _clearPreviousContainers();

    void _drawEWOfPreviousTrainings();
    void _drawPreviousEWOfCurrentTraining();
    void _drawNewEW();

    void _controlOwerflowXVirtual(const qreal& x);

    void _loadYEWActualMaxPreviousTrainings();
    void _checkYEWActualMaxAllTrainingsWithPreviousTrainings();

    void _loadYEWActualMaxCurrentTraining();
    void _checkYEWActualMaxAllTrainingsWithCurrentTraining();

    void _loadEWFromPreviousTrainings();

    void _calculateXVirtualIncForPreviousTrainings();
    bool _checkIfMaxEWIsNewEW();

    qreal _calculateYErrorVirtual(const qreal& yErrorActual, const qreal &yErrorActualMax);
    qreal _calculateYWeightVirtual(const qreal& yWeightActual, const qreal &yWeightActualMax);

signals:
    void signalPrepareDraw();
    void signalDrawCompleted();
    void signalTrainingLineCreated(bool isTrainingPrevious,size_t trainingIndex,qreal x1,qreal y1,qreal x2,qreal y2);
    void signalErrorEllipseCreated(qreal x1,qreal y1);
    void signalWeightEllipseCreated(qreal x1,qreal y1);
    void signalErrorLineCreated(qreal x1,qreal y1,qreal x2,qreal y2);
    void signalWeightLineCreated(qreal x1,qreal y1,qreal x2,qreal y2);
    void signalCountEWIncreased();
    void signalSceneNeedsSettingRectForExpand(qreal xError);
};

class FormSamplesFile;
class ThreadSampleImages:public QThread{
    Q_OBJECT
public:
    enum class OperationType{Fill,Draw};
    ThreadSampleImages(const FormSamplesFile*const parentGUI);
    ~ThreadSampleImages();
    void run();
    void setOperationType(const OperationType& operationType);
private:
    OperationType _operationType;
    const FormSamplesFile*const _parentGUI;
    QVector<QImage*>* _images;
    QVector<int>* _imageDigits;
    QImage* _resultImage;
    QPixmap* _pixmap;
    int _rowCountResultImage;
    int _columnCountResultImage;

signals:
    void signalFillImagesError();
    void signalFillImagesFinished();
    void signalPrepareImageGUI(int,int);
    void signalDrawImage(const QPixmap&);
};

#endif // THREADS_H
