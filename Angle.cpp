#include "Angle.h"

Angle::Angle(float pitch, float yaw, float roll) : m_pitch(pitch), m_yaw(yaw), m_roll(roll) {
}

// retourne un vecteur normalisé pointant dans la direction de l'angle
Vector Angle::direction() {
	// angles en radians
	float yawRad = m_yaw / 180 * PI;
	float pitchRad = m_pitch / 180 * PI;
	
	return Vector(sin(yawRad+PI) * cos(pitchRad), sin(pitchRad), cos(yawRad+PI) * cos(pitchRad)).normalized();
}

float Angle::pitch() {
	return m_pitch;
}

float Angle::yaw() {
	return m_yaw;
}

float Angle::roll() {
	return m_roll;
}

void Angle::setPitch(float pitch) {
	m_pitch = pitch;
}

void Angle::setYaw(float yaw) {
	m_yaw = yaw;
}

void Angle::setRoll(float roll) {
	m_roll = roll;
}

void Angle::addPitch(float pitch) {
	m_pitch += pitch;
}

void Angle::addYaw(float yaw) {
	m_yaw += yaw;
}

void Angle::addRoll(float roll) {
	m_roll += roll;
}