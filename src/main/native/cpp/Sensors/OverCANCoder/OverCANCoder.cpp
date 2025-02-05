// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "OvertureLib/Sensors/OverCANCoder/OverCANCoder.h"

#ifndef __FRC_ROBORIO__
#include "OvertureLib/Simulation/SimCANCoderManager/SimCANCoderManager.h"
#endif

/**
 * @brief Constructor for OverCANCoder
 *
 * @param _id    CAN ID of the CANCoder
 *
 * @param offset Offset of the CANCoder
 *
 * @param bus    CAN Bus of the CANCoder
 */
OverCANCoder::OverCANCoder(CanCoderConfig config, std::string bus) : CANcoder(
		config.CanCoderId, bus) {

	canCoderConfiguration.MagnetSensor.WithAbsoluteSensorDiscontinuityPoint(
			0.5_tr);
	canCoderConfiguration.MagnetSensor.WithMagnetOffset(config.Offset);
	canCoderConfiguration.MagnetSensor.WithSensorDirection(
			config.SensorDirection);

	GetConfigurator().Apply(canCoderConfiguration);

#ifndef __FRC_ROBORIO__
	SimCANCoderManager &simCANCoderManager = SimCANCoderManager::GetInstance();
	simCANCoderManager.AddSimCANCoderCandidate(this);
#endif
}

const CANcoderConfiguration& OverCANCoder::getConfiguration() {
	return canCoderConfiguration;
}
