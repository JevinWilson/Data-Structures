#include <graph_creator.h>

// Note: THIS is where the static attributes actually reside
ssuds::UnorderedMap<sf::Keyboard::Key, std::string> misc::GraphCreator::mKeycodeToName;
ssuds::UnorderedMap<sf::Keyboard::Key, std::string> misc::GraphCreator::mKeycodeToNameShifted;
ssuds::UnorderedMap<sf::Keyboard::Key, sf::Color> misc::GraphCreator::mFColors;


misc::GraphCreator::GraphCreator(const sf::Font& circle_font, const sf::Font& status_font) : mCurrentState(State::NONE),
mNextCircleId(0), mCircleFont(circle_font), mStatusFont(status_font)
{
	mPendingCircle = sf::TextCircle(0.0f, 0.0f, mCircleFont, "???");

	mStatusText.setFont(mStatusFont);
	mStatusText.setCharacterSize(20);
	mStatusText.setFillColor(sf::Color::White);
	mStatusText.setPosition(sf::Vector2f(0, 0));
	change_state(State::WAITING);
}

void misc::GraphCreator::create_keycode_to_name_dbase()
{
	// I was kind of surprised that SFML didn't have something like this (that I could
	// find).  And FYI: I didn't type all of these -- I wrote a python script
	// to generate all of them for me:-P
	mKeycodeToName[sf::Keyboard::A] = "a";		mKeycodeToNameShifted[sf::Keyboard::A] = "A";
	mKeycodeToName[sf::Keyboard::B] = "b";		mKeycodeToNameShifted[sf::Keyboard::B] = "B";
	mKeycodeToName[sf::Keyboard::C] = "c";		mKeycodeToNameShifted[sf::Keyboard::C] = "C";
	mKeycodeToName[sf::Keyboard::D] = "d";		mKeycodeToNameShifted[sf::Keyboard::D] = "D";
	mKeycodeToName[sf::Keyboard::E] = "e";		mKeycodeToNameShifted[sf::Keyboard::E] = "E";
	mKeycodeToName[sf::Keyboard::F] = "f";		mKeycodeToNameShifted[sf::Keyboard::F] = "F";
	mKeycodeToName[sf::Keyboard::G] = "g";		mKeycodeToNameShifted[sf::Keyboard::G] = "G";
	mKeycodeToName[sf::Keyboard::H] = "h";		mKeycodeToNameShifted[sf::Keyboard::H] = "H";
	mKeycodeToName[sf::Keyboard::I] = "i";		mKeycodeToNameShifted[sf::Keyboard::I] = "I";
	mKeycodeToName[sf::Keyboard::J] = "j";		mKeycodeToNameShifted[sf::Keyboard::J] = "J";
	mKeycodeToName[sf::Keyboard::K] = "k";		mKeycodeToNameShifted[sf::Keyboard::K] = "K";
	mKeycodeToName[sf::Keyboard::L] = "l";		mKeycodeToNameShifted[sf::Keyboard::L] = "L";
	mKeycodeToName[sf::Keyboard::M] = "m";		mKeycodeToNameShifted[sf::Keyboard::M] = "M";
	mKeycodeToName[sf::Keyboard::N] = "n";		mKeycodeToNameShifted[sf::Keyboard::N] = "N";
	mKeycodeToName[sf::Keyboard::O] = "o";		mKeycodeToNameShifted[sf::Keyboard::O] = "O";
	mKeycodeToName[sf::Keyboard::P] = "p";		mKeycodeToNameShifted[sf::Keyboard::P] = "P";
	mKeycodeToName[sf::Keyboard::Q] = "q";		mKeycodeToNameShifted[sf::Keyboard::Q] = "Q";
	mKeycodeToName[sf::Keyboard::R] = "r";		mKeycodeToNameShifted[sf::Keyboard::R] = "R";
	mKeycodeToName[sf::Keyboard::S] = "s";		mKeycodeToNameShifted[sf::Keyboard::S] = "S";
	mKeycodeToName[sf::Keyboard::T] = "t";		mKeycodeToNameShifted[sf::Keyboard::T] = "T";
	mKeycodeToName[sf::Keyboard::U] = "u";		mKeycodeToNameShifted[sf::Keyboard::U] = "U";
	mKeycodeToName[sf::Keyboard::V] = "v";		mKeycodeToNameShifted[sf::Keyboard::V] = "V";
	mKeycodeToName[sf::Keyboard::W] = "w";		mKeycodeToNameShifted[sf::Keyboard::W] = "W";
	mKeycodeToName[sf::Keyboard::X] = "x";		mKeycodeToNameShifted[sf::Keyboard::X] = "X";
	mKeycodeToName[sf::Keyboard::Y] = "y";		mKeycodeToNameShifted[sf::Keyboard::Y] = "Y";
	mKeycodeToName[sf::Keyboard::Z] = "z";		mKeycodeToNameShifted[sf::Keyboard::Z] = "Z";
	mKeycodeToName[sf::Keyboard::Num0] = "0";	mKeycodeToNameShifted[sf::Keyboard::Num0] = ")";
	mKeycodeToName[sf::Keyboard::Num1] = "1";	mKeycodeToNameShifted[sf::Keyboard::Num1] = "!";
	mKeycodeToName[sf::Keyboard::Num2] = "2";	mKeycodeToNameShifted[sf::Keyboard::Num2] = "@";
	mKeycodeToName[sf::Keyboard::Num3] = "3";	mKeycodeToNameShifted[sf::Keyboard::Num3] = "#";
	mKeycodeToName[sf::Keyboard::Num4] = "4";	mKeycodeToNameShifted[sf::Keyboard::Num4] = "$";
	mKeycodeToName[sf::Keyboard::Num5] = "5";	mKeycodeToNameShifted[sf::Keyboard::Num5] = "%";
	mKeycodeToName[sf::Keyboard::Num6] = "6";	mKeycodeToNameShifted[sf::Keyboard::Num6] = "^";
	mKeycodeToName[sf::Keyboard::Num7] = "7";	mKeycodeToNameShifted[sf::Keyboard::Num7] = "&";
	mKeycodeToName[sf::Keyboard::Num8] = "8";	mKeycodeToNameShifted[sf::Keyboard::Num8] = "*";
	mKeycodeToName[sf::Keyboard::Num9] = "9";	mKeycodeToNameShifted[sf::Keyboard::Num9] = "(";
	mKeycodeToName[sf::Keyboard::Space] = mKeycodeToNameShifted[sf::Keyboard::Space] = " ";
	mKeycodeToName[sf::Keyboard::LBracket] = "[";	mKeycodeToNameShifted[sf::Keyboard::LBracket] = "{";
	mKeycodeToName[sf::Keyboard::RBracket] = "]";	mKeycodeToNameShifted[sf::Keyboard::RBracket] = "}";
	mKeycodeToName[sf::Keyboard::Backslash] = "\\";	mKeycodeToNameShifted[sf::Keyboard::Backslash] = "|";
	mKeycodeToName[sf::Keyboard::Semicolon] = ";";	mKeycodeToNameShifted[sf::Keyboard::Semicolon] = ":";
	mKeycodeToName[sf::Keyboard::Quote] = "'";		mKeycodeToNameShifted[sf::Keyboard::Quote] = "\"";
	mKeycodeToName[sf::Keyboard::Comma] = ",";		mKeycodeToNameShifted[sf::Keyboard::Comma] = "<";
	mKeycodeToName[sf::Keyboard::Period] = ".";		mKeycodeToNameShifted[sf::Keyboard::Period] = ">";
	mKeycodeToName[sf::Keyboard::Slash] = "/";		mKeycodeToNameShifted[sf::Keyboard::Slash] = "?";
	mKeycodeToName[sf::Keyboard::Grave] = "`";		mKeycodeToNameShifted[sf::Keyboard::Grave] = "~";

	mFColors[sf::Keyboard::F1] = sf::Color(255u, 0u, 0u, 255u);
	mFColors[sf::Keyboard::F2] = sf::Color(0u, 128u, 0u, 255u);
	mFColors[sf::Keyboard::F3] = sf::Color(0u, 0u, 255u, 255u);
	mFColors[sf::Keyboard::F4] = sf::Color(128u, 128u, 0u, 255u);
	mFColors[sf::Keyboard::F5] = sf::Color(255u, 0u, 255u, 255u);
	mFColors[sf::Keyboard::F6] = sf::Color(0u, 128u, 128u, 255u);
}

