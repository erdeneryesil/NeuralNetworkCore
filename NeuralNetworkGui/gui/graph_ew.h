#ifndef GRAPHEW_H
#define GRAPHEW_H

#include<QtWidgets>
#include"gui/threads.h"
#include"neural_network_core/neural_network.h"

class GraphEW;
class TrainingLine:public QGraphicsLineItem{
public:
    static GraphEW* parent;
    TrainingLine(const bool& isTrainingPrevious,const size_t& trainingIndex,const qreal& x1,const qreal& y1,const qreal& x2,const qreal& y2);
    ~TrainingLine();
    size_t getCountEW()const;
    void updateCountEW();
    QString getToolTipText();

private:
    bool _isTrainingPrevious;
    size_t _trainingIndex;
    QVector<Cell::SummationFunction::Type>*_sumFuncTypesOfHiddenLayer;
    QVector<Cell::ActivationFunction::Type>*_actFuncTypesOfHiddenLayer;
    Cell::SummationFunction::Type _sumFuncTypeOfOutputLayer;
    Cell::ActivationFunction::Type _actFuncTypeOfOutputLayer;
    QVector<double>*_tolerances;
    double _lambda;
    double _alfa;
    int _countSample;
    size_t _countEW;
};

class GraphEW : public QWidget
{
    Q_OBJECT
public:
    GraphEW(const FormMain*const parentForm);
    ~GraphEW();
    const FormMain* getParentForm()const;

    bool getScrolling()const;
    qreal getSceneWidth()const;
    qreal getSceneHeight()const;
    qreal getViewWidth()const;
    qreal getPenTrainingWidth()const;
    static ThreadGraphEW* getThreadGraphEWObject();

private:
    const FormMain*const _parentForm;//silinmeyecek

    QVBoxLayout* _mainLayout;
    QHBoxLayout* _layoutHead;

    QCheckBox* _checkBoxPreviousTrainings;
    QCheckBox* _checkBoxMaxEWBasedOnAllTrainings;
    QGraphicsView* _view;
    QGraphicsScene* _scene;

    QVector<TrainingLine*>* _trainingLine;
    QPen _penTraining;
    QPen _penError;
    QPen _penWeight;
    QBrush _brushError;
    QBrush _brushWeight;

    static ThreadGraphEW* _threadGraphEWObject;
    bool _scrolling;

    void _clearTrainingLine();

    void closeEvent(QCloseEvent *);

private slots:
    void slotPrepareDraw();
    void slotDrawCompleted();
    void slotTrainingLineCreated(bool isTrainingPrevious,size_t trainingIndex,qreal x1,qreal y1,qreal x2,qreal y2);
    void slotErrorEllipseCreated(qreal x1,qreal y1);
    void slotWeightEllipseCreated(qreal x1,qreal y1);
    void slotErrorLineCreated(qreal x1,qreal y1,qreal x2,qreal y2);
    void slotWeightLineCreated(qreal x1,qreal y1,qreal x2,qreal y2);
    void slotCountEWIncreased();
    void slotSceneNeedsSettingRectForExpand(qreal xError);
    void slotCheckBoxPreviousTrainings(int);
    void slotCheckBoxMaxEWBasedOnAllTrainings(int);
    void slotScrollBarMoved(int);
    void slotScrollBarPressed();
    void slotScrollBarReleased();
};
#endif // GRAPHEW_H
