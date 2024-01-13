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
	};
}