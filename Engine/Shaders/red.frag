#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float srd;
void main()
{
    if(srd > 0.0){
    	   FragColor = vec4(1.0,0.0,0.0,1.0);
    }else{
        FragColor = texture(ourTexture, TexCoord);
    
    }
}