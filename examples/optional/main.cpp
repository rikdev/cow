#include <cow/optional.h>
#include <iostream>
#include <string>
#include <utility>

class tracker {
public:
	explicit tracker(std::string name)
		: name_{std::move(name)}
	{
		out("constructor");
	}

	~tracker()
	{
		out("destructor");
	}

	tracker(const tracker& other)
		: name_{other.name_}
	{
		out("copy constructor");
	}

	tracker(tracker&& other)
		: name_{std::move(other.name_)}
	{
		other.name_ = std::string{};
		out("move constructor");
	}

	tracker& operator=(const tracker& other)
	{
		out("copy assignment");
		name_ = other.name_;

		return *this;
	}

	tracker& operator=(tracker&& other)
	{
		out("move assignment");
		name_ = std::move(other.name_);
		other.name_ = std::string{};

		return *this;
	}

	const std::string& get_name() const noexcept
	{
		return name_;
	}

private:
	void out(const char* const text)
	{
		std::cout << "tracker " << name_ << ": " << text << '\n';
	}

	std::string name_;
};

int main()
{
	std::cout << "Step 1\n";
	cow::optional<tracker> v1{cow::in_place, "t1"};
	std::cout << "v1 name: " << v1->get_name() << '\n';

	std::cout << "\nStep 2\n";
	cow::optional<tracker> v2 = v1;
	std::cout << "v1 name: " << v1->get_name() << '\n';
	std::cout << "v2 name: " << v2->get_name() << '\n';

	std::cout << "\nStep 3\n";
	v1 = tracker{"t2"};
	std::cout << "v1 name: " << v1->get_name() << '\n';
	std::cout << "v2 name: " << v2->get_name() << '\n';

	std::cout << "\nStep 4\n";
}
