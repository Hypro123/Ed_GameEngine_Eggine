#version 410

in vec2 vTexCoord; //takes in texture coordinates
in vec3 vNormal; //takes in normal
in vec3 vTangent; //takes in tangent
in vec3 vBiTangent; //takes in bitangent
in vec4 vPosition; //takes in posiiton

//output is fragment colour
out vec4 FragColour;

uniform sampler2D diffuseTexture; //diffuse texture of the mesh
uniform sampler2D specularTexture; //specular texture of mesh
uniform sampler2D normalTexture; //normal texture of mesh

uniform vec3 Ka; // material ambient
uniform vec3 Kd; // material diffuse
uniform vec3 Ks; // material specular
uniform float specularPower;

uniform vec3 Ia; // light ambient
uniform vec3 Id; // light diffuse
uniform vec3 Is; // light specular
uniform vec3 lightDirection; //direciton of the light

//takes in camera position
uniform vec3 cameraPosition;

void main() {
	//normal normalised
	vec3 N = normalize(vNormal);
	//tangent normalised
	vec3 T = normalize(vTangent);
	//BiTangent normalised
	vec3 B = normalize(vBiTangent);
	//light direction 
	vec3 L = normalize(lightDirection);
	//TBN assign tot a matrix
	mat3 TBN = mat3(T, B, N);
	//texture diffuse
	vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
	//texture specular
	vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;
	//texture normal
	vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

	//normal recaculated
	N = TBN * (texNormal * 2 - 1);

	// calculate lambert term
	float lambertTerm = max( 0, dot( N, -L ) );
	
	// calculate view vector and reflection vector
	//camera viewing position calculation
	vec3 V = normalize(cameraPosition - vPosition.xyz);
	//reflection calculation
	vec3 R = reflect( L, N );
	
	// calculate specular term
	float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );
	
	// calculate each light property
	//ambience calculation
	vec3 ambient = Ia * Ka;
	//diffuse calculation
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	//specular calculation
	vec3 specular = Is * Ks * texSpecular * specularTerm;
	//fragment colour calculation
	FragColour = vec4(ambient + diffuse + specular, 1);
}