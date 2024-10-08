#include "stream_of_event.h"
#include <cmath>
#include <sstream>


Stream::Stream(QWidget *parent) : QWidget(parent) {
    QLabel *p1_label, *p2_label, *p3_label, *lambda_label, *N_label;

    btn_start = new QPushButton("Generate!");

    p1_label = new QLabel("Вероятность наступления 1 события");
    p2_label = new QLabel("Вероятность наступления 2 событий");
    p3_label = new QLabel("Вероятность наступления 3 событий");
    lambda_label = new QLabel("Параметр lambda эксп. распред.");
    N_label = new QLabel("Количество событий");
    
    chartView = new QChartView();

    QLabel *lbl1 = new QLabel("Здесь могла быть ваша реклама");

    p1_lineEdit = new QLineEdit();
    p1_lineEdit->setText(QString::number(0.1));
    p2_lineEdit = new QLineEdit();
    p2_lineEdit->setText(QString::number(0.1));
    p3_lineEdit = new QLineEdit();
    p3_lineEdit->setText(QString::number(0.8));
    lambda_lineEdit = new QLineEdit("1");
    N_lineEdit = new QLineEdit("1000");

    interval_txtEdit = new QTextEdit();
    times_txtEdit = new QTextEdit();
    interval_txtEdit->setReadOnly(true);
    times_txtEdit->setReadOnly(true);

    QHBoxLayout *qhb1 = new QHBoxLayout();
    QHBoxLayout *qhb2 = new QHBoxLayout();
    QHBoxLayout *qhb3 = new QHBoxLayout();
    QHBoxLayout *qhb4 = new QHBoxLayout();
    QHBoxLayout *qhb5 = new QHBoxLayout();
    QHBoxLayout *qhb6 = new QHBoxLayout();
    QHBoxLayout *qhb7 = new QHBoxLayout();

    QVBoxLayout *qvb1 = new QVBoxLayout();
    QVBoxLayout *qvb2 = new QVBoxLayout();

    QWidget *wgt1 = new QWidget();
    QWidget *wgt2 = new QWidget();
    QWidget *wgt3 = new QWidget();
    QWidget *wgt4 = new QWidget();
    QWidget *wgt5 = new QWidget();
    QWidget *wgt6 = new QWidget();
    QWidget *wgt7 = new QWidget();
    QWidget *wgt8 = new QWidget();

    qhb1->addWidget(p1_label);
    qhb1->addWidget(p1_lineEdit);

    qhb2->addWidget(p2_label);
    qhb2->addWidget(p2_lineEdit);

    qhb3->addWidget(p3_label);
    qhb3->addWidget(p3_lineEdit);

    qhb5->addWidget(lambda_label);
    qhb5->addWidget(lambda_lineEdit);

    qhb7->addWidget(N_label);
    qhb7->addWidget(N_lineEdit);

    qhb4->addWidget(lbl1);
    qhb4->addWidget(btn_start);

    wgt1->setLayout(qhb1);
    wgt2->setLayout(qhb2);
    wgt3->setLayout(qhb3);
    wgt5->setLayout(qhb5);
    wgt7->setLayout(qhb7);
    wgt4->setLayout(qhb4);

    qvb1->addWidget(wgt1);
    qvb1->addWidget(wgt2);
    qvb1->addWidget(wgt3);
    qvb1->addWidget(wgt5);
    qvb1->addWidget(wgt7);
    qvb1->addWidget(wgt4);

    wgt1->setMaximumWidth(350);
    wgt2->setMaximumWidth(350);
    wgt3->setMaximumWidth(350);
    wgt4->setMaximumWidth(350);
    wgt5->setMaximumWidth(350);
    wgt7->setMaximumWidth(350);

    wgt6->setLayout(qvb1);

    wgt8->setLayout(qvb2);
    wgt8->setMaximumWidth(250);

    qhb6->addWidget(wgt6);
    qhb6->addWidget(interval_txtEdit);
    qhb6->addWidget(times_txtEdit);
    wgt6->setMaximumHeight(280);
    chartView->setMinimumSize(QSize(600,400));
    QObject::connect(btn_start, SIGNAL(clicked()), SLOT(generate_chart()));
    
    generate_chart();
    setLayout(qhb6);   
}

double Stream::generate_exp() {
    return -log(1-uniform_dist(*mt_engine_exp)) / lambda;
}

int Stream::generate_events() {
    double u = uniform_dist(*mt_engine_event);
    int k{};
    if(u < p1) {
        k = 1;
    } else if(u < p1+p2) {
        k = 2;
    } else {
        k = 3;
    }
    return k;
}
void Stream::generate_chart() {
    mt_engine_event = new mt19937(chrono::system_clock::now().time_since_epoch().count());
    mt_engine_exp = new mt19937(chrono::system_clock::now().time_since_epoch().count());
    
    count_of_events = new list<int>{};
    times = new list<double>{};

    N = N_lineEdit->text().toInt();
    p1 = p1_lineEdit->text().toDouble();
    p2 = p2_lineEdit->text().toDouble();
    p3 = p3_lineEdit->text().toDouble();
    lambda = lambda_lineEdit->text().toDouble();
    
    int tmp, k;
    for(tmp = generate_events(), k = 0; k < N; k += tmp, tmp = generate_events()) {
        count_of_events->push_back(tmp);
        times->push_back(generate_exp());
    }
    count_of_events->push_back(tmp);
    times->push_back(generate_exp());

    int count_of_intervals = times->size();
    qDebug() << count_of_events->size() << times->size();
    ostringstream ostream_times;
    ostringstream ostream_intervals;

    auto it_times = times->begin();
    auto it_events = count_of_events->begin();

    k = 0;
    double t{};
    for(int i = 0; i < count_of_intervals - 1; ++i) {
        
        ostream_intervals << t << " - " << k << "\n";
        k += *it_events;
        
        ostream_times << "[ " << t;
        ++it_times;
        t += *it_times;
        ostream_times << " ; " << t << " ]" << " - " << *it_events << "\n";
        ++it_events;
    }
    ostream_intervals << t << " - " << k << "\n";
    

    interval_txtEdit->setText(QString(ostream_times.str().c_str()));
    times_txtEdit->setText(QString(ostream_intervals.str().c_str()));
}
