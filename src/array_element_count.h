#pragma once

/// Returns the number of elements in the given array
#define RADIANT_ARRAY_ELEMENT_COUNT(arr) (sizeof((arr)) / sizeof((arr)[0]))
