/*
** EPITECH PROJECT, 2019
** server
** File description:
** INetwork
*/

#pragma once

class INetwork {
	public:
		virtual ~INetwork() {};
        virtual void start() = 0;
};
