uniform float time;
uniform sampler2DRect texture;
uniform sampler2DRect flowMap;
uniform float cycleTime;

void main()
{
    vec2 pos = gl_TexCoord[0].st;
    float timeScaled = time / cycleTime;
    float timeCycle = timeScaled - floor(timeScaled);
    vec2 flowDirection = (texture2DRect( flowMap, pos ).rg - 0.5) * 2.0;    
    vec2 uv = pos + flowDirection * timeCycle;
    gl_FragColor = texture2DRect( texture, uv );
}
