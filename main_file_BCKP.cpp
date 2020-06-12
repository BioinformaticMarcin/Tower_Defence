/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define _CRT_SECURE_NO_DEPRECATE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "iostream"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <objloader.hpp>
#include <vboindexer.hpp>
#include <array>
#include <time.h>
#include <hero.h>
   


#define GLT_IMPLEMENTATION
#include "gltext.h"

using namespace std;



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float WindowX = 1920;
float WindowY = 1080;
float fov = 30.0f;
const float cameraSpeed = 0.1f;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.



std::vector<unsigned short> indices;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::vec2> indexed_uvs;
std::vector<glm::vec3> indexed_normals;

std::vector<float> wektor_indexed_vertices;
vector<int>Tablicelicznik1;
 int tablicalicznik1=0;

vector<int>Tablicelicznik;
int licznik=0;

std::vector<glm::vec2> FONTvertices;
std::vector<glm::vec2> FONTUVs;


vector<vector<float>>TabliceWektorowX;
vector<vector<float>>TabliceUvX;
vector<vector<float>>TabliceNormalX;
vector<vector<float>>TabliceKolorowX;



const float radius = 10.0f;
float obrot = 0.1f;
float camX = 0.0f;
float camZ = 3.0f;
glm::vec3 cameraPos = glm::vec3(camX, 0.0f, camZ);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLuint tex; //Uchwyt – deklaracja globalna


float jazda = 1.0f;
float jazda2 = 1.0f;
float jazda3 = 1.0f;
float jazda4 = 1.0f;

int wlacz_koordynaty = 1;

//Funkcja wczytująca teksturę 
float heroSpeed = 0.03f;
Hero dzban(heroSpeed);



GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	cout << "ERROR:" << error << "\n";
	//cout << "znacznik" << "\n";
	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}



float speed = PI; //[radiany/s]
//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}

void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {

	
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_A) 
		{
			
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (key == GLFW_KEY_D) {

			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (key == GLFW_KEY_S) {
			cameraPos -= cameraSpeed * cameraUp;
		}
		if (key == GLFW_KEY_W) {
			cameraPos += cameraSpeed * cameraUp;
		}
		if (key == GLFW_KEY_EQUAL) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda++;
		}
		if (key == GLFW_KEY_MINUS) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda--;
		}
		if (key == GLFW_KEY_0) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda2++;
		}
		if (key == GLFW_KEY_9) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda2--;
		}
		if (key == GLFW_KEY_8) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda3++;
		}
		if (key == GLFW_KEY_7) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda3--;
		}
		
		if (key == GLFW_KEY_6) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda4 -= 0.1f;
		}
		if (key == GLFW_KEY_5) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda4 += 0.1f;
		}
		if (key == GLFW_KEY_Q) {
			//cameraPos += cameraSpeed * cameraFront;
			wlacz_koordynaty++;
			system("CLS");
		}
		if (key == GLFW_KEY_ESCAPE)
		{
			exit(EXIT_SUCCESS);
		}
	}
	if (action == GLFW_REPEAT) {
		if (key == GLFW_KEY_A)
		{
			
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (key == GLFW_KEY_D) {
			
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (key == GLFW_KEY_S) {
			cameraPos -= cameraSpeed * cameraUp;
		}
		if (key == GLFW_KEY_W) {
			cameraPos += cameraSpeed * cameraUp;
		}
		if (key == GLFW_KEY_EQUAL) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda++;
		}
		if (key == GLFW_KEY_MINUS) {
			//cameraPos -= cameraSpeed * cameraFront;
			jazda--;
		}
		if (key == GLFW_KEY_0) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda2++;
		}
		if (key == GLFW_KEY_9) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda2--;
		}
		if (key == GLFW_KEY_8) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda3++;
		}
		if (key == GLFW_KEY_7) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda3--;
		}
		if (key == GLFW_KEY_6) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda4 -= 0.1f;
		}
		if (key == GLFW_KEY_5) {
			//cameraPos += cameraSpeed * cameraFront;
			jazda4 += 0.1f;
		}
		
	}

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W) printf("puszczone W\n");
		if (key == GLFW_KEY_A) printf("puszczone A\n");
		if (key == GLFW_KEY_D) printf("puszczone D\n");
		if (key == GLFW_KEY_S) printf("puszczone S\n");
	}
}

