#ifndef AVR_EMU_H
#define AVR_EMU_H

#include <QThread>

class AVR : public QThread
{
    Q_OBJECT
public:
    explicit AVR(QObject *parent = 0);
    void run(void);

    static unsigned int portd;

signals:
    
public slots:
    void PCINT0_vect(void);
};

#endif // AVR_EMU_H
