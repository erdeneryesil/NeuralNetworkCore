#ifndef FORMHIDDENLAYERSNEW_H
#define FORMHIDDENLAYERSNEW_H

#include<QtWidgets>
#include"gui/threads.h"

class FormHiddenLayersNew : public QWidget
{
    Q_OBJECT
public:
    FormHiddenLayersNew();
    ~FormHiddenLayersNew();
private:
    QVBoxLayout* _mainLayout;

    QLabel* _labelCountHiddenLayer;
    QSpinBox* _spinBoxCountHiddenLayers;
    QSpacerItem* _spacerCountHiddenLayers;
    QHBoxLayout* _layoutHead;

    QScrollArea* _scrollArea;
    QWidget* _widgetScrollArea;
    QVBoxLayout* _layoutScrollArea;
    QVector<QHBoxLayout*>* _layoutRowsScrollArea;

    QVector<QLabel*>* _labelCountCell;
    QVector<QSpinBox*>* _spinBoxCountCell;
    QVector<QHBoxLayout*>*_layoutCountCell;
    QVector<QWidget*>*_widgetCountCell;
    QVector<QLabel*>* _labelSumFunction;
    QVector<QComboBox*>* _comboBoxSumFunction;
    QVector<QHBoxLayout*>*_layoutSumFunction;
    QVector<QWidget*>*_widgetSumFunction;
    QVector<QLabel*>* _labelActFunction;
    QVector<QComboBox*>* _comboBoxActFunction;
    QVector<QHBoxLayout*>*_layoutActFunction;
    QVector<QWidget*>*_widgetActFunction;

    QPushButton* _pushButtonSubmit;

    size_t _countHiddenLayer;

    ThreadWidgetRowOperation* _threadWidgetRowOperation;

    void _threadOperationStarted();

    void _removeHiddenLayerItemsRow(const int& countRow);
    void _addHiddenLayerItemsRow(const int& countRow);

signals:
    void signalHiddenLayersNewParameters(size_t,size_t*const,int*const,int*const);

private slots:
    void slotCreateWidgetsInRow();
    void slotDeleteWidgetsInRow();
    void slotWidgetScrollAreaSetHeight(const ThreadWidgetRowOperation::OperationType&);
    void slotThreadOperationFinished();
    void slotSpinBoxCountHiddenLayersValueChanged(int value);
    void slotPushButtonSubmitClicked();
};

#endif // FORMHIDDENLAYERSNEW_H
