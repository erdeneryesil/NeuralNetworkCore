#ifndef FORMSAMPLESFILE_H
#define FORMSAMPLESFILE_H

#include<QtWidgets>

class FormSamplesFile : public QWidget{
    Q_OBJECT
public:
    enum class FileType{TrainingSet,TestSet};
    FormSamplesFile(FileType fileType);
    ~FormSamplesFile();
    FileType getFileType()const;

private:
    QVBoxLayout* _mainLayout;

    QHBoxLayout* _layoutCountSample;
    QLabel*_labelCountSample;
    QSpinBox* _spinBoxCountSample;
    QSpacerItem* _spacerCountSample;

    QHBoxLayout* _layoutFileName;
    QPushButton* _pushButtonOpen;
    QLineEdit*_lineEditSamplesFileName;
    QPushButton* _pushButtonSubmit;

    FileType _fileType;

signals:
    void signalSamplesFileParameters(int,std::string);

private slots:
    void slotPushButtonSubmitClicked();
    void slotPushButtonOpenClicked();
};

#endif // FORMSAMPLESFILE_H