bool misc::GraphCreator::handle_left_click(const sf::Vector2f& mpos)
{
	if (mCurrentState == State::WAITING)
	{
		int index = find_circle(mpos);
		if (index == -1)
		{
			change_state(State::CREATING);
			//mPendingCircle.set_circle_color(sf::Color::Red);
			mPendingCircle.set_string("???");
			mPendingCircle.set_position(mpos);
		}
		else
		{
			mSelectedCircle = index;
			mCircleData[mSelectedCircle].set_highlight(sf::TextCircleHighlightMode::WHITE);
			change_state(State::FIRST_EDGE);
		}
	}
	else if (mCurrentState == State::FIRST_EDGE)
	{
		int other_circle = find_circle(mpos);
		if (other_circle != -1 && other_circle != mSelectedCircle)
		{
			sf::Vector2f a, b;
			a = mCircleData[mSelectedCircle].get_position();
			b = mCircleData[other_circle].get_position();
			float distance = sqrtf(powf(a.x - b.x, 2.0f) + powf(a.y - b.y, 2.0f));
			mInternalGraph.set_edge(mSelectedCircle, other_circle, distance);

			mCircleData[mSelectedCircle].set_highlight(sf::TextCircleHighlightMode::NONE);
		}
		change_state(State::WAITING);
	}
	else if (mCurrentState == State::CREATING)
	{
		mInternalGraph.add_node(mNextCircleId);
		mCircleData[mNextCircleId++] = mPendingCircle;
		change_state(State::WAITING);
	}

	return false;
}


