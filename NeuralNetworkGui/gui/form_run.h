#ifndef FORMRUN_H
#define FORMRUN_H

#include<QtWidgets>

class FormRun : public QWidget{
    Q_OBJECT
public:
    FormRun();
    ~FormRun();
private:
    QVBoxLayout* _mainLayout;

    QHBoxLayout* _layoutTop;
    QLabel*_labelSeparator;
    QLineEdit*_lineEditSeparator;
    QSpacerItem* _spacerSeparator;

    QHBoxLayout* _layoutBottom;
    QLabel* _labelInputs;
    QLineEdit*_lineEditInputs;
    QPushButton* _pushButtonSubmit;
signals:
    void signalRunParameters(int*const);
private slots:
    void slotPushButtonSubmitClicked();
};

#endif // FORMRUN_H
