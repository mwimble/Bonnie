#ifndef __MOTOR_H
#define __MOTOR_H

#include <ros.h>
#include <QueueList.h>

class Motor {
public:
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT_TURN,
        RIGHT_TURN,
        STOP
    };
  
      typedef struct {
        Direction direction;
    } Command;
  
private:
  
    static const int I1 = 8;
    static const int I2 = 11;
    static const int I3 = 12;
    static const int I4 = 13;
    static const int SPEED_A = 9;
    static const int SPEED_B = 10;
    int _speed;  // Speed of motor.

    const ros::NodeHandle&  _nh;

    static QueueList<Command> _commands;

    void forward() {
        analogWrite(SPEED_A, _speed);
        analogWrite(SPEED_B, _speed);
        digitalWrite(I4, HIGH); // Motor B clockwise.
        digitalWrite(I3, LOW);
        digitalWrite(I2, LOW);  // Motor A clockwise.
        digitalWrite(I1, HIGH);
    }
  
    void backward() {
        analogWrite(SPEED_A, _speed);
        analogWrite(SPEED_B, _speed);
        digitalWrite(I4, LOW); // Motor B anticlockwise.
        digitalWrite(I3, LOW);
        digitalWrite(I2, HIGH);  // Motor A anticlockwise.
        digitalWrite(I1, LOW);
    }
  
    void left() {
        analogWrite(SPEED_A, _speed);
        analogWrite(SPEED_B, _speed);
        digitalWrite(I4, HIGH); // Motor B clockwise.
        digitalWrite(I3, LOW);
        digitalWrite(I2, HIGH);  // Motor A anticlockwise.
        digitalWrite(I1, LOW);
    }
  
    void right() {
        analogWrite(SPEED_A, _speed);
        analogWrite(SPEED_B, _speed);
        digitalWrite(I4, LOW); // Motor B anticlockwise.
        digitalWrite(I3, HIGH);
        digitalWrite(I2, LOW);  // Motor A clockwise.
        digitalWrite(I1, HIGH);
    }
  
    void stop() {
        digitalWrite(SPEED_A, LOW);
        digitalWrite(SPEED_B, LOW);
    }

public:
    Motor(const ros::NodeHandle&  nh) 
        : _nh(nh) {
        _speed = 127;
    }
  
    void enqueue(Command& command) {
        cli();
        _commands.push(command);
        sei();
    }
  
};

QueueList<Motor::Command> Motor::_commands;

#endif
