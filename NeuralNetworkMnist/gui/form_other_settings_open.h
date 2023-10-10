#ifndef FORMOTHERSETTINGSOPEN_H
#define FORMOTHERSETTINGSOPEN_H

#include<QtWidgets>

class FormOtherSettingsOpen : public QWidget
{
    Q_OBJECT
public:
    FormOtherSettingsOpen(const double&lambda,const double&alfa,const char&separator,const std::string&parametersFile);
    ~FormOtherSettingsOpen();

private:
    QVBoxLayout* _mainLayout;

    QGroupBox *_groupBoxTraining;
    QVBoxLayout*_layoutTraining;
    QSpacerItem*_spacerTraining;
    QVector<QHBoxLayout*>*_layoutRowsTraining;
    QLabel*_labelLambda;
    QDoubleSpinBox*_spinBoxLambda;
    QLabel*_labelAlfa;
    QDoubleSpinBox*_spinBoxAlfa;

    QGroupBox *_groupBoxParametersFile;
    QVBoxLayout*_layoutParametersFile;
    QVector<QHBoxLayout*>*_layoutRowsParametersFile;
    QSpacerItem* _spacerParametersFile;
    QLabel*_labelParametersFileName;
    QLineEdit*_lineEditParametersFileName;
    QLabel*_labelSeparator;
    QLineEdit*_lineEditSeparator;

    QPushButton* _pushButtonSubmit;

signals:
    void signalOtherSettingsOpenParameters(double,double);

private slots:
    void slotPushButtonSubmitClicked();
};

#endif // FORMOTHERSETTINGSOPEN_H
