#include <text_circle.h>
#include <SFML/Graphics.hpp>

namespace sf
{
	TextCircle::TextCircle() {
		// default constructor
	}

	TextCircle::TextCircle(float x, float y, const Font& font_ref, const std::string& text) {
		mText.setFont(font_ref);
		mText.setString(text);
		mText.setCharacterSize(24);
		mText.setFillColor(Color::Black);

		mTextRect = mText.getLocalBounds();
		mText.setOrigin(mTextRect.left + mTextRect.width / 2.0f, mTextRect.top + mTextRect.height / 2.0f);
		mText.setPosition(Vector2f(x, y));

		float radius = std::sqrt(std::pow(mTextRect.width / 2.0f, 2) + std::pow(mTextRect.height / 2.0f, 2));
		mCircle.setRadius(radius);
		mCircle.setOrigin(radius, radius);
		mCircle.setPosition(x, y);
	}

	void TextCircle::setPosition(const Vector2f& position) {
		mCircle.setPosition(position);
		mText.setPosition(position);
	}

	Vector2f TextCircle::getPosition() const {
		return mCircle.getPosition();
	}

	bool TextCircle::isInside(const Vector2f& point) const {
		Vector2f center = mCircle.getPosition();
		float distance = std::sqrt(std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2));
		return distance <= mCircle.getRadius();
	}

	void TextCircle::draw(RenderTarget& target, RenderStates states) const {
		target.draw(mCircle, states);
		target.draw(mText, states);
	}
}