void rysujobiekt(int numerobiektu)
{
	//spTextured->use();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, &TabliceWektorowX[numerobiektu][0]);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, &TabliceNormalX[numerobiektu][0]);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, &TabliceUvX[numerobiektu][0]);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, &TabliceKolorowX[numerobiektu][0]);
	
	glDrawArrays(GL_TRIANGLES, 0, Tablicelicznik1[numerobiektu]);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glClearColor(0.1, 0.1, 0.1, 0);

}
//Procedura rysująca zawartość sceny

void wyswietlpolozenie()
{
	system("CLS");
	cout << "X:" << jazda << "\n";
	cout << "Y:" << jazda2 << "\n";
	cout << "Z:" << jazda3 << "\n";
	cout << "Wspolczynnik swiatla:" << jazda4 << "\n";
}
int klatkaz = 0;
int ogien = 0;
void animacja_ogniska(int migotanie)
{

	if (migotanie % 12 == 0)
	{
		ogien = rand() % 10 + 1;
	}
	if (jazda4 < ogien)
	{
		jazda4 += 0.2;
	}
	if (jazda4 > ogien)
	{
		jazda4 -= 0.2;
	}
}

void drawScene(GLFWwindow* window, float angle, int numerobiektu) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyszczenie bufora kolorów i bufora głębokości
	glEnable(GL_DEPTH_TEST);
	glm::mat4 P = glm::perspective(glm::radians(fov), WindowX / WindowY, 0.1f, 100.0f);  //Wyliczenie macierzy rzutowania
	glm::mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); //Wyliczenie macierzy widoku
	
	glm::mat4 M = glm::mat4(1.0f); //Macierz swiata RTS 
	

	spLambertTextured->use();//Aktywacja programu cieniującego
	
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V));
	
	//Mt = glm::rotate(Mt, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//Mt = glm::scale(Mt, glm::vec3(0.5f, 0.5f, 0.5f));
	//glUniform4f(spLambertTextured->u("color"), 1, 0.5, 0.5, 1);
	glm::mat4 Mt = glm::mat4(1.0f);
	glm::mat4 kostka = glm::mat4(1.0f);
	Mt = glm::scale(M, glm::vec3(0.1f, 0.1f, 0.1f));
	kostka = Mt;
	glm::mat4 Mp = M;
	//glUniformMatrix4fv(spLambertTextured->u("Mt"), 1, false, glm::value_ptr(Mt));
	glUniform4f(spLambertTextured->u("lp"), 0, 0, -40, 1);
	//glUniform4f(spLambertTextured->u("lp"), jazda, jazda2, jazda3, 0);//zdrodlo swiatla 1

	

	animacja_ogniska(klatkaz);
	
	glUniform4f(spLambertTextured->u("wspolczynnikswiatla"), jazda4, jazda4, jazda4, jazda4);//zdrodlo swiatla 1
	//glUniform4f(spLambertTextured->u("lp2"), 0, 0,-6, 1);//zdrodlo swiatla 2
	
	for (int x = 0; x < numerobiektu + 1; x++)
	{

		glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M));
		if (x == 1)
		{


			glm::mat4 Mdzbana = dzban.calculate(M);

			//Mdzbana =glm::scale(M, glm::vec3(0.1f, 0.1f, 0.1f));
			glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(Mdzbana));

			Mt = kostka;
			M = glm::mat4(1.0f);
		}
		if (x == 2)
		{

			Mt = glm::translate(Mt, glm::vec3((float)49, 6, -63));//X Y Z lewy dolny rog
			M = Mt;
			glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M));
			Mt = kostka;
			M = glm::mat4(1.0f);
		}
		if (x == 3)
		{

			Mt = glm::translate(Mt, glm::vec3((float)-14, 6, -127));//X Y Z prawy gorny rog
			M = Mt;
			glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M));
			Mt = kostka;
			M = glm::mat4(1.0f);
		}
		if (x == 4)
		{

			Mt = glm::translate(Mt, glm::vec3((float)49, 6, -127));//X Y Z prawy dolny rog
			M = Mt;
			glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M));
			Mt = kostka;
			M = glm::mat4(1.0f);
		}


		rysujobiekt(x);
	}
	if (wlacz_koordynaty % 2 == 0)
	{
		wyswietlpolozenie();
	}
		



		klatkaz;


	glfwSwapBuffers(window);

}


