#include "Angle.h"

Angle::Angle(double pitch, double yaw, double roll) : m_pitch(pitch), m_yaw(yaw), m_roll(roll) {
}

// retourne un vecteur normalisé pointant dans la direction de l'angle
Vector Angle::direction() {
	// angles en radians
	double yawRad = m_yaw / 180 * PI;
	double pitchRad = m_pitch / 180 * PI;
	
	return Vector(sin(yawRad+PI) * cos(pitchRad), sin(pitchRad), cos(yawRad+PI) * cos(pitchRad)).normalized();
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