bool misc::GraphCreator::handle_right_click(const sf::Vector2f& mpos)
{
	if (mCurrentState == State::CREATING)
		change_state(State::WAITING);
	if (mCurrentState == State::WAITING)
	{
		int index = find_circle(mpos);
		if (index >= 0)
		{
			mCircleData.remove(index);
			mInternalGraph.remove_node(index);
		}
	}
	else if (mCurrentState == State::FIRST_EDGE)
	{
		int index = find_circle(mpos);
		if (index >= 0)
			mInternalGraph.remove_edge(mSelectedCircle, index);
		change_state(State::WAITING);
	}

	return false;
}


bool misc::GraphCreator::handle_key_press(const sf::Keyboard::Key& code, bool shift)
{
	if (mCurrentState == State::CREATING)
	{
		// Modify text of the circle
		std::string temp = mPendingCircle.get_string();
		ssuds::UnorderedMap< sf::Keyboard::Key, sf::Color>::UnorderedMapIterator fit = mFColors.find(code);
		if (fit != mFColors.end())
		{
			mPendingCircle.set_circle_color((*fit).second);
		}
		else if (code == sf::Keyboard::BackSpace)
		{
			if (temp.length() > 0)
				temp = temp.substr(0, temp.length() - 1);
			if (temp.length() == 0)
				temp = "???";
			mPendingCircle.set_string(temp);
		}
		else if (shift)
		{
			ssuds::UnorderedMap<sf::Keyboard::Key, std::string>::UnorderedMapIterator it = mKeycodeToNameShifted.find(code);
			if (it != mKeycodeToNameShifted.end())
			{
				if (temp == "???")
					temp = "";
				mPendingCircle.set_string(temp + (*it).second);
			}
		}
		else
		{
			ssuds::UnorderedMap<sf::Keyboard::Key, std::string>::UnorderedMapIterator it = mKeycodeToName.find(code);
			if (it != mKeycodeToName.end())
			{
				if (temp == "???")
					temp = "";
				mPendingCircle.set_string(temp + (*it).second);
			}
		}
	}
	else if (mCurrentState == State::WAITING)
	{
		if (code == sf::Keyboard::F10)
			save();
		else if (code == sf::Keyboard::F11)
			load();
		else if (code == sf::Keyboard::F9)
			clear();
	}

	return false;
}

