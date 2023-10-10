#ifndef FORMMAIN_H
#define FORMMAIN_H

#include<QtWidgets>
#include"neural_network_core/neural_network.h"
#include"gui/form_input_layer_new.h"
#include"gui/form_hidden_layers_new.h"
#include"gui/form_output_layer_new.h"
#include"gui/form_other_settings_new.h"
#include"gui/form_input_layer_open.h"
#include"gui/form_hidden_layers_open.h"
#include"gui/form_output_layer_open.h"
#include"gui/form_other_settings_open.h"
#include"gui/form_nn_file.h"
#include"gui/form_samples_file.h"
#include"gui/form_run.h"
#include"gui/graph_ew.h"
#include"gui/threads.h"

class FormMain : public QWidget
{
    Q_OBJECT
public:
    FormMain();
    ~FormMain();
    static NeuralNetwork* NeuralNetworkObject();
    void receiveTrainingInfo(const double& error,const size_t& weight);
    void showOngoingTrainingInfo(const int& countSample,const int& epoch,const double& error,const size_t& weight);
    void showFinishedTrainingInfo(const NeuralNetwork::StatusTraining& statusTraining,const int& countSample,const int& epoch);
    void showTestInfoSample(const int& indexSample,const size_t& indexOutput,const double& output,const double& expectedOutput);
    void showTestInfoResult(const int& countError,const int& countAllOutput,const double& result);
    void showRunInfo(const size_t& indexSingleOutput,const double& singleOutput);
    void resizeEvent(QResizeEvent*) override;
    bool isGraphEWShowing()const;
    const QVector<qreal>* getErrorValues()const;
    const QVector<qreal>* getUpdatedWeights()const;
    size_t getCountEW()const;
    int getCountSample()const;
    const QGraphicsView* getGraphicsView()const;
    int getPaddingGraphicScene()const;
    size_t getMaxCountCell()const;
    int getRCell()const;
    int getRDot()const;
    const QPen& getPenLine()const;
    const QPen& getPenEllipse()const;
    const QBrush& getBrushInputCell()const;
    const QBrush& getBrushHiddenCell()const;
    const QBrush& getBrushOutputCell()const;
    const QBrush& getBrushBiasCell()const;

private:
    QHBoxLayout* _mainLayout;

    QScrollArea* _scrollArea;
    QWidget* _widgetScrollArea;
    QGridLayout* _layoutScrollArea;

    QVBoxLayout* _layoutNNAsset;
    QPushButton* _pushButtonNew;
    QPushButton* _pushButtonOpen;
    QPushButton* _pushButtonEdit;
    QTreeWidget* _treeWidgetNN;
    QSpacerItem* _spacerTop;

    QVBoxLayout* _layoutNNAction;
    QPushButton* _pushButtonTrain;
    QCheckBox* _checkBoxGraph;
    QPushButton* _pushButtonTest;
    QPushButton* _pushButtonRun;
    QLabel* _labelInformation;
    QTextEdit* _textEditInformation;
    QSpacerItem* _spacerBottom;

    QGraphicsView* _graphicViewNN;

    //NeuralNetwork variables
    InputLayerPattern *_inputPattern;
    HiddenLayerPattern *_hiddenPattern;
    OutputLayerPattern *_outputPattern;

    double _lambda;
    double _alfa;
    std::string _parametersFile;
    char _separator;
    double _randomWeightMin;
    double _randomWeightMax;

    bool _errorCreateNNFromFile;
    QString _exceptionWhatCreateNNFromFile;

    static NeuralNetwork* neuralNetwork;

    //Current training variables
    QVector<qreal>*_errorValues;
    QVector<qreal>*_updatedWeights;
    size_t _countEW;
    int _countSample;

    //Test variables
    QString _testInfo;
    int _countErrorOfTest;
    bool _isTextEditInformationFull;

    //Run variables
    QString _runInfo;

    //NNDiagram variables
    ThreadDiagramNN* _threadDiagramNN;
    QGraphicsScene* _graphicSceneNN;
    QPen _penLine;
    QPen _penEllipse;
    QBrush _brushInputCell;
    QBrush _brushHiddenCell;
    QBrush _brushOutputCell;
    QBrush _brushBiasCell;
    size_t _maxCountCell;
    int _rCell;
    int _rDot;
    int _paddingGraphicScene;

