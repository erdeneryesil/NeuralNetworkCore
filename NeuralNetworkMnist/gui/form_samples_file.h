#ifndef FORMSAMPLESFILE_H
#define FORMSAMPLESFILE_H

#include<QtWidgets>
#include"gui/threads.h"

class FormSamplesFile : public QWidget{
    Q_OBJECT
public:
    enum class FileType{TrainingSet,TestSet};
    FormSamplesFile(FileType fileType);
    ~FormSamplesFile();
    FileType getFileType()const;
    int getCountImage()const;
    std::string getSamplesFile()const;
    int getImageDigitValue()const;
    qreal getSceneImageWidth()const;
    qreal getSceneImageHeight()const;
    bool isSceneImageReady()const;
private:
    QVBoxLayout* _mainLayout;

    QHBoxLayout* _layoutCountSample;
    QLabel*_labelCountSample;
    QSpinBox* _spinBoxCountSample;
    QSpacerItem* _spacerCountSample;

    QHBoxLayout* _layoutFileName;
    QPushButton* _pushButtonOpenFile;
    QLineEdit*_lineEditSamplesFileName;

    QPushButton* _pushButtonLoadImages;
    QHBoxLayout* _layoutImage;
    QLabel*_labelImage;
    QComboBox* _comboBoxImage;
    QScrollArea* _scrollAreaImage;
    QGraphicsView* _graphicsViewImage;
    QSpacerItem* _spacerImage;

    ThreadSampleImages* _threadSampleImages;
    int _countImage;
    int _imageDigitValue;
    std::string _samplesFile;
    QGraphicsScene* _sceneImage;
    bool _isReadySceneImage;


    QPushButton* _pushButtonSubmit;

    FileType _fileType;


    void _viewBeforeLoadImages();
    void _viewAfterLoadImages();

signals:
    void signalSamplesFileParameters(int,std::string);

private slots:
    void slotPushButtonLoadImagesClicked();
    void slotFillImagesError();
    void slotFillImagesFinished();
    void slotPrepareImageGUI(int,int );
    void slotDrawImage(QPixmap);
    void slotPushButtonSubmitClicked();
    void slotPushButtonOpenClicked();
    void slotComboBoxImageCurrentIndexChanged(int);
};

#endif // FORMSAMPLESFILE_H
