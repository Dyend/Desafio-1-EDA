# Desafio-1-EDA

# Instrucciones

Para windows con vscode:
- primero se debe clonar el respositorio con el siguiente comando en consola: git clone https://github.com/Dyend/Desafio-1-EDA.git
- abrir vscode y abrir el poryecto clonado en este.
- pedira que se instale la extensión de c++, hacerlo ya que esto permitira llamar al compilador dentro de vscode. (asumiendo que se tiene instalado un compilador de c++ en el sistema).
- luego para configurar el compilador se debe ir a "Terminal" -> "Configure Default Build Task" y seleccionar el compilador que tenga en su sistema.
- finalmente seleccionar el archivo main.cpp en el vscode, tener el archivo abierto y apretar f5 para que este compile y se ejecute el programa. (si tiene algún problema por favor verificar task.json y el launch.json)

# Descripción del Problema

El problema seleccionado por nuestro grupo correponde al Sudoku, cuyo objetivo es rellenar una cuadrícula de 9 × 9 celdas (81 casillas) dividida en subcuadrículas de 3 × 3 (también llamadas "cajas" o "regiones") con las cifras del 1 al 9 partiendo de algunos números ya dispuestos en algunas de las celdas. Lo importante es que no se debe repetir ningún número, del 1 al 9, en ninguna fila, columna o subsecciones de 3x3 dentro de la matriz de 9 x 9. Se considera resuelto cuando se encuentran las 81 casillas con algun numero del 1 al 9 y que se cumplan las condiciones planteadas al comienzo.

# Solución al problema

Para abarcar este problema decidimos utilizar el "Depth First Search", con una pequeña modificación (ordenar por prioridad) y el Best First Search, los cuales serán puestos a prueba y se verá que tan eficientes pueden ser a la hora de intentar resolver un sudoku, en diferentes niveles de dificultad. Para la resolucion del problema definimos un estado como una matriz llenada con los numeros del sudoku, siendo los guiones bajo representando los espacios vacios. 

En el algoritmo DFS se parte de un estado inicial y se buscan todos los estados hijos que pueden ser generados a partir de este. Los estados hijos son todas las posibilidades de poner numeros en los casilleros vacios, siempre y cuando sean validos, es decir que no esten repetidos en la region, columna y fila. Los estados hijos en el DFS antes de ser ingresados a la estructura de datos STACK (que es usada para este tipo de búsqueda), son priorizados considerando en conjunto cuantos casilleros vacios queden en la fila, columna y region, siendo más prioritario un estado hijo que tenga menos espacios vacios en estos tres espacios mencionados.
Es decir, en el algoritmo DFS siempre ira en profundidad por el estado hijo mas posible o con mayor prioridad y de no encontrar mas estados hijos o que no se tenga un estado final, se devolera al estado padre y posteriormente a los otros hijos.

Por otro lado, para el algoritmo BFS se ocupa la estructura de datos "priority queue", la cual se va reordenando y recorriendo con el estado con mas prioridad. Esta prioridad es similar a la ocupada en el DFS, solamente que aquí se acumula considerando la prioridad del estado padre y en vez de ir por profundidad, salta siempre al estado que tenga mayor prioridad. Siempre que se considere un estado, se generan los hijos con prioridad y son ingresados a la Priority Queue.

- Seleccionar sodoku desde: https://www.sudoku-online.org/

