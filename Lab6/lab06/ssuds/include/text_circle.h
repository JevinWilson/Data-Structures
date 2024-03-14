#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
	class TextCircle : public Drawable
	{
	protected:
		Text mText;
		CircleShape mCircle;
		FloatRect mTextRect;

	public:
		TextCircle(const std::string& text, const Font& font, float radius);
		void setPosition(const Vector2f& position);
		Vector2f getPosition() const;
		bool isInside(const Vector2f& point) const;
		virtual void draw(RenderTarget& target, RenderStates states) const override;
	};
}