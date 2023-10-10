#include "form_run.h"
#include"gui/defines_gui.h"
#include "form_main.h"


GraphicsViewHandwriting::GraphicsViewHandwriting(QWidget*){
    this->_widthImageHandwriting=HANDWRITING_AREA_WIDTH;
    this->_heightImageHandwriting=HANDWRITING_AREA_HEIGHT;

    this->_widthImageSample=IMAGE_WIDTH;
    this->_heightImageSample=IMAGE_HEIGHT;

    this->_requiredHeightCroppedArea=HANDWRITING_CROPPED_AREA_HEIGHT;

    this->_imageHandwriting=new QImage();
    this->_imageCroppedArea=new QImage();
    this->_imageHeighthAdjustedCroppedArea=new QImage();
    this->_pixmapSample=new QPixmap();
    this->_imageSample=new QImage();

    this->_pen=new QPen();
    this->_pen->setColor(Qt::white);
    this->_pen->setCapStyle(Qt::PenCapStyle::RoundCap);
    this->_pen->setWidth(HANDWRITING_PEN_WIDTH);

    this->setFixedSize(HANDWRITING_AREA_WIDTH+2*this->frameWidth(),HANDWRITING_AREA_HEIGHT+2*this->frameWidth());
    this->_sceneHandwriting=new QGraphicsScene(0,0,this->width()-2*this->frameWidth(),this->height()-2*this->frameWidth());

    this->_firstPoint=new QPointF(-1,-1);
    this->_secondPoint=new QPointF(-1,-1);

    this->setScene(this->_sceneHandwriting);
    this->setBackgroundBrush(Qt::black);

}
GraphicsViewHandwriting::~GraphicsViewHandwriting(){

    this->_sceneHandwriting->clear();
    delete this->_sceneHandwriting;

    delete this->_imageHandwriting;
    delete this->_imageCroppedArea;
    delete this->_imageHeighthAdjustedCroppedArea;
    delete _pixmapSample;
    delete this->_imageSample;

    delete this->_firstPoint;
    delete this->_secondPoint;
    delete this->_pen;

}
const QPixmap* GraphicsViewHandwriting::getCurrentPixmap(){

    this->_createImageHandwritten();
    this->_calculateCroppedAreaMinMaxXY();
    this->_calculateCroppedAreaRectangle();
    this->_createImageCroppedArea();
    this->_createImageHeighthAdjustedCroppedArea();
    this->_updateTopLeftYCroppedArea();
    this->_createImageSample();

    delete this->_pixmapSample;
    this->_pixmapSample=new QPixmap(QPixmap::fromImage(*this->_imageSample).scaled(this->_widthImageSample,this->_heightImageSample,Qt::AspectRatioMode::KeepAspectRatio));
    return this->_pixmapSample;
}

void GraphicsViewHandwriting::mousePressEvent(QMouseEvent*e){
    this->_firstPoint->setX(e->x());
    this->_firstPoint->setY(e->y());
}
void GraphicsViewHandwriting::mouseMoveEvent(QMouseEvent*e){

    this->_secondPoint->setX(e->x());
    this->_secondPoint->setY(e->y());

    this->_sceneHandwriting->addLine(this->_firstPoint->x(),this->_firstPoint->y(),this->_secondPoint->x(),this->_secondPoint->y(),*this->_pen);

    this->_firstPoint->setX(this->_secondPoint->x());
    this->_firstPoint->setY(this->_secondPoint->y());

    emit signalWriting(this->getCurrentPixmap());
}

