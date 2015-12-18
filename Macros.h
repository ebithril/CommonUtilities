#pragma once

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SAFE_DELETE(aPointer) delete[] (aPointer); (aPointer) = nullptr;

#define FOR_EACH_NEED_INDEX(i, vector) for(i = 0; i < static_cast<int>(vector.size()); i++)

#define FOR_EACH(vector) for(unsigned int i = 0; i < vector.size(); i++)
#define FOR_EACH_GA(growingarray) for(unsigned int i = 0; i < growingarray.Size(); i++)

#define CYCLIC_ERASE(vector, index) vector[index] = vector[vector.size() - 1]; vector.pop_back();

#define UNLESS(x) if ((x) == false)
#define UNTIL(x) while ((x) == false)
#define GET_PERCENTAGE(numerator, denumerator) ((static_cast<long double>((numerator)) / static_cast<long double>((denumerator))) * 100.0)