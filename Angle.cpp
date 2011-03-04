#include "Angle.h"

Angle::Angle(double pitch, double yaw, double roll) : m_pitch(pitch), m_yaw(yaw), m_roll(roll) {
}

double Angle::pitch() {
	return m_pitch;
}

double Angle::yaw() {
	return m_yaw;
}

double Angle::roll() {
	return m_roll;
}

void Angle::setPitch(double pitch) {
	m_pitch = pitch;
}

void Angle::setYaw(double yaw) {
	m_yaw = yaw;
}

void Angle::setRoll(double roll) {
	m_roll = roll;
}

void Angle::addPitch(double pitch) {
	m_pitch += pitch;
}

void Angle::addYaw(double yaw) {
	m_yaw += yaw;
}

void Angle::addRoll(double roll) {
	m_roll += roll;
}