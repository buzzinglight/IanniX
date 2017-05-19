varying vec2 texcoord0;
varying vec2 texcoord1;

void main() {
	gl_Position = ftransform();
	//gl_TexCoord[0] = gl_MultiTexCoord0;
	//gl_TexCoord[1] = gl_MultiTexCoord1;

	texcoord0 = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
	texcoord1 = vec2(gl_TextureMatrix[1] * gl_MultiTexCoord1);

	//texcoord0 = gl_MultiTexCoord0.st;
	//texcoord1 = gl_MultiTexCoord1.st;
}