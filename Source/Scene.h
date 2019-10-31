#pragma once

class Scene {
public:
	Scene& getInstance();
	void draw();
private:
	Scene();
	static Scene* instance;
};