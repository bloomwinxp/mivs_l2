#pragma once

#include <QtCore>
#include <QtWidgets>
#include <QtCharts>
#include <random>
#include <chrono>
#include <vector>
#include <list>

using namespace std;

class Stream : public QWidget {
    Q_OBJECT
    double lambda;
    int N;

    double p1, p2, p3;
    list<int> *count_of_events;
    list<double> *times;
    
    QTextEdit *interval_txtEdit, *times_txtEdit;
    QLineEdit *p1_lineEdit, *p2_lineEdit, *p3_lineEdit, *lambda_lineEdit, *N_lineEdit;
    QPushButton *btn_start;
    QChartView *chartView;
    

    mt19937 *mt_engine_exp;
    mt19937 *mt_engine_event;
    
    uniform_real_distribution<> uniform_dist;

public:
    Stream(QWidget* parent = 0);
    double generate_exp(); // use lambda
    int generate_events(); 
public slots:
    void generate_chart(); 
};