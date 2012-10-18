#pragma once

//Time
typedef glm::highp_uint  microseconds;
typedef glm::lowp_uint   milliseconds;
typedef glm::highp_float seconds;

//Position
#if defined(GLM_PRECISION_HIGHP_FLOAT)
    typedef glm::highp_float coord;
	typedef glm::highp_vec3  point;
	typedef glm::highp_vec2  point2;
#else
    typedef glm::mediump_float coord;
	typedef glm::mediump_vec3 point;
	typedef glm::mediump_vec2 point2;
#endif

//Orientation
typedef glm::mediump_float degrees;
typedef glm::mediump_float radians;
typedef glm::mediump_vec3 angles;

//Material
typedef glm::lowp_vec4 colour;

#ifdef DEBUG
	#pragma warning(default:4146)
#endif