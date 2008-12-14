#ifndef __VEC3_STACK_H__
#define __VEC3_STACK_H__

#if(GM_USE_VECTOR3_STACK)

#include "vector.h"

struct gmVec3Data
{
	float x, y, z;
};

inline gmVec3Data ConvertVec3(const Vector3d &v)
{
	gmVec3Data vr = {v.x,v.y,v.z};
	return vr;
}

inline Vector3d ConvertVec3(const gmVec3Data &v)
{
	return Vector3d(v.x,v.y,v.z);
}
extern gmVec3Data ZERO_VEC3;

class gmMachine;
class gmThread;
struct gmVariable;
void BindVector3Stack(gmMachine *a_machine);

#endif

#endif
