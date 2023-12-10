#pragma once

#include <cmath>


enum EaseStates
{


	Sine,
	Quad,
	Cubic,
	Quart,
	Quint,
	Expo,
	Circ

		
};

static float EaseIn(EaseStates states, float t)
{

	if (t < 0.0f)
	{
		t = 0;
	}
	else if (t > 1.0f)
	{
		t = 1.0f;
	}


	switch (states)
	{
	case Sine:

		return 1 - std::cos((t * 3.14) / 2);

		break;
	case Quad:
		return t * t;

		break;
	case Cubic:
		return t * t * t;

		break;
	case Quart:
		return t * t * t * t;

		break;
	case Quint:
		return t * t * t * t * t;

		break;
	case Expo:
		return t == 0 ? 0 : std::pow(2, 10 * t - 10);

		break;
	case Circ:
		return 1 - std::sqrt(1 - std::pow(t, 2));

		break;
	default:
		break;
	}

}

static float EaseOut(EaseStates states, float t)
{

	if (t < 0.0f)
	{
		t = 0;
	}
	else if (t > 1.0f)
	{
		t = 1.0f;
	}

	switch (states)
	{
	case Sine:
		return std::sin((t * 3.14) / 2);

		break;
	case Quad:
		return 1 - (1 - t) * (1 - t);

		break;
	case Cubic:
		return 1 - std::pow(1 - t, 3);

		break;
	case Quart:
		return 1 - std::pow(1 - t, 4);

		break;
	case Quint:
		return 1 - std::pow(1 - t, 5);

		break;
	case Expo:
		return t == 1 ? 1 : 1 - std::pow(2, -10 * t);

		break;
	case Circ:
		return std::sqrt(1 - std::pow(t - 1, 2));

		break;
	default:
		break;
	}

}

