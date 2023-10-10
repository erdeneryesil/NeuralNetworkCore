#ifndef FORMOTHERSETTINGSNEW_H
#define FORMOTHERSETTINGSNEW_H

#include<QtWidgets>

class FormOtherSettingsNew : public QWidget
{
    Q_OBJECT
public:
    FormOtherSettingsNew();
    ~FormOtherSettingsNew();
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
    QLabel*_labelRandomWeightMin;
    QDoubleSpinBox*_spinBoxRandomWeightMin;
    QLabel*_labelRandomWeightMax;
    QDoubleSpinBox*_spinBoxRandomWeightMax;

    QGroupBox *_groupBoxParametersFile;
    QVBoxLayout*_layoutParametersFile;
    QSpacerItem*_spacerParametersFile;
    QVector<QHBoxLayout*>*_layoutRowsParametersFile;
    QLabel*_labelSeparator;
    QComboBox* _comboBoxSeparator;
    QPushButton* _pushButtonParametersFileLocation;
    QLineEdit*_lineEditParametersFileLocation;
    QLabel*_labelParametersFileName;
    QLineEdit* _lineEditParametersFileName;

    QPushButton* _pushButtonSubmit;

signals:
    void signalOtherSettingsNewParameters(double,double,double,double,std::string,char);

private slots:
    void slotPushButtonSubmitClicked();
    void slotPushButtonParametersFileLocationClicked();
};


#endif // FORMOTHERSETTINGSNEW_H
