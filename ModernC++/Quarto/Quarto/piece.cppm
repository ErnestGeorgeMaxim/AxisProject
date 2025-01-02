export module piece;

import <iostream>;
import <cstdint>;

namespace quarto
{
	export class Piece
	{
	public:

		enum class Colour : uint8_t
		{
			Dark,
			Light
		};
		enum class Body : uint8_t
		{
			Full,

		};
		enum class Shape : uint8_t
		{
			Round,
			Square
		};
		enum class Height : uint8_t
		{
			Short,
			Tall
		};

	private:
		Colour m_colour : 1;
		Body   m_body   : 1;
		Shape  m_shape  : 1;
		Height m_height : 1;
	};
}