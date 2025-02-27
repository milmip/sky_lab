#ifndef TERMINI
#define TERMINI

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Termini
{
public:
	Termini() = default;
	~Termini() = default;

	void Init(unsigned int SHADER);
	void Draw();

private:
	unsigned int shader;
	glm::mat4 projMat = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	
};
#endif