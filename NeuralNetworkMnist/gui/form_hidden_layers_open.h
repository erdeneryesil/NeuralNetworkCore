#ifndef FORMHIDDENLAYERSOPEN_H
#define FORMHIDDENLAYERSOPEN_H

#include<QtWidgets>
#include"neural_network_core/neural_network.h"

class FormHiddenLayersOpen : public QWidget
{
    Q_OBJECT
public:
    FormHiddenLayersOpen(const HiddenLayerPattern*const hiddenLayerPattern);
    ~FormHiddenLayersOpen();
private:
    QVBoxLayout* _mainLayout;

    QScrollArea* _scrollArea;
    QWidget* _widgetScrollArea;
    QVBoxLayout* _layoutScrollArea;
    QVector<QHBoxLayout*>* _layoutRowsScrollArea;

    QVector<QHBoxLayout*>*_layoutCountCell;
    QVector<QWidget*>*_widgetCountCell;
    QVector<QLabel*>* _labelCountCell;
    QVector<QHBoxLayout*>*_layoutSumFunction;
    QVector<QWidget*>*_widgetSumFunction;
    QVector<QLabel*>* _labelSumFunction;
    QVector<QComboBox*>* _comboBoxSumFunction;
    QVector<QHBoxLayout*>*_layoutActFunction;
    QVector<QWidget*>*_widgetActFunction;
    QVector<QLabel*>* _labelActFunction;
    QVector<QComboBox*>* _comboBoxActFunction;

    QPushButton* _pushButtonSubmit;

    size_t _countHiddenLayer;

    void _createItemsRows(const int*const countsCell,const int*const sumFunctions, const int*const actFunctions);
signals:
    void signalHiddenLayersOpenParameters(size_t,int*const,int*const);
private slots:
    void slotPushButtonSubmitClicked();
};

#endif // FORMHIDDENLAYERSOPEN_H
