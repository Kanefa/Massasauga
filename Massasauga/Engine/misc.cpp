#include "misc.h"
#include <math.h>

double Round(double value)
{
	return floor(value + 0.5);
}

double ForceProgress(double value)
{
	if (value < 0.0)
	{
		// round towards negative infinity
		return (value > -1.0 && value < 0.0) ? -1.0 : value;
	}
	else
	{
		// round towards positive infinity
		return (value > 0.0 && value < 1.0) ? 1.0 : value;
	}
}