//
// Created by Nelson Amerei on 10/24/21.
//

namespace ft
{
	class Test {
	private:
		int _number;

	public:
		explicit Test(int name) {
			_number = name;
		}

		int getName() const
		{
			return _number;
		}
	};
}

#ifndef FT_CONTAINERS_TEST_HPP
#define FT_CONTAINERS_TEST_HPP

#endif //FT_CONTAINERS_TEST_HPP
