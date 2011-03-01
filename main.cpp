#include <iostream>
#include "Application.h"
#include "MyScene.h"

int main(int argc, char *argv[]) {
	Application *app = Application::instance();
	
	app->setup(&argc, argv, "Projet OpenGL", new MyScene());
		
	return app->exec();
}