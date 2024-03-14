#include <text_circle.h>
#include <SFML/Graphics.hpp>

namespace sf
{
	TextCircle::TextCircle(const std::string& text, const Font& font, float radius) {
		mText.setFont(font);
		mText.setString(text);
		mText.setCharacterSize(24);

		mTextRect = mText.getLocalBounds();
		mText.setOrigin(mTextRect.left + mTextRect.width / 2.0f, mTextRect.top + mTextRect.height / 2.0f);

		mCircle.setRadius(radius);
		mCircle.setOrigin(radius, radius);
	}
}