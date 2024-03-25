#pragma once
#include "Framework.h"

namespace RLCIS {
	constexpr float
		RL_TICKRATE = 120.f,
		RL_TICKTIME = 1 / RL_TICKRATE;

	void Init();

	// All state information needed for the solver
	struct SolverCarState {
		Vec pos;
		RotMat rot;
		Vec vel, angVel;

		SolverCarState() = default;
		explicit SolverCarState(const CarState& carState);

		explicit operator CarState() const;
	};

	struct SolverConfig {
		// Analog inputs below this theshold will be zeroed
		float inputDeadzone = 0.1f;

		// Analog inputs above this threshold will be made 1.0
		float inputInverseDeadzone = 0.95f;

		// Steer and yaw will be assumed to always be equal
		// When on the ground, yaw will be set to steer
		// When in the air, steer will be set to yaw
		bool steerIsYaw = true;
	};

	CarControls Solve(const SolverCarState& fromState, const SolverCarState& toState, float deltaTime, const SolverConfig& config);
}