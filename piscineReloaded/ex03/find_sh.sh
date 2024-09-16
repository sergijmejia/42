#funcion para mostrar los nombres de archivos ".sh" sin mostrar el ".sh"

find . -name '*.sh' -exec basename {} \; | sed 's/\.sh$//'
