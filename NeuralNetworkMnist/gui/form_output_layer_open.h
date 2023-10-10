#ifndef FORMOUTPUTLAYEROPEN_H
#define FORMOUTPUTLAYEROPEN_H

#include<QtWidgets>
#include"neural_network_core/neural_network.h"

class FormOutputLayerOpen : public QWidget
{
    Q_OBJECT
public:
    FormOutputLayerOpen(const OutputLayerPattern*const outputLayerPattern);
    ~FormOutputLayerOpen();

private:
    QVBoxLayout* _mainLayout;

    QLabel* _labelCountOutput;
    QLabel* _labelSumFunction;
    QComboBox* _comboBoxSumFunction;
    QLabel* _labelActFunction;
    QComboBox* _comboBoxActFunction;
    QHBoxLayout* _layoutHead;

    QScrollArea* _scrollArea;
    QWidget* _widgetScrollArea;
    QVBoxLayout* _layoutScrollArea;
    QVector<QHBoxLayout*>* _layoutRowsScrollArea;
    QHBoxLayout* _layoutBunch;

    QVector<QHBoxLayout*>*_layoutDataType;
    QVector<QWidget*>*_widgetDataType;
    QVector<QLabel*>* _labelDataType;
    QVector<QHBoxLayout*>*_layoutMinimum;
    QVector<QWidget*>*_widgetMinimum;
    QVector<QLabel*>* _labelMinimum;
    QVector<QHBoxLayout*>*_layoutMaximum;
    QVector<QWidget*>*_widgetMaximum;
    QVector<QLabel*>* _labelMaximum;
    QVector<QHBoxLayout*>*_layoutTolerance;
    QVector<QWidget*>*_widgetTolerance;
    QVector<QLabel*>* _labelTolerance;
    QVector<QDoubleSpinBox*>* _spinBoxTolerance;

    QPushButton* _pushButtonSubmit;

    size_t _countOutput;

    void _createItemsRows(const int*const dataTypes,const int*const minimums,const int*const maximums,const double*const tolerances);

signals:
    void signalOutputLayerOpenParameters(size_t,int,int,double*const);

private slots:
    void slotPushButtonSubmitClicked();
};

#endif // FORMOUTPUTLAYEROPEN_H
