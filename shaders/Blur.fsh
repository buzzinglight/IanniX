uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float slide_up;
uniform float slide_down;

varying vec2 texcoord0;
varying vec2 texcoord1;

void main(void) {
	vec4 su, sd, up, down, amount;

	// sample inputs at texcoords
	vec4 input0 = texture2D(tex0, texcoord0);
	vec4 input1 = texture2D(tex1, texcoord1);

	// get contribution
	amount.x = input0.x > input1.x ? 1.0 : 0.0;
	amount.y = input0.y > input1.y ? 1.0 : 0.0;
	amount.z = input0.z > input1.z ? 1.0 : 0.0;
	amount.w = input0.w > input1.w ? 1.0 : 0.0;

	// calculate slide down
	float d = max(1.0, abs(slide_down));
	sd = vec4(1.0 / d);
	down = input1 + ((input0 - input1) * sd);

	// calculate slide up
	float u = max(1.0, abs(slide_up));
	su = vec4(1.0 / u);
	up = input1 + ((input0 - input1) * su);

	// mix between down and up
	gl_FragColor = mix(down, up, amount);
}