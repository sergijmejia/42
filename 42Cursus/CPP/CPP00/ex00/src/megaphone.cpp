/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:37:03 by smejia-a          #+#    #+#             */
/*   Updated: 2026/06/05 17:38:05 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int	main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return (0);
    }
    for (size_t i = 1; i < (size_t) argc; i++) {
        std::string caps = argv[i];
        for (size_t j = 0; j < caps.length(); j++)
            caps[j] = std::toupper(caps[j]);
        std::cout << caps;
    }
    std::cout << std::endl;
    return (0);
}
