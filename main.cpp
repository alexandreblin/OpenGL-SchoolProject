#include <iostream>
#include "Application.h"
#include "Scene.h"

int main(int argc, char *argv[]) {
	Application *app = Application::instance();
	
	app->setup(&argc, argv, "Projet OpenGL", new Scene());
		
	return app->exec();
}