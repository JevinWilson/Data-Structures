#pragma once
#include <array_list.h>
#include <text_circle.h>
#include <iostream>
#include <unordered_map.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <graph.h>
#include <fstream>
#include <string>

namespace misc
{
	/// <summary>
	/// A class to create and manage my simple visual graph
	/// </summary>
	class GraphCreator
	{
	protected:
		/// <summary>
		/// The font object to be used within the circles
		/// </summary>
		sf::Font mCircleFont;

		/// <summary>
		/// The font object to be used for status messages
		/// </summary>
		sf::Font mStatusFont;

		/// <summary>
		/// The Text object to be used to display status text
		/// </summary>
		sf::Text mStatusText;

		/// <summary>
		/// Different states the manager can be in
		/// </summary>
		enum class State { WAITING, FIRST_EDGE, CREATING, NONE };

		/// <summary>
		/// The current state the system is in
		/// </summary>
		State mCurrentState;

		/// <summary>
		/// If we're in the process of creating a circle/node, this is it
		/// </summary>
		sf::TextCircle mPendingCircle;

		/// <summary>
		/// The "ID#" of the next circle (will be used as keys in mCircleData and the Nodes in mInternalGraph
		/// </summary>
		int mNextCircleId;

		/// <summary>
		/// The Graph used to track connections between the nodes.  The Nodes are integers which correspond to
		/// an entry in mCircleData
		/// </summary>
		ssuds::Graph<int, float> mInternalGraph;

		/// <summary>
		/// Instead of storing the Node data in mInternalGraph, I chose to store it here, indexed by id# (this
		/// was mostly because I didn't want to create a hash function for text circle)
		/// </summary>
		ssuds::UnorderedMap<int, sf::TextCircle> mCircleData;

		/// <summary>
		/// If we're creating an edge between two nodes, this is the id of the first one
		/// </summary>
		int mSelectedCircle;

		// We haven't really used the following construct, but...when you declare a class attribute static, it is 
		// associated with the class, not an instance.  But...you have to declared it as a global somewhere.
		// My declaration is in graph_creator.cpp

		/// <summary>
		/// A mapping between SFML keycodes and names (ex. "a", "b", "1", etc.)
		/// </summary>
		static ssuds::UnorderedMap<sf::Keyboard::Key, std::string> mKeycodeToName;

		/// <summary>
		/// A mapping like mKeycodeToName, but the ones to use when shift is held (ex. "A", "B", "!", etc.)
		/// </summary>
		static ssuds::UnorderedMap<sf::Keyboard::Key, std::string> mKeycodeToNameShifted;

		/// <summary>
		/// A few F1 keys that are mapped to color values
		/// </summary>
		static ssuds::UnorderedMap<sf::Keyboard::Key, sf::Color> mFColors;

		// A new C++ technique I just found: you can define static const's inline with the constexpr keyword
		static constexpr const char* mDataFname = "../../../media/output.txt";

	public:
		/// <summary>
		/// Main constructor
		/// </summary>
		/// <param name="circle_font">the font to be used withing node circles</param>
		/// <param name="status_font">the font to be used for status text</param>
		GraphCreator(const sf::Font& circle_font, const sf::Font& status_font);

		/// <summary>
		/// A method to initialize all the internal map "databases" (Note how this is called from main)
		/// </summary>
		static void create_keycode_to_name_dbase();

		/// <summary>
		/// A method to draw all things (the graph, the status text, etc.)
		/// </summary>
		/// <param name="Vector2f"></param>
		void draw(sf::RenderWindow& rw);

		/// <summary>
		/// Saves the current map to mDataFname
		/// </summary>
		void save();

		/// <summary>
		/// Replaces the current graph with that loaded from mDataFname
		/// </summary>
		/// <param name="mpos"></param>
		/// <returns></returns>
		void load();

		/// <summary>
		/// Clears the current graph
		/// </summary>
		void clear();

		/// <summary>
		/// Method to process an SFML event, fed to us from the main loop
		/// </summary>
		bool handle_event(const sf::Event& evt);

	protected:
		/// <summary>
		/// Internal method to handle left click events
		/// </summary>
		bool handle_left_click(const sf::Vector2f& mpos);

		/// <summary>
		/// Internal method to handle right click events
		/// </summary>
		bool handle_right_click(const sf::Vector2f& mpos);

		/// <summary>
		/// Internal method to handle key presses
		/// </summary>
		bool handle_key_press(const sf::Keyboard::Key& code, bool shift);


		/// <summary>
		/// Internal method to change the current state (and update the status text)
		/// </summary>
		void change_state(const State& new_state);

		/// <summary>
		/// Internal method to find the ID# of the first circle that contains the given position
		/// </summary>
		int find_circle(const sf::Vector2f& pos);
	};
}
