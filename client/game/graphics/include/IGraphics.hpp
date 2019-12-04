/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP_
#define IGRAPHICS_HPP_

#include <vector>

class IGraphics {
	public:
		virtual ~IGraphics(){};
        virtual void setPosition(float x, float y) = 0;
        virtual std::vector<float> getPosition() const = 0;
};

#endif /* !IGRAPHICS_HPP_ */
