#include <string>

//#define USE_USBCON 1
#include <ros.h>
#include <QueueList.h>

#include "LineSensor.h"
#include "Motor.h"
#include "QTRSensors.h"
#include "QuadratureEncoder.h"
#include "RosLogger.h"
#include <Timer5.h>

ros::NodeHandle  	nh;
LineSensor*			lineSensor;
Motor*				motor;
QuadratureEncoder*	quadratureEncoder;
RosLogger*			rlog;

int loopCounter = 1;

void setup() {
//	Serial.begin(115200);
	nh.initNode();
	delay(1000);

	rlog = new RosLogger(nh);
	quadratureEncoder = new QuadratureEncoder();
	lineSensor = new LineSensor();
	lineSensor->calibrate();
	motor = new Motor(nh);
}

char buffer[128];

void loop() {
	lineSensor->read();
	const LineSensor::TSensorArray& values = lineSensor->sensorValues();

	sprintf(buffer, "Position: %d, values: L> %d, %d, %d, %d, %d, %d, %d, %d <R",
		lineSensor->position(),
		values[0],
		values[1],
		values[2],
		values[3],
		values[4],
		values[5],
		values[6],
		values[7]
		);
	
	rlog->info("Number: %d, quad: %d", loopCounter++, QuadratureEncoder::Counter());
	rlog->info(buffer);
	quadratureEncoder->info();
	nh.spinOnce();
	delay(1000);
}