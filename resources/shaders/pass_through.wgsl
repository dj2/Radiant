struct Uniforms {
  modelViewProjectionMatrix : mat4x4<f32>,
  frame: u32,
  frame_radians: f32,
}

@binding(0) @group(0) var<uniform> uniforms : Uniforms;
struct VertexInput {
  @location(0) pos: vec3f,
  @location(1) color: vec3f,
  @builtin(instance_index) instance: u32,
}

struct VertexOutput {
  @builtin(position) pos: vec4f,
  @location(0) color: vec3f,
}

@vertex
fn vs_main(in : VertexInput) -> VertexOutput {
  let pos  = in.pos + select(vec3f(1, sin(uniforms.frame_radians), 0),
                             vec3f(-1, cos(uniforms.frame_radians), 0),
                             in.instance == 0);
  let projected = uniforms.modelViewProjectionMatrix * vec4(pos, 1);
  return VertexOutput(projected, in.color);
}

@fragment
fn fs_main(in : VertexOutput) -> @location(0) vec4f {
  return vec4(in.color, 1);
}
