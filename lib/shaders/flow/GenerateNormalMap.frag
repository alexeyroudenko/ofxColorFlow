uniform float time;
uniform sampler2DRect texture;

void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    float delta = 1.;
    float M = abs(texture2DRect(texture, pos + vec2(0, 0)).r);
    float L = abs(texture2DRect(texture, pos + vec2(delta, 0)).r);
    float R = abs(texture2DRect(texture, pos + vec2(-delta, 0)).r);
    float U = abs(texture2DRect(texture, pos + vec2(0, delta)).r);
    float D = abs(texture2DRect(texture, pos + vec2(0, -delta)).r);
    float X = ((R-M)+(M-L))*.5;
    float Y = ((D-M)+(M-U))*.5;
    vec4 N = vec4(normalize(vec3(X, Y, .05)), 1.0);
    N = N * 0.5 + 0.5;
    gl_FragColor = N;
}