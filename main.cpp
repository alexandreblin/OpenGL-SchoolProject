#include <iostream>
#include "Application.h"

int main(int argc, char *argv[]) {
	Application *app = Application::instance();
	
	app->setup(&argc, argv, "Projet OpenGL");
		
	return app->exec();
}
