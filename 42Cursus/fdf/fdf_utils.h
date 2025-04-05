/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:09:26 by smejia-a          #+#    #+#             */
/*   Updated: 2025/04/05 12:27:44 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Utils*/
float			ft_max_float(float *cord, int len);
float			ft_min_float(float *cord, int len);
char			*ft_clean_split(char **str);
t_pixel_data	*copy_map(t_pixel_data *map_points, int len);
void			ft_error(t_image_data *image);
void			end_image(t_image_data *image);
void			set_first_min_max(t_image_data *image, char *line);
void			color_hexa(t_image_data *image, char *color, int i);
int				hexa_to_int(char *s, int len);
