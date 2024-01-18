namespace ssuds
{
	class ArrayList
	{
	protected:
		std::string* mData;		// Holds the current DYNAMIC ARRAY of strings
		unsigned int mSize;
	public:
		ArrayList();
		~ArrayList();     // Destructor
		void append(std::string s);
		unsigned int size();
		// ... and the rest of the methods

		void ArrayList::append(std::string value);
		unsigned int ArrayList::size();
		void ArrayList::insert(std:: string value, unsigned int index);
		void ArrayList::clear();
		std::string ArrayList::get(unsigned int index);
		int ArrayList::find(std::string value, int startIndex);
		void ArrayList::remove(unsigned int index);
		int ArrayList::remove_all(std::string value);
	};
}