struct VertexInput {
  @location(0) pos: vec3<f32>,
  @location(1) color: vec3<f32>,
}

struct VertexOutput {
  @builtin(position) pos: vec4<f32>,
  @location(0) color: vec3<f32>,
}

@vertex
fn vs_main(in : VertexInput) -> VertexOutput {
  return VertexOutput(vec4(in.pos, 1), in.color);
}

@fragment
fn fs_main(in : VertexOutput) -> @location(0) vec4<f32> {
  return vec4(in.color, 1);
}
