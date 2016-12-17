uniform sampler2DRect texture;
uniform vec2 mouse;
uniform float pressure;
uniform float size;

void main()
{
    vec2 pos = gl_TexCoord[0].xy;
    
    vec2 delta = (mouse - pos);
    float angle = atan(delta.y, delta.x);
    
    float cm = 1.0 / (sqrt(dot(delta, delta)) + 10.0);
    
    
//    float scale = .4;
    float red   = pressure * cm * delta.x * size;
    float green = pressure * cm * delta.y * size;
    
    vec3 mcolor = vec3(red + 0.5, green + 0.5, 0.0);
    vec4 color = vec4(mcolor, 1.0);
    float alpha = cm;
    gl_FragColor = mix(texture2DRect(texture, pos), color, cm);
}