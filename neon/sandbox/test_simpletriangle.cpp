#include <iostream>
#include "test_simpletriangle.h"
#include "renderer\renderer.h"
#include <vector>
#include "interface\neon_interface.h"
#include "renderer\shader.h"
#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Mesh = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Mesh;
}

bool TestSimpleTriangle::Init()
{


	return true;
}

bool TestSimpleTriangle::Update()
{
	return true;
}

void TestSimpleTriangle::Test1SingleTriangleDrawArrayNoShader()
{
	static bool init = false;
	if (!init)
	{
		GLuint bufferId = 0;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);

		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			+0.0f, +1.0f, z_value,
			+1.0f, -1.0f, z_value,
			-1.0f, -1.0f, z_value,
		};
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void TestSimpleTriangle::Test2SingleTriangleDrawArray()
{
	static bool init = false;
	if (!init)
	{
		Renderer* renderer = Renderer::get();
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexColor", VERT_COLOR_LOC },
		};
		Shader *shader = new Shader("resources/shaders/v140/base.vert", "resources/shaders/v140/base.frag", infos);
		shader->Set();

		GLuint bufferId = 0;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);

		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			+0.0f, +1.0f, z_value,
			+1.0f, +0.0f, +0.0,
			+1.0f, -1.0f, z_value,
			+0.0f, +0.0f, +1.0,
			-1.0f, -1.0f, z_value,
			+0.0f, +1.0f, +0.0,
		};
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(VERT_POS_LOC);
		glVertexAttribPointer(VERT_POS_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(VERT_COLOR_LOC);
		glVertexAttribPointer(VERT_COLOR_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void TestSimpleTriangle::Test3TwoTriangleDrawArray()
{
	static bool init = false;
	if (!init)
	{
		Renderer* renderer = Renderer::get();
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexColor", VERT_COLOR_LOC },
		};
		Shader *shader = new Shader("resources/shaders/v140/base.vert", "resources/shaders/v140/base.frag", infos);
		shader->Set();

		GLuint bufferId = 0;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);

		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			+0.0f, +1.0f, z_value,
			+1.0f, +0.0f, +0.0,
			+1.0f, +0.0f, z_value,
			+0.0f, +0.0f, +1.0,
			-1.0f, +0.0f, z_value,
			+0.0f, +1.0f, +0.0,

			+0.0f, -1.0f, z_value,
			+1.0f, +0.0f, +0.0,
			+1.0f, +0.0f, z_value,
			+0.0f, +0.0f, +1.0,
			-1.0f, +0.0f, z_value,
			+0.0f, +1.0f, +0.0

		};
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(VERT_POS_LOC);
		glVertexAttribPointer(VERT_POS_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(VERT_COLOR_LOC);
		glVertexAttribPointer(VERT_COLOR_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void TestSimpleTriangle::Test4TwoTriangleDrawElements()
{
	static bool init = false;
	if (!init)
	{
		Renderer* renderer = Renderer::get();
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexColor", VERT_COLOR_LOC },
		};
		Shader *shader = new Shader("resources/shaders/v140/base.vert", "resources/shaders/v140/base.frag", infos);
		shader->Set();

		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			//0
			+0.0f, +1.0f, z_value,
			+1.0f, +0.0f, +0.0,
			//1
			+1.0f, +0.0f, z_value,
			+0.0f, +0.0f, +1.0,
			//2
			-1.0f, +0.0f, z_value,
			+0.0f, +1.0f, +0.0,
			//3
			+0.0f, -1.0f, z_value,
			+1.0f, +0.0f, +0.0,
		};
		std::vector<GLushort> indices = { 0,1,2, 3,1,2 };

		GLuint vertBufferId = 0;
		glGenBuffers(1, &vertBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, vertBufferId);
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERT_POS_LOC); //vertex position
		glVertexAttribPointer(VERT_POS_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(VERT_COLOR_LOC); //vertex color
		glVertexAttribPointer(VERT_COLOR_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		GLuint indexBufferId = 0;
		glGenBuffers(1, &indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void TestSimpleTriangle::Test4ChangeVertexDepth()
{
	static bool init = false;
	if (!init)
	{
#ifdef _MSC_VER
		int msgboxID = MessageBox(
			NULL,
			(LPCSTR)"Rendering 2 viewports, spliting screen in 2 halfs\nLeft viewport - Depth Enable\nRight viewport - Depth Disable",
			(LPCSTR)"Test4: check depth buffer",
			MB_ICONINFORMATION
		);
#endif
		Renderer* renderer = Renderer::get();
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexColor", VERT_COLOR_LOC },
		};
		Shader *shader = new Shader("resources/shaders/v140/base.vert", "resources/shaders/v140/base.frag", infos);
		shader->Set();


		GLfloat z_value1 = 1.0f;
		GLfloat z_value2 = 0.0f;
		//4			//0			//5

		//2						//1

		//6			//3			//7
		std::vector<GLfloat> vertexArray =
		{
			//0
			+0.0f, +1.0f, z_value2,
			+0.0f, +1.0f, +0.0,
			//1
			+1.0f, +0.0f, z_value1,
			+0.0f, +0.0f, +1.0,
			//2
			-1.0f, +0.0f, z_value1,
			+0.0f, +1.0f, +0.0,
			//3
			+0.0f, -1.0f, z_value2,
			+0.0f, +0.0f, +1.0,
			//4
			-1.0f, +1.0f, z_value1,
			+0.0f, +0.0f, +1.0,
			//5
			+1.0f, +1.0f, z_value1,
			+0.0f, +0.0f, +1.0,
			//6
			-1.0f, -1.0f, z_value1,
			+0.0f, +1.0f, +0.0,
			//7
			+1.0f, -1.0f, z_value1,
			+0.0f, +1.0f, +0.0,
		};
		std::vector<GLushort> indices = { 0,7,6, 3,4,5 };

		GLuint vertBufferId = 0;
		glGenBuffers(1, &vertBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, vertBufferId);
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERT_POS_LOC); //vertex position
		glVertexAttribPointer(VERT_POS_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(VERT_COLOR_LOC); //vertex color
		glVertexAttribPointer(VERT_COLOR_LOC, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		GLuint indexBufferId = 0;
		glGenBuffers(1, &indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);


		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, (GLsizei)(NeonInterface::get()->Width() / 2.0), (GLsizei)(NeonInterface::get()->Height()));
	glEnable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glViewport((GLsizei)(NeonInterface::get()->Width() / 2.0), 0, (GLsizei)(NeonInterface::get()->Width() / 2.0), (GLsizei)(NeonInterface::get()->Height()));
	glDisable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glViewport(0, 0, NeonInterface::get()->Width(), NeonInterface::get()->Height());


}

#include "renderer\model.h"
void TestSimpleTriangle::Test5Model()
{
	static bool init = false;
	static Mesh *model = 0;
	if (!init)
	{
		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			+0.0f, +1.0f, z_value,
			+1.0f, -1.0f, z_value,
			-1.0f, -1.0f, z_value,
		};

		model = new Mesh(vertexArray);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model->Render();

}

void TestSimpleTriangle::Test6ModelDrawElement()
{
	static bool init = false;
	static Mesh *model = 0;
	if (!init)
	{
		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			//0
			+0.0f, +1.0f, z_value,
			//1
			+1.0f, +0.0f, z_value,
			//2
			-1.0f, +0.0f, z_value,
			//3
			+0.0f, -1.0f, z_value,
		};
		std::vector<GLushort> indices = { 0,1,2, 3,1,2 };

		model = new Mesh(vertexArray, indices);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model->Render();
}

bool TestSimpleTriangle::Render()
{
	//Test1SingleTriangleDrawArrayNoShader();
	//Test2SingleTriangleDrawArray();
	//Test3TwoTriangleDrawArray();
	//Test4TwoTriangleDrawElements();
	//Test4ChangeVertexDepth();
	//Test5Model();
	//Test6ModelDrawElement();
	switch (testId)
	{
	case 0: Test1SingleTriangleDrawArrayNoShader();
		break;
	case 1: Test2SingleTriangleDrawArray();
		break;
	case 2: Test3TwoTriangleDrawArray();
		break;
	case 3: Test4TwoTriangleDrawElements();
		break;
	case 4: Test4ChangeVertexDepth();
		break;
	case 5: Test5Model();
		break;
	case 6: Test6ModelDrawElement();
		break;
	default: testId = 0;//not handled set to 0
		break;
	}

	return true;
}

void TestSimpleTriangle::HandleKeyInput(int key, int action)
{
	if (action == 1)
	{
		switch (key)
		{
		case 262: testId++;  //right arrow key
			break;
		case 263: testId--; // left arrow key
			break;
		}
	}
	//std::cout << "key " << key << " " << action << " " << std::endl;
}
