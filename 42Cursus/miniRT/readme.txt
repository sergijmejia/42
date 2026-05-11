readme.md

Bonus (make bonus): scenes/bonus_demo.rt, bonus_checker_floor.rt,
bonus_multilight_rgb.rt, bonus_cone_spotlight.rt, bonus_all_features.rt

Showcase "wow": showcase_greek_temple_mandatory.rt (make),
showcase_greek_temple_bonus.rt (make bonus).

Ficheros en scenes
01_basic_sphere.rt: Mínimo: una esfera.
02_all_primitives.rt: Plano + 2 esferas + cilindro (similar a tu escena actual).
03_depth_two_spheres.rt: Dos esferas en el eje de vista: comprobar t más cercano.
04_shadow_occluder.rt: Plano vertical + objetos: sombras y oclusiones.
05_cylinder_diagonal.rt: Cilindro con eje no vertical + intersección con esfera/plano.
06_sphere_on_plane.rt: Esfera apoyada en plano, cámara baja.
07_many_objects.rt: Varios objetos y orden de intersección.

Errores esperados (deben imprimir Error\n y salir ≠ 0):
err_duplicate_A.rt, err_duplicate_C.rt
err_missing_light.rt (falta L)
err_bad_fov.rt (FOV fuera de rango)
err_zero_sphere.rt (diámetro 0)
err_bad_cylinder.rt (eje 0,0,0)
err_color_out_of_range.rt
err_unknown_element.rt (token sph)

Ejemplo:

./miniRT scenes/02_all_primitives.rt