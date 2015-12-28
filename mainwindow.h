#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "qpixmap.h"
#include "paintwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_generateBtn_clicked();

    void on_SaveBtn_clicked();

    void on_OpenBtn_clicked();

    void on_pushButton_clicked();

    void on_GABtn_clicked();

    void on_ACOBtn_clicked();

private:
    int edgesCount;
    int vertexCount;
    Graph* graph;
    Ui::MainWindow *ui;
    QPixmap*  pixmap;
    PaintWidget * widget;


    void outputGraphIntoTable();
    void clearTable();
    void drawGraph();
    void drawPathOnGraph(const QVector<Vertex>& path);
};

#endif // MAINWINDOW_H
