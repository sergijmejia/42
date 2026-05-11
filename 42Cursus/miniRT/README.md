*This project has been created as part of the 42 curriculum by rafaguti.*

## Description

**miniRT** is a minimal ray tracer written in C. It parses scene descriptions (`.rt` files), intersects rays with geometric primitives (sphere, plane, finite cylinder; cone and extensions in the bonus build), and shades hits using ambient light, diffuse lighting, and hard shadows. The image is rendered with the MiniLibX library into a fixed-size framebuffer and displayed in a window.

The goal is to implement the core ideas of ray tracing—vectors, intersections, lighting—in a small, norm-compliant codebase suitable for peer evaluation at 42.

## Instructions

### Prerequisites

- A C compiler (`cc`) and `make`
- X11 development libraries (Linux)
- MiniLibX placed in a `minilibx` directory at the project root (as expected by the Makefile), built via its own Makefile
- **libft** in `libft/`, built via its Makefile

### Compilation

From the project root:

```bash
make          # mandatory part
make bonus    # mandatory + bonus (Phong specular, checker planes, multi/colored lights, cone)
```

The executable is **`miniRT`**.

### Execution

```bash
./miniRT path/to/scene.rt
```

Example:

```bash
./miniRT scenes/02_all_primitives.rt
```

Press **ESC** or close the window (**red cross**) to quit cleanly.

### Bonus scenes (after `make bonus`)

Examples that showcase bonus features include `scenes/bonus_demo.rt`, `bonus_checker_floor.rt`, `bonus_multilight_rgb.rt`, `bonus_cone_spotlight.rt`, and `bonus_all_features.rt`. For a heavier “showcase” scene (many objects, checker floor, multi lights, cones), see `scenes/showcase_greek_temple_bonus.rt`.

### Showcase (mandatory)

`scenes/showcase_greek_temple_mandatory.rt` is a dense Greek-temple style portico (columns, entablature, tympanum) using only mandatory primitives; build with `make` (not `make bonus`).

## Resources

- **Ray tracing basics:** Peter Shirley, *Ray Tracing in One Weekend* (series).
- **Linear algebra for graphics:** essential vector operations (dot/cross, normalization).
- **42 MiniLibX:** official documentation and man pages shipped with the library.
- **Phong reflection model:** common computer graphics references (ambient + diffuse + specular).
