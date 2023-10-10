#ifndef FORMNNFILE_H
#define FORMNNFILE_H

#include<QtWidgets>

class FormNNFile : public QWidget
{
    Q_OBJECT
public:
    FormNNFile();
    ~FormNNFile();

private:
    QVBoxLayout* _mainLayout;

    QHBoxLayout* _layoutTop;
    QLabel*_labelSeparator;
    QComboBox* _comboBoxSeparator;
    QSpacerItem* _spacerSeparator;

    QHBoxLayout* _layoutBottom;
    QPushButton* _pushButtonOpen;
    QLineEdit*_lineEditParametersFileName;
    QPushButton* _pushButtonSubmit;

signals:
    void signalNNFileParameters(char,std::string);

private slots:
    void slotPushButtonSubmitClicked();
    void slotPushButtonOpenClicked();
};

#endif // FORMNNFILE_H
