// #version 430 core

// layout(local_size_x = 16, local_size_y = 16) in;

// layout(rgba8, binding = 0) uniform image2D img;

// in uvec3 gl_NumWorkGroups;
// in uvec3 gl_WorkGroupID;
// in uvec3 gl_LocalInvocationID;
// in uvec3 gl_GlobalInvocationID;
// in uint  gl_LocalInvocationIndex;

// uniform sampler2D inpTexture;


// void main(){
//     ivec2 pixel = ivec2(gl_GlobalInvocationID.xy);
//     imageStore(img, pixel, vec4(1.0, 0.0, 0.0, 1.0));
// }