// Task #2:

// 1. You are provided with an abstract system called DynamicSystem. It is abstract system which have 3 internal fields: 
// - tick_(aka timestamp);
// - force_;
// - velocity_;

// 2. The main loop of the application updates the internal tick_ to drive the state updates of DynamicSystem;
// 3. Your task is to implement the PRegulate() method such that it maintains the system’s Velocity() close to 1000 ± 100;
// 4. Important: You are not allowed to modify any code outside the PRegulate() method;

// 6. What we expect:
// - a task-2.cpp file with your implementation inside PRegulate();
// - when the program runs correctly, it should output: "Congratulations, you have solved problem!\n";  
// - if you use Git, that’s a bonus and appreciated;
// - as for the build system, use any method you prefer:: from scratch in command line, makefile, cmake - up to you.

// Note: code adapted for c++98

#include <stdio.h>
#include <stdlib.h>

#define TARGET_VELOCITY 	(1000)
#define TARGET_VELOCITY_DELTA 	(100)


class DynamicSystem {
public:
	DynamicSystem() : tick_(0), force_(1), velocity_(0) {}

	void UpdateTick() {
		tick_++;
		velocity_ += force_;
	}

	unsigned int GetTick() {
		return tick_; 
	}

	void SetForce(int force) {
		force_ = force;
	}

	int Velocity() {
		return velocity_; 
	}

private:
	unsigned int tick_;
	int force_;
	int velocity_;
};

DynamicSystem dynamic_system; 

void PRegulate() {
	const int target = TARGET_VELOCITY;
	const int v = dynamic_system.Velocity();
	const int error = target - v;

	const double Kp = 0.05; // must be small to prevent oscillation

	// compute new force
	int new_force = (int)(error * Kp);

	// constrain to avoid runaway
	if (new_force > 50)
		new_force = 50;
	else if (new_force < -50)
		new_force = -50;

	dynamic_system.SetForce(new_force);
}

int main() {
	bool result = true;

	for (unsigned int tick_ms = 0; tick_ms < 10000; tick_ms++) {
		dynamic_system.UpdateTick();

		if (tick_ms % 4 == 0) {
			PRegulate();
		}
		
		bool is_regulation_ok =  abs(dynamic_system.Velocity() - TARGET_VELOCITY) < TARGET_VELOCITY_DELTA;

		if ((!is_regulation_ok) && (dynamic_system.GetTick() > 100)) {
			result = false;
#if 1 // maybe, this printf can help you to debug problem
			printf("%u: velocity fail: %d\n", dynamic_system.GetTick(), dynamic_system.Velocity());
#endif
		}
	}

	if (result) {
		printf("Congratulations, you have solved the problem!\n");
	} 
	else {
		printf("Problem has not been solved.\n");
	}

	return 0;
}
