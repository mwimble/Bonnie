#include <ros.h>

#include "QuadratureEncoder.h"
#include "RosLogger.h"

ros::NodeHandle  	nh;
QuadratureEncoder*	quadratureEncoder;
RosLogger*			rlog;

int loopCounter = 1;

void setup() {
//	Serial.begin(115200);
	nh.initNode();
	delay(1000);

	rlog = new RosLogger(nh);
	quadratureEncoder = new QuadratureEncoder();
}

void loop() {
	rlog->info("Number: %d", loopCounter++);
	quadratureEncoder->info();
	nh.spinOnce();
	delay(1000);
}