#ifndef FORMOUTPUTLAYERNEW_H
#define FORMOUTPUTLAYERNEW_H

#include<QtWidgets>
#include"gui/threads.h"

class FormOutputLayerNew : public QWidget
{
    Q_OBJECT
public:
    FormOutputLayerNew();
    ~FormOutputLayerNew();

private:
    QVBoxLayout* _mainLayout;

    QLabel* _labelCountOutput;
    QSpinBox* _spinBoxCountOutput;
    QCheckBox* _checkBoxSame;
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
    QVector<QComboBox*>* _comboBoxDataType;
    QVector<QHBoxLayout*>*_layoutMinimum;
    QVector<QWidget*>*_widgetMinimum;
    QVector<QLabel*>* _labelMinimum;
    QVector<QSpinBox*>* _spinBoxMinimum;
    QVector<QHBoxLayout*>*_layoutMaximum;
    QVector<QWidget*>*_widgetMaximum;
    QVector<QLabel*>* _labelMaximum;
    QVector<QSpinBox*>* _spinBoxMaximum;
    QVector<QHBoxLayout*>*_layoutTolerance;
    QVector<QWidget*>*_widgetTolerance;
    QVector<QLabel*>* _labelTolerance;
    QVector<QDoubleSpinBox*>* _spinBoxTolerance;

    QPushButton* _pushButtonSubmit;

    size_t _countOutput;

    ThreadWidgetRowOperation* _threadWidgetRowOperation;

    void _threadOperationStarted();

signals:
    void signalOutputLayerNewParameters(size_t,int,int,int*const,int*const,int*const,double*const);

private slots:
    void slotCreateWidgetsInRow();
    void slotDeleteWidgetsInRow();
    void slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType);
    void slotThreadOperationFinished();
    void slotSpinBoxCountOutputValueChanged(int);
    void slotCheckBoxSameClicked(bool);
    void slotPushButtonSubmitClicked();
    void slotComboBoxDataTypeCurrentIndexChanged(int);
    void slotFirstComboBoxDataTypeCurrentIndexChanged(int);
    void slotFirstSpinBoxMinimumValueChanged(int);
    void slotFirstSpinBoxMaximumValueChanged(int);
    void slotFirstSpinBoxToleranceValueChanged(double);
};

#endif // FORMOUTPUTLAYERNEW_H