bool misc::GraphCreator::handle_event(const sf::Event& evt)
{
	if (evt.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f mouse_pos((float)evt.mouseButton.x, (float)evt.mouseButton.y);
		if (evt.mouseButton.button == sf::Mouse::Left)
			return handle_left_click(mouse_pos);
		else if (evt.mouseButton.button == sf::Mouse::Right)
			return handle_right_click(mouse_pos);
	}
	else if (evt.type == sf::Event::KeyPressed)
	{
		if (evt.key.code == sf::Keyboard::Escape)
			return true;

		return handle_key_press(evt.key.code, evt.key.shift);
	}
	else if (evt.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mouse_pos((float)evt.mouseMove.x, (float)evt.mouseMove.y);
		if (mCurrentState == State::CREATING)
			mPendingCircle.set_position(mouse_pos);
	}

	return false;
}

void misc::GraphCreator::draw(sf::RenderWindow& rw)
{
	// Draw status text
	rw.draw(mStatusText);

	// Draw edges
	sf::VertexArray lines(sf::LinesStrip, 2);
	ssuds::UnorderedMap<int, ssuds::UnorderedMap<int, float>>::UnorderedMapIterator outer_it = mInternalGraph.begin();
	while (outer_it != mInternalGraph.end())
	{
		ssuds::UnorderedMap<int, float>::UnorderedMapIterator inner_it = (*outer_it).second.begin();
		while (inner_it != (*outer_it).second.end())
		{
			std::pair<int, float> p = *inner_it;

			// See if this is a bi-directional edge or not
			bool bidirectional = false;
			ssuds::UnorderedMap<int, ssuds::UnorderedMap<int, float>>::UnorderedMapIterator test_it = mInternalGraph.find(p.first);
			if (test_it != mInternalGraph.end())
			{
				ssuds::UnorderedMap<int, float>::UnorderedMapIterator test_it2 = (*test_it).second.find((*outer_it).first);
				if (test_it2 != (*test_it).second.end())
					bidirectional = true;
			}
			if (bidirectional)
			{
				lines[0].color = lines[1].color = sf::Color::White;

			}
			else
			{
				lines[0].color = sf::Color(0u, 0u, 255u, 255u);
				lines[1].color = sf::Color::White;
			}
			lines[0].position = mCircleData[(*outer_it).first].get_position();
			lines[1].position = mCircleData[p.first].get_position();
			rw.draw(lines);
			++inner_it;
		}
		++outer_it;
	}

	// Draw nodes
	ssuds::UnorderedMap<int, sf::TextCircle>::UnorderedMapIterator it = mCircleData.begin();
	while (it != mCircleData.end())
	{
		std::pair<int, sf::TextCircle> p = *it;
		rw.draw(p.second);
		++it;
	}

	// Draw the temporary circle we use as creating a new graph node
	if (mCurrentState == State::CREATING)
		rw.draw(mPendingCircle);
}


