#ifndef __QUADRATURE_ENCODER_H
#define __QUADRATURE_ENCODER_H

#include <Arduino.h>
#include "RosLogger.h"

extern RosLogger* rlog;

class QuadratureEncoder {
private:
  static const int QEA = 4;  // Quadrature Encoder Signal A (black wire) => INT-4, Pin 19.
  static const int QEB = 5;  // Quadrature Encoder Signal B (white wire) => INT-5, Pin 18.
  static const int SIGA = 19;
  static const int SIGB = 18;

  static long counter;		// Running counter.

public:
	
	QuadratureEncoder() {
		rlog->info("QuadratureEncoder started");
		pinMode(QEA, INPUT_PULLUP);
		pinMode(QEB, INPUT_PULLUP);
		attachInterrupt(QEA, qeaChange, CHANGE);
		attachInterrupt(QEB, qebChange, CHANGE);
	}

	void info() {
		rlog->info("QE response");
	}

  	static long Counter() {
  		return QuadratureEncoder::counter;
	}

private:
	static void qeaChange() {
		int a = digitalRead(SIGA);
		int b = digitalRead(SIGB);
		if (a == b) counter++;
		else counter--;
	}

	static void qebChange() {
		int a = digitalRead(SIGA);
		int b = digitalRead(SIGB);
		if (a != b) counter++;
		else counter--;
	}

};

long QuadratureEncoder::counter;		// Running counter.

#endif