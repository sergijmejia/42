#Imprime las direcciones MAC 

ip link show | awk '/ether/ {print $2}'