    //**************
    FormInputLayerNew* _formInputLayerNew;
    FormHiddenLayersNew* _formHiddenLayersNew;
    FormOutputLayerNew* _formOutputLayerNew;
    FormOtherSettingsNew* _formOtherSettingsNew;
    FormInputLayerOpen* _formInputLayerOpen;
    FormHiddenLayersOpen* _formHiddenLayersOpen;
    FormOutputLayerOpen* _formOutputLayerOpen;
    FormOtherSettingsOpen* _formOtherSettingsOpen;
    FormNNFile* _formNNFile;
    FormSamplesFile* _formSamplesFile;
    FormRun* _formRun;
    GraphEW* _graphEW;

    //***********

    void _createNNFromFile(const std::string&parametersFileName,const char&separator);
    void _createNNWithParameters(const double& lambda,const double& alfa,const std::string& parametersFileName,const char& separator,const double& randomWeightMin,const double& randomWeightMax);

    void _fillTreeWidget();
    void _setMaxCountCellForDiagramNN();
    void _allControlsEnabled();
    void _commonViewOngoingEvents();
    void _viewNoNeuralNetwork();
    void _viewAvailableNeuralNetwork();
    void _viewTrainingIsOngoing();
    void _viewTrainingIsFinished();
    void _viewTestIsOngoing();
    void _viewTestIsFinished();
    void _viewRunIsOngoing();
    void _viewRunIsFinished();
    void _setTextsNoNeuralNetwork();
    void _setTextsAvailableNeuralNetwork();
    void _setTextsTrainingIsOngoing();
    void _setTextsTrainingIsFinished();
    void _setTextsTestIsOngoing();
    void _setTextsTestIsFinished();
    void _setTextsRunIsOngoing();
    void _setTextsRunIsFinished();

private slots:
    void slotPushButtonNewClicked();
    void slotPushButtonOpenClicked();
    void slotPushButtonEditClicked();
    void slotPushButtonTrainClicked();
    void slotCheckBoxGraphClicked(bool);
    void slotPushButtonTestClicked();
    void slotPushButtonRunClicked();
    void slotTreeWidget(QModelIndex);

    //************

    void slotInputLayerNewParameters(size_t,int*const,int*const,int*const);
    void slotHiddenLayersNewParameters(size_t,size_t*const,int*const,int*const);
    void slotOutputLayerNewParameters(size_t,int,int,int*const,int*const,int*const,double*const);
    void slotOtherSettingsNewParameters(double,double,double,double,std::string,char);
    void slotInputLayerOpenParameters();
    void slotHiddenLayersOpenParameters(size_t,int*const,int*const);
    void slotOutputLayerOpenParameters(size_t,int,int,double*const);
    void slotOtherSettingsOpenParameters(double,double);
    void slotNNFileParameters(char,std::string);
    void slotRunParameters(int*const);
    void slotSamplesFileParameters(int,std::string);

    void slotDestroyedInputLayerNew();
    void slotDestroyedHiddenLayersNew();
    void slotDestroyedOutputLayerNew();
    void slotDestroyedOtherSettingsNew();
    void slotDestroyedInputLayerOpen();
    void slotDestroyedHiddenLayersOpen();
    void slotDestroyedOutputLayerOpen();
    void slotDestroyedOtherSettingsOpen();
    void slotDestroyedNNFile();
    void slotDestroyedRun();
    void slotDestroyedSamplesFile();
    void slotDestroyedGraphEW();

    //****************************

    void slotPrepareGraphicSceneForNNDiagram();
    void slotAddLineForNNDiagram(qreal,qreal,qreal, qreal,const QPen&);
    void slotAddEllipseForNNDiagram(qreal,qreal,qreal, qreal,const QPen&,const QBrush&);

   //****************************

signals:
    void signalTextEditInformationSetText(QString);
};

class SignalEpochHandler{
public:
    static void handleSignal(int signalNum);
    static FormMain* owner;
};
#endif // FORMMAIN_H
