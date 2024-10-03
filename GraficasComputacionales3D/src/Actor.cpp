#include "Actor.h"

Actor::Actor(std::string actorName){
	//setup actor name
	m_name = actorName;
	//setup shape
	EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
	addComponent(shape);

	//setup trasnform

	//setup sprite
}
void 
Actor::update(float deltaTime)
{
}

void 
Actor::render(Window& window) {
    for (size_t i = 0; i < components.size(); i++) {
        window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
    }
}


void 
Actor::destroy()
{
}