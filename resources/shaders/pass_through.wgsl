struct VertexInput {
  @location(0) pos: vec3f,
  @location(1) color: vec3f,
}

struct VertexOutput {
  @builtin(position) pos: vec4f,
  @location(0) color: vec3f,
}

@vertex
fn vs_main(in : VertexInput) -> VertexOutput {
  return VertexOutput(vec4(in.pos, 1), in.color);
}

@fragment
fn fs_main(in : VertexOutput) -> @location(0) vec4f {
  return vec4(in.color, 1);
}
