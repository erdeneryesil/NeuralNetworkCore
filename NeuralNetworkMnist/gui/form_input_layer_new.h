#ifndef FORMINPUTLAYERNEW_H
#define FORMINPUTLAYERNEW_H

#include<QtWidgets>
#include"gui/threads.h"

class FormInputLayerNew : public QWidget{
    Q_OBJECT
public:
    FormInputLayerNew();
    ~FormInputLayerNew();
private:
    QVBoxLayout* _mainLayout;

    QLabel* _labelCountInput;
    QSpinBox* _spinBoxCountInput;
    QCheckBox* _checkBoxSame;
    QSpacerItem* _spacerCountInput;
    QHBoxLayout* _layoutHead;

    QScrollArea* _scrollArea;
    QWidget* _widgetScrollArea;
    QVBoxLayout* _layoutScrollArea;
    QVector<QHBoxLayout*>* _layoutRowsScrollArea;

    QVector<QLabel*>* _labelDataType;
    QVector<QComboBox*>* _comboBoxDataType;
    QVector<QHBoxLayout*>*_layoutDataType;
    QVector<QWidget*>*_widgetDataType;
    QVector<QLabel*>* _labelMinimum;
    QVector<QSpinBox*>* _spinBoxMinimum;
    QVector<QHBoxLayout*>*_layoutMinimum;
    QVector<QWidget*>*_widgetMinimum;
    QVector<QLabel*>* _labelMaximum;
    QVector<QSpinBox*>* _spinBoxMaximum;
    QVector<QHBoxLayout*>*_layoutMaximum;
    QVector<QWidget*>*_widgetMaximum;

    QPushButton* _pushButtonSubmit;

    size_t _countInput;

    ThreadWidgetRowOperation* _threadWidgetRowOperation;

    void _threadOperationStarted();
signals:
    void signalInputLayerNewParameters(size_t,int*const,int*const,int*const);

private slots:
    void slotCreateWidgetsInRow();
    void slotDeleteWidgetsInRow();
    void slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType);
    void slotThreadOperationFinished();
    void slotSpinBoxCountInputValueChanged(int);
    void slotCheckBoxSameClicked(bool);
    void slotPushButtonSubmitClicked();
    void slotComboBoxDataTypeCurrentIndexChanged(int);
    void slotFirstComboBoxDataTypeCurrentIndexChanged(int);
    void slotFirstSpinBoxMinimumValueChanged(int);
    void slotFirstSpinBoxMaximumValueChanged(int);
};

#endif // FORMINPUTLAYERNEW_H
