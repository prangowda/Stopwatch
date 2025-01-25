#include "stopwatch.h"

StopWatch::StopWatch(QWidget *parent)
    : QMainWindow(parent), running(false), elapsedMilliseconds(0) {
    // Set up the time display
    timeDisplay = new QLabel("00:00:00.000", this);
    timeDisplay->setAlignment(Qt::AlignCenter);
    timeDisplay->setStyleSheet("font-size: 32px; color: #FFFFFF; background-color: #007BFF; border-radius: 10px;");
    timeDisplay->setFixedHeight(80);

    // Set up buttons
    startStopButton = new QPushButton("Start", this);
    resetButton = new QPushButton("Reset", this);

    startStopButton->setStyleSheet("font-size: 18px; padding: 10px; color: #007BFF; background-color: #FFFFFF; border: 2px solid #007BFF; border-radius: 5px;");
    resetButton->setStyleSheet("font-size: 18px; padding: 10px; color: #007BFF; background-color: #FFFFFF; border: 2px solid #007BFF; border-radius: 5px;");

    startStopButton->setFixedSize(100, 40);
    resetButton->setFixedSize(100, 40);

    // Set up timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StopWatch::updateDisplay);

    // Set up button connections
    connect(startStopButton, &QPushButton::clicked, this, &StopWatch::startStopTimer);
    connect(resetButton, &QPushButton::clicked, this, &StopWatch::resetTimer);

    // Set up the layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(startStopButton);
    buttonLayout->addWidget(resetButton);

    mainLayout->addWidget(timeDisplay);
    mainLayout->addLayout(buttonLayout);

    // Set up central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Set window properties
    setWindowTitle("Stopwatch");
    setFixedSize(300, 200);
    setStyleSheet("background-color: #F5F5F5;");
}

StopWatch::~StopWatch() {}

void StopWatch::startStopTimer() {
    if (running) {
        timer->stop();
        startStopButton->setText("Start");
    } else {
        timer->start(10); // Update every 10ms
        startStopButton->setText("Stop");
    }
    running = !running;
}

void StopWatch::resetTimer() {
    timer->stop();
    running = false;
    elapsedMilliseconds = 0;
    startStopButton->setText("Start");
    timeDisplay->setText("00:00:00.000");
}

void StopWatch::updateDisplay() {
    elapsedMilliseconds += 10;

    int milliseconds = elapsedMilliseconds % 1000;
    int seconds = (elapsedMilliseconds / 1000) % 60;
    int minutes = (elapsedMilliseconds / (1000 * 60)) % 60;
    int hours = (elapsedMilliseconds / (1000 * 60 * 60));

    QString timeString = QString("%1:%2:%3.%4")
                             .arg(hours, 2, 10, QChar('0'))
                             .arg(minutes, 2, 10, QChar('0'))
                             .arg(seconds, 2, 10, QChar('0'))
                             .arg(milliseconds, 3, 10, QChar('0'));

    timeDisplay->setText(timeString);
}
