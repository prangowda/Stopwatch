#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>

class StopWatch : public QMainWindow {
    Q_OBJECT

public:
    StopWatch(QWidget *parent = nullptr);
    ~StopWatch();

private slots:
    void startStopTimer();
    void resetTimer();
    void updateDisplay();

private:
    QLabel *timeDisplay;
    QPushButton *startStopButton;
    QPushButton *resetButton;
    QTimer *timer;

    bool running;
    int elapsedMilliseconds;
};

#endif // STOPWATCH_H
