/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pharse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:46:27 by smejia-a          #+#    #+#             */
/*   Updated: 2026/01/13 18:46:34 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_type {
    SPHERE,
    PLANE,
    CYLINDER,
    CONE
} t_type;

typedef struct s_vector
{
    double  x;
    double  y;
    double  z;
}   t_vector;

typedef struct s_ambient
{
    double      light_ratio;
    t_vector    color;
}

typedef struct s_camera
{
    double      fov;
    t_vector    pos;
    t_vector    normal;
}

typedef struct s_light
{
    double          bright;
    t_vector        pos;
    t_vector        color;
    struct s_light  *next;
}   t_light;

typedef struct s_object
{
    t_type          type;      // ¿Qué soy? (SP, PL, CY)
    double          diameter;
    double          height;
    t_vector        reference;     //Punto de referencia del type
    t_vector        normal;
    t_vector        color;     // Color (común a todos)
    struct s_object *next;     // Puntero al siguiente objeto
}   t_object;

typedef struct s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     *light;
    t_object    *objects;
}   t_scene;

/* Function to create a new object */
t_object *create_object(int type)
{
    t_object *new_object;

    new_object = (t_object *)ft_calloc(1, sizeof(t_object));
    if (!new_object)
        return (NULL);
    new_object->type = type;
    new_object->next = NULL;
    return (new_object);
}

/* Function to free **char (usually created with a ft_split function) */
static char	**free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

/* Function to load x, y, z components in the vector reference */
static int  data_to_vector(char *data, t_vector *reference)
{
    char    **values;
    int     i;

    i = 0;
    if (!ft_isdigit(data[i]) && !ft_strcontains("+-,.", data[i]))
        return (0);
    while (data[i + 1] != '\0')
    {
        if (data[i] == ',' && data[i + 1] == ',')
            return (0);
        if (!ft_isdigit(data[i + 1]) && !ft_strcontains("+-,.", data[i + 1]))
            return (0);
        i++;
    }
    if (ft_countwords(data, ',') != 3)
        return (0);
    values = ft_split(data, ',');
    if (!values)
        return (0);
    reference->x = ft_atod(values[0]);
    reference->y = ft_atod(values[1]);
    reference->z = ft_atod(values[2]);
    free_split(values);
    return (1);
}

/* Parsing of an object sphere */
int parse_sphere(char *line, t_object *sphere)
{
    char        **data;

    data = ft_split(line, ' ');
    if (!data)
        return (0);
    sphere = create_object(SPHERE);
    if (sphere == NULL)
    {
        free_split(data);
        return (0);
    }
    sphere->diameter = ft_atod(data[2]); //se debe crear la funcio atod para pasar alphabetic to double. Si falla devuelve 0
    if (sphere->diameter <= 0 ||
        data_to_vector(data[1], &(sphere->reference)) == 0 || //se debe crear el data_to_vector que almacena coordenadas xyz en una variable vector. Devuelve un 0 si falla
        data_to_vector(data[3], &(sphere->color)) == 0)
    {
        free(sphere);
        free_split(data);
        return (0);
    }
    free_split(data);
    return (1);
}

int parse_plane(char *line, t_object *plane)
{
    char    **data;

    data = ft_split(line, ' ');
    if (!data)
        return (0);
    plane = create_object(PLANE);
    if (plane == NULL)
    {
        free_split(data);
        return (0);
    }
    if (data_to_vector(data[1], &(plane->reference)) == 0 ||
        data_to_vector(data[2], &(plane->normal)) == 0 ||
        data_to_vector(data[3], &(plane->color)) == 0)
    {
        free(plane);
        free_split(data);
        return (0);
    }
    free_split(data);
    return (1);
}

int parse_cylinder(char *line, t_object *cylinder)
{
    char    **data;

    data = ft_split(line, ' ');
    if (!data)
        return (0);
    cylinder = create_object(CYLINDER);
    if (cylinder == NULL)
    {
        free_split(data);
        return (0);
    }
    cylinder->diameter = ft_atod(data[3]);
    cylinder->height = ft_atod(data[4]);
    if (cylinder->diameter <= 0 || cylinder->height <= 0 ||
        data_to_vector(data[1], &(cylinder->reference)) == 0 ||
        data_to_vector(data[2], &(cylinder->normal)) == 0 ||
        data_to_vector(data[5], &(cylinder->color)) == 0)
    {
        free(cylinder);
        free_split(data);
        return (0);
    }
    free_split(data);
    return (1);
}

int parse_cone(char *line, t_object *cone)
{
    char    **data;

    data = ft_split(line, ' ');
    if (!data)
        return (0);
    cone = create_object(CONE);
    if (cone == NULL)
    {
        free_split(data);
        return (0);
    }
    cylinder->diameter = ft_atod(data[3]);
    cylinder->height = ft_atod(data[4]);
    if (cone->diameter <= 0 || cone->height <= 0 ||
        data_to_vector(data[1], &(cone->reference)) == 0 ||
        data_to_vector(data[2], &(cone->normal)) == 0 ||
        data_to_vector(data[5], &(cone->color)) == 0)
    {
        free(cone);
        free_split(data);
        return (0);
    }
    free_split(data);
    return (1);
}
