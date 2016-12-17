uniform float time;
uniform sampler2DRect texture;
uniform sampler2DRect flowMap;
uniform float flowSpeed;
uniform float cycleTime;
uniform int type;

uniform vec2 imageSize;
uniform vec2 mapSize;

void main()
{
    vec2 iUV = gl_TexCoord[0].xy;
    vec2 mUV = iUV *  mapSize / imageSize;
    vec2 flowDirection = (texture2DRect( flowMap, mUV).rg - 0.5) * 2.0;
    float t1 = time / cycleTime;
    float t2 = t1 + 0.5;
    float cycleTime1 = t1 - floor(t1);
    float cycleTime2 = t2 - floor(t2);
    vec2 flowDirection1 = flowDirection * cycleTime1 * flowSpeed;
    vec2 flowDirection2 = flowDirection * cycleTime2 * flowSpeed;
    vec2 uv1 = iUV + flowDirection1;
    vec2 uv2 = iUV + flowDirection2;
    vec4 color1 = texture2DRect( texture, uv1 );
    vec4 color2 = texture2DRect( texture, uv2 );
    gl_FragColor = mix(color1, color2, abs(cycleTime1-0.5) * 2.0);
    if (type == 1) gl_FragColor = texture2DRect(flowMap, mUV);
    if (type == 2) gl_FragColor = texture2DRect(texture, iUV);
     
    
}
