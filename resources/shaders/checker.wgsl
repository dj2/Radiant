struct Uniforms {
  modelViewProjectionMatrix : mat4x4<f32>,
  frame: u32,
  frame_radians: f32,
  image_width: u32,
  image_height: u32,
}

@binding(0) @group(0) var<uniform> uniforms : Uniforms;
struct VertexInput {
  @location(0) pos: vec3f,
}

struct VertexOutput {
  @builtin(position) pos: vec4f,
  @location(0) uv: vec3f,
}

@vertex
fn vs_main(in : VertexInput) -> VertexOutput {
  let projected = uniforms.modelViewProjectionMatrix * vec4(in.pos, 1);
  var uv =  in.pos.xyz /
                vec3(f32(uniforms.image_width), f32(uniforms.image_height), f32(uniforms.image_width));
  return VertexOutput(projected, uv);
}

const inverse_checker_size = 256;

@fragment
fn fs_main(in : VertexOutput) -> @location(0) vec4f {
  var pos = in.uv;

  let size = floor(pos * inverse_checker_size);
  let amount = abs((size.x + size.y + size.z) % 2);
  let colour = mix(.9, 1, amount);
  return vec4(vec3(colour), 1);
}
