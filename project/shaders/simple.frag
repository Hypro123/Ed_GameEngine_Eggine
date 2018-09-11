#version 410

//tsakes in position
in vec4 vPosition;
//takes in normal 
in vec3 vNormal;

//fragment colour is the output
out vec4 FragColor;

uniform sampler2D diffuseTexture; //sampled colour

uniform vec3 Ia; //ambient light

//main light
uniform vec3 Id; //diffuse
uniform vec3 Is; //specular
uniform vec3 lightDirection; //direction

uniform vec3 Ka; //ambient material colour
uniform vec3 Kd; //diffuse material colour
uniform vec3 Ks; //speculat material Colour
uniform float specularPower; //Material specular power

uniform vec3 cameraPosition;

void main()
{
	//normal is normalsed for calcualtions
	vec3 N = normalize(vNormal);
	//lightdirection is normalised for calculation
	vec3 L = normalize(lightDirection);

	//calculate lambert term
	float lambertTerm = max(0, min(1, dot(N, -L)));

	// calculate view vector and reflection vector
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	//reflection is calculated
	vec3 R = reflect( L, N );
	// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );

	//calculates ambient lighting
	vec3 ambient = Ia * Ka;
	//calculates the diffuse
	vec3 diffuse = Id * Kd * lambertTerm;
	//calculates specular
	vec3 specular = Is * Ks * specularTerm;

	//output lambert as greyscale
	FragColor = vec4(ambient + diffuse + specular, 1);
}