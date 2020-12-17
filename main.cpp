#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QMainWindow>
#include <QtWidgets>

void loadModules(QSplashScreen* psplash)
{
    QTime time;
    time.start();

    for(int i = 0; i < 100; ) {
        if (time.elapsed() > 40) {
            time.start();
            i++;
        }

        psplash->showMessage("Loading modules: " + QString::number(i) + "%",
                             Qt::AlignCenter | Qt::AlignCenter, Qt::black);
        qApp->processEvents();
    }
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
       QSplashScreen splash(QPixmap("C:\\Users\\flenn\\OneDrive\\Desktop\\viz_rest\\base\\load.webp"
                                    ""));
       splash.show();
       loadModules(&splash);
       splash.finish(&w);

   w.show();
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForLocale(codec);
    QFile file("C:\\Users\\flenn\\OneDrive\\Desktop\\viz_rest\\qss.qss");
        file.open(QFile::ReadOnly);
        QString strCSS = QLatin1String(file.readAll());
        a.setStyleSheet(strCSS);


    return a.exec();
}
