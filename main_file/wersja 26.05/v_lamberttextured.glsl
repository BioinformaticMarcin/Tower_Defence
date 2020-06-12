#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 lp;//zrodlo swiatla 1
uniform vec4 lp2;//zrodlo swiatla 2


uniform vec4 wspolczynnikswiatla;

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 texCoord; //wspó³rzêdne teksturowania
//layout (location=3) in vec4 color; //wspó³rzêdne teksturowania


//Zmienne interpolowane
out vec2 i_tc;
out float i_nl;

void main(void) {
    gl_Position=P*V*M*vertex;

	vec4 l1=normalize(V*lp - V*M*vertex);
	vec4 l2=normalize(V*lp2 - V*M*vertex);
	l1=l1*wspolczynnikswiatla;
	vec4 lo=l1+l2;
    mat4 G=mat4(inverse(transpose(mat3(M))));

	
   vec4 n=normalize(V*G*normal);

   i_nl=clamp(dot(n,lo),0,1);
    i_tc=texCoord;
}
