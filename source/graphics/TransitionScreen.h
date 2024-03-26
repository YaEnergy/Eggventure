#pragma once

class TransitionScreen
{
	public:
		void Update(float deltaTime);
	private:
		float timePassed;
		float transitionTime;
};