void GraphicsViewHandwriting::_createImageHandwritten(){
    delete this->_imageHandwriting;
    this->_imageHandwriting=new QImage(HANDWRITING_AREA_WIDTH+2*this->frameWidth(),HANDWRITING_AREA_HEIGHT+2*this->frameWidth(),QImage::Format::Format_Mono);
    this->_imageHandwriting->fill(Qt::transparent);

    QPainter painterImageHandwritten(this->_imageHandwriting);
    this->scene()->render(&painterImageHandwritten);
}
void GraphicsViewHandwriting::_calculateCroppedAreaMinMaxXY(){
    this->_xMinCroppedArea=this->_imageHandwriting->width();
    this->_xMaxCroppedArea=0;
    this->_yMinCroppedArea=this->_imageHandwriting->height();
    this->_yMaxCroppedArea=0;

    for(int y=0;y<this->_imageHandwriting->height();y++){
        for(int x=0;x<this->_imageHandwriting->width();x++){
            QColor color(this->_imageHandwriting->pixel(x,y));
            int pixel=1-color.blackF();

            if(pixel==1){
                if(x<this->_xMinCroppedArea)this->_xMinCroppedArea=x;
                if(y<this->_yMinCroppedArea)this->_yMinCroppedArea=y;
                if(x>this->_xMaxCroppedArea)this->_xMaxCroppedArea=x;
                if(y>this->_yMaxCroppedArea)this->_yMaxCroppedArea=y;
            }
        }
    }
}
void GraphicsViewHandwriting::_calculateCroppedAreaRectangle(){
    this->_widthCroppedArea=this->_xMaxCroppedArea-this->_xMinCroppedArea;
    this->_heightCroppedArea=this->_yMaxCroppedArea-this->_yMinCroppedArea;
    this->_topLeftYCroppedArea=(this->_imageHandwriting->height()-std::abs(this->_yMaxCroppedArea-this->_yMinCroppedArea))/2;
    this->_topLeftXCroppedArea=(this->_imageHandwriting->width()-std::abs(this->_xMaxCroppedArea-this->_xMinCroppedArea))/2;
}
void GraphicsViewHandwriting::_createImageCroppedArea(){
    delete this->_imageCroppedArea;
    this->_imageCroppedArea=new QImage(this->_imageHandwriting->copy(this->_xMinCroppedArea,this->_yMinCroppedArea,this->_widthCroppedArea,this->_heightCroppedArea));
}
void GraphicsViewHandwriting::_createImageHeighthAdjustedCroppedArea(){
    if(this->_imageCroppedArea->isNull())return;

    double rateHeight=(double)this->_requiredHeightCroppedArea/(double)this->_heightCroppedArea;
    delete this->_imageHeighthAdjustedCroppedArea;
    this->_imageHeighthAdjustedCroppedArea=new QImage(this->_imageCroppedArea->scaled(this->_widthCroppedArea,rateHeight*this->_heightCroppedArea,Qt::AspectRatioMode::IgnoreAspectRatio));
}
void GraphicsViewHandwriting::_updateTopLeftYCroppedArea(){
    this->_topLeftYCroppedArea-=(this->_requiredHeightCroppedArea-this->_heightCroppedArea)/2.0;
}
void GraphicsViewHandwriting::_createImageSample(){
    delete this->_imageSample;
    this->_imageSample=new QImage(HANDWRITING_AREA_WIDTH+2*this->frameWidth(),HANDWRITING_AREA_HEIGHT+2*this->frameWidth(),QImage::Format::Format_Mono);
    this->_imageSample->fill(Qt::transparent);

    QPainter painterImageSample(this->_imageSample);
    painterImageSample.drawImage(QRect(this->_topLeftXCroppedArea,this->_topLeftYCroppedArea,this->_imageHeighthAdjustedCroppedArea->width(),this->_imageHeighthAdjustedCroppedArea->height()),*this->_imageHeighthAdjustedCroppedArea,QRect(0,0,this->_imageHeighthAdjustedCroppedArea->width(),this->_imageHeighthAdjustedCroppedArea->height()));
    painterImageSample.end();
}


FormRun::FormRun(){

    this->_mainLayout=new QVBoxLayout();

    this->_graphicsViewHandwriting=new GraphicsViewHandwriting();

    this->_layoutTop=new QHBoxLayout();

    this->_layoutBottom=new QHBoxLayout();
    this->_pushButtonClear=new QPushButton();
    this->_pushButtonSubmit=new QPushButton();

    this->_mainLayout->addWidget(this->_graphicsViewHandwriting);


    this->_pushButtonClear->setText("Clear");
    this->_layoutTop->addWidget(this->_pushButtonClear);

    this->_mainLayout->addLayout(this->_layoutTop);

    this->_graphicsViewSample=new QGraphicsView();
    this->_graphicsViewSample->setFixedSize(IMAGE_WIDTH+2*this->_graphicsViewSample->frameWidth(),IMAGE_HEIGHT+2*this->_graphicsViewSample->frameWidth());
    this->_graphicsViewSample->setBackgroundBrush(Qt::black);
    this->_sceneSample=new QGraphicsScene(0,0,this->_graphicsViewSample->width()-2*this->_graphicsViewSample->frameWidth(),this->_graphicsViewSample->height()-2*this->_graphicsViewSample->frameWidth());
    this->_graphicsViewSample->setScene(this->_sceneSample);
    this->_layoutBottom->addWidget(this->_graphicsViewSample);

    this->_pushButtonSubmit->setText("OK");
    this->_layoutBottom->addWidget(this->_pushButtonSubmit);

    this->_mainLayout->addLayout(this->_layoutBottom);

    this->setWindowTitle("Run");

    this->setLayout(this->_mainLayout);
    this->setFixedSize(this->sizeHint().width(),this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
    connect(this->_pushButtonClear,SIGNAL(clicked()),this,SLOT(slotPushButtonClearClicked()));
    connect(this->_graphicsViewHandwriting,SIGNAL(signalWriting(const QPixmap*)),this,SLOT(slotWriting(const QPixmap*)));
}
FormRun::~FormRun(){
    this->_sceneSample->clear();
    delete _sceneSample;
    delete this->_graphicsViewSample;
    delete this->_pushButtonSubmit;
    delete this->_layoutBottom;

    delete this->_pushButtonClear;

    delete this->_graphicsViewHandwriting;
    delete this->_layoutTop;

    delete this->_mainLayout;
}

void FormRun::slotPushButtonSubmitClicked(){

    int inputs[FormMain::NeuralNetworkObject()->getInputLayerPattern()->getCountOriginal()];
    QImage image(IMAGE_WIDTH,IMAGE_HEIGHT,QImage::Format::Format_Mono);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    this->_sceneSample->render(&painter);

    int counterInput=0;
    for(int y=0;y<image.height();y++){
        for(int x=0;x<image.width();x++){
            QColor pixel(image.pixel(x,y));
            inputs[counterInput++]=1-pixel.blackF();
        }
    }

    emit signalRunParameters(inputs);
    this->close();
}
void FormRun::slotPushButtonClearClicked(){
    this->_graphicsViewHandwriting->scene()->clear();
    this->_graphicsViewSample->scene()->clear();
}
void FormRun::slotWriting(const QPixmap* pixmap){
    this->_sceneSample->clear();
    this->_sceneSample->addPixmap(*pixmap);
}
