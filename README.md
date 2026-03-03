Universidad Central de Venezuela. Facultad de Ciencias.
Escuela de Computación. Matemáticas Discretas III (Cód.6108)
Tarea 1
Un mensajero astral necesita entregar fragmentos estelares en distintos santuarios de la ciudad, siguiendo un orden específico. Cada sendero de luz tiene un tiempo asociado, que es lo que se tarda en recorrer dicho tramo. Además, cada sendero tiene una estabilidad mágica máxima que se debe respetar para poder transitarlo con la carga. Se desea que planifique la ruta de menor tiempo para poder entregar todos los fragmentos en el orden suministrado, respetando siempre la estabilidad máxima de cada sendero por el que se vaya a circular.
Entrada
● Se recibirá una cantidad no determinada de pares de enteros S K separados por un espacio que representan el santuario de entrega S y el peso mágico en unidades K del fragmento que se dejará en dicho punto.
● El orden en que se visitarán los santuarios es el mismo orden con que se reciben en este paso.
● Posteriormente, se leerá una cantidad no especificada de 4-tuplas de enteros separados por espacios A B T M, que indica la existencia de un sendero que une los santuarios A con B, requiere un tiempo T recorrerlo y M es la estabilidad máxima (peso permitido) del tramo en cuestión.
● Finalmente, se recibirá un entero I que indica que el mensajero partirá desde el santuario I de la ciudad.
Salida
● Se escribirá una línea con todo el camino recorrido por el mensajero en forma de una lista de enteros (ID de santuarios) separados por espacios.
● Luego de esto, se escribirá una línea con un único entero que representa el tiempo total del viaje, desde el punto de partida hasta el último santuario de entrega.
EjemploEntrada
Salida
1 2
4 4
2 10
3 4
1 2 3 18
1 4 8 25
1 3 3 10
2 3 5 10
2 4 4 20
3 4 2 18
1
1 2 4 2 3
16
Consideraciones:
● La solución requiere la implementación del algoritmo de Dijkstra de acuerdo a lo visto en clases.
● Los senderos de luz pueden ser recorridos en ambos sentidos.
● Independientemente de dónde comience el mensajero y de los puntos por donde pase, solo se puede entregar un fragmento en el orden exacto especificado.
● El peso del mensajero es despreciable y no será considerado para transitar los senderos. Solo se debe considerar el peso de la carga mágica que transporta en ese momento.
● Debe respetar el formato de entrada/salida especificado. De no ser así, se aplicará una penalización a juicio del evaluador.
● El código debe tomar los datos por entrada estándar y escribir el resultado por salida estándar.
● Lenguajes permitidos: C/C++ y Python 3
● La tarea debe ser enviada al correo del preparador a lo sumo el domingo 8 de marzo de 2026 a las 11:59 p.m.
● Cualquier duda puede ser planteada directamente al preparador a través del correo, mensajería privada o en el grupo de Telegram.
● Se debe entregar un único archivo con el código se su solución cuyo nombre debe respetar el siguiente formato: Apellido_Nombre.ext donde ext puede ser py, c o cpp.
● La tarea es de carácter individual.
● Las copias serán severamente penalizadas según lo establecido en la Ley de Universidades.
● Se anima a la discusión pero se prohíbe la copia de proyectos. Cualquier proyecto entregado debe ser fruto de su propio trabajo.
GDMDIII/II-2025