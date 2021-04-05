# Desafio-1-EDA

# Instrucciones

Para windows con vscode:
- primero se debe clonar el respositorio con el siguiente comando en consola: git clone https://github.com/Dyend/Desafio-1-EDA.git
- abrir vscode y abrir el poryecto clonado en este.
- pedira que se instale la extensión de c++, hacerlo ya que esto permitira llamar al compilador dentro de vscode. (asumiendo que se tiene instalado un compilador de c++ en el sistema).
- luego para configurar el compilador se debe ir a "Terminal" -> "Configure Default Build Task" y seleccionar el compilador que tenga en su sistema.
- finalmente seleccionar el archivo main.cpp en el vscode, tener el archivo abierto y apretar f5 para que este compile y se ejecute el programa. (si tiene algún problema por favor verificar task.json y el launch.json)

# Descripción-del-Problema

El problema seleccionado por nuestro grupo correponde al Sudoku, cuyo objetivo es rellenar una cuadrícula de 9 × 9 celdas (81 casillas) dividida en subcuadrículas de 3 × 3 (también llamadas "cajas" o "regiones") con las cifras del 1 al 9 partiendo de algunos números ya dispuestos en algunas de las celdas. Lo importante es que no se debe repetir ningún número, del 1 al 9, en ninguna fila, columna o subsecciones de 3x3 dentro de la matriz de 9 x 9. Se considera resuelto cuando se encuentran las 81 casillas con algun numero del 1 al 9 y que se cumplan las condiciones palnteadas al comienzo (numeros del 1 al 9 sin repetirse tanto, en columnas, filas y casilleros de 3x3)

# Solución al problema

Para abarcar este problema decidimos utilizar el "Depth First Search", con una pequeña modificación (ordenar por prioridad) y el Best First Search, los cuales serán puestos a prueba y se verá que tan eficientes pueden ser a la hora de intentar resolver un sudoku, en diferentes niveles de dificultad.


# Coevaluación

|Criterio                 | Jose Luis Alonso | Juan Pablo Raab | Jonathan Reyes | Diego Acosta |
|-------------------------|------------------|-----------------|----------------|--------------|
|Asistencia y puntualidad |Asiste con puntualidad a todas las reuniones                  |Asiste con puntualidad a todas las reuniones                  |Asiste con puntualidad a todas las reuniones                 |Asiste con puntualidad a todas las reuniones               |
|Integración              |Se integra bien en el grupo, buena comunicación                  |Se integra bien en el grupo, buena comunicación                  |Se integra bien en el grupo, buena comunicación                 | Se integra bien en el grupo, buena comunicación              |Se integra bien en el grupo, buena comunicación 
|Responsabilidad          | Cumple con todas las tareas que se le asignan                 | Cumple con todas las tareas que se le asignan                  | Cumple con todas las tareas que se le asignan                 | Cumple con todas las tareas que se le asignan               |
|Contribución             | Aporta buenas ideas para lograr la solución del problema                 | Aporta buenas ideas para lograr la solución del problema                 |  Aporta buenas ideas para lograr la solución del problema               | Aporta buenas ideas para lograr la solución del problema              |
|Resolución de conflictos | Acepta ideas de otros y a la vez aporta las propias. 0 conflictos                 | Acepta ideas de otros y a la vez aporta las propias. 0 conflictos                 | Acepta ideas de otros y a la vez aporta las propias. 0 conflictos                | Acepta ideas de otros y a la vez aporta las propias. 0 conflictos              |


- Seleccionar sodoku desde: https://www.sudoku-online.org/
- Link al video: https://drive.google.com/file/d/1ZEuAsBY0VOLxk_di_aFcyyZlnIvOiAgk/view?usp=sharing