float lastX = WindowX/2, lastY = WindowY/2;
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}
void przybliz()
{
	cameraPos += cameraSpeed*10 * cameraFront;
}
void oddal()
{
	cameraPos -= cameraSpeed*10 * cameraFront;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset > 0)
	{
		przybliz();
		//jazda--;
	}
	else
	{
		oddal();
		//jazda++;
	}
	
	
		
		
}

void wektorowanie()
{	
	//wierzcholki
	for (int i = 0; i < vertices.size(); i++)
	{
		licznik++;
		wektor_indexed_vertices.push_back(vertices[i].x);
		wektor_indexed_vertices.push_back(vertices[i].y);
		wektor_indexed_vertices.push_back(vertices[i].z);
		wektor_indexed_vertices.push_back(1.0);
		tablicalicznik1++;
		tablicalicznik1++;
		tablicalicznik1++;
		tablicalicznik1++;

	}
	TabliceWektorowX.push_back(wektor_indexed_vertices);
	cout << "PRZEPISANIE NA WIERZCHOLKI\n";
	//Uv
	int licznik2 = 0;
	vector<float>wektor_uvs;
	for (int i = 0; i < uvs.size(); i++)
	{
		licznik2++;
		licznik2++;
		wektor_uvs.push_back(uvs[i].x);
		wektor_uvs.push_back(uvs[i].y);


	}
	TabliceUvX.push_back(wektor_uvs);
	cout << "PRZEPISANIE NA UV\n";
	//normal
	int licznik3 = 0;
	vector<float>wektor_normals;
	for (int i = 0; i < normals.size(); i++)
	{
		licznik3++;
		wektor_normals.push_back(normals[i].x);
		wektor_normals.push_back(normals[i].y);
		wektor_normals.push_back(normals[i].z);
		wektor_normals.push_back(0.0);



	}
	TabliceNormalX.push_back(wektor_normals);
	cout << "PRZEPISANIE NA NORMALE\n";
	//kolory
	vector<float>kolory;
	for (int a = 0; a < wektor_indexed_vertices.size(); a+=4)
	{
		kolory.push_back(1.0);

		kolory.push_back(0.0);
		kolory.push_back(0.0);
		kolory.push_back(1.0);
		
	}
	TabliceKolorowX.push_back(kolory);
	cout << "PRZEPISANIE NA KOLORY\n";

	//czyszczenie

	Tablicelicznik1.push_back(vertices.size());
	tablicalicznik1 = 0;

	Tablicelicznik.push_back(licznik);
	licznik = 0;


	vertices.clear();
	uvs.clear();
	normals.clear();

	//vertexbuffer.clear();
	//uvbuffer.clear();
	//normalbuffer.clear();
	//elementbuffer.clear();

	indices.clear();
	indexed_vertices.clear();
	indexed_uvs.clear();
	indexed_normals.clear();

	wektor_indexed_vertices.clear();
	wektor_uvs.clear();
	wektor_normals.clear();
	kolory.clear();
	cout << "UKONCZONO\n";
}
void przygotuj_obiektVer2(const char* path, int numerobiektu)
{

	bool res = loadOBJ(path, vertices, uvs, normals);
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
	tex = readTexture("bricks.png");
	wektorowanie();
	


}


int main(void)
{
	
	srand(time(NULL));
	
	



	

	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno
	
	
	

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(WindowX, WindowY, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla

	float angle = 0;
	glfwSetTime(0);
	

	int numerobiektu = 0;

	przygotuj_obiektVer2("model//pokojzestolikiemrazy4.obj", numerobiektu);
	
	numerobiektu++;
	przygotuj_obiektVer2("model//kostka.obj", numerobiektu);
	numerobiektu++;
	przygotuj_obiektVer2("model//kostka.obj", numerobiektu);
	numerobiektu++;
	przygotuj_obiektVer2("model//kostka.obj", numerobiektu);
	numerobiektu++;
	przygotuj_obiektVer2("model//kostka.obj", numerobiektu);

		


	
	
	while (!glfwWindowShouldClose(window)) {
		
		

			angle += speed * glfwGetTime();

			glfwSetScrollCallback(window, scroll_callback);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(window, mouse_callback);
			
			glfwSetTime(0);

			glfwSetKeyCallback(window, key_callback);
			drawScene(window, angle, numerobiektu);//liczba obiektow
			glfwPollEvents();
		
	}
	//Usunięcie tekstury z pamięci karty graficznej – w freeOpenGLProgram
	glDeleteTextures(1, &tex);
	freeOpenGLProgram(window);

	

	


	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
