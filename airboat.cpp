#include "airboat.h"



namespace Models {

	Airboat airboat;

	Airboat::Airboat() {
		vertices = AirboatInternal::vertices;
		normals = AirboatInternal::normals;
		vertexNormals = AirboatInternal::vertexNormals;
		texCoords = AirboatInternal::texCoords;
		colors = AirboatInternal::colors;
		vertexCount = AirboatInternal::vertexCount;
	}

	Airboat::~Airboat() {
	}

	void Airboat::drawSolid(bool smooth) {
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//glEnableVertexAttribArray(3);


		glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, vertices);
		if (!smooth) glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, normals);
		else glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, vertexNormals);
		glVertexAttribPointer(2, 4, GL_FLOAT, false, 0, texCoords);
		//glVertexAttribPointer(3,4,GL_FLOAT,false,0,Models::CubeInternal::colors);

		glDrawArrays(GL_TRIANGLES, 0, vertexCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		//glDisableVertexAttribArray(3);
	}


	namespace AirboatInternal {

		unsigned int vertexCount = 8;

		float vertices[] = {
1.000000f,-1.000000f,-1.000000f,
1.000000f,-1.000000f,1.000000f,
-1.000000f,-1.000000f,1.000000f,
-1.000000f,-1.000000f,-1.000000f,
1.000000f,1.000000f,-0.999999f,
0.999999f,1.000000f,1.000001f,
-1.000000f,1.000000f,1.000000f,
-1.000000f,1.000000f,-1.000000f,
		};
		float texCoords[] = {
		1.000000f,0.333333f,
		1.000000f,0.666667f,
		0.666667f,0.666667f,
		0.666667f,0.333333f,
		0.666667f,0.000000f,
		0.000000f,0.333333f,
		0.000000f,0.000000f,
		0.333333f,0.000000f,
		0.333333f,1.000000f,
		0.000000f,1.000000f,
		0.000000f,0.666667f,
		0.333333f,0.333333f,
		0.333333f,0.666667f,
		1.000000f,0.000000f,
		};
		float vertexNormals[] = {
		0.000000f,-1.000000f,0.000000f,
		0.000000f,1.000000f,0.000000f,
		1.000000f,0.000000f,0.000000f,
		-0.000000f,0.000000f,1.000000f,
		-1.000000f,-0.000000f,-0.000000f,
		0.000000f,0.000000f,-1.000000f,
		};
		float normals[] = {
		0.000000f,-1.000000f,0.000000f,
		0.000000f,1.000000f,0.000000f,
		1.000000f,0.000000f,0.000000f,
		-0.000000f,0.000000f,1.000000f,
		-1.000000f,-0.000000f,-0.000000f,
		0.000000f,0.000000f,-1.000000f,
		};


		float colors[] = {
			0.7f,1.0f,0.4f,1.0f,
			0.7f,1.0f,0.4f,1.0f,
			0.7f,1.0f,0.4f,1.0f,
			0.7f,1.0f,0.4f,1.0f,
			0.7f,1.0f,0.4f,1.0f,
			0.7f,1.0f,0.4f,1.0f,
			0.7f,1.0f,0.4f,1.0f,
			0.7f,1.0f,0.4f,1.0f,
			
		};
	}
}
