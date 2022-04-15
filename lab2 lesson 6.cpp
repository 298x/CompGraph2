
// Урок 6 - перемещение

#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
using namespace glm;

// Указатель VBO на буфер вершин
GLuint VBO;
float Scale = 0.0;

void RenderScene() {
	// Очистка буфера кадра
	glClear(GL_COLOR_BUFFER_BIT);

	// Сдвиг
	Scale += 0.1;

	// Матрица перемещения
	// Cинус для периода
	mat4x4 World;
	World[0][0] = 1.0; World[0][1] = 0.0; World[0][2] = 0.0; World[0][3] = sinf(Scale);
	World[1][0] = 0.0; World[1][1] = 1.0; World[1][2] = 0.0; World[1][3] = 0.0;
	World[2][0] = 0.0; World[2][1] = 0.0; World[2][2] = 1.0; World[2][3] = 0.0;
	World[3][0] = 0.0; World[3][1] = 0.0; World[3][2] = 0.0; World[3][3] = 1.0;

	// Описание треугольника и его перемещение
	vec3 Vertices[3];
	Vertices[0] = vec4(vec3(-0.5, -0.5, 0.0), 1.0) * World;
	Vertices[1] = vec4(vec3( 0.5, -0.5, 0.0), 1.0) * World;
	Vertices[2] = vec4(vec3( 0.0,  0.5, 0.0), 1.0) * World;

	// Генерация объектов
	glGenBuffers(1, &VBO);

	// Цель использованиея буферов - хранит массив вершин
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Наполнение объекта нужными данными
	// GL_STATIC_DRAW - флаг, обозначающий исп. паттернов для этих данных
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// Координаты вершин, исп. в буфере, рассм. как атрибут вершины с индексом 0
	glEnableVertexAttribArray(0);

	// Обратно привязываем наш буфер, приготавливая его для отрисовки
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Говорим конвейеру, как воспринимать данные внутри буфера
	// 0-индекс атрибута, 3-кол-во компонентов, GL_FLOAT-тип данных компонентов
	// GL_FALSE - не нормализовать атрибуты, 0-число байтов м-у 2 экз. атрибута
	// 0-смещение в структуре, которую получит конвейер
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Вызываем функцию отрисовки треугольника
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Отключение атрибутов вершины
	glDisableVertexAttribArray(0);

	// Смена буфера фона на буфер кадра
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// Инициализация GLUT
	glutInit(&argc, argv);

	// Включение двойной буферизации и буфера цвета
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// Размер окна
	glutInitWindowSize(700, 700);

	// Положение окна
	glutInitWindowPosition(400, 50);

	// Создание окна 
	glutCreateWindow("Window");

	// Общение с оконной системой
	// Вызов функции отображения на экран
	glutDisplayFunc(RenderScene);
	
	// Установка глобального обратного вызова, 
	// даём GLUT возможность выполнения непрерывной анимации
	glutIdleFunc(RenderScene);

	// Установка цвета, которой будет использоваться
	// во время очистки буфера кадра
	glClearColor(0.4f, 0.0f, 0.0f, 0.0f);

	// Инициализация glew и проверка на ошибки
	GLenum res = glewInit();
	if (res != GLEW_OK)
		fprintf(stderr, "Error : '%s'\n", glewGetErrorString(res)); 

	// Передача контроля GLUT'у
	glutMainLoop();

	return 0;
}