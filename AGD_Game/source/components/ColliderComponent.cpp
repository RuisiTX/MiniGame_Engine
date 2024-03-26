#include "../../include/components/ColliderComponent.h"

void BoxColliderComponent::init(const Vector2f& sz)
{
	size = sz;
}

void BoxColliderComponent::update(const Entity& entity)
{
	boundingBox.setTopLeft(entity.getPosition());
	boundingBox.setBottomRight(entity.getPosition() + size);
}

void BoxColliderComponent::draw(Window* window)
{
	window->draw(boundingBox.getDrawableRect());
}

bool BoxColliderComponent::interesects(BoxColliderComponent* cc)
{
	return false;
}

void BoxColliderComponent::setBoundingBox(const Vector2f& topLeft, const Vector2f& bottomRight)
{
	boundingBox.setTopLeft(topLeft);
	boundingBox.setBottomRight(bottomRight);
}
