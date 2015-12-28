#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphgenerator.h"
#include "graphpainter.h"
#include "qfiledialog.h"
#include "qstring.h"
#include "qtextstream.h"
#include "qfile.h"

#include "antcolony.h"
#include "geneticalgorithm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList lst;
    lst << "Начальная" << "Конечная" << "Вес" ;
    ui->edgesInputTable->setHorizontalHeaderLabels(lst);
    edgesCount = 0;
    vertexCount = 0;
    graph = NULL;
    pixmap = new QPixmap(800, 800);
    widget = new PaintWidget(ui->centralWidget);
    widget->setGeometry(360,10,800,800);
    widget->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::outputGraphIntoTable()
{
    clearTable();
    int edgeNumber = -1;
    for ( int i = 0; i < graph->VertexCount(); i++){
        int j = ( graph->IsDirected() ) ? 0 : i+1;
        for (; j < graph->VertexCount(); j++){
            if ( graph->EdgeWeight( i, j ) > 0){
                edgeNumber++;
                ui->edgesInputTable->insertRow(edgeNumber);
                QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(i));
                ui->edgesInputTable->setItem(edgeNumber, 0, newItem);
                newItem = new QTableWidgetItem(QString::number(j));
                ui->edgesInputTable->setItem(edgeNumber, 1, newItem);
                newItem = new QTableWidgetItem(QString::number(graph->EdgeWeight( i, j )));
                ui->edgesInputTable->setItem(edgeNumber, 2, newItem);
            }
        }
    }

}

void MainWindow::on_generateBtn_clicked()
{
    int vertexCount2 = ui->vertexGenerateEdit->text().toInt();
    int density = ui->densityEdit->text().toInt();
    int minWeight = ui->minWeightEdit->text().toInt();
    int maxWeight = ui->maxWeightEdit->text().toInt();
    bool directed = (ui->isDirectedCBox->checkState() == Qt::Checked) ? true : false;
    bool weighted = (ui->weightedCBox->checkState() == Qt::Checked) ? true : false;
    bool oneDirect = (ui->OneDirectCB->checkState() == Qt::Checked) ? true : false;
    GraphGenerator generator(vertexCount2, density, directed, weighted, minWeight, maxWeight, oneDirect);
    if ( graph != NULL ) {
        delete graph;
    }
    graph = generator.generateGraph();
    outputGraphIntoTable();
    drawGraph();

}

void MainWindow::on_SaveBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName();
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)){
        return;
    }
    QTextStream out(&file);
    out << graph->VertexCount() << endl;
    out << graph->EdgeCount() << endl;
    out << graph->IsDirected() << endl;
    for ( int i = 0; i < graph->VertexCount(); i++){
        int j = ( graph->IsDirected() ) ? 0 : i+1;
        for (; j < graph->VertexCount(); j++){
            if ( graph->EdgeWeight( i, j ) > 0){
                out << i << ' ' << j << ' ' << graph->EdgeWeight( i, j ) << endl;
            }
        }
    }

}

void MainWindow::on_OpenBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        return;
    }
    QTextStream in(&file);
    if ( graph != NULL ) {
        delete graph;
    }
    int vertexCount;
    int edgeCount;
    int directed;
    in >> vertexCount;
    in >> edgeCount;
    in >> directed;
    graph = new Graph(vertexCount, directed);
    for ( int i = 0; i < edgeCount; i++ ){
        int source, destination, weight;
        in >> source >> destination >> weight;
        graph->InsertEdge( Edge(source, destination, weight) );
    }
    outputGraphIntoTable();
    drawGraph();
}

void MainWindow::clearTable()
{
    ui->edgesInputTable->setRowCount(0);
}

void MainWindow::drawGraph()
{
    pixmap->fill();
    GraphPainter painter(pixmap);
    painter.drawGraph(graph);
    widget->setPixmap(pixmap);
    widget->repaint();
}

void MainWindow::on_pushButton_clicked()
{
    AntColony ac(7, 3, 0.5,  *graph);
    GraphPainter painter(pixmap);
    painter.drawGraph(graph);
    QVector<int> result = ac.shortestRoute(15, &painter, widget);
    QString outputPathStr = "";
    QString temp = "";
    for ( int i = 0; i < result.count(); i++){
        temp.setNum(result[i]);
        outputPathStr += temp;
        outputPathStr += ' ';
    }
    outputPathStr += '\n';
    temp.setNum(ac.routeLength());
    outputPathStr += temp;
    ui->textBrowser->setPlainText(outputPathStr);
}

void MainWindow::on_GABtn_clicked()
{
    GraphPainter painter(pixmap);
    painter.drawGraph(graph);
    GeneticAlgorithm ga(*graph, &painter, widget);
    QVector<int> result = ga.shortestRoute();

    QString outputPathStr = "";
    QString temp = "";
    for ( int i = 0; i < result.count(); i++){
        temp.setNum(result[i]);
        outputPathStr += temp;
        outputPathStr += ' ';
    }
    outputPathStr += '\n';
    temp.setNum(ga.routeLength());
    outputPathStr += temp;
    ui->textBrowser->setPlainText(outputPathStr);
}

void MainWindow::on_ACOBtn_clicked()
{
    on_pushButton_clicked();
}