void misc::GraphCreator::save()
{
	std::ofstream fp(mDataFname);

	// Write out the nodes
	ssuds::UnorderedMap<int, sf::TextCircle>::UnorderedMapIterator nit = mCircleData.begin();
	while (nit != mCircleData.end())
	{
		sf::TextCircle tc = (*nit).second;
		sf::Vector2f cpos = tc.get_position();
		sf::Color ccol = tc.get_color();
		std::string cstr = tc.get_string();
		fp << "n:" << (*nit).first << ":" << cstr << ":";
		fp << (unsigned int)ccol.r << ":" << (unsigned int)ccol.g << ":" << (unsigned int)ccol.b;
		fp << ":" << cpos.x << ":" << cpos.y << "\n";
		++nit;
	}

	ssuds::UnorderedMap<int, ssuds::UnorderedMap<int, float>>::UnorderedMapIterator it = mInternalGraph.begin();
	while (it != mInternalGraph.end())
	{
		ssuds::UnorderedMap<int, float>::UnorderedMapIterator inner_it = (*it).second.begin();
		int i1 = (*it).first;
		while (inner_it != (*it).second.end())
		{
			int i2 = (*inner_it).first;
			float d = (*inner_it).second;
			fp << "e:" << i1 << ":" << i2 << ":" << d << "\n";
			++inner_it;
		}
		++it;
	}
}

void misc::GraphCreator::load()
{
	// Clear out any existing data
	mInternalGraph.clear();
	mCircleData.clear();
	mNextCircleId = 0;

	std::ifstream fp(mDataFname);
	if (fp.is_open())
	{
		while (true)
		{
			std::string datatype;
			std::getline(fp, datatype, ':');
			if (fp.eof())
				break;
			if (datatype == "n")
			{
				// Format=>     n:id:name:red:green:blue:x:y
				int red, green, blue;
				float x, y;
				int id;
				std::string name;
				fp >> id;
				std::getline(fp, name, ':');		// Consumes the ':'
				std::getline(fp, name, ':');
				fp >> red;
				fp.ignore(1);
				fp >> green;
				fp.ignore(1);
				fp >> blue;
				fp.ignore(1);
				fp >> x;
				fp.ignore(1);
				fp >> y;
				fp.ignore(1);
				mCircleData[id] = sf::TextCircle(x, y, mCircleFont, name);
				mCircleData[id].set_circle_color(sf::Color((sf::Uint8)red, (sf::Uint8)green, (sf::Uint8)blue));
				mInternalGraph.add_node(id);
				if (id >= mNextCircleId)
					mNextCircleId = id + 1;
			}
			else if (datatype == "e")
			{
				// Format=>     e:id_start:id_end:edge_value
				float d;
				int id_start, id_end;
				fp >> id_start;
				fp.ignore(1);
				fp >> id_end;
				fp.ignore(1);
				fp >> d;
				fp.ignore(1);
				if (mInternalGraph.contains_node(id_start) && mInternalGraph.contains_node(id_end))
					mInternalGraph.set_edge(id_start, id_end, d);
			}
		}
	}
}

void misc::GraphCreator::clear()
{
	change_state(State::WAITING);
	mInternalGraph.clear();
	mCircleData.clear();
	mNextCircleId = 0;
}

	
void misc::GraphCreator::change_state(const State& new_state)
{
	if (new_state == mCurrentState)
		return;

	mCurrentState = new_state;
	if (new_state == State::CREATING)
		mStatusText.setString("Type F1-F6:color LC:place RClick:abandon");
	else if (new_state == State::WAITING)
		mStatusText.setString("LC:select/create RC:delete-node F9:clear F10:save F11:load");
	else if (new_state == State::FIRST_EDGE)
		mStatusText.setString("LClick Node: make edge     RClick Node: delete edge");
}

int misc::GraphCreator::find_circle(const sf::Vector2f& pos)
{
	ssuds::UnorderedMap<int, sf::TextCircle>::UnorderedMapIterator it = mCircleData.begin();
	while (it != mCircleData.end())
	{
		std::pair<int, sf::TextCircle> p = *it;
		if (p.second.point_inside(pos))
			return p.first;
		++it;
	}

	return -1;
}