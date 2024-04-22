#include <visual_graph.h>
#include <queue.h>


misc::VisualGraph::VisualGraph(const sf::Font& circle_font, const std::string& fname) : mCircleFont(circle_font)
{
	load(fname);
}






void misc::VisualGraph::draw(sf::RenderWindow& rw)
{
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
}



void misc::VisualGraph::load(const std::string& fname)
{
	// Clear out any existing data
	mInternalGraph.clear();
	mCircleData.clear();

	std::ifstream fp(fname);
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

ssuds::ArrayList<int> misc::VisualGraph::handle_mouse_click(const float X, const float Y, bool end) {
	unsigned int node_count;

	if (end)
		node_count = 2;
	else
		node_count = 1;

	for (std::pair<int, sf::TextCircle>& pair : mCircleData) {
		sf::Vector2f node_position = pair.second.get_position();
		float radius = pair.second.get_radius();
		float distance = std::hypot(node_position.x - X, node_position.y - Y);

		if (distance <= radius) {
			int i;

			if (selectedNode.size() > 0)
				i = selectedNode.find(pair.first);
			else
				i = -1;

			if (i != -1)
				selectedNode.remove(i);
			else {
				if (selectedNode.size() < node_count)
					selectedNode.append(pair.first);
			}
			break;
		}
	}

	return selectedNode;
}

void misc::VisualGraph::bfs(ssuds::ArrayList<std::pair<int, int>>& traverseMap) {
	if (selectedNode.size() == 0)
		throw std::out_of_range("Node not found");

	mInternalGraph.breadth(traverseMap, selectedNode[0]);
}

void misc::VisualGraph::dfs(ssuds::ArrayList<std::pair<int, int>>& traverseMap) {
	if (selectedNode.size() == 0)
		throw std::out_of_range("Node not found");

	mInternalGraph.depth(traverseMap, selectedNode[0]);
}

