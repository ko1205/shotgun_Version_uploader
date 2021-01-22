#include "selectfiledialog.h"


SelectFileDialog::SelectFileDialog(Core *core)
{
    tmpDir.setPath("./tmp");
    outFormat << ".mp4" << ".webm" << ".jpg";
    this->core = core;
    QString projectName = core->getProjectName();
    QString leftView = core->getLeftViewCurrent();
    QString centerView = core->getCenterViewCurrent();
    QString rightView = core->getRightViewCurrent();

    QString elementType;

    if(core->getElementType() == ASSET){
        elementType = "Asset";
    }else{
        elementType = "Shot";
    }

    QString labelString;
    labelString = QString("Current Project : %1\nCurrent Linek : %2 -> %3 -> %4 -> %5").arg(projectName).arg(elementType).arg(leftView).arg(centerView).arg(rightView);

    label = new QLabel(labelString);
    fileSelectBtn = new QPushButton("Select Upload File");

//    messageWindow = new QPlainTextEdit;
    messageWindow = new QTextBrowser;
    messageWindow->setReadOnly(true);


    layout = new QGridLayout;

    layout->addWidget(label,0,0);
    layout->addWidget(fileSelectBtn,1,0);
    layout->addWidget(messageWindow,2,0);

    setLayout(layout);

    process = new QProcess(this);

    connect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickSelectFile()));

    connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(writeMessage()));
    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(writeMessage()));
    connect(process,SIGNAL(finished(int)),this,SLOT(transeCodingProcess()));


}

SelectFileDialog::~SelectFileDialog()
{
//    thread->terminate();
    qDebug() << "diallog close";
}


void SelectFileDialog::clickSelectFile()
{
    QStringList list = tmpDir.entryList(QDir::Files|QDir::NoDotAndDotDot);
    if(!list.isEmpty()){
        for(int i = 0; i < list.size(); i++)
        {
            QFileInfo output(tmpDir.absoluteFilePath(list[i]));
            if (output.exists() && output.isFile())
            {
                QFile::remove(output.absoluteFilePath());
            }
        }
    }
    selectedFile = QFileDialog::getOpenFileName(this,"Select File",".","movie (*.mov *.mp4 *.avi);;image (*.jpg *.jpeg *.png)");
    QFileInfo check_file(selectedFile);
    if (check_file.exists() && check_file.isFile()) {
        messageWindow->append("Selected File : " + selectedFile);
        messageWindow->append("Start Transecoding........");
        disconnect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickSelectFile()));
        connect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickCancel()));
        fileSelectBtn->setText("Cancel");
//        thread = new JobThread(core, this);
//        thread->start();
//        QString

        transcodingStep = 0;
        transeCodingProcess();
//        process->start("ffmpeg -i "+selectedFile+" -f mp4 ./test.mp4");
//        process->waitForFinished();


    }
    qDebug() << selectedFile;
}

void SelectFileDialog::clickCancel()
{
//    thread->terminate();
//    delete thread;
    if(process->state() == QProcess::Running)
    {
        qDebug() << "process is runing";
        process->terminate();
    }
    qDebug() << "process other thread";
    fileSelectBtn->setText("Select Upload File");
    transcodingStep = 4;
    for(int i = 0; i < outputFile.size(); i++)
    {
        QFileInfo output(outputFile[i]);
        if (output.exists() && output.isFile())
        {
            QFile::remove(outputFile[i]);
        }
    }
    disconnect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickCancel()));
    connect(fileSelectBtn,SIGNAL(clicked(bool)),this,SLOT(clickSelectFile()));

}

void SelectFileDialog::writeMessage()
{
    messageWindow->append(process->readAllStandardOutput());
    messageWindow->append(process->readAllStandardError());
}

void SelectFileDialog::transeCodingProcess()
{
    QFileInfo fileInfo(selectedFile);
    QString baseName = fileInfo.baseName();

    QStringList arg;
    outputFile.clear();

//    QDir tmpDir("./tmp");
    switch(transcodingStep)
    {
        case 0:
            arg << "-i" << selectedFile << "-vcodec" << "libx264";
            arg << "-pix_fmt" << "yuv420p" << "-preset" << "veryslow" << "-crf" << "18";
            arg << "-vf" << "pad=ceil(iw/2)*2:ceil(ih/2)*2"<< "-x264-params" << "colorprim=smpte170m:transfer=smpte170m:colormatrix=smpte170m";
            arg <<"-f" << "mp4" << tmpDir.absolutePath()+ QDir::separator() + baseName + outFormat[0];
            process->start("ffmpeg", arg);
            transcodingStep = 1;
            arg.clear();
            qDebug() << arg;
            outputFile << tmpDir.absolutePath()+ QDir::separator() + baseName + outFormat[0];
            break;

         case 1:
            arg << "-i" << selectedFile << "-vcodec" << "libvpx";
            arg << "-pix_fmt" <<  "yuv420p" << "-g" << "30" << "-b:v" << "2000k";
            arg << "-quality" <<  "realtime" << "-cpu-used" << "0" <<  "-qmin" <<  "10" << "-qmax" << "42";
            arg << "-f" << "webm" << tmpDir.absolutePath()+ QDir::separator() + baseName + outFormat[1];
            process->start("ffmpeg", arg);
            transcodingStep = 2;
            arg.clear();
            outputFile << tmpDir.absolutePath()+ QDir::separator() + baseName + outFormat[0];

            break;

        case 2:
//        ffmpeg -ss 00:00:00 -i KakaoTalk_Video_2020-12-31-14-44-29-1.mp4 -vframes 1 -q:v 2 output.jpg
            arg << "-i" << selectedFile << "-ss" << "00:00:00" << "-vframes" << "1" << "-q:v" << "2";
            arg << tmpDir.absolutePath()+ QDir::separator() + baseName + outFormat[2];
            process->start("ffmpeg", arg);
            transcodingStep = 3;
            arg.clear();
            outputFile << tmpDir.absolutePath()+ QDir::separator() + baseName + outFormat[0];
            break;
        case 3:
            break;
    }
}
