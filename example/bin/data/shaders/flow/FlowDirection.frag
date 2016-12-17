uniform sampler2DRect texture;
uniform sampler2DRect flowMap;

void main() {
    vec2 pos = gl_TexCoord[0].xy;
    vec2 flowDirection = (texture2DRect( flowMap, pos ).rg - 0.5) * 2.0;
    vec2 uv = pos + flowDirection;
    gl_FragColor = texture2DRect( texture, uv );
}