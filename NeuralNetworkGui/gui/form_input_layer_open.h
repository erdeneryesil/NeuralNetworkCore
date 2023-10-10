#ifndef FORMINPUTLAYEROPEN_H
#define FORMINPUTLAYEROPEN_H

#include<QtWidgets>
#include"neural_network_core/neural_network.h"

class FormInputLayerOpen : public QWidget{
    Q_OBJECT
public:
    FormInputLayerOpen(const InputLayerPattern*const inputLayerPattern);
    ~FormInputLayerOpen();
private:
    QVBoxLayout* _mainLayout;

    QScrollArea* _scrollArea;
    QWidget* _widgetScrollArea;
    QVBoxLayout* _layoutScrollArea;
    QVector<QHBoxLayout*>* _layoutRowsScrollArea;

    QVector<QHBoxLayout*>*_layoutDataType;
    QVector<QWidget*>*_widgetDataType;
    QVector<QLabel*>* _labelDataType;
    QVector<QHBoxLayout*>*_layoutMinimum;
    QVector<QWidget*>*_widgetMinimum;
    QVector<QLabel*>* _labelMinimum;
    QVector<QHBoxLayout*>*_layoutMaximum;
    QVector<QWidget*>*_widgetMaximum;
    QVector<QLabel*>* _labelMaximum;

    QPushButton* _pushButtonSubmit;

    int _countInput;

    void _createItemsRows(const int*const dataTypes,const int*const minimums,const int*const maximums);

signals:
    void signalInputLayerOpenParameters();

private slots:
    void slotPushButtonSubmitClicked();

};

#endif // FORMINPUTLAYEROPEN_H
